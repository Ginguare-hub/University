.stack 100h

.data
    array dw 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
    
.code
    
start:
    MOV AX, @data
    MOV DS, AX
    
    LEA BX, array
    
    XOR CX, CX 
    
    MOV DL, 5
    MOV AL, [BX]  
    XOR AH, AH
    DIV DL
    
    CMP AH, 0
    JE is_multiple
    
    INC CX 
    
is_multiple:
    LEA DX, A
    INT 21h
    
    
end start 