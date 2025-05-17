section .data
msg:
    db "Hello, World!", 0

section .text
    push msg
    call test
    hlt

test:
    ; preserve PC
    pop E
    pop F

    pop C
    mov A, 1
    mov B, 1
    mov D, 13
    int 1

    ; restore PC
    push F
    push E
    ret