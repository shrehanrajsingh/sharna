#include "rom.h"

SH_API rom_t
sh_rom_new (void)
{
  rom_t r;
  r.l = 0;

  return r;
}

SH_API void
sh_rom_push (rom_t *r, uint8_t v)
{
  if (r->l == ROM_SIZE - 1)
    {
      eprintf ("sh_rom_push: ROM is full");
      exit (EXIT_FAILURE);
    }

  r->v[r->l++] = v;
}