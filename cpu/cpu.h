#pragma once

#include "../header.h"
#include "../registers.h"

typedef struct
{
  uint8_t reg_8[R_8bit];
  uint16_t reg_16[R_16bit];

} cpu_t;

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API cpu_t sh_cpu_new (void);

#if defined(__cplusplus)
}
#endif
