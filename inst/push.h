#pragma once

#include "../header.h"
struct _sharna_vm_s;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_push_v (struct _sharna_vm_s *_VM, char _B);
  SH_API void sh_push_r (struct _sharna_vm_s *_VM, char _R);

#if defined(__cplusplus)
}
#endif
