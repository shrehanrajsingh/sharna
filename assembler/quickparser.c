#include "quickparser.h"

static int
is_register (char *k)
{
  for (int i = 0; REGNAMES[i] != NULL; i++)
    if (!strcmp (REGNAMES[i], k))
      return i;

  return -1;
}

SH_API sh_qp_vtable_t
sh_qp_vt_new (void)
{
  sh_qp_vtable_t t;
  t.kc = QP_VTABLE_KEYS_CAPACITY;
  t.kl = 0;
  t.keys = shmalloc (t.kc * sizeof (char *));

  return t;
}

SH_API int
sh_qp_vt_keyexists (sh_qp_vtable_t *vt, char *key)
{
  for (size_t i = 0; i < vt->kl; i++)
    if (!strcmp (vt->keys[i], key))
      return 1;

  return 0;
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
  r.vt = sh_qp_vt_new ();

  return r;
}

SH_API sh_qp_t
sh_qp_new_fromFile (char *f)
{
  sh_qp_t r = sh_qp_new ();
  r.fptr = fopen (f, "r");

  if (!r.fptr)
    {
      eprintf ("error: No such file or directory");
      exit (EXIT_FAILURE);
    }

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

  if (vt->kc == vt->kl)
    {
      vt->kc += QP_VTABLE_KEYS_CAPACITY;
      vt->keys = shrealloc (vt->keys, vt->kc * sizeof (char *));
    }

  vt->keys[vt->kl++] = strdup (key);
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
      _STR_TRIM (qp->flines[i]);

      /* unescape string */
      char *p = qp->flines[i];
      char *q = p;
      while (*p)
        {
          if (*p == '\\')
            {
              p++;
              switch (*p)
                {
                case 'n':
                  *q++ = '\n';
                  break;
                case 't':
                  *q++ = '\t';
                  break;
                case 'r':
                  *q++ = '\r';
                  break;
                case '\\':
                  *q++ = '\\';
                  break;
                case '\"':
                  *q++ = '\"';
                  break;
                case '\'':
                  *q++ = '\'';
                  break;
                default:
                  *q++ = *p;
                }
              p++;
            }
          else
            {
              *q++ = *p++;
            }
        }
      *q = '\0';
      //   printf ("(%s)\n", qp->flines[i]);
    }

  size_t pp_bytecount = 0; /* pre processor byte count */

  size_t sec_text_lc = 0, sec_text_bc = 0;
  size_t sec_data_lc = 0, sec_data_bc = 0;

  /* add labels to memory */
  for (size_t i = 0; i < qp->fls; i++)
    {
      char *line = qp->flines[i];

      if (*line == '\0')
        continue;

      if (line[strlen (line) - 1] == ':')
        {
          line[strlen (line) - 1] = '\0';
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

          DBG (printf ("found section '%s'\n", line));

          if (!strcmp (line, "text"))
            {
              sec_text_lc = i;
              sec_text_bc = pp_bytecount;
            }
          else if (!strcmp (line, "data"))
            {
              sec_data_lc = i;
              sec_data_bc = pp_bytecount;
            }

          qp->prog_sections[qp->ps_c].name = shstrdup (line);
          qp->prog_sections[qp->ps_c].lc = i;
          qp->prog_sections[qp->ps_c++].bc = pp_bytecount;
        }

      if (_str_startswith_ncs (line, "db"))
        {
          // pp_bytecount += 1;
          line += 2;
          _STR_TRIM (line);

          size_t bufc = 16, bufl = 0;
          char **buf = shmalloc (bufc * sizeof (char *));

          int in_str = 0;
          int last_comma_idx = -1;
          char str_q = 0;
          for (size_t j = 0; line[j] != '\0'; j++)
            {
              char d = line[j];

              if (d == '\"' || d == '\'')
                {
                  if (!in_str)
                    {
                      str_q = d;
                      in_str = 1;
                    }
                  else
                    {
                      if (d == str_q
                          && (line[j - 1] != '\\'
                              || (line[j - 1] == '\\' && j > 1
                                  && line[j - 2] != '\\')))
                        in_str = 0;
                    }
                }

              if (d == ',' && !in_str)
                {
                  if (bufl == bufc)
                    {
                      bufc += 16;
                      buf = shrealloc (buf, bufc * sizeof (char *));
                    }

                  line[j] = '\0';
                  buf[bufl++] = line + last_comma_idx + 1;
                  last_comma_idx = j;
                }
            }

          if (bufl == bufc)
            {
              bufc += 1;
              buf = shrealloc (buf, bufc * sizeof (char *));
            }
          buf[bufl++] = line + last_comma_idx + 1;

          for (size_t j = 0; j < bufl; j++)
            {
              _STR_TRIM (buf[j]);
              if (buf[j][0] == '\"')
                {
                  size_t bjl = strlen (buf[j]);
                  pp_bytecount += (bjl - 2);
                }
              else if (buf[j][0] == '\'')
                pp_bytecount++;

              else if (_str_isnumber (buf[j]))
                pp_bytecount++;
            }

          shfree (buf);
        }
    }

  for (size_t i = sec_text_lc + 1; i < qp->fls; i++)
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
          int a2ir;

          if (a1ir != -1) /* standard mov */
            {
              if (_str_isnumber (arg2))
                {
                  qp->cg[sec_text_bc + qp->cgc++] = MOV_rv;
                  qp->cg[sec_text_bc + qp->cgc++] = a1ir;
                  qp->cg[sec_text_bc + qp->cgc++] = atoi (arg2);
                }
              else if ((a2ir = is_register (arg2)) != -1)
                {
                  qp->cg[sec_text_bc + qp->cgc++] = MOV_rr;
                  qp->cg[sec_text_bc + qp->cgc++] = a1ir;
                  qp->cg[sec_text_bc + qp->cgc++] = a2ir;
                }
              else if (sh_qp_vt_keyexists (&qp->vt, arg2))
                {
                  /* label */
                  qp->cg[sec_text_bc + qp->cgc++] = MOV_rv;
                  qp->cg[sec_text_bc + qp->cgc++] = a1ir;
                  qp->cg[sec_text_bc + qp->cgc++]
                      = sh_qp_getfromvtable (&qp->vt, arg2);
                }
              else
                {
                  eprintf ("Invalid argument: '%s'", arg2);
                  exit (EXIT_FAILURE);
                }
            }

          DBG (printf ("found mov instruction '%s', '%s'\n", arg1, arg2));
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

          if (a1ir != -1) /* standard add */
            {
              if (_str_isnumber (arg2))
                {
                  qp->cg[sec_text_bc + qp->cgc++] = ADD_rv;
                  qp->cg[sec_text_bc + qp->cgc++] = a1ir;
                  qp->cg[sec_text_bc + qp->cgc++] = atoi (arg2);
                }
              else if ((a2ir = is_register (arg2)) != -1)
                {
                  qp->cg[sec_text_bc + qp->cgc++] = ADD_rr;
                  qp->cg[sec_text_bc + qp->cgc++] = a1ir;
                  qp->cg[sec_text_bc + qp->cgc++] = a2ir;
                }
            }

          DBG (printf ("found add instruction '%s', '%s'\n", arg1, arg2));
        }

      else if (_str_startswith_ncs (line, "hlt"))
        {
          qp->cg[sec_text_bc + qp->cgc++] = HLT;

          DBG (printf ("found hlt instruction\n"));
          break;
        }

      else if (_str_startswith_ncs (line, "int"))
        {
          qp->cg[sec_text_bc + qp->cgc++] = INTERRUPT;

          line += 4;
          _STR_TRIM (line);

          assert (_str_isnumber (line));
          qp->cg[sec_text_bc + qp->cgc++] = (uint8_t)atoi (line);

          DBG (printf ("found interrupt instruction\n"));
        }

      else if (_str_startswith_ncs (line, "jne"))
        {
          qp->cg[sec_text_bc + qp->cgc++] = JNE_v;

          line += 4;
          _STR_TRIM (line);

          int li;

          if (_str_isnumber (line))
            li = atoi (line);
          else if (sh_qp_vt_keyexists (&qp->vt, line))
            li = sh_qp_getfromvtable (&qp->vt, line);

          assert (li < (1 << 16) - 1);

          li &= ~(1 << 16);

          uint8_t li_lsbh = (uint8_t)(li >> 8); /* least significant half */

          uint8_t li_msbh
              = (uint8_t)(li & ~(1 << 8)); /* most significant half */

          if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
            {
              qp->cg[sec_text_bc + qp->cgc++] = li_lsbh;
              qp->cg[sec_text_bc + qp->cgc++] = li_msbh;
            }
          else
            {
              qp->cg[sec_text_bc + qp->cgc++] = li_msbh;
              qp->cg[sec_text_bc + qp->cgc++] = li_lsbh;
            }

          DBG (printf ("found jne instruction: %d, %d\n", li_lsbh, li_msbh));
        }
      else if (_str_startswith_ncs (line, "je"))
        {
          qp->cg[sec_text_bc + qp->cgc++] = JE_v;

          line += 4;
          _STR_TRIM (line);

          int li = 0;

          if (_str_isnumber (line))
            li = atoi (line);
          else if (sh_qp_vt_keyexists (&qp->vt, line))
            {
              li = sh_qp_getfromvtable (&qp->vt, line);
            }

          assert (li < (1 << 16) - 1);

          li &= (1 << 16);

          uint8_t li_lsbh = (uint8_t)(li >> 8); /* least significant half */

          uint8_t li_msbh
              = (uint8_t)(li & (1 << 8)); /* most significant half */

          if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
            {
              qp->cg[sec_text_bc + qp->cgc++] = li_lsbh;
              qp->cg[sec_text_bc + qp->cgc++] = li_msbh;
            }
          else
            {
              qp->cg[sec_text_bc + qp->cgc++] = li_msbh;
              qp->cg[sec_text_bc + qp->cgc++] = li_lsbh;
            }

          DBG (printf ("found je instruction: %d %d\n", li_lsbh, li_msbh));
        }
    }

  qp->cgc = 0;

  for (size_t i = sec_data_lc + 1; i < qp->fls; i++)
    {
      char *line = qp->flines[i];

      while (*line == ' ' || *line == '\t')
        line++;

      if (*line == '\0')
        continue;

      if (_str_startswith_ncs (line, "section"))
        {
          break;
        }

      else if (_str_startswith_ncs (line, "db"))
        {
          line += 2;
          _STR_TRIM (line);

          size_t bufc = 16, bufl = 0;
          char **buf = shmalloc (bufc * sizeof (char *));

          int in_str = 0;
          int last_comma_idx = -1;
          char str_q = 0;
          for (size_t j = 0; line[j] != '\0'; j++)
            {
              char d = line[j];

              if (d == '\"' || d == '\'')
                {
                  if (!in_str)
                    {
                      str_q = d;
                      in_str = 1;
                    }
                  else
                    {
                      if (d == str_q
                          && (line[j - 1] != '\\'
                              || (line[j - 1] == '\\' && j > 1
                                  && line[j - 2] != '\\')))
                        in_str = 0;
                    }
                }

              if (d == ',' && !in_str)
                {
                  if (bufl == bufc)
                    {
                      bufc += 16;
                      buf = shrealloc (buf, bufc * sizeof (char *));
                    }

                  line[j] = '\0';
                  buf[bufl++] = line + last_comma_idx + 1;
                  last_comma_idx = j;
                }
            }

          if (bufl == bufc)
            {
              bufc += 1;
              buf = shrealloc (buf, bufc * sizeof (char *));
            }
          buf[bufl++] = line + last_comma_idx + 1;

          for (size_t j = 0; j < bufl; j++)
            {
              _STR_TRIM (buf[j]);
              if (buf[j][0] == '\"')
                {
                  size_t bjl = strlen (buf[j]);
                  for (size_t k = 1; k < bjl - 1; k++)
                    qp->cg[sec_data_bc + qp->cgc++] = buf[j][k];
                }
              else if (buf[j][0] == '\'')
                qp->cg[sec_data_bc + qp->cgc++] = buf[j][1];

              else if (_str_isnumber (buf[j]))
                {
                  qp->cg[sec_data_bc + qp->cgc++] = (uint8_t)atoi (buf[j]);
                }
            }

          shfree (buf);
        }
    }

  qp->prog_sections[qp->ps_c].bc = pp_bytecount;
  qp->prog_sections[qp->ps_c++].name = NULL;
  qp->cgc = pp_bytecount;
}