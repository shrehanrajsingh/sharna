#include "cmp.h"
#include "../vm.h"

SH_API void
sh_cmp_rv (struct _sharna_vm_s *vm, char r1, char v1)
{
  char r = (vm->cpu.reg_8[r1] - v1);
  vm->cpu.reg_8[R_SF] |= (REG_SF_CF * (r < 0)) | (REG_SF_ZF * !r);
}

SH_API void
sh_cmp_rr (struct _sharna_vm_s *vm, char r1, char r2)
{
  char r = vm->cpu.reg_8[r1] - vm->cpu.reg_8[r2];
  vm->cpu.reg_8[R_SF] |= (REG_SF_CF * (r < 0)) | (REG_SF_ZF * !r);
}