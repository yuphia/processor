in
pop ax

in
pop bx

in
pop cx ; getting a b c coefficients

call Lin:

SqrCall:

call Discr:

pop dx
push 0 
push dx
jae sqrtHere:

WrongCoeffs:
END:

hlt

Discr:
    push 4
    push ax ; b^2  4a
    mul

    push cx
    mul 

    push bx
    push bx
    mul ; b^2
   
    sub ; b^2 - 4ac 
    pop dx
    push dx 
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;
Lin:
    push ax
    push 0    
 
    jne SqrCall:
    

    push bx
    push 0

    je WrongCoeffsPrint:   
    
    push bx 

    push cx    
    print

    push cx    
    push -1
    mul

    div
    print
    jmp END:

;;;;;;;;;;;;;;;;;;;;;;;;;;;
WrongCoeffsPrint:
    ;push cx
    ;print
    push cx
    push 0
    je INFSOL:

    jmp WrongCoeffs:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Sqr:
    ret

INFSOL:
push 1
push 2
push 3
print
print
print

hlt

sqrtHere:
    push dx
    sqrt
    pop dx
       
;;;;;;;;;;;
       
    push ax
    push 2
    mul

    push dx
    push -1
    mul

    push bx
    push -1
    mul
    add
        
    div
    print
;;;;;;;;;;;;;;;;;
    push ax
    push 2
    mul

    push dx
    push bx
    push -1
    mul
    
    add
    
    div
    print

    hlt

