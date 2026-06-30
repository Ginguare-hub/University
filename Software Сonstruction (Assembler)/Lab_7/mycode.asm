.model small

.stack 100h
.data
    prompt  db  'Vvedite stroku $'
    labelOne db '1: $'
    labelTwo db '2: $'
    newline db 0Dh, 0Ah, '$'
    buffer1 db 50, 0, 50 dup(0)        
            ; максимум 49 символов + Enter
            ; сюда DOS запишет реальную длину
            ; сам буфер под символы 
    buffer2 db  50, 0, 50 dup(0)  

.code
start:
    mov ax, @data
    mov ds, ax

    ; --- Вывод приглашения ---
    mov ah, 09h
    lea dx, prompt
    int 21h
    
    mov ah, 09h
    lea dx, labelOne
    int 21h

    ; --- Чтение строки (INT 21h / AH=0Ah) ---
    mov ah, 0Ah
    lea dx, buffer1
    int 21h

    ; --- Перевод строки (Enter не выводится автоматически) ---
    mov ah, 02h
    mov dl, 0Ah         ; LF
    int 21h

    ; --- Теперь строка лежит в buffer+2 ---
    ; --- Длина строки в buffer+1          ---

    ; Пример: вывод введённой строки обратно
    ; Заменим 0Dh в конце на '$' для вывода через INT 21h/09h
    lea si, buffer1+2        ; SI > начало строки
    mov cl, buffer1[1]       ; CL = длина строки
    mov ch, 0
    mov si, cx
    lea bx, buffer1+2
    mov byte ptr [bx+si], '$'  ; ставим '$' после последнего символа 
    
    mov ah, 09h
    lea dx, newline
    int 21h
                           
                           
    ;====================================
    
    ; --- Вывод приглашения ---
    mov ah, 09h
    lea dx, prompt
    int 21h
    
    mov ah, 09h
    lea dx, labelTwo
    int 21h

    ; --- Чтение строки (INT 21h / AH=0Ah) ---
    mov ah, 0Ah
    lea dx, buffer2
    int 21h

    ; --- Перевод строки (Enter не выводится автоматически) ---
    mov ah, 02h
    mov dl, newline         ; LF
    int 21h

    ; --- Теперь строка лежит в buffer+2 ---
    ; --- Длина строки в buffer+1          ---

    ; Пример: вывод введённой строки обратно
    ; Заменим 0Dh в конце на '$' для вывода через INT 21h/09h
    lea si, buffer2+2        ; SI > начало строки
    mov cl, buffer2[1]       ; CL = длина строки
    mov ch, 0
    mov si, cx
    lea bx, buffer2+2
    mov byte ptr [bx+si], '$'  ; ставим '$' после последнего символа
    
    mov ah, 09h
    lea dx, newline
    int 21h
    
    mov ah, 09h
    lea dx, buffer1+2
    int 21h
    
    mov ah, 09h
    lea dx, newline
    int 21h
    
    mov ah, 09h
    lea dx, buffer2+2
    int 21h

    ; --- Выход ---
    mov ah, 4Ch
    mov al, 0
    int 21h

end start