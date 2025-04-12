#pragma once

#include "header.h"

enum
{
  R_A,
  R_B,
  R_C,
  R_D,
  R_E,
  R_F,
  R_8bit, /* number of 8 bit registers */
  R_PC = 0,
  R_16bit /* total number of registers */
};

enum
{
  REG_TYPE_8,
  REG_TYPE_16
};

static const char *REGNAMES[] = { "A", "B", "C", "D", "E", "F" };