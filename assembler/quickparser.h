#pragma once

/**
 * The purpose of a quickparser is to
 * 1) Process assembly files.
 * 2) Parse them without any intermediate ASTs.
 * 3) Generate machine code.
 *
 * This is a single header library to generate
 * sharna machine code by eliminating certain
 * conventions in interpreter design.
 *
 * The parser works as follows:
 * 1) Read the entire file, break the code into lines.
 * 2) Find and track all labels and macros, while keeping a track of bytes used
 * in text and data section.
 * 3) Replace all macros with their definition.
 * 4) Parse each line individually, replacing any label names with memory
 * reference.
 */

#include "../header.h"
#include "../shmalloc.h"

#define QP_VTABLE_SIZE 5000

typedef struct
{
  int val[QP_VTABLE_SIZE];

} sh_qp_vtable_t;

typedef struct
{
  FILE *fptr;  /* file pointer */
  char *fcont; /* file contents */
  size_t fs;   /* file content size */

  char **flines; /* file contents into lines */
  size_t fls;    /* file lines size */

  sh_qp_vtable_t vt; /* to store labels */

} sh_qp_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API sh_qp_t sh_qp_new (void);
  SH_API sh_qp_t sh_qp_new_fromFile (char *_fname);
  SH_API void sh_qp_close (sh_qp_t *);

#if defined(__cplusplus)
}
#endif
