; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD/SSL)
; date: Friday, May 9
; time: 11:55 PM
; "At my lowest, I will code"

; Standard puts expects strings to 
; end with 0.
; Message to print is stored in stack
puts:
    pop C           ; message on stack is now in C
    mov D, C        ; char *D = (char *) C
    l1:
    cmp D, 0
    je l2           ; if (*D == '\0') goto l2
    inc D           ; D++
    jmp l1          ; goto l1
    sub D, C        ; D -= C

    l2:
        mov A, 1    ; write
        mov B, 1    ; stdout
        int 1       ; IO
    
    ret