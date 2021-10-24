; ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»
; º SCIHOLA.  GRUPO J&J.                                    MICROBOTICA    º
; ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹
; º  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             º
; º  Este programa se debe cargar en la RAM interna del 6811.              º
; º                                                                        º
; º    Se envia una cadena por el puerto serie al pulsarse una tecla.      º
; ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼

; Registros del SCI

BAUD    equ  $2B
SCCR1   equ  $2C
SCCR2   equ  $2D
SCSR    equ  $2E
SCDR    equ  $2F

        LDX #$1000       ; Para acceder a registros del SCI

bucle   BSR leer_car     ; Esperar a que llegue un car cter por SCI
        LDY #hola        ; Meter en Y la direcci¢n de la cadena hola
        BSR send_cad     ; Enviar la cadena por el perto serie
        BRA bucle

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³ Rutina par leer un car cter del puerto serie (SCI)     ³
;³ La rutina espera hasta que llegue alg£n car cter       ³
;³ ENTRADAS: Ninguna.                                     ³
;³ SALIDAS: El acumulador A contiene el car cter recibido ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
leer_car BRCLR SCSR,X $10 leer_car   ; Esperar hasta que llegue un car cter
        LDAA SCDR,X
        RTS

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³ Enviar un car cer por el puerto serie (SCI)             ³
;³ ENTRADAS: El acumulador A contiene el car cter a enviar ³
;³ SALIDAS: Ninguna.                                       ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
enviar  BRCLR SCSR,X $80 enviar
        STAA SCDR,X
        RTS

;ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
;³ Enviar una cadena de caracteres por el puerto serie.    ³
;³ La cadena debe terminar con el car cter 0               ³
;³ ENTRADAS: Registro Y contiene direcci¢n cadena a enviar ³
;³ SALIDAS: El acumulador A contiene el car cter recibido  ³
;ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
send_cad LDAA 0,Y        ; Meter en A el car cter a enviar
         CMPA #0         ; ¨Fin de la cadena?
         BEQ fin         ; Si--> retornar
         BSR enviar      ; NO--> enviar car cter.
         INY             ; Apuntar a la sig. posici¢n de memoria
         BRA send_cad    ; Repetir todo
fin      RTS


;ÚÄÄÄÄÄÄÄÄ¿
;³ DATOS  ³
;ÀÄÄÄÄÄÄÄÄÙ
hola    FCC "Hola como estas.."
        FCB 0

        END

