; Standard Sharna Library (SSL)
; I cannot call my standard library SSL (for obvious reasons)
; Therefore, here it is, Sharna's Standard Library (STD/SSL)
; date: Saturday, May 17
; time: 06:28 PM
; "Everyone and everything is an object, but who/what do we initialize from?"

; writelen routine prints N characters
; to console
; Both message and message length need to be
; passed
; Register C -> Message
; Register D -> Message length
; writelen (Message, Message Length)
;            push1       push2
section .text
writelen:
    ; preserve SP
    pop E
    pop F

    pop D
    pop C
    
    ; preserve A
    push A
    ; preserve B
    push B

    mov A, 1
    mov B, 1
    int 1

    ; restore B
    pop B
    ; restore A
    pop A

    ; restore stack
    push F
    push E
    ret