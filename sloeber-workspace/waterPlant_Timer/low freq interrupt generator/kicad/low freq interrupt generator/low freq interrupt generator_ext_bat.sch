EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Timer:ICM7242IPAZ IC1
U 1 1 61DD59E8
P 4450 3100
F 0 "IC1" H 5400 3365 50  0000 C CNN
F 1 "ICM7242IPAZ" H 5400 3274 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6200 3200 50  0001 L CNN
F 3 "https://www.mouser.in/datasheet/2/698/icm7242-1528825.pdf" H 6200 3100 50  0001 L CNN
F 4 "Counter/Time Base ICs Long Range Fixed Timer" H 6200 3000 50  0001 L CNN "Description"
F 5 "5.33" H 6200 2900 50  0001 L CNN "Height"
F 6 "Renesas Electronics" H 6200 2800 50  0001 L CNN "Manufacturer_Name"
F 7 "ICM7242IPAZ" H 6200 2700 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "968-ICM7242IPAZ" H 6200 2600 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Renesas-Intersil/ICM7242IPAZ?qs=9fLuogzTs8I3wmfaOcs9Gg%3D%3D" H 6200 2500 50  0001 L CNN "Mouser Price/Stock"
	1    4450 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61DD8F62
P 6700 2500
F 0 "R1" H 6770 2546 50  0000 L CNN
F 1 "800K" H 6770 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 6630 2500 50  0001 C CNN
F 3 "~" H 6700 2500 50  0001 C CNN
	1    6700 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61DD9A16
P 7000 2650
F 0 "C1" H 7115 2696 50  0000 L CNN
F 1 "15uF" H 7115 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7038 2500 50  0001 C CNN
F 3 "~" H 7000 2650 50  0001 C CNN
	1    7000 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3300 6550 3300
Wire Wire Line
	6550 3300 6550 2250
Connection ~ 6550 2250
Wire Wire Line
	6550 2250 6700 2250
Wire Wire Line
	4450 3100 4350 3100
Wire Wire Line
	4350 3100 4350 2250
Wire Wire Line
	4350 2250 6550 2250
Text Notes 3250 3050 0    50   ~ 0
+5v
$Comp
L Connector:TestPoint TP1
U 1 1 61DF1F51
P 4350 3650
F 0 "TP1" H 4292 3676 50  0000 R CNN
F 1 "TestPoint" H 4292 3767 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4550 3650 50  0001 C CNN
F 3 "~" H 4550 3650 50  0001 C CNN
	1    4350 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 3200 4350 3200
Wire Wire Line
	4350 3200 4350 3650
Text Notes 5350 4000 0    50   ~ 0
Valores para obtener un RC=15s serán R=1M, 15uF\nEntonces 15s * 256 = 3840. Aprox 1.06 horas.\nTendremos un flanco de subida cada 1.06 horas
$Comp
L Device:R_POT RV1
U 1 1 61DF3725
P 6700 2900
F 0 "RV1" H 6631 2946 50  0000 R CNN
F 1 "200K" H 6631 2855 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6700 2900 50  0001 C CNN
F 3 "~" H 6700 2900 50  0001 C CNN
	1    6700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3200 6700 3200
Wire Wire Line
	6700 3050 6700 3100
Connection ~ 6700 3200
Wire Wire Line
	6700 2750 6700 2650
Wire Wire Line
	6700 2350 6700 2250
Wire Wire Line
	6700 2250 7000 2250
Wire Wire Line
	7000 2250 7000 2500
Connection ~ 6700 2250
Wire Wire Line
	7000 2800 7000 3200
Wire Wire Line
	6850 2900 6850 3100
Wire Wire Line
	6850 3100 6700 3100
Connection ~ 6700 3100
Wire Wire Line
	6700 3100 6700 3200
Wire Wire Line
	6700 3200 7000 3200
Wire Wire Line
	2700 3300 4450 3300
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 61DDB61D
P 2500 3300
F 0 "J1" H 2608 3581 50  0000 C CNN
F 1 "Conn_01x03_Male" H 2608 3490 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2500 3300 50  0001 C CNN
F 3 "~" H 2500 3300 50  0001 C CNN
	1    2500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3200 3300 3200
Wire Wire Line
	3300 3200 3300 3100
Wire Wire Line
	3300 3100 4350 3100
Connection ~ 4350 3100
Wire Wire Line
	2700 3400 4450 3400
$EndSCHEMATC
