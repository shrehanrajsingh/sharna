#pragma once

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(SH_API)
#define SH_API
#endif

#define eprintf(...) fprintf (stderr, __VA_ARGS__)