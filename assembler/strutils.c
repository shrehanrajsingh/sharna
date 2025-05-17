#include "strutils.h"

SH_API int
_str_startswith (char *b, char *l)
{
  while (*b++ == *l++)
    ;
  return !*--l;
}

SH_API int
_str_startswith_ncs (char *b, char *l)
{
  while (*l)
    {
      if (*l >= 'A' && *l <= 'Z')
        *l = (*l) - 'A';

      if (*b >= 'A' && *b <= 'Z')
        *b = (*b) - 'A';

      if (*b != *l)
        return 0;

      b++;
      l++;
    }

  return 1;
}

SH_API int
_str_contains (char *b, char l)
{
  while (*b != '\0' && *b != l)
    b++;
  return *b == l;
}

SH_API int
_str_isnumber (char *b)
{
  while (*b != '\0' && *b >= '0' && *b <= '9')
    b++;

  return !*b;
}