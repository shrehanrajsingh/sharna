; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD)
; date: Friday, May 9
; time: 11:55 PM
; "At my lowest, I will code"

; Standard puts expects strings to 
; end with 0.
; Message to print is stored in stack
puts:
    pop C           ; message is stored on stack
    mov D, C        ; char *D = (char *) C
    cmp D, 0        ; if (*D == '\0')
    l1:
        inc D       ; D++;
    je l1           ; goto l1;
    sub D, C        ; D -= C; // String length
    mov A, 1
    mov B, 1
    int 1
    ret