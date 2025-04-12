#pragma once

#include "../header.h"
struct _sharna_vm_s;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_add_rv (struct _sharna_vm_s *_VM, char _R1, char _V);
  SH_API void sh_add_rr (struct _sharna_vm_s *_VM, char _R1, char _R2);

#if defined(__cplusplus)
}
#endif
