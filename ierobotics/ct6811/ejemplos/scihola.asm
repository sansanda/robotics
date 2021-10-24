; ������������������������������������������������������������������������ͻ
; � SCIHOLA.  GRUPO J&J.                                    MICROBOTICA    �
; ������������������������������������������������������������������������͹
; �  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             �
; �  Este programa se debe cargar en la RAM interna del 6811.              �
; �                                                                        �
; �    Se envia una cadena por el puerto serie al pulsarse una tecla.      �
; ������������������������������������������������������������������������ͼ

; Registros del SCI

BAUD    equ  $2B
SCCR1   equ  $2C
SCCR2   equ  $2D
SCSR    equ  $2E
SCDR    equ  $2F

        LDX #$1000       ; Para acceder a registros del SCI

bucle   BSR leer_car     ; Esperar a que llegue un car�cter por SCI
        LDY #hola        ; Meter en Y la direcci�n de la cadena hola
        BSR send_cad     ; Enviar la cadena por el perto serie
        BRA bucle

;��������������������������������������������������������Ŀ
;� Rutina par leer un car�cter del puerto serie (SCI)     �
;� La rutina espera hasta que llegue alg�n car�cter       �
;� ENTRADAS: Ninguna.                                     �
;� SALIDAS: El acumulador A contiene el car�cter recibido �
;����������������������������������������������������������
leer_car BRCLR SCSR,X $10 leer_car   ; Esperar hasta que llegue un car�cter
        LDAA SCDR,X
        RTS

;���������������������������������������������������������Ŀ
;� Enviar un car�cer por el puerto serie (SCI)             �
;� ENTRADAS: El acumulador A contiene el car�cter a enviar �
;� SALIDAS: Ninguna.                                       �
;�����������������������������������������������������������
enviar  BRCLR SCSR,X $80 enviar
        STAA SCDR,X
        RTS

;���������������������������������������������������������Ŀ
;� Enviar una cadena de caracteres por el puerto serie.    �
;� La cadena debe terminar con el car�cter 0               �
;� ENTRADAS: Registro Y contiene direcci�n cadena a enviar �
;� SALIDAS: El acumulador A contiene el car�cter recibido  �
;�����������������������������������������������������������
send_cad LDAA 0,Y        ; Meter en A el car�cter a enviar
         CMPA #0         ; �Fin de la cadena?
         BEQ fin         ; Si--> retornar
         BSR enviar      ; NO--> enviar car�cter.
         INY             ; Apuntar a la sig. posici�n de memoria
         BRA send_cad    ; Repetir todo
fin      RTS


;��������Ŀ
;� DATOS  �
;����������
hola    FCC "Hola como estas.."
        FCB 0

        END

