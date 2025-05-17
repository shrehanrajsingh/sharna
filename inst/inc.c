#include "inc.h"
#include "../vm.h"

SH_API void
sh_inc_r (struct _sharna_vm_s *vm, char r)
{
  uint8_t v = vm->cpu.reg_8[r];

  vm->cpu.reg_8[R_SF] &= ~(REG_SF_OF | REG_SF_CF | REG_SF_ZF | REG_SF_SF
                           | REG_SF_AF | REG_SF_PF);

  int8_t s_v = (int8_t)v;
  int16_t s_result = (int16_t)s_v + 1;
  if (s_result < -128 || s_result > 127)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_OF;
    }

  vm->cpu.reg_8[r]++;

  if (vm->cpu.reg_8[r] == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_ZF;
    }

  if (((vm->cpu.reg_8[r] >> 7) & 1) == 1)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_SF;
    }

  if (((v & 0x0F) + 1) > 0x0F)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_AF;
    }

  unsigned char result = vm->cpu.reg_8[r];
  unsigned char parity = 0;
  for (int i = 0; i < 8; i++)
    {
      if ((result >> i) & 1)
        {
          parity++;
        }
    }
  if ((parity & 1) == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_PF;
    }
}