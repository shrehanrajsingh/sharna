#pragma once

#include "../header.h"

enum SysCall
{
  SC_IO = 1,
  SC_NUMCALLS
};

enum IOFstream
{
  IOFS_STDOUT = 1,
  IOFS_STDIN = 2,
  IOFS_CUST = 3
};

enum IOCall
{
  SC_IO_WRITE = 1,
  SC_IO_READ = 2
};

#if defined(__cplusplus)
extern "C"
{
#endif

  SH_API void sh_int_sys_io_write (void *_fs, uint8_t *_Msg, uint8_t _MsgLen);
  SH_API void sh_int_sys_io_read (void *_fs, uint8_t *_MsgBuf,
                                  uint8_t _BytesToRead);

#if defined(__cplusplus)
}
#endif
