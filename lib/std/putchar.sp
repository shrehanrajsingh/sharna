; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD/SSL)
; date: Friday, May 9
; time: 11:55 PM
; "At my lowest, I will code"

; assume program counter will
; be stored by VM in the Gulag
; when putchar is called using `call`
putchar:
    pop C           ; character to print is stored on stack
    mov A, 1        ; IO
    mov B, 1        ; STDOUT
    mov D, 1        ; msglen
    int 1           ; interrupt
    ret             ; give back control to OG memory