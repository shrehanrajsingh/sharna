; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD/SSL)
; date: Friday, May 21
; time: 10:52 PM
; "If you love them, let them go,
; if they come back, they were always yours,
; if not, they never were"
;                           -- The most brainless, stupid quote ever

; we will assume the buffer
; location is stored on stack
; followed by buffer length
; A variant of input routine, inputAB
; will assume the buffer is stored in register A and
; buffer size is stored in register B
section .text
input:
    ; preserve PC
    pop E
    pop F

    ; pop buffer length to D
    pop D
    ; pop buffer location to C
    pop C
    ; A -> read
    mov A, 2
    ; B -> filestream: STDIN
    mov B, 2
    int 1

    ; restore PC
    push F
    push E
    ret