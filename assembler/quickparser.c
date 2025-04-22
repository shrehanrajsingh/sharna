#include "quickparser.h"

static int
is_register (char *k)
{
  for (int i = 0; REGNAMES[i] != NULL; i++)
    if (!strcmp (REGNAMES[i], k))
      return i;

  return -1;
}

SH_API sh_qp_t
sh_qp_new (void)
{
  sh_qp_t r;
  r.fcont = NULL;
  r.flines = NULL;
  r.fls = 0;
  r.fptr = NULL;
  r.fs = 0;
  r.ps_c = 0;
  r.cgc = 0;
  // r.vt = ...

  return r;
}

SH_API sh_qp_t
sh_qp_new_fromFile (char *f)
{
  sh_qp_t r = sh_qp_new ();
  r.fptr = fopen (f, "r");

  /* get file contents and split into lines */
  size_t fc_cap = 64;
  r.fcont = shmalloc (fc_cap * sizeof (char));

  /**
   * fgetc is designed to return an int
   * if we use char for `c` then there stems
   * an ambiguity between -1 and 255
   */
  int c;

  while ((c = fgetc (r.fptr)) != EOF)
    {
      if (r.fs == fc_cap)
        {
          fc_cap += 64;
          r.fcont = shrealloc (r.fcont, fc_cap * sizeof (char));
        }
      r.fcont[r.fs++] = c;
    }

  if (r.fs == fc_cap)
    {
      fc_cap += 1;
      r.fcont = shrealloc (r.fcont, fc_cap * sizeof (char));
    }

  r.fcont[r.fs++] = '\0';
  char *fc_pres = shstrdup (r.fcont);

  size_t lc = 0;
  for (size_t i = 0; i < r.fs - 1; i++)
    {
      if (r.fcont[i] == '\n')
        {
          lc++;
        }
    }

  if (r.fs > 0 && r.fcont[r.fs - 2] != '\n')
    {
      lc++;
    }

  r.flines = shmalloc (lc * sizeof (char *));
  r.fls = lc;

  char *st = r.fcont;
  size_t li = 0;

  for (size_t i = 0; i < r.fs - 1; i++)
    {
      if (r.fcont[i] == '\n')
        {
          r.fcont[i] = '\0';
          r.flines[li++] = st;
          st = &r.fcont[i + 1];
        }
    }

  if (li < lc)
    {
      r.flines[li] = st;
    }

  r.fcont = fc_pres;
  return r;
}

SH_API void
sh_qp_close (sh_qp_t *q)
{
  fclose (q->fptr);
}

/*
a very bad hashing algorithm.
replace with own if reproducing
*/
static int
hash (char *k)
{
  int r = 0;

  for (size_t i = 0; k[i]; i++)
    r += (k[i] * (i + 1)) >> i;

  //   printf ("%d\n", r);
  return r % QP_VTABLE_SIZE;
}

SH_API void
sh_qp_addtovtable (sh_qp_vtable_t *vt, char *key, size_t val)
{
  vt->val[hash (key)] = val;
}

SH_API int
sh_qp_getfromvtable (sh_qp_vtable_t *vt, char *key)
{
  return vt->val[hash (key)];
}

SH_API void
sh_qp_parse (sh_qp_t *qp)
{
  /* trim left */
  for (size_t i = 0; i < qp->fls; i++)
    {
      _STR_TRIMLEFT (qp->flines[i]);

      size_t sl = strlen (qp->flines[i]);
      while (qp->flines[i][sl - 1] == ' ' || qp->flines[i][sl - 1] == '\t')
        sl--;

      qp->flines[i][sl] = '\0';
      //   printf ("(%s)\n", qp->flines[i]);
    }

  size_t pp_bytecount = 0; /* pre processor byte count */
  /* add labels to memory */
  for (size_t i = 0; i < qp->fls; i++)
    {
      char *line = qp->flines[i];

      if (*line == '\0')
        continue;

      if (line[strlen (line) - 1] == ':')
        {
          sh_qp_addtovtable (&qp->vt, line, pp_bytecount);
          continue;
        }

      for (size_t j = 0; INST_3B[j] != NULL; j++)
        {
          if (_str_startswith_ncs (line, (char *)INST_3B[j]))
            {
              pp_bytecount += 3;
              break;
            }
        }

      for (size_t j = 0; INST_2B[j] != NULL; j++)
        {
          if (_str_startswith_ncs (line, (char *)INST_2B[j]))
            {
              pp_bytecount += 2;
              break;
            }
        }

      for (size_t j = 0; INST_1B[j] != NULL; j++)
        {
          if (_str_startswith_ncs (line, (char *)INST_1B[j]))
            {
              pp_bytecount += 1;
              break;
            }
        }

      if (_str_startswith_ncs (line, "section"))
        {
          line += 7;

          while (*line++ != '.')
            ;

          printf ("found section '%s'\n", line);
          qp->prog_sections[qp->ps_c].name = shstrdup (line);
          qp->prog_sections[qp->ps_c++].bc = pp_bytecount;
        }
    }

  for (size_t i = 0; i < qp->fls; i++)
    {
      char *line = qp->flines[i];

      while (*line == ' ' || *line == '\t')
        line++;

      if (*line == '\0')
        continue;

      if (_str_startswith_ncs (line, "mov"))
        {
          char *arg1, *arg2;

          line += 3;

          while (*line == ' ' || *line == '\t')
            line++;

          int gb = 0;
          size_t j = 0;

          for (j = 0; line[j] != '\0'; j++)
            {
              if (line[j] == ',' && !gb)
                break;

              if (_str_contains ("([", line[j]))
                gb++;

              if (_str_contains (")]", line[j]))
                gb--;
            }

          arg1 = line;
          line[j++] = '\0';
          arg2 = line + j;

          _STR_TRIMLEFT (arg2);
          _STR_TRIMRIGHT (arg1);

          int a1ir = is_register (arg1);

          if (a1ir != -1 && _str_isnumber (arg2)) /* standard mov */
            {
              qp->cg[qp->cgc++] = MOV_rv;
              qp->cg[qp->cgc++] = a1ir;
              qp->cg[qp->cgc++] = atoi (arg2);
            }

          printf ("found mov instruction '%s', '%s'\n", arg1, arg2);
        }

      else if (_str_startswith_ncs (line, "add"))
        {
          char *arg1, *arg2;

          line += 3;

          while (*line == ' ' || *line == '\t')
            line++;

          int gb = 0;
          size_t j = 0;

          for (j = 0; line[j] != '\0'; j++)
            {
              if (line[j] == ',' && !gb)
                break;

              if (_str_contains ("([", line[j]))
                gb++;

              if (_str_contains (")]", line[j]))
                gb--;
            }

          arg1 = line;
          line[j++] = '\0';
          arg2 = line + j;

          _STR_TRIMLEFT (arg2);
          _STR_TRIMRIGHT (arg1);

          int a1ir = is_register (arg1);
          int a2ir;

          if (a1ir != -1) /* standard mov */
            {
              if (_str_isnumber (arg2))
                {
                  qp->cg[qp->cgc++] = ADD_rv;
                  qp->cg[qp->cgc++] = a1ir;
                  qp->cg[qp->cgc++] = atoi (arg2);
                }
              else if ((a2ir = is_register (arg2)) != -1)
                {
                  qp->cg[qp->cgc++] = ADD_rr;
                  qp->cg[qp->cgc++] = a1ir;
                  qp->cg[qp->cgc++] = a2ir;
                }
            }

          printf ("found add instruction '%s', '%s'\n", arg1, arg2);
        }

      else if (_str_startswith_ncs (line, "hlt"))
        {
          qp->cg[qp->cgc++] = HLT;

          printf ("found hlt instruction\n");
        }
    }

  qp->prog_sections[qp->ps_c].bc = pp_bytecount;
  qp->prog_sections[qp->ps_c++].name = NULL;
}