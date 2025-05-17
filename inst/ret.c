#include "ret.h"
#include "../vm.h"

SH_API void
sh_ret (struct _sharna_vm_s *vm)
{
  char b1 = vm->ram.v[++vm->cpu.reg_16[R_SP]];
  char b2 = vm->ram.v[++vm->cpu.reg_16[R_SP]];

  uint16_t addr;
  if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
    {
      /* [...stack data, msb, lsb] */
      /*                  b2   b1 */
      /*
       b1: lsb
       b2: msb
      */

      addr = ((((uint16_t)b2) << 8) | (uint16_t)b1);
    }
  else
    {
      /* [...stack data, lsb, msb] */
      /*                  b2   b1 */
      /*
       b1: msb
       b2: lsb
      */

      addr = ((((uint16_t)b1) << 8) | (uint16_t)b2);
    }

  vm->cpu.reg_16[R_PC] = addr; /* this will be the address of call instruction,
                                  vm will do a +1, but we need another +1 since
                                  call is a 3-byte instruction */
}