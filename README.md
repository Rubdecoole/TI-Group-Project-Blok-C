# TI-Group-Project-Blok-C
Repository voor het TI project
Setup Serial MP3 player A:
	Pin 12: Gaat naar de TX pin van de vlamsensor
	Pin 9: Gaat naar de RX pin van de vlamsensor
	VCC: Gaat op 5V van de Arduino
	GND: Gaat op de Ground van de Arduino

Setup Afstandssensoren(HC-SR04):
	Pin 2: Gaat naar alle triggerpinnen van de afstandsensoren
	Pin 13: Gaat naar de echopin van de linkerkant afstandssensor
	Pin 4: Gaat naar de echopin van de rechterkant afstandssensor
	Pin 7: Gaat naar de echopin van de rechtervoorkant afstandssensor
	Pin 8: Gaat naar de echopin van de linkervoorkant afstandssensor
	VCC(van elke afstandssensor): Gaat op 5V van de Arduino
	GND(van elke afstandsensor): Gaat op de Ground van de Arduino

Setup Motoren:
	De motoren krijgen een eigen 9V batterij.
	Pin 5: Gaat naar de linkermotor vooruit
	Pin 6: Gaat naar de linkermotor achteruit
	Pin 10: Gaat naar de rechtermotor vooruit
	Pin 11: Gaat naar de rechtermotor achteruit.
	VCC: Naar de Power van de H-brug
	GND: Naar de Ground van de H-brug

Setup ventilator(GRAND FLEX SM1225GF12SH-P):
	De ventilator krijgt een eigen 9V batterij.
	Pin 3: Gaat naar de Mosfet(TIP122);
	VCC: Gaat naar de Mosfet opstelling.
	GND: Gaat naar de arduino ground.
