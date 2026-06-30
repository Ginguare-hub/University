.stack 100h

.data
    str     db "hello world programming in assembler is very hard", 0Dh, 0Ah, '$'
    ;buffer  db 200 dup(?)
    words   dw 50 dup(0)   
    lengths dw 50 dup(0)   
    count   dw 0           
    msg     db 0Dh, 0Ah, "Sorted string:", 0Dh, 0Ah, '$'

.code

start:
    MOV AX, @data
    MOV DS, AX
    ;MOV ES, AX
    
    ;MOV SI, OFFSET str
    LEA SI, str 
    ;MOV DI, OFFSET words
    LEA DI, words 
    ;MOV BX OFFSET lengths
    LEA BX, lengths
    MOV word ptr count, 0
  
  ;Find first symphol of new word
find_words:
    MOV AL, [si]
    CMP AL, '$'
    JE  end_find
    CMP AL, 0Dh
    JE  end_find
    CMP Al, ' '
    JNE is_word_start

    INC SI
    JMP find_words

is_word_start:
    MOV [DI], SI  
    ADD DI, 2

    XOR CX, CX ; Cx now equals 0  
    
count_length:
    MOV AL, [SI]
    CMP AL, ' '
    JE  end_of_word
    CMP AL, 0Dh
    JE  end_of_word
    CMP AL, '$'
    JE  end_of_word
    INC CX
    INC SI
    JMP count_length

end_of_word:
    MOV [BX], CX      
    ADD BX, 2
    INC word ptr count
    JMP find_words

end_find:
    MOV CX, count
    DEC CX       

bubble_outer:
    PUSH CX
    LEA DI, lengths
    LEA SI, words
    MOV BX, 0           

bubble_inner:
    MOV AX, [DI]          
    MOV DX, [DI+2]       

    CMP AX, DX
    JBE no_swap          
 
    XCHG AX, DX
    MOV [DI], AX
    MOV [DI+2], DX

    MOV AX, [SI]
    MOV DX, [SI+2]
    XCHG AX, DX
    MOV [SI], AX
    MOV [SI+2], DX

no_swap:
    ADD DI, 2
    ADD SI, 2
    INC DX
    LOOP bubble_inner

    POP CX
    LOOP bubble_outer

    MOV AH, 9
    LEA DX, msg
    INT 21h

    LEA SI, words
    MOV CX, count

print_loop:
    PUSH CX
    MOV DI, [SI]     
    MOV BX, [SI + offset lengths - offset words]

print_word:
    MOV AL, [DI]
    CMP AL, ' '
    JE  print_space
    CMP AL, 0Dh
    JE  print_space
    CMP AL, '$'
    JE  print_space

    MOV AH, 2
    MOV DL, AL
    INT 21h

    INC DI
    DEC BX
    JNZ print_word

print_space:
    MOV AH, 2
    MOV DL, ' '
    INT 21h

    ADD SI, 2
    POP CX
    LOOP print_loop

    MOV AH, 4Ch
    INT 21h

end start