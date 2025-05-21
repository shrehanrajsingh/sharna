%icl "lib/std/input.sp"
%icl "lib/std/puts.sp"
%icl "lib/std/writelen.sp"

section .data
msg:
    ; 20 byte buffer
    times 20 db 0

text:
    db "Enter your name: ", 0

section .text
    push text
    push 17
    call writelen

    mov A, msg

stblk:
    push R0
    push 1
    call input

    cmp [R0], 10
    je end

    inc R0
    jmp stblk

end:
    push msg
    call puts
    hlt