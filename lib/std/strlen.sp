; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD/SSL)
; date: Saturday, May 17
; time: 08:28 PM
; "I like Dove's eyes"

section .text
strlen:
    ; preserve SP
    pop E
    pop F

    ; preserve B
    push B

    ; store the message in A
    pop A
    mov B, A
__strlen_label_stlp:
    cmp [A], 0
    je __strlen_label_endif

    inc A
    jmp __strlen_label_stlp

__strlen_label_endif:
    sub A, B
    ; restore B
    pop B
    ; restore SP
    push F
    push E
    ret