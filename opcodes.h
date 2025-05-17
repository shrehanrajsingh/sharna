#pragma once

#include "header.h"

enum
{
  MOV_rv, /* mov to a register, a constant value */
  MOV_rr, /* mov to a register, a value in a register */
  ADD_rv, /* add to a register, a constant value. Store result in first
             register */
  ADD_rr, /* add to a register, a value stored in a register. Store result in
             first register */
  PUSH_r, /* push the value in a register to stack */
  PUSH_v, /* push a constant value to a register */
  POP_r,  /* pop the value of a stack to a register */
  HLT,    /* end of program */
  INTERRUPT, /* interrupt */
  CMP_rv,    /* compare a value in a register with a constant value */
  CMP_rr, /* compare a value in a register with a value in another register */
  CMP_byte_r_v, /* compare byte in a memory location stored in a register to a
                   constant value */
  CMP_byte_r_r, /* compare a byte in a memory location stored in a register to
                   a value stored in another register */
  JE_v,  /* jump to a constant value address if SF.ZF = 1, 2-byte jump */
  JNE_v, /* jump to a constant value address if SF.ZF != 1, 2-byte jump */
  SJE_v, /* JE_v but 1-byte jump */
  SJE_r, /* JE_r but 1-byte jump */
  JC_v,  /* jump to a constant value address if SF.CF = 1, 2-byte jump */
  JC_r, /* jump to an address contained in a register if SF.CF = 1, 2-byte jump
         */
  JMP_v,  /* jump to memory address, 2-byte jump */
  CALL_v, /* move control to memory address at v, 2-byte jump */
  RET,    /* return control */
  SUB_rv, /* subtract from a register, a constant value. Store result in first
             register */
  SUB_rr, /* subtract from a register, a value in another register. Store
             result in first register */
  INC_r,  /* incremenet value in a register by 1 */
  DEC_r,  /* decrement value in a register by 1 */
  NOI     /* number of instructions */
};

#define MOV (MOV_rv)
#define ADD (ADD_rv)
#define PUSH (PUSH_r)
#define POP (POP_r)
#define CMP (CMP_rv)
#define JE (JE_v)
#define JNE (JNE_v)
#define SJE (SJE_v)
#define JC (JC_v)
#define JMP (JMP_v)
#define CALL (CALL_v)
#define SUB (SUB_rv)
#define INC (INC_r)
#define DEC (DEC_r)

static const char *INST_3B[]
    = { "mov", "add", "cmp", "je", "jc", "jne", "jmp", "call", "sub", NULL };
static const char *INST_2B[]
    = { "push", "pop", "sje", "int", "inc", "dec", NULL };
static const char *INST_1B[] = { "hlt", "ret", NULL };