#pragma once

#include "header.h"

enum
{
  MOV_rv, /* mov to a register, a constant value */
  MOV_rr, /* mov to a register, a value in a register */
  ADD_rv, /* add to a register, a constant value */
  ADD_rr, /* add to a register, a value stored in a register */
  PUSH_r, /* push the value in a register to stack */
  PUSH_v, /* push a constant value to a register */
  POP_r,  /* pop the value of a stack to a register */
  HLT,    /* end of program */
  NOI     /* number of instructions */
};

#define MOV (MOV_rv)
#define ADD (ADD_rv)
#define PUSH (PUSH_r)
#define POP (POP_r)