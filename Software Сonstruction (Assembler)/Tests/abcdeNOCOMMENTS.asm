        ORG     $8000

        LDY     #0
        CLRA
        LDX     #$8200
        LDAB    #0

again:
        LDAA    ,X
        BLE     next
        TAB
        ABY
        INCA
next:
        INX
        DECB
        BNE     again

	TBA
        BRA     *