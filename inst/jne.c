#include "jne.h"
#include "../vm.h"

SH_API void
sh_jne_v (struct _sharna_vm_s *vm, char b1, char b2)
{
  if ((vm->cpu.reg_8[R_SF] & REG_SF_ZF) == 0)
    {
      uint16_t addr = 0;
      if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
        addr = (((uint8_t)b1) << 8) | ((uint8_t)b2);
      else
        addr = (((uint8_t)b2) << 8) | ((uint8_t)b1);

      vm->cpu.reg_16[R_PC] = addr;
    }
}