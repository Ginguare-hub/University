.model small
.stack 256

.data

handle DW 0
limit DW 0
line_len DW 0
count DW 0
one_byte  DB 0

fname DB 'Document1.txt', 0

msg1 DB 'Start', 0Dh, 0Ah, '$'
msg2 DB 'Result: $'
msg3 DB 0Dh, 0Ah, '$'
msg_e1 DB 'Error: open file', 0Dh, 0Ah, '$'

.code
print_str PROC
    MOV AH, 09h
    INT 21h
    RET  
    
print_str ENDP

print_num PROC
    XOR CX, CX
    MOV BX, 10
    
push_loop:
    XOR DX, DX
    DIV BX
    PUSH DX
    INC CX
    TEST AX, AX
    JNZ push_loop
    
pop_loop:
    POP DX
    ADD DL, '0'
    MOV AH, 02h
    INT 21h
    LOOP pop_loop
    RET          
    
print_num ENDP

read_byte PROC
    MOV BX, handle
    MOV CX, 1
    LEA DX, one_byte
    MOV AH, 3Fh
    INT 21h
    RET 
    
read_byte ENDP

main PROC
    MOV AX, @data
    MOV DS, AX
    ;MOV ES, AX

    LEA DX, msg1
    CALL print_str

    LEA DX, fname
    MOV AX, 3D00h
    INT 21h 
    
    JC  err_open
    MOV handle, AX

    XOR AX, AX
    MOV limit, AX
    
parse_loop:
    CALL read_byte
    CMP AX, 0
    JE  do_close
    MOV AL, one_byte
    CMP AL, 0Dh
    JE  parse_loop
    CMP AL, 0Ah
    JE  parse_done
    
    SUB AL, '0'
    XOR AH, AH
    MOV BX, 10
    PUSH AX
    MOV AX, limit
    MUL BX
    POP BX
    ADD AX, BX
    MOV limit, AX
    JMP parse_loop
    
parse_done:
    MOV line_len, 0
    MOV count, 0

next_char:
    CALL read_byte
    CMP AX, 0
    JE  eof
    MOV AL, one_byte

    CMP AL, 0Dh
    JE  next_char
    CMP AL, 0Ah
    JE  eol

    INC line_len
    JMP next_char

eol:
    MOV AX, line_len
    CMP AX, limit
    JGE reset
    INC count 
    
reset:
    MOV line_len, 0
    JMP next_char

eof:
    MOV AX, line_len
    CMP AX, 0
    JE  do_close
    CMP AX, limit
    JGE do_close
    INC count

do_close:
    MOV BX, handle
    MOV AH, 3Eh
    INT 21h

    LEA DX, msg2
    CALL print_str
    MOV AX, count
    CALL print_num
    LEA DX, msg3
    CALL print_str

    MOV AX, 4C00h
    INT 21h

err_open:
    LEA DX, msg_e1
    CALL print_str
    MOV AX, 4C01h
    INT 21h

main ENDP  

END main