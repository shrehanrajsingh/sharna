#include "interrupt.h"

SH_API void
sh_int_sys_io_write (void *fs, uint8_t *msg, uint8_t mlen)
{
  while (mlen-- > 0)
    fputc (*msg++, (FILE *)fs);
}

SH_API void
sh_int_sys_io_read (void *fs, uint8_t *msgbuf, uint8_t bttoread)
{
  while (bttoread-- > 0)
    *msgbuf++ = (uint8_t)fgetc ((FILE *)fs);
}