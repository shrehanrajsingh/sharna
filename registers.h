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
  R_SF,   /* status flag */
  R_8bit, /* number of 8 bit registers */
  R_PC = 0,
  R_SP = 1,
  R_16bit /* total number of registers */
};

enum
{
  REG_TYPE_8,
  REG_TYPE_16
};

enum
{
  REG_SF_CF = 0b00000001,
  REG_SF_PF = 0b00000010,
  REG_SF_AF = 0b00000100,
  REG_SF_ZF = 0b00001000,
  REG_SF_SF = 0b00010000,
  REG_SF_OF = 0b00100000,
  REG_SF_UDF1 = 0b01000000,
  REG_SF_UDF2 = 0b10000000
};

static const char *REGNAMES[] = { "A", "B", "C", "D", "E", "F", "SF", NULL };