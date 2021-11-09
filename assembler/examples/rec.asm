in
pop ax ; get the number

push 0
pop bx ; make the counter 0

push 1
pop cx ; make the mnozhitel 1

push 1 ; make the start for factorial 1
pop dx

call Factorial:

hlt

Factorial:
    push cx
    push dx
    mul
    pop dx

    push cx
    push 1
    add
    pop cx

    push bx
    push 1
    add
    pop bx

    push ax
    push bx

    jb Factorial:
    
    push dx
    print 
    ret
    

