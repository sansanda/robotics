; 浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
; ? LEDP. GRUPO J&J.                                         MICROBOTICA   ?
; 麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様郵
; ?  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             ?
; ?  Este programa se debe cargar en la RAM interna del 6811.              ?
; ?                                                                        ?
; ?    Simplemente se enciende y se apaga el led de la tarjeta CT6811.     ?
; 藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕

        ORG $000

comienzo
        LDAA $1000
        EORA #$40         ; Cambiar de estado el bit PA6
        STAA $1000

        LDY #$FFFF        ; Realizar una pausa
dec     DEY
        CPY #0
        BNE dec

        BRA comienzo      ; Repetir el proceso

        END
