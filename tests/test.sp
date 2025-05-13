section .data
msg:
    db "Hello, World!", 0

section .text
    push msg
    mov A, 1
    mov B, 1
    pop C
    mov D, 13
    int 1
    hlt