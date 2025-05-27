#include "xor.h"
#include "../vm.h"

SH_API void
sh_xor_rr (struct _sharna_vm_s *vm, char r1, char r2)
{
  uint8_t rv1 = vm->cpu.reg_8[r1];
  uint8_t rv2 = vm->cpu.reg_8[r2];

  uint8_t res = rv1 ^ rv2;

  /* clear SF, PF and ZF */
  vm->cpu.reg_8[R_SF]
      &= ~(REG_SF_PF | REG_SF_SF | REG_SF_ZF | REG_SF_OF | REG_SF_CF);

  if (res >> 7)
    vm->cpu.reg_8[R_SF] |= REG_SF_SF;

  if (res == 0)
    vm->cpu.reg_8[R_SF] |= REG_SF_ZF;

  vm->cpu.reg_8[r1] = res; /* store in register 1 */

  uint8_t bc = 0;
  while (res)
    {
      bc += (res & 1);
      res >>= 1;
    }

  if ((bc & 1) == 0) /* even */
    vm->cpu.reg_8[R_SF] |= REG_SF_PF;
}