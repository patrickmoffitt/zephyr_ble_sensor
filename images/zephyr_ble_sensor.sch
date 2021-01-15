EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Bluetooth Low Energy Environmental Sensor"
Date "2021-01-14"
Rev "1.0"
Comp ""
Comment1 "This schematic is in the public domain."
Comment2 "Adafruit Feather nRF52840 Express, Adafruit BME680, and Pololu #2562"
Comment3 "Drawn by: Patrick K. Moffitt"
Comment4 ""
$EndDescr
$Comp
L Sensor:BME680 U1
U 1 1 60007229
P 4100 4350
F 0 "U1" H 3671 4396 50  0000 R CNN
F 1 "BME680" H 3671 4305 50  0000 R CNN
F 2 "Package_LGA:Bosch_LGA-8_3x3mm_P0.8mm_ClockwisePinNumbering" H 5550 3900 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME680-DS001.pdf" H 4100 4150 50  0001 C CNN
	1    4100 4350
	1    0    0    -1  
$EndComp
$Comp
L mcu_adafruit_feather_m0_jp3-connector:MCU_Adafruit_Feather_M0_JP3-Connector JP3?
U 1 1 60008266
P 5600 3200
F 0 "JP3?" H 5828 2546 50  0000 L CNN
F 1 "MCU_Adafruit_Feather_JP3-Connector" H 5828 2455 50  0000 L CNN
F 2 "" H 5600 3200 50  0001 C CNN
F 3 "" H 5600 3200 50  0001 C CNN
	1    5600 3200
	1    0    0    -1  
$EndComp
$Comp
L mcu_adafruit_feather_m0_jp1-connector:MCU_Adafruit_Feather_M0_JP1-Connector JP1?
U 1 1 60009661
P 2200 2700
F 0 "JP1?" H 1708 3265 50  0000 C CNN
F 1 "MCU_Adafruit_Feather_JP1-Connector" H 1708 3174 50  0000 C CNN
F 2 "" H 2200 3100 50  0001 C CNN
F 3 "" H 2200 3100 50  0001 C CNN
	1    2200 2700
	1    0    0    -1  
$EndComp
$Comp
L 5v_step_up_voltage_regulator_Pololu_2562_u1v11f5:5V_Step_Up_Voltage_Regulator_U1V11F5 U2
U 1 1 60009E65
P 3200 2550
F 0 "U2" H 3528 2596 50  0000 L CNN
F 1 "5V_Step_Up_Voltage_Regulator_U1V11F5" H 3528 2505 50  0000 L CNN
F 2 "" H 3200 2550 50  0001 C CNN
F 3 "" H 3200 2550 50  0001 C CNN
	1    3200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2500 2750 2500
Wire Wire Line
	1900 2700 2150 2700
Wire Wire Line
	2550 2700 2550 2600
Wire Wire Line
	2550 2600 2750 2600
Wire Wire Line
	1900 2800 2350 2800
Wire Wire Line
	2350 2800 2350 2400
Wire Wire Line
	2350 2400 2750 2400
Wire Wire Line
	4700 4450 5450 4450
Wire Wire Line
	4700 4250 5200 4250
Wire Wire Line
	5200 4250 5200 4350
Wire Wire Line
	5200 4350 5450 4350
Connection ~ 2150 2700
Wire Wire Line
	2150 2700 2550 2700
Wire Wire Line
	2150 2700 2150 3350
Wire Wire Line
	2150 5200 4000 5200
Wire Wire Line
	4000 5200 4000 4950
Wire Wire Line
	2750 2700 2750 3600
Wire Wire Line
	2750 3600 4200 3600
Wire Wire Line
	4200 3600 4200 3750
$Comp
L Device:Battery BT1
U 1 1 60017358
P 4250 3150
F 0 "BT1" H 4358 3196 50  0000 L CNN
F 1 "3.7V LIPo" H 4358 3105 50  0000 L CNN
F 2 "" V 4250 3210 50  0001 C CNN
F 3 "~" V 4250 3210 50  0001 C CNN
	1    4250 3150
	1    0    0    -1  
$EndComp
Connection ~ 2150 3350
Wire Wire Line
	2150 3350 2150 5200
Wire Wire Line
	2150 3350 4250 3350
Wire Wire Line
	4250 2950 5150 2950
Wire Wire Line
	5150 2950 5150 3350
Wire Wire Line
	5150 3350 5450 3350
$EndSCHEMATC
