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
#include "../opcodes.h"
#include "../registers.h"
#include "../shmalloc.h"
#include "strutils.h"

#define QP_VTABLE_SIZE 5000
#define QP_CODEGEN_SIZE (32 * 1024 + 32 * 1024) /* 32KB text, 32KB data */
#define QP_VTABLE_KEYS_CAPACITY 128

typedef struct
{
  size_t val[QP_VTABLE_SIZE];

  char **keys;
  size_t kc;
  size_t kl;

} sh_qp_vtable_t;

typedef struct
{
  FILE *fptr;  /* file pointer */
  char *fcont; /* file contents */
  size_t fs;   /* file content size */

  char **flines; /* file contents into lines */
  size_t fls;    /* file lines size */

  sh_qp_vtable_t vt; /* to store labels */

  /**
   * one section is reserved for end of program (.name = NULL, .bc = bytes used
   * by program)
   */
  struct
  {
    char *name; /* section name, containing '.' */
    size_t bc;  /* byte count */
    size_t lc;  /* line count */

  } prog_sections[64]; /* 64 unique sections per program */
  size_t ps_c;         /* program section count */

  char cg[QP_CODEGEN_SIZE]; /* codegen */
  size_t cgc;

} sh_qp_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API sh_qp_t sh_qp_new (void);
  SH_API sh_qp_t sh_qp_new_fromFile (char *_fname);
  SH_API void sh_qp_close (sh_qp_t *_QP);

  SH_API void sh_qp_addtovtable (sh_qp_vtable_t *, char *, size_t);
  SH_API int sh_qp_getfromvtable (sh_qp_vtable_t *_VT, char *_Key);
  SH_API int sh_qp_vt_keyexists (sh_qp_vtable_t *_VT, char *_Key);
  SH_API sh_qp_vtable_t sh_qp_vt_new (void);

  SH_API void sh_qp_parse (sh_qp_t *_QP);

#if defined(__cplusplus)
}
#endif
