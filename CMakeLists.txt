cmake_minimum_required(VERSION 3.10.0)
project(sharna VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)

add_library(sharna
    header.h
    registers.h
    opcodes.h
    shmalloc.h shmalloc.c

    cpu/cpu.h cpu/cpu.c
    ram/ram.h ram/ram.c
    rom/rom.h rom/rom.c
    vm.h vm.c

    inst/mov.h inst/mov.c
    inst/add.h inst/add.c
    inst/interrupt.h inst/interrupt.c
    inst/je.h inst/je.c
    inst/jne.h inst/jne.c
    inst/cmp.h inst/cmp.c
    inst/jmp.h inst/jmp.c
    inst/push.h inst/push.c
    inst/pop.h inst/pop.c
    inst/call.h inst/call.c
    inst/ret.h inst/ret.c
    inst/sub.h inst/sub.c
    inst/inc.h inst/inc.c
    inst/dec.h inst/dec.c
    inst/xor.h inst/xor.c
    inst/inst.h

    assembler/strutils.h assembler/strutils.c
    assembler/shasm.h assembler/shasm.c
    assembler/ctx.h assembler/ctx.c
    assembler/tok.h assembler/tok.c
    assembler/ast.h assembler/ast.c
    assembler/codegen.h assembler/codegen.c
    assembler/quickparser.h assembler/quickparser.c

    sharna.h sharna.c)

