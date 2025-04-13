#pragma once

#include "../header.h"

#define ASM_IDENT_SIZE_LIMIT 32

struct _sh_asm_ctx_s;
enum
{
  TOK_INST = 0,
  TOK_STRING_DOUBLE_Q = 1,
  TOK_STRING_SINGLE_Q = 2,
  TOK_IDENTIFIER = 3,
  TOK_OPERATOR = 4,
  TOK_COMMENT = 5,
  TOK_NUMBER = 6,
  TOK_NL = 7,
  TOK_COUNT /* number of tokens */
};

enum
{
  INST_MOV,
  INST_ADD,
  INST_PUSH,
  INST_HLT
};

static const char *INSTNAMES[] = { "mov", "add", "push", "hlt", NULL };

typedef struct
{
  int type;

  union
  {
    struct
    {
      int type;

    } inst;

    struct
    {
      char *v;

    } strdq;

    struct
    {
      char v;

    } strsq;

    struct
    {
      char *v;

    } ident, opt, cmt;

    struct
    {
      uint8_t v;

    } num;

  } v;

} sh_tok_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_asm_tok_parse (struct _sh_asm_ctx_s *_CTX);

#if defined(__cplusplus)
}
#endif
