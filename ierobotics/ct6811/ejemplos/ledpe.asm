; ������������������������������������������������������������������������ͻ
; � LEDPE. GRUPO J&J.                                        MICROBOTICA   �
; ������������������������������������������������������������������������͹
; �  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             �
; �  Este programa se debe Grabar en la EEPROM del 6811.                   �
; �                                                                        �
; �    Simplemente se enciende y se apaga el led de la tarjeta CT6811.     �
; ������������������������������������������������������������������������ͼ

        ORG $B600          ; �Memoria EEPROM!

comienzo
        LDAA $1000
        EORA #$40
        STAA $1000         ; Cambiar bit PA6 de estado

        LDY #$8000         ; Realizar una pausa
dec     DEY
        CPY #0
        BNE dec

        BRA comienzo       ; Repetir proceso

        END
