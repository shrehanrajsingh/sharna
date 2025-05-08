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

static sh_inst_arg_t parse (sh_tok_t *_Toks, int _Len);
sh_asm_ast_t fetch_inst_3b (sh_tok_t *_Toks, int _Start, int *_Jmp);
sh_asm_ast_t fetch_inst_2b (sh_tok_t *_Toks, int _Start, int *_Jmp);

SH_API void
sh_asm_ast_parse_toks (sh_asm_ctx_t *c)
{
  int i = 0;
  sh_asm_ast_t cv;
  int curr_sec = SECTION_TEXT;

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
                  cv = fetch_inst_3b (c->toks, i, &i);
                  cv.curr_section = curr_sec;
                  _tree_push (c, cv);
                }
                break;

              case INST_ADD:
                {
                  cv = fetch_inst_3b (c->toks, i, &i);
                  cv.curr_section = curr_sec;
                  _tree_push (c, cv);
                }
                break;

              case INST_HLT:
                {
                  cv.type = AST_INST_1BYTE;
                  cv.v.i1b.v = HLT;
                  cv.curr_section = curr_sec;

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

sh_inst_arg_t
parse (sh_tok_t *toks, int len)
{
  sh_inst_arg_t r;

  for (int i = 0; i < len; i++)
    {
      sh_tok_t *c = &toks[i];

      switch (c->type)
        {
        case TOK_NUMBER:
          {
            // printf ("[%d]\n", c->v.num.v);
            r.type = ARG_TYPE_NUM;
            r.v.num.v = c->v.num.v;
          }
          break;

        case TOK_IDENTIFIER:
          {
            r.type = ARG_TYPE_VAR;
            r.v.var.v = shstrdup (c->v.ident.v);
          }
          break;

        default:
          break;
        }
    }

  return r;
}

sh_asm_ast_t
fetch_inst_3b (sh_tok_t *toks, int st, int *jmp)
{
  sh_asm_ast_t cv;
  cv.type = AST_INST_3BYTE;
  cv.v.i3b.v1 = toks[st].v.inst.type;

  int ci = st + 1; /* comma idx */
  int gb = 0;

  for (;; ci++)
    {
      sh_tok_t *d = &toks[ci];

      if (d->type == TOK_OPERATOR)
        {
          if (*d->v.opt.v == ',' && !gb)
            break;

          if (*d->v.opt.v == '(' || *d->v.opt.v == '[')
            gb++;
          else if (*d->v.opt.v == ')' || *d->v.opt.v == ']')
            gb--;
        }
    }

  cv.v.i3b.v2 = parse (toks + st + 1, ci - st - 1);
  ci++;

  int cip = ci;
  gb = 0;

  for (;; ci++)
    {
      sh_tok_t *d = &toks[ci];

      if (d->type == TOK_NL && !gb)
        break;

      if (d->type == TOK_OPERATOR)
        {
          if (*d->v.opt.v == ';' && !gb)
            break;

          if (*d->v.opt.v == '(' || *d->v.opt.v == '[')
            gb++;
          else if (*d->v.opt.v == ')' || *d->v.opt.v == ']')
            gb--;
        }
    }

  cv.v.i3b.v3 = parse (toks + cip, ci - cip);

  if (jmp)
    {
      (*jmp) = ci;
    }

  return cv;
}