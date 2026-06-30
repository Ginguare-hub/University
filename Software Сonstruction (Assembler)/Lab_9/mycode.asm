.model small

.stack 100h

.code

start:
    mov ax, 0013h
    int 10h

    mov ax, 0A000h
    mov es, ax

    ; 4 линии = прямоугольник (контур дома)
    ; Верх:  Y=50, X=100..139
    mov di, 16100      ; 50*320 + 100
    mov cx, 20
    mov ax, 0F08h
    rep stosw

    ; Низ:  Y=100, X=100..139
    mov di, 32100      ; 100*320 + 100
    mov cx, 20
    rep stosw

    ; Лево: X=100, Y=50..100
    mov bx, 50
left:
    mov ax, bx
    mov dx, 320
    mul dx
    add ax, 100
    mov di, ax
    mov byte ptr es:[di], 15
    inc bx
    cmp bx, 101
    jl  left

    ; Право: X=139, Y=50..100
    mov bx, 50
right:
    mov ax, bx
    mov dx, 320
    mul dx
    add ax, 139
    mov di, ax
    mov byte ptr es:[di], 15
    inc bx
    cmp bx, 101
    jl  right

    mov ah, 0
    int 16h

    mov ax, 0003h
    int 10h
    mov ax, 4C00h
    int 21h

END start