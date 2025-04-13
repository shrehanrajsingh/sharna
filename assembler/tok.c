#include "tok.h"
#include "ctx.h"

char
fetch (sh_asm_ctx_t *s)
{
  return fgetc (s->src);
}

int
is_identifier (char *s)
{
  for (int i = 0; s[i]; i++)
    {
      if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
          || (s[i] && s[i] >= '0' && s[i] <= '9') || s[i] == '_')
        {
          /* do nothing */
        }
      else
        return 0;
    }

  return 1;
}

int
is_number (char *s)
{
  for (int i = 0; s[i]; i++)
    {
      if (i >= '0' && i <= '9')
        ; /* do nothing */
      else
        return 0;
    }

  return 1;
}

SH_API void
sh_asm_tok_parse (sh_asm_ctx_t *s)
{
  char c = fetch (s);
  sh_tok_t ct;

  while (c != EOF)
    {
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
        {
          char var[ASM_IDENT_SIZE_LIMIT];
          var[0] = c;

          char d = fetch (s);
          int j = 1;

          while ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z')
                 || (d >= '0' && d <= '9') || d == '_')
            {
              if (j == ASM_IDENT_SIZE_LIMIT)
                {
                  eprintf ("sh_asm_tok_parse: too big identifier");
                  exit (EXIT_FAILURE);
                }

              var[j++] = d;
              d = fetch (s);
            }

          var[j] = '\0';

          ct.type = TOK_IDENTIFIER;
          for (j = 0; INSTNAMES[j] != NULL; j++)
            {
              if (!strcmp (INSTNAMES[j], var))
                {
                  ct.type = TOK_INST;
                  ct.v.inst.type = j;
                  break;
                }
            }

          if (ct.type == TOK_IDENTIFIER)
            {
              ct.v.ident.v = shstrdup (var);
            }

          sh_asm_ctx_push_tok (s, ct);
          c = d;
          continue;
        }
      else if (c == ',' || c == '+' || c == '-' || c == ':' || c == '.'
               || c == '[' || c == ']' || c == '(' || c == ')' || c == ';')
        {
          ct.type = TOK_OPERATOR;
          ct.v.opt.v = shstrdup (" ");
          *ct.v.opt.v = c;

          sh_asm_ctx_push_tok (s, ct);
        }
      else if (c == '\n')
        {
          ct.type = TOK_NL;

          sh_asm_ctx_push_tok (s, ct);
        }
      else if (c >= '0' && c <= '9')
        {
          uint8_t num; /* 8 bit numbers cannot be > 255 */
          num = 100 * (c - '0');

          char d = fetch (s);
          if (d >= '0' && d <= '9')
            {
              num += 10 * (d - '0');

              d = fetch (s);

              if (d >= '0' && d <= '9')
                {
                  num += (d - '0');
                  ct.type = TOK_NUMBER;
                  ct.v.num.v = num;

                  sh_asm_ctx_push_tok (s, ct);
                  goto le;
                }
              else
                {
                  c = d;
                  num /= 10;
                }
            }
          else
            {
              c = d;
              num /= 10;
            }

          ct.type = TOK_NUMBER;
          ct.v.num.v = num;
          sh_asm_ctx_push_tok (s, ct);
          continue;
        }
    le:
      c = fetch (s);
    }
}