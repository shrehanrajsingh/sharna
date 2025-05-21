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
  R_SF, /* status flag */
  R_R0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
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

static const char *REGNAMES[]
    = { "A",  "B",  "C",  "D",  "E",  "F",  "SF", "R0",
        "R1", "R2", "R3", "R4", "R5", "R6", "R7", NULL };