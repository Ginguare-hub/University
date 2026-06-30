.model tiny   
 
.code 

org  100h

start:
    ;MOV AX, @data
    ;MOV DS, AX
   
    MOV AH, 9
    MOV DX, OFFSET message
    INT 21h  
    
    MOV AH, 2
    MOV DL, 07h    
    INT 21h

    ret 
    message db "Hello",0Dh,0Ah,'World!$'
end start