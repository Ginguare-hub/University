ORG     $8000

        LDY     #0
        CLRA	
	CLRB
        LDX     #$8200
        LDAB    #0

again:
	CPX #$8300
	BPL done
	CLRA
	LDAA ,X
        BLE next
	PSHB
	TAB
	ABY
	PULB
	INCB

next:
        INX
        BNE     again

done:	TBA   
	BRA     *