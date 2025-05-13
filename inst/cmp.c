#include "cmp.h"
#include "../vm.h"

SH_API void
sh_cmp_rv (struct _sharna_vm_s *vm, char r1, char v1)
{
  vm->cpu.reg_8[R_SF] &= ~(REG_SF_ZF | REG_SF_SF | REG_SF_CF | REG_SF_OF
                           | REG_SF_AF | REG_SF_PF);

  uint8_t r = vm->cpu.reg_8[r1] - (uint8_t)v1;
  uint8_t rv1 = vm->cpu.reg_8[r1];
  uint8_t imm = (uint8_t)v1;

  uint8_t is_zero = (r == 0);
  uint8_t is_negative = ((r >> 7) & 1);
  uint8_t has_carry = (rv1 < imm);

  vm->cpu.reg_8[R_SF] |= ((REG_SF_ZF * is_zero) | (REG_SF_SF * is_negative)
                          | (REG_SF_CF * has_carry));

  if ((rv1 > 0 && v1 < 0 && r < 0) || (rv1 < 0 && v1 > 0 && r > 0))
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_OF;
    }

  uint8_t parity = 0;
  for (size_t i = 0; i < 8; i++)
    {
      parity += (r >> i) & 1;
    }

  if ((parity & 1) == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_PF;
    }
}

SH_API void
sh_cmp_rr (struct _sharna_vm_s *vm, char r1, char r2)
{
  vm->cpu.reg_8[R_SF] &= ~(REG_SF_ZF | REG_SF_SF | REG_SF_CF | REG_SF_OF
                           | REG_SF_AF | REG_SF_PF);

  uint8_t r = vm->cpu.reg_8[r1] - vm->cpu.reg_8[r2];

  uint8_t rv1 = vm->cpu.reg_8[r1];
  uint8_t rv2 = vm->cpu.reg_8[r2];

  uint8_t is_zero = (r == 0);
  uint8_t is_negative = ((r >> 7) & 1);
  uint8_t has_carry = (rv1 < rv2);

  vm->cpu.reg_8[R_SF] |= ((REG_SF_ZF * is_zero) | (REG_SF_SF * is_negative)
                          | (REG_SF_CF * has_carry));

  if ((rv1 > 0 && rv2 < 0 && r < 0) || (rv1 < 0 && rv2 > 0 && r > 0))
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_OF;
    }

  uint8_t parity = 0;
  for (size_t i = 0; i < 8; i++)
    {
      parity += (r >> i) & 1;
    }

  if ((parity & 1) == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_PF;
    }
}