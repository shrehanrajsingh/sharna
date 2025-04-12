#include "add.h"
#include "../vm.h"

SH_API void
sh_add_rv (struct _sharna_vm_s *vm, char r1, char v)
{
  vm->cpu.reg_8[r1] += v;
}

SH_API void
sh_add_rr (struct _sharna_vm_s *vm, char r1, char r2)
{
  vm->cpu.reg_8[r1] += vm->cpu.reg_8[r2];
}