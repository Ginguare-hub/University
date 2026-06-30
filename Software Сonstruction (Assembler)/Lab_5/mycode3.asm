.stack 100h

.data
    array dw 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
    space db ' ', '$'  

.code
start:
    MOV AX, @data
    MOV DS, AX

    LEA SI, array       
    MOV CX, 20         

next:
    MOV AX, [SI]     
    CALL print_num    

    MOV AH, 9
    LEA DX, space
    INT 21h

    ADD SI, 2         
    LOOP next          

    MOV AH, 4Ch
    INT 21h

print_num proc
    CMP AX, 10
    JB one_digit

   
    XOR DX, DX
    MOV BX, 10
    DIV BX             
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 02h
    INT 21h        
    ADD AH, '0'
    MOV DL, AH
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