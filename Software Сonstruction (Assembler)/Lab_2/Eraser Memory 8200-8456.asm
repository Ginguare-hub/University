        ORG   $8000

        ldx   #$8200

loop:
        clr   ,x
        inx
        cpx   #$8300            
        bne   loop

        bra   *