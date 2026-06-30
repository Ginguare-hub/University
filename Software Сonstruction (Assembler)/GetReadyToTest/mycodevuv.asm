.model small
.stack 100h

.code
start:
    mov ax, 0B800h
    mov es, ax

    xor di, di          ; позиция в видеопамяти
    xor cx, cx          ; счётчик в строке

    mov bl, 0           ; ASCII-код

next_char:
    mov al, bl
    mov ah, 07h         ; атрибут

    mov es:[di], ax

    add di, 2           ; следующий экранный символ

    inc bl
    inc cl

    cmp cl, 16
    jne same_line

    ; переход на новую строку
    xor cl, cl

    ; 80 символов * 2 байта = 160 байт на строку
    ; уже вывели 16 символов (=32 байта)
    add di, 128         ; 160 - 32

same_line:
    cmp bl, 0
    jne next_char       ; после 255 -> 0

    mov ah, 00h
    int 16h             ; ожидание клавиши

    mov ax, 4C00h
    int 21h

end start