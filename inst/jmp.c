#include "jmp.h"
#include "../vm.h"

SH_API void
sh_jmp_v (struct _sharna_vm_s *vm, char b1, char b2)
{
  uint16_t addr;
  if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
    addr = (((uint8_t)b1) << 8) | ((uint8_t)b2);
  else
    addr = (((uint8_t)b2) << 8) | ((uint8_t)b1);

  vm->cpu.reg_16[R_PC] = addr - 1; /* +1 will be added later by vm */
}