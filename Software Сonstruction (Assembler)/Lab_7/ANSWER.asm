.model small
.stack 100h
.data
    prompt   db  'Vvedite stroku $'
    labelOne db  '1: $'
    labelTwo db  '2: $'
    newline  db  0Dh, 0Ah, '$'
    buffer1  db  50, 0, 50 dup(0)
    buffer2  db  50, 0, 50 dup(0)
    msgEqual    db 'Stroki ravny$'
    msgNotEqual db 'Stroki ne ravny$'

.code
start:
    mov ax, @data
    mov ds, ax
    mov es, ax         

    ; write prompt
    mov ah, 09h
    lea dx, prompt
    int 21h

    mov ah, 09h
    lea dx, labelOne
    int 21h
           
    ; get first word
    mov ah, 0Ah
    lea dx, buffer1
    int 21h

    mov ah, 09h
    lea dx, newline
    int 21h

    ; write prompt
    mov ah, 09h
    lea dx, prompt
    int 21h

    mov ah, 09h
    lea dx, labelTwo
    int 21h
           
    ; get second word
    mov ah, 0Ah
    lea dx, buffer2
    int 21h

    mov ah, 09h
    lea dx, newline
    int 21h

    ; change Enter to '$'
    lea bx, buffer1+2
    mov cl, buffer1[1]
    mov ch, 0 
    lea bx, buffer1+2
    mov cl, buffer1[1]
    mov ch, 0
    mov si, cx                  
    mov byte ptr [bx+si], '$'  

    lea bx, buffer2+2
    mov cl, buffer2[1]
    mov ch, 0
    lea bx, buffer2+2
    mov cl, buffer2[1]
    mov ch, 0
    mov si, cx
    mov byte ptr [bx+si], '$'

    ; write both words
    mov ah, 09h
    lea dx, buffer1+2
    int 21h

    mov ah, 09h
    lea dx, newline
    int 21h

    mov ah, 09h
    lea dx, buffer2+2
    int 21h

    mov ah, 09h
    lea dx, newline
    int 21h

    ; compare length
    mov al, buffer1[1]
    cmp al, buffer2[1]
    jne not_equal

    ; compare words by using operator CMPSB
    lea si, buffer1+2   
    lea di, buffer2+2   
    mov cl, buffer1[1]  
    mov ch, 0

    cld ; DF = 0 so -> direction of reading string                
    repe cmpsb         
    je equal      

not_equal:
    mov ah, 09h
    lea dx, newline
    int 21h
    mov ah, 09h
    lea dx, msgNotEqual
    int 21h
    jmp done

equal:
    mov ah, 09h
    lea dx, newline
    int 21h
    mov ah, 09h
    lea dx, msgEqual
    int 21h

done:
    mov ah, 4Ch
    mov al, 0
    int 21h

end start