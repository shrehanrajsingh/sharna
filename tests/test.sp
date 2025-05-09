section .data
    msg:
        db "Two values are equal!\n"

section .text

    mov A, 10
    mov B, 10
    cmp A, B
    je print_msg

    end:
        hlt

    print_msg:
        mov A, 1
        mov B, 1
        mov C, msg
        mov D, 22
        int
        je end