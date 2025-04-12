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
    inst/inst.h
    sharna.h sharna.c)

