%icl "lib/std/strlen.sp"
%icl "lib/std/writelen.sp"

section .data
msg:
    db "Hello, World!", 0

section .text
    push msg
    call strlen
    
    push msg
    push A
    call writelen
    hlt