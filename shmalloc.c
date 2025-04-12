#include "shmalloc.h"

SH_API void *
_SH_Malloc (size_t s)
{
  void *n = malloc (s);

  if (n == NULL)
    {
      eprintf ("_SH_Malloc: memory allocation failed");
      exit (EXIT_FAILURE);
    }

  return n;
}

SH_API void *
_SH_Realloc (void *o, size_t n)
{
  void *np = realloc (o, n);

  if (np == NULL)
    {
      eprintf ("_SH_Realloc: memory reallocation failed");
      exit (EXIT_FAILURE);
    }

  return np;
}

SH_API void
_SH_Free (void *o)
{
  if (o == NULL)
    {
      eprintf ("_SH_Free: pointer is NULL, skipping free()");
      return;
    }

  free (o);
}