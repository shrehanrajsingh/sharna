#pragma once

#include "../header.h"
#include "../rom/rom.h"

#define RAM_SIZE (1 << 16)

typedef struct
{
  uint8_t v[RAM_SIZE];
  uint16_t l;

  struct
  {
    uint16_t p_data, p_text, stack, heap;

  } offsets;

} ram_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API ram_t sh_ram_new (void);
  SH_API void sh_ram_reset_offsets (ram_t *, rom_t *);
  SH_API void sh_ram_reset_offsets_m (ram_t *_Ram, uint16_t _pt, uint16_t _pd,
                                      uint16_t _heap, uint16_t _st);
  SH_API void sh_ram_load (ram_t *_Ram, char *_Data, int _From, int _To);
  SH_API void sh_ram_load_u (ram_t *_Ram, uint8_t *_Data, int _From, int _To);
  SH_API void sh_ram_push (ram_t *_Ram, uint8_t _Val);

#if defined(__cplusplus)
}
#endif
