 	ORG   $8000

    	;Найти наименьшее и наибольшее, и поменять местами
			; Индекс наибольшего в X 
			; Индекс наименьшего в Y
			; Счётчик A, сравниваемое число B  
     
	LDAA #1
	STAA $8100
	LDAA #2
	STAA $8101
	LDAA #3
	STAA $8102
	LDAA #4
	STAA $8103
	LDAA #5
	STAA $8104
	LDAA #6
	STAA $8105
	LDAA #7
	STAA $8106
	LDAA #8
	STAA $8107
	LDAA #9
	STAA $8108

	LDX #$8100
	LDY #$8100	
	LDAA #$00
	LDAB #$00

find_greatest:
	PSHX
	LDX #$8100	
	PSHB
	TAB
	ABX
	PULB
	LDAB  0,X
	PULX

	PSHA
	LDAA 0,X 	;A Макс значение  
	CBA
	BGT new_greatest_to_X
	PULA	

	INCA
	CMPA #$0A  
	BNE find_greatest
	JMP exit

new_greatest_to_X:
	PSHB
	PSHA
	PSHA

	LDD #$0000
	LDAB #$00
	PULA
	TAB
	LDAA #$81
	XGDX

	PULA
	PULB
	JMP find_greatest

exit:
      

