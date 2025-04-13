#pragma once

#include "../header.h"
#include "../opcodes.h"
#include "../shmalloc.h"

struct _sh_asm_ctx_s;

enum
{
  AST_DB = 0,
  AST_INST_1BYTE = 1,
  AST_INST_2BYTE = 2,
  AST_INST_3BYTE = 3,
  AST_LABEL = 4,
  AST_SECTION = 5,
};

enum
{
  SECTION_TEXT,
  SECTION_DATA,
};

enum
{
  ARG_TYPE_NUM = 0,
  ARG_TYPE_VAR = 1,
};

typedef struct
{
  int type;

  union
  {
    struct
    {
      uint8_t v;
    } num;

    struct
    {
      char *v;
    } var;

  } v;

} sh_inst_arg_t;

typedef struct
{
  int type;
  int curr_section;

  union
  {
    struct
    {
      int v;  /* number of bytes */
      char f; /* fill `v` bytes with `f` */
    } db;

    /* byte 1 is always opcode */
    struct
    {
      uint8_t v;
    } i1b;

    struct
    {
      uint8_t v1;
      sh_inst_arg_t v2;
    } i2b;

    struct
    {
      uint8_t v1;
      sh_inst_arg_t v2, v3;
    } i3b;

    struct
    {
      char *v;
    } lab;

    struct
    {
      int type;
    } sec;

  } v;

} sh_asm_ast_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_asm_ast_parse_toks (struct _sh_asm_ctx_s *_CTX);

#if defined(__cplusplus)
}
#endif
