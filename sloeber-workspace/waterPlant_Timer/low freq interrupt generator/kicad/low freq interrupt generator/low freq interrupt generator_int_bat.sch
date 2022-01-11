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
L power:VSS #PWR0101
U 1 1 61DD63AC
P 4000 3750
F 0 "#PWR0101" H 4000 3600 50  0001 C CNN
F 1 "VSS" H 4015 3923 50  0000 C CNN
F 2 "" H 4000 3750 50  0001 C CNN
F 3 "" H 4000 3750 50  0001 C CNN
	1    4000 3750
	-1   0    0    1   
$EndComp
$Comp
L power:VDD #PWR0102
U 1 1 61DD6BF6
P 4000 2100
F 0 "#PWR0102" H 4000 1950 50  0001 C CNN
F 1 "VDD" H 4015 2273 50  0000 C CNN
F 2 "" H 4000 2100 50  0001 C CNN
F 3 "" H 4000 2100 50  0001 C CNN
	1    4000 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61DD8F62
P 6700 2500
F 0 "R1" H 6770 2546 50  0000 L CNN
F 1 "1M" H 6770 2455 50  0000 L CNN
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
	4000 2250 4350 2250
Wire Wire Line
	4000 3400 4450 3400
Wire Wire Line
	4000 2100 4000 2250
Wire Wire Line
	4000 3400 4000 3750
Wire Wire Line
	4350 3100 4350 2250
Connection ~ 4350 2250
Wire Wire Line
	4350 2250 6550 2250
$Comp
L Device:120591-1 BT1
U 1 1 61DED8B0
P 3350 2400
F 0 "BT1" V 3704 2528 50  0000 L CNN
F 1 "120591-1" V 3795 2528 50  0000 L CNN
F 2 "Battery:BatteryHolder_AmpTeConnectivity_CR2032_Horizontal_CircularHoles_ref120591-1" H 4000 2500 50  0001 L CNN
F 3 "http://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=120591&DocType=Customer+Drawing&DocLang=English&DocFormat=pdf&PartCntxt=120591-1" H 4000 2400 50  0001 L CNN
F 4 "Holder pcb 2 way Battery Holder pcb 2 way Battery" H 4000 2300 50  0001 L CNN "Description"
F 5 "TE Connectivity" H 4000 2100 50  0001 L CNN "Manufacturer_Name"
F 6 "120591-1" H 4000 2000 50  0001 L CNN "Manufacturer_Part_Number"
F 7 "571-1205911" H 4000 1900 50  0001 L CNN "Mouser Part Number"
F 8 "https://www.mouser.co.uk/ProductDetail/TE-Connectivity/120591-1?qs=cB%252BprIo57OeZ1n1mnEiYEw%3D%3D" H 4000 1800 50  0001 L CNN "Mouser Price/Stock"
F 9 "120591-1" H 4000 1700 50  0001 L CNN "Arrow Part Number"
F 10 "https://www.arrow.com/en/products/120591-1/te-connectivity?region=nac" H 4000 1600 50  0001 L CNN "Arrow Price/Stock"
	1    3350 2400
	0    1    1    0   
$EndComp
Connection ~ 4000 3400
Text Notes 4100 1950 0    50   ~ 0
+3v
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 61DF0B32
P 2500 3300
F 0 "J1" H 2608 3481 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2608 3390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2500 3300 50  0001 C CNN
F 3 "~" H 2500 3300 50  0001 C CNN
	1    2500 3300
	1    0    0    -1  
$EndComp
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
$Comp
L Switch:SW_SPST SW1
U 1 1 61DDDE97
P 3650 2250
F 0 "SW1" H 3650 2485 50  0000 C CNN
F 1 "SW_SPST" H 3650 2394 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DIP_SPSTx01_Slide_6.7x4.1mm_W7.62mm_P2.54mm_LowProfile" H 3650 2250 50  0001 C CNN
F 3 "~" H 3650 2250 50  0001 C CNN
	1    3650 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2250 4000 2250
Connection ~ 4000 2250
Wire Wire Line
	3250 2400 3350 2400
Wire Wire Line
	3350 2250 3450 2250
Wire Wire Line
	3350 2250 3350 2400
Connection ~ 3350 2400
Wire Wire Line
	3350 3200 3350 3400
Connection ~ 3350 3400
Wire Wire Line
	3350 3400 4000 3400
Wire Wire Line
	2700 3300 4450 3300
Wire Wire Line
	2700 3400 3350 3400
$EndSCHEMATC
