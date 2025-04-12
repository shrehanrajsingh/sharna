#pragma once

#include "../header.h"
#include "../shmalloc.h"
#include "ast.h"
#include "tok.h"

#define ASM_CTX_TOK_CAP 32
#define ASM_CTX_TREE_CAP 32

typedef struct _sh_asm_ctx_s
{
  FILE *src;
  int fc;

  sh_tok_t *toks;
  size_t ts; /* size */
  size_t tc; /* capacity */

  sh_asm_ast_t *tree;
  size_t trs; /* size */
  size_t trc; /* capacity */

  char *text; /* text section */
  char *data; /* data section */

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
