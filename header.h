#pragma once

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(SH_API)
#define SH_API
#endif

#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#define wprintf(...)                                                          \
  fprintf (stdout, "[warn] ");                                                \
  fprintf (stdout, __VA_ARGS__);

#define __development__                                                       \
  fprintf (stderr, "%s(%d): requested feature is under development",          \
           __FUNCTION__, __LINE__);                                           \
  exit (EXIT_FAILURE);

#define DBG(X) X

#define SH_ARCH_BIG_ENDIAN 0
#define SH_ARCH_LITTLE_ENDIAN 1

#if !defined(SH_ARCH_TYPE)
#define SH_ARCH_TYPE SH_ARCH_BIG_ENDIAN
#endif
