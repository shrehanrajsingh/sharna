#include "quickparser.h"

SH_API sh_qp_t
sh_qp_new (void)
{
  sh_qp_t r;
  r.fcont = NULL;
  r.flines = NULL;
  r.fls = 0;
  r.fptr = NULL;
  r.fs = 0;
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

  char c;

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