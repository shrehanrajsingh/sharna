section .data
__ps_msg:
    db "This is a test message"

section .text
print:
    mov A, 1
    mov B, 1
    int 1
    jmp end