; ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
; บ LEDON. GRUPO J&J.                                        MICROBOTICA   บ
; ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
; บ  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             บ
; บ  Este programa se debe cargar en la RAM interna del 6811.              บ
; บ                                                                        บ
; บ    Simplemente se enciende el led de la tarjeta CT6811.                บ
; ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ

        ORG $000

        LDAA #$40       ; Almacenar en el acumulador A el valor $40
        STAA $1000      ; Enviar el valor $40 a la posiciขn de memoria $1000

inf     BRA inf         ; Bucle infinito

        END


