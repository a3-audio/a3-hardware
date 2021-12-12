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
L flex_AmbisonicLib:ATtiny861V-10SU U1
U 1 1 61B25FEB
P 5050 3800
F 0 "U1" H 4420 3846 50  0000 R CNN
F 1 "ATtiny861V-10SU" H 4420 3755 50  0000 R CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 5050 3800 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2588-8-bit-avr-microcontrollers-tinyavr-attiny261-attiny461-attiny861_datasheet.pdf" H 5050 3800 50  0001 C CNN
	1    5050 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 61B2BAA9
P 5150 2250
F 0 "C3" H 5265 2296 50  0000 L CNN
F 1 "100nF" H 5265 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5188 2100 50  0001 C CNN
F 3 "~" H 5150 2250 50  0001 C CNN
	1    5150 2250
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L1
U 1 1 61B2C408
P 4700 2450
F 0 "L1" H 4700 2665 50  0000 C CNN
F 1 "10uH" H 4700 2574 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric_Pad1.22x1.90mm_HandSolder" H 4700 2450 50  0001 C CNN
F 3 "~" H 4700 2450 50  0001 C CNN
	1    4700 2450
	1    0    0    -1  
$EndComp
Text GLabel 3350 2450 0    50   Input ~ 0
VCC
Wire Wire Line
	5150 2700 5150 2450
Wire Wire Line
	4950 2450 5150 2450
Connection ~ 5150 2450
Wire Wire Line
	5150 2450 5150 2400
Wire Wire Line
	4450 2450 4350 2450
$Comp
L power:GND #PWR0101
U 1 1 61B2CFE3
P 5150 2100
F 0 "#PWR0101" H 5150 1850 50  0001 C CNN
F 1 "GND" H 5155 1927 50  0000 C CNN
F 2 "" H 5150 2100 50  0001 C CNN
F 3 "" H 5150 2100 50  0001 C CNN
	1    5150 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 2700 5050 2600
Wire Wire Line
	5050 2600 4350 2600
Wire Wire Line
	4350 2600 4350 2450
Connection ~ 4350 2450
Wire Wire Line
	4350 2450 4200 2450
$Comp
L Device:CP C1
U 1 1 61B2E1E8
P 3850 2300
F 0 "C1" H 3968 2346 50  0000 L CNN
F 1 "10uF" H 3968 2255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.0mm_P2.50mm" H 3888 2150 50  0001 C CNN
F 3 "~" H 3850 2300 50  0001 C CNN
	1    3850 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 61B2E94E
P 4200 2300
F 0 "C2" H 4315 2346 50  0000 L CNN
F 1 "100nF" H 4315 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 4238 2150 50  0001 C CNN
F 3 "~" H 4200 2300 50  0001 C CNN
	1    4200 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2150 4050 2150
Wire Wire Line
	4050 1950 4050 2150
Connection ~ 4050 2150
Wire Wire Line
	4050 2150 3850 2150
Wire Wire Line
	4200 2450 3850 2450
Connection ~ 4200 2450
Connection ~ 3850 2450
Wire Wire Line
	3850 2450 3500 2450
$Comp
L power:GND #PWR0103
U 1 1 61B2FE96
P 5150 4900
F 0 "#PWR0103" H 5150 4650 50  0001 C CNN
F 1 "GND" H 5155 4727 50  0000 C CNN
F 2 "" H 5150 4900 50  0001 C CNN
F 3 "" H 5150 4900 50  0001 C CNN
	1    5150 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61B30FF9
P 5050 4900
F 0 "#PWR0104" H 5050 4650 50  0001 C CNN
F 1 "GND" H 5055 4727 50  0000 C CNN
F 2 "" H 5050 4900 50  0001 C CNN
F 3 "" H 5050 4900 50  0001 C CNN
	1    5050 4900
	1    0    0    -1  
$EndComp
Text GLabel 5750 3000 2    50   Input ~ 0
SDA
Text GLabel 6400 3000 2    50   Input ~ 0
PB1
Text GLabel 5750 3200 2    50   Input ~ 0
SCL
Text GLabel 6300 2700 2    50   Input ~ 0
PB3
Text GLabel 6350 2850 2    50   Input ~ 0
PB2
Text GLabel 6450 3150 2    50   Input ~ 0
ENCSW
Text GLabel 6550 3450 2    50   Input ~ 0
ADC1
Text GLabel 6500 3300 2    50   Input ~ 0
ADC0
Wire Wire Line
	7000 3250 7500 3250
Wire Wire Line
	7250 3350 7000 3350
Connection ~ 7000 3350
Wire Wire Line
	7000 3350 7000 3250
Wire Wire Line
	7000 3350 7000 3800
Wire Wire Line
	7100 3450 7500 3450
Wire Wire Line
	7100 3450 7100 3550
Wire Wire Line
	7100 3550 7250 3550
Connection ~ 7100 3550
Wire Wire Line
	7100 3550 7100 3900
Wire Wire Line
	7200 3650 7500 3650
Wire Wire Line
	7200 3750 7250 3750
Connection ~ 7200 3750
Wire Wire Line
	7200 3750 7200 3650
Wire Wire Line
	7200 3750 7200 4000
Wire Wire Line
	5750 3900 5750 3800
Wire Wire Line
	5750 4000 5850 4000
Wire Wire Line
	5850 4000 5850 3900
Wire Wire Line
	5750 4100 5950 4100
Wire Wire Line
	5950 4100 5950 4000
Wire Wire Line
	5750 4200 6100 4200
Wire Wire Line
	6100 4200 6100 4100
Wire Wire Line
	7350 4100 7350 3850
Wire Wire Line
	7350 3850 7750 3850
Text GLabel 7500 3250 2    50   Input ~ 0
MOSI
Text GLabel 7250 3350 2    50   Input ~ 0
PSHFDATA
Text GLabel 7500 3450 2    50   Input ~ 0
MISO
Text GLabel 7250 3550 2    50   Input ~ 0
PB0
Text GLabel 7500 3650 2    50   Input ~ 0
PSFHCLK
Text GLabel 7250 3750 2    50   Input ~ 0
SCK
Text GLabel 7750 3850 2    50   Input ~ 0
PSHFUPDATE
Text GLabel 5750 4500 2    50   Input ~ 0
ENCA
Wire Wire Line
	5750 4600 6100 4600
Wire Wire Line
	6100 4600 6100 4700
Wire Wire Line
	6100 4800 6200 4800
Wire Wire Line
	6100 4700 6200 4700
Connection ~ 6100 4700
Wire Wire Line
	6100 4700 6100 4800
Text GLabel 6200 4700 2    50   Input ~ 0
ENCB
Text GLabel 6200 4800 2    50   Input ~ 0
RESET
Text GLabel 9350 1650 2    50   Input ~ 0
PB1
Text GLabel 7600 2100 0    50   Input ~ 0
PB3
Text GLabel 7600 2000 0    50   Input ~ 0
PB2
Text GLabel 9350 1450 2    50   Input ~ 0
ENCSW
Text GLabel 9350 2050 2    50   Input ~ 0
ADC1
Text GLabel 9350 1850 2    50   Input ~ 0
ADC0
Text GLabel 7600 1500 0    50   Input ~ 0
PSHFDATA
Text GLabel 7600 1300 0    50   Input ~ 0
PB0
Text GLabel 7600 1700 0    50   Input ~ 0
PSFHCLK
Text GLabel 7600 1600 0    50   Input ~ 0
PSHFUPDATE
Text GLabel 9350 1550 2    50   Input ~ 0
ENCB
Text GLabel 9350 1350 2    50   Input ~ 0
ENCA
Text GLabel 1800 3250 2    50   Input ~ 0
MISO
Text GLabel 1800 3150 2    50   Input ~ 0
MOSI
Text GLabel 1800 3350 2    50   Input ~ 0
RESET
Text GLabel 1800 3450 2    50   Input ~ 0
SCK
Text GLabel 1800 3900 2    50   Input ~ 0
SCL
Text GLabel 1800 4200 2    50   Input ~ 0
SDA
Text GLabel 9350 1750 2    50   Input ~ 0
VCC
Text GLabel 2900 3150 2    50   Input ~ 0
GND
$Comp
L power:GND #PWR0106
U 1 1 61B42418
P 2750 3200
F 0 "#PWR0106" H 2750 2950 50  0001 C CNN
F 1 "GND" H 2755 3027 50  0000 C CNN
F 2 "" H 2750 3200 50  0001 C CNN
F 3 "" H 2750 3200 50  0001 C CNN
	1    2750 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3150 2850 3150
Wire Wire Line
	2750 3150 2750 3200
Text GLabel 9350 2150 2    50   Input ~ 0
GND
Text GLabel 9350 1950 2    50   Input ~ 0
GND
Text GLabel 7600 1900 0    50   Input ~ 0
VCC
Text GLabel 7600 1800 0    50   Input ~ 0
GND
Text GLabel 7600 1400 0    50   Input ~ 0
GND
Wire Wire Line
	5750 3100 6000 3100
Wire Wire Line
	6000 3100 6000 2700
Wire Wire Line
	5750 3300 6050 3300
Wire Wire Line
	6050 3300 6050 2850
Wire Wire Line
	5750 3400 6100 3400
Wire Wire Line
	6100 3400 6100 3000
Wire Wire Line
	5750 3800 7000 3800
Wire Wire Line
	5850 3900 7100 3900
Wire Wire Line
	5950 4000 7200 4000
Wire Wire Line
	6100 4100 7350 4100
Wire Wire Line
	6150 3150 6150 3500
Wire Wire Line
	6150 3500 5750 3500
Wire Wire Line
	6200 3300 6200 3600
Wire Wire Line
	6200 3600 5750 3600
Wire Wire Line
	6250 3450 6250 3700
Wire Wire Line
	6250 3700 5750 3700
$Comp
L Connector:Conn_01x09_Female J4
U 1 1 61B543E3
P 7800 1700
F 0 "J4" H 7828 1726 50  0000 L CNN
F 1 "Conn_01x09_Female" H 7828 1635 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x09_P2.54mm_Vertical" H 7800 1700 50  0001 C CNN
F 3 "~" H 7800 1700 50  0001 C CNN
	1    7800 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x09_Female J5
U 1 1 61B5546A
P 9150 1750
F 0 "J5" H 9042 1125 50  0000 C CNN
F 1 "Conn_01x09_Female" H 9042 1216 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x09_P2.54mm_Vertical" H 9150 1750 50  0001 C CNN
F 3 "~" H 9150 1750 50  0001 C CNN
	1    9150 1750
	-1   0    0    1   
$EndComp
Text GLabel 1800 4000 2    50   Input ~ 0
VCC
Text GLabel 1800 3800 2    50   Input ~ 0
GND
Text GLabel 1800 4100 2    50   Input ~ 0
GND
Text GLabel 1800 4750 2    50   Input ~ 0
SCL
Text GLabel 1800 4450 2    50   Input ~ 0
SDA
Text GLabel 1800 4650 2    50   Input ~ 0
VCC
Text GLabel 1800 4850 2    50   Input ~ 0
GND
Text GLabel 1800 4550 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 61B5D90A
P 1600 3350
F 0 "J1" H 1492 2925 50  0000 C CNN
F 1 "Conn_01x04_Female" H 1492 3016 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 1600 3350 50  0001 C CNN
F 3 "~" H 1600 3350 50  0001 C CNN
	1    1600 3350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Female J2
U 1 1 61B5E7D1
P 1600 4000
F 0 "J2" H 1492 3575 50  0000 C CNN
F 1 "Conn_01x05_Female" H 1492 3666 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Horizontal" H 1600 4000 50  0001 C CNN
F 3 "~" H 1600 4000 50  0001 C CNN
	1    1600 4000
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Male J3
U 1 1 61B5F7CF
P 1600 4650
F 0 "J3" H 1708 5031 50  0000 C CNN
F 1 "Conn_01x05_Male" H 1708 4940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 1600 4650 50  0001 C CNN
F 3 "~" H 1600 4650 50  0001 C CNN
	1    1600 4650
	1    0    0    -1  
$EndComp
$Comp
L btn-matrix-rescue:PWR_FLAG-power #FLG0101
U 1 1 61B60824
P 3500 2450
F 0 "#FLG0101" H 3500 2525 50  0001 C CNN
F 1 "PWR_FLAG-power" H 3500 2623 50  0000 C CNN
F 2 "" H 3500 2450 50  0001 C CNN
F 3 "" H 3500 2450 50  0001 C CNN
	1    3500 2450
	1    0    0    -1  
$EndComp
Connection ~ 3500 2450
Wire Wire Line
	3500 2450 3350 2450
$Comp
L btn-matrix-rescue:GND-power #PWR0107
U 1 1 61B60F85
P 2850 3150
F 0 "#PWR0107" H 2850 2900 50  0001 C CNN
F 1 "GND-power" H 2855 2977 50  0000 C CNN
F 2 "" H 2850 3150 50  0001 C CNN
F 3 "" H 2850 3150 50  0001 C CNN
	1    2850 3150
	1    0    0    -1  
$EndComp
Connection ~ 2850 3150
Wire Wire Line
	2850 3150 2750 3150
Text GLabel 4050 1950 1    50   Input ~ 0
GND
NoConn ~ 5750 4300
NoConn ~ 5750 4400
Wire Wire Line
	6000 2700 6300 2700
Wire Wire Line
	6050 2850 6350 2850
Wire Wire Line
	6100 3000 6400 3000
Wire Wire Line
	6150 3150 6450 3150
Wire Wire Line
	6200 3300 6500 3300
Wire Wire Line
	6250 3450 6550 3450
$EndSCHEMATC
