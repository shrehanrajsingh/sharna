#include "mov.h"
#include "../vm.h"

SH_API void
sh_mov_rv (vm_t *v, char r, char _v)
{
  /* if (r > R_8bit)
    {
      eprintf ("sh_mov_rv: invalid register");
      exit (EXIT_FAILURE);
    } */

  v->cpu.reg_8[r] = _v;
}

SH_API void
sh_mov_rr (vm_t *v, char r1, char r2)
{
  /* if (r1 > R_8bit || r2 > R_8bit)
    {
      eprintf ("sh_mov_rr: invalid register");
      exit (EXIT_FAILURE);
    } */

  v->cpu.reg_8[r1] = v->cpu.reg_8[r2];
}