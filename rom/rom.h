#pragma once

#include "../header.h"

#define ROM_SIZE (1 << 16)

typedef struct
{
  uint8_t v[ROM_SIZE];
  uint16_t l;

} rom_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API rom_t sh_rom_new (void);
  SH_API void sh_rom_push (rom_t *_Rom, uint8_t _V);

#if defined(__cplusplus)
}
#endif
