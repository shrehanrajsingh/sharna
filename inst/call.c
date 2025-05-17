#include "call.h"
#include "../vm.h"
#include "push.h"

SH_API void
sh_call_v (struct _sharna_vm_s *vm, char b1, char b2)
{
  uint16_t curr_pc = vm->cpu.reg_16[R_PC];
  char m1, m2;

  if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
    {
      m2 = curr_pc & 0xFF;
      m1 = (curr_pc >> 8) & 0xFF;
    }
  else
    {
      m1 = curr_pc & 0xFF;
      m2 = (curr_pc >> 8) & 0xFF;
    }

  sh_push_v (vm, m1);
  sh_push_v (vm, m2);

  //   printf ("%d %d\n", vm->ram.v[vm->cpu.reg_16[R_SP] - 1],
  //           vm->ram.v[vm->cpu.reg_16[R_SP] - 2]);

  uint16_t addr;
  if (SH_ARCH_TYPE == SH_ARCH_BIG_ENDIAN)
    addr = ((((uint16_t)b1) << 8) | (uint16_t)b2);
  else
    addr = ((((uint16_t)b2) << 8) | (uint16_t)b1);

  vm->cpu.reg_16[R_PC] = addr - 1; /* vm will do a +1 */
}