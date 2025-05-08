#include "codegen.h"
#include "../registers.h"

static uint8_t parse (sh_asm_ctx_t *_CTX, sh_inst_arg_t *_INST);

SH_API void
sh_asm_codegen (sh_asm_ctx_t *c)
{
  size_t i = 0;
  size_t tc = 0, dc = 0; /* text count and data count */

  while (i < c->trs)
    {
      sh_asm_ast_t *cur = &c->tree[i];
      //   printf ("[%d]\n", cur->type);

      switch (cur->type)
        {
        case AST_INST_1BYTE:
          {
            // printf ("1b\n");
            if (cur->curr_section != SECTION_TEXT)
              {
                wprintf (
                    "sh_asm_codegen: instruction found in non-text section");
              }

            c->text[tc++] = cur->v.i1b.v;
          }
          break;

        case AST_INST_2BYTE:
          {
            c->text[tc++] = cur->v.i2b.v1;
            c->text[tc++] = parse (c, &cur->v.i2b.v2);
          }
          break;

        case AST_INST_3BYTE:
          {
            // printf ("3b\n");
            c->text[tc++] = cur->v.i3b.v1;
            c->text[tc++] = parse (c, &cur->v.i3b.v2);
            c->text[tc++] = parse (c, &cur->v.i3b.v3);
          }
          break;

        case AST_LABEL:
          {
            __development__
          }
          break;
        case AST_SECTION:
          {
            __development__
          }
          break;

        case AST_DB:
          {
            for (int i = 0; i < cur->v.db.v; i++)
              ;
          }
          break;

        default:
          {
            __development__
          }
          break;
        }
    le:
      i++;
    }
}

uint8_t
parse (sh_asm_ctx_t *c, sh_inst_arg_t *inst)
{
  uint8_t r = 0;

  switch (inst->type)
    {
    case ARG_TYPE_NUM:
      {
        r = inst->v.num.v;
      }
      break;
    case ARG_TYPE_VAR:
      {
        for (int i = 0; REGNAMES[i] != NULL; i++)
          {
            if (!strcmp (REGNAMES[i], inst->v.var.v))
              {
                r = i;
                break;
              }
          }
      }
      break;

    default:
      {
        __development__
      }
      break;
    }

  return r;
}