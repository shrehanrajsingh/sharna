#pragma once

#include "../header.h"
struct _sharna_vm_s;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_cmp_rv (struct _sharna_vm_s *_VM, char _R1, char _V1);
  SH_API void sh_cmp_rr (struct _sharna_vm_s *_VM, char _R1, char _R2);
  SH_API void sh_cmp_byte_r_v (struct _sharna_vm_s *_VM, char _R1, char _R2);
  SH_API void sh_cmp_byte_r_r (struct _sharna_vm_s *_VM, char _R1, char _R2);

#if defined(__cplusplus)
}
#endif
