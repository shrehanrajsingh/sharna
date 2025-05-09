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
        mov A, 1            ; IO
        mov B, 1            ; stdout
        mov C, msg          ; msg
        mov D, 22           ; msglen
        int
        je end