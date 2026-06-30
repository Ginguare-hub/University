.stack 100h

.data
    array dw 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,105,20
    msg db 'Answers: $'          
    space db ' $'                
    newline db 13,10,'$'         

.code

print_num 
    PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX, 0        
    MOV BX, 10
           
convert:
    XOR DX, DX
    DIV BX             
    ADD DL, '0'
    PUSH DX
    INC CX
    TEST AX, AX
    JNZ convert  
    
print_digits:
    POP DX
    MOV AH, 02h
    INT 21h
    LOOP print_digits
    POP DX
    POP CX
    POP BX
    POP AX
    RET
print_num 
    ENDP

start:
    MOV AX, @data
    MOV DS, AX

    
    MOV AH, 09h
    LEA DX, msg
    INT 21h

    LEA SI, array      
    MOV CX, 20        

check_next:
    LODSW              
    PUSH AX            
    MOV BL, 5
    DIV BL              
    CMP AH, 0
    JNE not_multiple

  
    POP AX             
    CALL print_num

   
    MOV AH, 09h
    LEA DX, space
    INT 21h

    JMP next_element

not_multiple:
    POP AX             
next_element:
    LOOP check_next

    MOV AH, 09h
    LEA DX, newline
    INT 21h

    MOV AH, 4ch
    INT 21h

END start