%icl "tests/other.sp"

section .text
    mov A, 1
    mov B, 1
    mov C, othermsg
    mov D, 17
    int 1
    hlt