        ORG   $8000

main:
        ldy   #0              
        clra                  
        
        ldx   #$8200
        ldab  #$00            

again:
        ldaa  ,x              
        ble   next                            
	tba
	clra
	aby                   
        
        inca                  
	
next:
        inx
        decb
        bne   again

forever:
        bra   forever         