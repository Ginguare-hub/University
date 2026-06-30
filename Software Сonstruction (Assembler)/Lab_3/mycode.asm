.model small
.stack 100h

.code
begin:
    MOV AX, @data
    MOV DS, AX
   
    MOV AH, 9
    MOV DX, OFFSET Msg
    INT 21h  
    
    MOV AH, 2
    MOV DL, 07h    
    INT 21h

    MOV AH, 4Ch
    INT 21h

.data
    Msg  DB 'Hello', 0DH, 0AH, 'World!$'
    
END begin
