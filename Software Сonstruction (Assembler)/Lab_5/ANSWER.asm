.stack 100h

.data
    array dw 5,2,3,4,5,15,7,8,9,10;,11,12,13,14,15,75,75,18,19,20
    space db ' ', '$'
    newline db 13,10,'$'     
    count dw 0           

.code
start:
    MOV AX, @data          
    MOV DS, AX

    LEA SI, array
    MOV CX, 10

next:
    MOV AX, [SI]
    CALL check_multiple      
    ADD SI, 2
    LOOP next

    MOV AH, 9
    LEA DX, newline
    INT 21h

    MOV AX, count
    CALL print_num

    MOV AH, 4Ch
    INT 21h

check_multiple proc
    PUSH AX                 
    MOV BX, 5
    XOR DX, DX
    DIV BX                  
    POP AX                   
    CMP DX, 0
    JNE not_multiple
    
    CALL print_num
    MOV AH, 9
    LEA DX, space
    INT 21h
    INC count 
               
not_multiple:
    RET          
    
check_multiple endp

print_num proc
    CMP AX, 10
    JB one_digit
    XOR DX, DX
    MOV BX, 10
    DIV BX                
    PUSH DX 
    
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    
    POP DX
    ADD DL, '0'
    MOV AH, 02h
    INT 21h
    RET   
    
one_digit:
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    RET
    
print_num endp

end start