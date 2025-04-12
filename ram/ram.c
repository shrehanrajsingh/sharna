#include "ram.h"

SH_API ram_t
sh_ram_new (void)
{
  ram_t n;
  n.offsets.p_text = 0;
  n.offsets.p_data = 0;
  n.offsets.heap = 0;
  n.offsets.stack = RAM_SIZE - 1;
  n.l = 0;

  return n;
}

SH_API void
sh_ram_reset_offsets (ram_t *a, rom_t *o)
{
  a->offsets.p_text = 0;
  a->offsets.p_data = o->l;
  a->offsets.heap = o->l * 2;
  a->offsets.stack = RAM_SIZE - 1;
}

SH_API void
sh_ram_reset_offsets_m (ram_t *r, uint16_t pt, uint16_t pd, uint16_t h,
                        uint16_t st)
{
  r->offsets.heap = h;
  r->offsets.p_data = pd;
  r->offsets.p_text = pt;
  r->offsets.stack = st;
}

SH_API void
sh_ram_load (ram_t *r, char *d, int f, int t)
{
  for (int i = f; i < t; i++)
    r->v[r->l++] = d[i];
}

SH_API void
sh_ram_push (ram_t *r, char v)
{
  if (r->l == RAM_SIZE - 1)
    {
      eprintf ("sh_ram_push: RAM is full");
      exit (EXIT_FAILURE);
    }

  r->v[r->l++] = v;
}