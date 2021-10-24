; ������������������������������������������������������������������������ͻ
; � MENU.  GRUPO J&J.                                        MICROBOTICA   �
; ������������������������������������������������������������������������͹
; �  Programa ejemplo para ser ejecutado en la tarjeta CT6811.             �
; �  Este programa se debe cargar en la RAM interna del 6811.              �
; �                                                                        �
; �  Ejemplo de c�mo manejar un menu de opciones para programas interac-   �
; � tivos con el usuario.                                                  �
; ������������������������������������������������������������������������ͼ
CR      equ  13    ; Retorno de carro
LF      equ  10    ; Avance de linea

; Registros del SCI

BAUD    equ  $2B
SCCR1   equ  $2C
SCCR2   equ  $2D
SCSR    equ  $2E
SCDR    equ  $2F

        LDX #$1000       ; Para acceder a registros del SCI

bucle   LDY #menu
        BSR send_cad     ; Sacar menu
wait    BSR leer_car     ; Leer tecla
        CMPA #'1'
        BEQ opcion1      ; Tecla '1'--> Opcion 1 del menu.
        CMPA #'2'
        BEQ opcion2      ; Tecla '2'--> Opcion 2 del menu.
        BRA wait

opcion1 LDAA $1000
        EORA #$40        ; Cambiar estado bit 6 puerto A
        STAA $1000
        BRA wait

opcion2 BRA bucle        ; Volver a sacar el menu


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
menu    FCB CR,LF,LF
        FCC "       MENU DE OPCIONES"
        FCB CR,LF
        FCC "       ================"
        FCB CR,LF,LF
        FCC "  1.- Cambiar de estado el LED"
        FCB CR,LF
        FCC "  2.- Sacar este menu"
        FCB CR,LF
        FCC "  Opcion: "
        FCB 0

        END



