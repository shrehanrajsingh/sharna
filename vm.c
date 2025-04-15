#include "vm.h"

SH_API vm_t
sh_vm_new (void)
{
  vm_t v;
  v.ram = sh_ram_new ();
  v.cpu = sh_cpu_new ();
  v.rom = sh_rom_new ();

  return v;
}

SH_API void
sh_vm_run (vm_t *v)
{
  uint16_t *pc = &v->cpu.reg_16[R_PC];

  uint8_t *ra = &v->cpu.reg_8[R_A], *rb = &v->cpu.reg_8[R_B],
          *rc = &v->cpu.reg_8[R_C], *rd = &v->cpu.reg_8[R_D],
          *re = &v->cpu.reg_8[R_E], *rf = &v->cpu.reg_8[R_F];

  char c;

  while ((c = v->ram.v[*pc]) != HLT)
    {
      switch (c)
        {
        case MOV_rv:
          {
            char r = v->ram.v[++(*pc)];
            char vl = v->ram.v[++(*pc)];

            sh_mov_rv (v, r, vl);
          }
          break;

        case ADD_rv:
          {
            char r = v->ram.v[++(*pc)];
            char vl = v->ram.v[++(*pc)];

            sh_add_rv (v, r, vl);
          }
          break;
        case ADD_rr:
          {
            char r1 = v->ram.v[++(*pc)];
            char r2 = v->ram.v[++(*pc)];

            sh_add_rr (v, r1, r2);
          }
          break;

        default:
          {
            eprintf ("sh_vm_run: invalid instruction %d", c);
          }
          break;
        }

    le:
      (*pc)++;
    }
}