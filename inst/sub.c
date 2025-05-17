#include "sub.h"
#include "../vm.h"

SH_API void
sh_sub_rv (struct _sharna_vm_s *vm, char r1, char v)
{
  uint8_t orig_val = vm->cpu.reg_8[r1];

  vm->cpu.reg_8[R_SF] &= ~(REG_SF_OF | REG_SF_CF | REG_SF_ZF | REG_SF_SF
                           | REG_SF_AF | REG_SF_PF);

  uint16_t u_result = (uint16_t)orig_val - (uint16_t)v;
  if (u_result > 255)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_CF;
    }

  int8_t s_orig = (int8_t)orig_val;
  int8_t s_v = (int8_t)v;
  int16_t s_result = (int16_t)s_orig - (int16_t)s_v;
  if (s_result < -128 || s_result > 127)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_OF;
    }

  vm->cpu.reg_8[r1] -= v;

  if (vm->cpu.reg_8[r1] == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_ZF;
    }

  if (((vm->cpu.reg_8[r1] >> 7) & 1) == 1)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_SF;
    }

  if (((orig_val & 0x0F) + (v & 0x0F)) > 0x0F)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_AF;
    }

  uint8_t result = vm->cpu.reg_8[r1];
  uint8_t parity = 0;
  for (int i = 0; i < 8; i++)
    {
      if ((result >> i) & 1)
        parity++;
    }
  if ((parity & 1) == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_PF;
    }
}

SH_API void
sh_sub_rr (struct _sharna_vm_s *vm, char r1, char r2)
{
  uint8_t v = vm->cpu.reg_8[r1];
  uint8_t orig_val = v;

  vm->cpu.reg_8[R_SF] &= ~(REG_SF_OF | REG_SF_CF | REG_SF_ZF | REG_SF_SF
                           | REG_SF_AF | REG_SF_PF);

  uint16_t u_result = (uint16_t)orig_val - (uint16_t)v;
  if (u_result > 255)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_CF;
    }

  int8_t s_orig = (int8_t)orig_val;
  int8_t s_v = (int8_t)v;
  int16_t s_result = (int16_t)s_orig - (int16_t)s_v;
  if (s_result < -128 || s_result > 127)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_OF;
    }

  vm->cpu.reg_8[r1] -= vm->cpu.reg_8[r2];

  if (vm->cpu.reg_8[r1] == 0)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_ZF;
    }

  if (((vm->cpu.reg_8[r1] >> 7) & 1) == 1)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_SF;
    }

  if (((orig_val & 0x0F) + (v & 0x0F)) > 0x0F)
    {
      vm->cpu.reg_8[R_SF] |= REG_SF_AF;
    }

  unsigned char result = vm->cpu.reg_8[r1];
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