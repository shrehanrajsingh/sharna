#pragma once

#include "header.h"

enum
{
  MOV_rv = 0, /* mov to a register, a constant value */
  MOV_rr = 1, /* mov to a register, a value in a register */
  ADD_rv = 2, /* add to a register, a constant value. Store result in first
             register */
  ADD_rr = 3, /* add to a register, a value stored in a register. Store result
             in first register */
  PUSH_r = 4, /* push the value in a register to stack */
  PUSH_v = 5, /* push a constant value to a register */
  POP_r = 6,  /* pop the value of a stack to a register */
  HLT = 7,    /* end of program */
  INTERRUPT = 8, /* interrupt */
  CMP_rv = 9,    /* compare a value in a register with a constant value */
  CMP_rr
  = 10, /* compare a value in a register with a value in another register */
  CMP_byte_r_v = 11, /* compare byte in a memory location stored in a register
                   to a constant value */
  CMP_byte_r_r = 12, /* compare a byte in a memory location stored in a
                   register to a value stored in another register */
  JE_v = 13,  /* jump to a constant value address if SF.ZF = 1, 2-byte jump */
  JNE_v = 14, /* jump to a constant value address if SF.ZF != 1, 2-byte jump */
  SJE_v = 15, /* JE_v but 1-byte jump */
  SJE_r = 16, /* JE_r but 1-byte jump */
  JC_v = 17,  /* jump to a constant value address if SF.CF = 1, 2-byte jump */
  JC_r
  = 18, /* jump to an address contained in a register if SF.CF = 1, 2-byte jump
         */
  JMP_v = 19,  /* jump to memory address, 2-byte jump */
  CALL_v = 20, /* move control to memory address at v, 2-byte jump */
  RET = 21,    /* return control */
  SUB_rv = 22, /* subtract from a register, a constant value. Store result in
             first register */
  SUB_rr = 23, /* subtract from a register, a value in another register. Store
             result in first register */
  INC_r = 24,  /* incremenet value in a register by 1 */
  DEC_r = 25,  /* decrement value in a register by 1 */
  XOR_rr = 26, /* xor the value in register with a value in another register.
                  Store the result in the first register */
  NOI          /* number of instructions */
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
#define XOR (XOR_rr)

static const char *INST_3B[] = { "mov", "add",  "cmp", "je",  "jc", "jne",
                                 "jmp", "call", "sub", "xor", NULL };
static const char *INST_2B[]
    = { "push", "pop", "sje", "int", "inc", "dec", NULL };
static const char *INST_1B[] = { "hlt", "ret", NULL };