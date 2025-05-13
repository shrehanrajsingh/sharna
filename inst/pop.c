#include "pop.h"
#include "../vm.h"

SH_API void
sh_pop_r (struct _sharna_vm_s *vm, char r)
{
  vm->cpu.reg_8[r] = vm->ram.v[++vm->cpu.reg_16[R_SP]];
}