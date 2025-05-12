#pragma once

#include "header.h"

#define shmalloc(X) _SH_Malloc (X)
#define shrealloc(X, Y) _SH_Realloc (X, Y)
#define shfree(X) _SH_Free (X)
#define shstrdup(X) _SH_Strdup (X)

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void *_SH_Malloc (size_t _Size);
  SH_API void *_SH_Realloc (void *_Old, size_t _NewSize);
  SH_API void _SH_Free (void *_Old);
  SH_API char *_SH_Strdup (char *_Target);

#if defined(__cplusplus)
}
#endif
