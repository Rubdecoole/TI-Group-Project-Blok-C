# TI-Group-Project-Blok-C
Repository voor het TI project

De kenmerken van onze brandweerwagen Bruni:

-	We hebben gekozen voor een 3 wieler model omdat dit zorgt voor een draaicirkel die zo klein mogelijk is.
-	We hebben het formaat van onze auto in verhouding groot gemaakt omdat dit zo robuust is en alle onderdelen kan dragen die we erop wouden.
-	De motoren zitten op een aparte powerbron omdat deze piekstormen kunnen geven en dan de sensoren zouden verstoren.
-	We hebben gebruik gemaakt van een 120 graden vlamsensor, zodat Bruni weet waar de vlam zich bevindt en er meteen naartoe kan rijden.
-	 We hebben 2 voorkant sensoren zodat bruni voor beide wielen kan kijken of er niets staat. Daarnaast hebben we ook 2 zijkant sensoren, waneer Bruni niet verder kan kijkt hij of hij naar links of naar rechts kan en op basis daarvan maakt hij een beslissing. Wanneer hij niet naar links en rechts kan gaat hij achteruit.
-	Wanneer Bruni bij de vlam is zet hij de ventilator aan deze draait tot hij geen vuur meer meet, dan wacht hij 5 seconden en doet hij een check of het vuur daadwerkelijk uit is. Wanneer het vuur weer aan is gegaan schakelt hij de ventilator weer in, wanneer het vuur uit is gaat hij verder.
-	De ventilator heeft meer stroom nodig dan de Arduino kan geven, vandaar hebben wij ook deze hebben op een aparte powerbron zitten.
-	Wanneer Bruni de vlam heeft gevonden en gedoofd gaat hij zijn overwinningsdansje doen.
-	Ook heeft Bruni een speaker ingebouwd, wanneer Bruni vuur heeft gespot gaat hij met een alarm aan ernaartoe, dit alarm gaat pas weer uit wanneer het vuur is gedoofd. Ook speelt hij tijdens zijn overwinningsdansje een liedje af om te vieren dat het vuur uit is.
-	We hebben alle draadjes per onderdeel ingetaped met isolatietape voor zo min mogelijk interferentie.



Setup Serial MP3 player A:
Pin 12: Gaat naar de TX pin van de vlamsensor.
Pin 9: Gaat naar de RX pin van de vlamsensor.
VCC: Gaat op 5V van de Arduino.
GND: Gaat op de Ground van de Arduino.

Setup Afstandssensoren(HC-SR04):
Pin 2: Gaat naar alle triggerpinnen van de afstandsensoren.
Pin 13: Gaat naar de echopin van de linkerkant afstandssensor.
Pin 4: Gaat naar de echopin van de rechterkant afstandssensor.
Pin 7: Gaat naar de echopin van de rechtervoorkant afstandssensor.
Pin 8: Gaat naar de echopin van de linkervoorkant afstandssensor.
VCC(van elke afstandssensor): Gaat op 5V van de Arduino.
GND(van elke afstandsensor): Gaat op de Ground van de Arduino.

Setup Motoren:
De motoren krijgen een eigen 9V batterij.
Pin 5: Gaat naar de linkermotor vooruit.
Pin 6: Gaat naar de linkermotor achteruit.
Pin 10: Gaat naar de rechtermotor vooruit.
Pin 11: Gaat naar de rechtermotor achteruit.
VCC: Naar de Power van de H-brug.
GND: Naar de Ground van de H-brug.

Setup ventilator(GRAND FLEX SM1225GF12SH-P):
De ventilator krijgt een eigen 9V batterij.
Pin 3: Gaat naar de Mosfet(TIP122).
VCC: Gaat naar de Mosfet opstelling.
GND: Gaat naar de arduino ground.
