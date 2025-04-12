#include "ctx.h"

SH_API sh_asm_ctx_t
sh_asm_ctx_new (void)
{
  sh_asm_ctx_t ctx;
  ctx.fc = 0;
  ctx.src = NULL;
  ctx.tc = ASM_CTX_TOK_CAP;
  ctx.toks = shmalloc (ctx.tc * sizeof (sh_tok_t));
  ctx.ts = 0;
  ctx.trs = 0;
  ctx.trc = ASM_CTX_TREE_CAP;
  ctx.tree = shmalloc (ctx.trc * sizeof (sh_asm_ast_t));

  return ctx;
}

SH_API sh_asm_ctx_t
sh_asm_ctx_new_fromFilename (char *fn)
{
  sh_asm_ctx_t ctx = sh_asm_ctx_new ();
  ctx.src = fopen (fn, "r");

  if (ctx.src == NULL)
    {
      eprintf ("sh_asm_ctx_new_fromFilename: cannot open file");
      exit (EXIT_FAILURE);
    }

  return ctx;
}

SH_API void
sh_asm_ctx_push_tok (sh_asm_ctx_t *c, sh_tok_t t)
{
  if (c->tc == c->ts)
    {
      c->tc += ASM_CTX_TOK_CAP;
      c->toks = shrealloc (c->toks, c->tc * sizeof (sh_tok_t));
    }

  c->toks[c->ts++] = t;
}

SH_API void
sh_asm_destroy (sh_asm_ctx_t *c)
{
  fclose (c->src);
}