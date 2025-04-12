#pragma once

#include "cpu/cpu.h"
#include "header.h"
#include "inst/inst.h"
#include "opcodes.h"
#include "ram/ram.h"
#include "registers.h"
#include "rom/rom.h"

typedef struct _sharna_vm_s
{
  cpu_t cpu;
  ram_t ram;
  rom_t rom;
} vm_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API vm_t sh_vm_new (void);
  SH_API void sh_vm_run (vm_t *_VM);

#if defined(__cplusplus)
}
#endif
