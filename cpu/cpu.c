#include "cpu.h"

SH_API cpu_t
sh_cpu_new (void)
{
  cpu_t c;

  for (char i = 0; i < R_8bit; ++i)
    c.reg_8[i] = 0;

  for (char i = 0; i < R_16bit; ++i)
    c.reg_16[i] = 0;

  return c;
}