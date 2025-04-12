#include "ast.h"
#include "ctx.h"

void
_tree_push (sh_asm_ctx_t *c, sh_asm_ast_t v)
{
  if (c->trc == c->trs)
    {
      c->trc += ASM_CTX_TREE_CAP;
      c->tree = shrealloc (c->tree, c->trc * sizeof (sh_asm_ast_t));
    }

  c->tree[c->trs++] = v;
}

SH_API void
sh_asm_ast_parse_toks (sh_asm_ctx_t *c)
{
  int i = 0;
  sh_asm_ast_t cv;

  while (i < c->ts)
    {
      sh_tok_t *ct = &c->toks[i];

      switch (ct->type)
        {
        case TOK_COMMENT:
          {
          }
          break;
        case TOK_IDENTIFIER:
          {
          }
          break;
        case TOK_INST:
          {
            switch (ct->v.inst.type)
              {
              case INST_MOV:
                {
                  cv.type = AST_INST_3BYTE;

                  /* for now */
                  cv.v.i3b.v1 = MOV;
                  assert (c->toks[i + 1].type == TOK_IDENTIFIER);

                  char *id = c->toks[i + 1].v.ident.v;

                  if (id[1] == '\0' && (id[0] >= 'A' && id[0] <= 'F'))
                    {
                      cv.v.i3b.v2 = id[0] - 'A';
                    }
                  else
                    {
                      eprintf (
                          "sh_asm_ast_parse_toks: feature in development");
                      exit (EXIT_FAILURE);
                    }

                  if (c->toks[i + 2].type == TOK_NUMBER)
                    {
                      cv.v.i3b.v3 = c->toks[i + 2].v.num.v;
                    }

                  _tree_push (c, cv);
                }
                break;

              case INST_ADD:
                {
                  cv.type = AST_INST_3BYTE;

                  /* for now */
                  cv.v.i3b.v1 = ADD;
                  assert (c->toks[i + 1].type == TOK_IDENTIFIER);

                  char *id = c->toks[i + 1].v.ident.v;

                  if (id[1] == '\0' && (id[0] >= 'A' && id[0] <= 'F'))
                    {
                      cv.v.i3b.v2 = id[0] - 'A';
                    }
                  else
                    {
                      eprintf (
                          "sh_asm_ast_parse_toks: feature in development");
                      exit (EXIT_FAILURE);
                    }

                  if (c->toks[i + 2].type == TOK_NUMBER)
                    {
                      cv.v.i3b.v3 = c->toks[i + 2].v.num.v;
                    }

                  _tree_push (c, cv);
                }
                break;

              case INST_HLT:
                {
                  cv.type = AST_INST_1BYTE;
                  cv.v.i1b.v = HLT;

                  _tree_push (c, cv);
                }
                break;

              default:
                break;
              }
          }
          break;
        case TOK_NUMBER:
          {
          }
          break;
        case TOK_OPERATOR:
          {
          }
          break;

        default:
          break;
        }

    le:
      i++;
    }
}