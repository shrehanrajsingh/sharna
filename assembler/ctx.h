#pragma once

#include "../header.h"
#include "../shmalloc.h"
#include "ast.h"
#include "tok.h"

#define ASM_CTX_TOK_CAP 32
#define ASM_CTX_TREE_CAP 32

#define ASM_CTX_SECTION_TEXT_SIZE (32 * 1024 * sizeof (uint8_t)) /* 32KB */
#define ASM_CTX_SECTION_DATA_SIZE (32 * 1024 * sizeof (uint8_t)) /* 32KB */

typedef struct _sh_asm_ctx_s
{
  FILE *src;
  int fc;

  sh_tok_t *toks;
  size_t ts; /* size of toks */
  size_t tc; /* capacity of toks */

  sh_asm_ast_t *tree;
  size_t trs; /* size of tree */
  size_t trc; /* capacity of tree */

  uint8_t *text; /* text section */
  uint8_t *data; /* data section */

} sh_asm_ctx_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API sh_asm_ctx_t sh_asm_ctx_new (void);
  SH_API sh_asm_ctx_t sh_asm_ctx_new_fromFilename (char *_FName);
  SH_API void sh_asm_ctx_push_tok (sh_asm_ctx_t *_CTX, sh_tok_t _Tok);
  SH_API void sh_asm_destroy (sh_asm_ctx_t *_CTX);

#if defined(__cplusplus)
}
#endif
