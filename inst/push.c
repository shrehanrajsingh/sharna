#include "push.h"
#include "../vm.h"

SH_API void
sh_push_v (struct _sharna_vm_s *vm, char b)
{
  vm->ram.v[vm->cpu.reg_16[R_SP]--] = b;
}

SH_API void
sh_push_r (struct _sharna_vm_s *vm, char r)
{
  vm->ram.v[vm->cpu.reg_16[R_SP]--] = vm->cpu.reg_8[r];
}