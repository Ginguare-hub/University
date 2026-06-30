.model small
.stack 100h

.code

start:
    mov ax, 0013h  
    int 10h

    mov ax, 0A000h    
    mov es, ax

    ; ГТрава
    mov al, 10         ; цвет зел
    mov di, 320*150   
    mov cx, 320      
    rep stosb       
    
    ; ВСтена1
    mov cx, 80        ; X
    mov dx, 60        ; Y 
    mov bp, 85        ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down1: 
    mov al, 6          ; цвет кор 
    mov es:[di], al   
    add di, 320     
    dec bp
    jnz draw_down1 
    
    ; ВСтена2
    mov cx, 240       ; X
    mov dx, 60        ; Y 
    mov bp, 85        ; Длина


    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down2:    
    mov al, 6          ; цвет кор
    mov es:[di], al    
    add di, 320       
    dec bp
    jnz draw_down2 
    
    
    
    ; ГПотолок 
    mov cx, 80       ; X
    mov dx, 60       ; Y 
    mov si, 160     ; Длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 6       ; цвет кор

    mov cx, si       
    rep stosb  
    
    
    ; ГОкно1
    mov cx, 170      ; X
    mov dx, 85       ; Y 
    mov si, 50       ; Длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 11         ; цвет голубой

    mov cx, si       
    rep stosb    
    
    ; ГОкно2
    mov cx, 170       ; X
    mov dx, 100       ; Y 
    mov si, 50        ; Длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 11         ; Цвет 

    mov cx, si       
    rep stosb
    
    ; ГОкно3
    mov cx, 170       ; X
    mov dx, 115       ; Y 
    mov si, 50        ; длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 11         ; цвет кор 

    mov cx, si       
    rep stosb 
    
    
    
    ; ВОкно1
    mov cx, 170       ; X
    mov dx, 85        ; Y 
    mov bp, 30        ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down3: 
    mov al, 11         ; цвет кор
    mov es:[di], al   
    add di, 320       
    dec bp
    jnz draw_down3  
    
     ; ВОкно2
    mov cx, 195        ; X
    mov dx, 85        ; Y 
    mov bp, 30         ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down4: 
    mov al, 11          ; цвет кор 
    mov es:[di], al   
    add di, 320        
    dec bp
    jnz draw_down4
    
    
     ; ВОкно3
    mov cx, 220        ; X
    mov dx, 85         ; Y 
    mov bp, 30         ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down5: 
    mov al, 11         ; цвет 
    mov es:[di], al    ; рисуем пиксель
    add di, 320        ; идём вниз на следующую строку
    dec bp
    jnz draw_down5 
    
    
     ; ВДверь1
    mov cx, 140       ; X
    mov dx, 85        ; Y 
    mov bp, 60        ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down6: 
    mov al, 6          ; цвет кор 
    mov es:[di], al   
    add di, 320     
    dec bp
    jnz draw_down6   
    
     ; ВДверь2
    mov cx, 100       ; X
    mov dx, 85        ; Y 
    mov bp, 60        ; Длина

    mov ax, dx        
    mov bx, 320
    mul bx            
    add ax, cx      
    mov di, ax

draw_down7: 
    mov al, 6          ; цвет кор
    mov es:[di], al   
    add di, 320       
    dec bp
    jnz draw_down7 
    
    ; ГДверь1
    mov cx, 100      ; X
    mov dx, 85       ; Y 
    mov si, 40       ; Длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 6         ; цвет кор

    mov cx, si       
    rep stosb   
    
    ; ГРучка
    mov cx, 130      ; X
    mov dx, 115      ; Y 
    mov si, 3        ; Длина 

    mov ax, dx
    mov bx, 320
    mul bx             
    add ax, cx       
    mov di, ax
    
    mov al, 12         ; Цвет красн 

    mov cx, si       
    rep stosb                                    

    mov ax, 4C00h
    int 21h

end start