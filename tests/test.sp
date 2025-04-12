section .data
msg: db "Hello, World!", 0

section .text
mov A, 10
mov B, 20
mov C, 30
add A, B
add B, C
hlt