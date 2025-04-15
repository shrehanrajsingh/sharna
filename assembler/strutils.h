#pragma once

#include "../header.h"
#include "../shmalloc.h"

#define _STR_TRIMLEFT(X)                                                      \
  while (*(X) == ' ' || *(X) == '\t')                                         \
    (X)++;

#define _STR_TRIMRIGHT(X)                                                     \
  while ((X)[strlen ((X)) - 1] == ' ' || (X)[strlen ((X)) - 1] == '\t')       \
    (X)[strlen ((X)) - 1] = '\0';

#define _STR_TRIM(X)                                                          \
  _STR_TRIMLEFT ((X));                                                        \
  _STR_TRIMRIGHT ((X));

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API int _str_startswith (char *_Big,
                              char *_Little); /* (big starts with little)? */

  SH_API int _str_startswith_ncs (
      char *_Big,
      char *_Little); /* same as _str_startswith but case insensitive */

  SH_API int _str_contains (char *_Big,
                            char _Little); /* (big contains little)? */

  SH_API int _str_isnumber (char *_Big);

#if defined(__cplusplus)
}
#endif
