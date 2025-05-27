section .data

; TODO
; Implement
section .text
    ; loadsp is an instruction that
    ; takes the values in SP register (16 bit)
    ; and puts it into two 8 bit registers
    ; E and F
    ; The MSB depends on the architecture of the system
    ; Big Endian --> E is the MSB
    ; Little Endian --> F is the MSB
    loadsp

    ; shift MSB to E
%if eq _ARCH "little-endian"
    add E, F
    sub F, E
    add E, F
%endif
    mov A, E
    sub A, 32           ; char arr[4]
    mov [A], 48         ; arr[0] = '0'
    mov [A + 8], 49     ; arr[1] = '1'
    mov [A + 16], 50    ; arr[2] = '2'
    mov [A + 24], 51    ; arr[3] = '3'

    ; print message
    push A
    mov A, 1
    mov B, 1
    pop C
    mov D, 4
    int 1

; Another approach
; use SP
    sub16 SP, 32            ; char arr[4]
    mov16 [SP], 48          ; arr[0] = '0'
    mov16 [SP + 8], 49      ; arr[1] = '1'
    mov16 [SP + 16], 50     ; arr[2] = '2'
    mov16 [SP + 24], 51     ; arr[3] = '3'

; Default interrupt 1 takes message address
; in C register, but it cannot take addresses above 255
; so we cannot refer to addresses in SP to C
; What can be an alternate to this that supports 16 bit addresses?
; One solution, use 16 bit interrupt version which uses two registers
; to store memory addresses (C and D). Use E to store length
; Another solution is to use stack to read `n` bytes, n is stored in D

    mov A, 1
    mov B, 1
    mov D, 4
; note the `s` in ints
; s denotes reading from stack
    ints 1

    hlt