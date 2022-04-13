#include <Arduino_AVRSTL.h>                                                             // Include de benodigde libraries voor ons project.
#include <SoftwareSerial.h>
using namespace std;
#define MP3_RX 12 // to TX                                                              // Benoem de RX/TX pinnen voor de MP3 speler.
#define MP3_TX 9 // to RX

static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef};                        // Kies de sd card voor de speaker.
static int8_t stopgeluid[] = {0x7e, 0x02, 0x0e, 0xef};                                  // Stop het geluid dat nu wordt afgespeeld.
static int8_t volume[] = {0x7e, 0x03, 0x31, 0x14, 0xef};                                // Volume regelen, 4de bit vanaf links bepaald hoe hard.
static int8_t sirene[] = {0x7e, 0x04, 0x41, 0x00, 0x03, 0xef};                          // Kies nummer om af te spelen, 5de bit vanaf links bepaalt welk mp3 bestand.
static int8_t overwinningsmuziekje[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef};            // Wij hebben alleen een sirene en een overwinningsmuziekje.
SoftwareSerial MP3(MP3_RX, MP3_TX);

int TriggerPin1 = 2;                                                                    // Definiëren van de pinnen voor de afstandssensoren.
int EchoPin1 = 13;
int EchoPin2 = 4;
int EchoPin4 = 7;
int EchoPin5 = 8;

int fanPin = 3;                                                                         // Definiëren van de pin voor de ventilator.

int motorForwardPin = 5;                                                                // Definiëren van de pinnen voor de motoren.
int motorReversePin = 6;
int motorForwardPin2 = 10;
int motorReversePin2 = 11;


const int treshold = 300;                                                               // Vuur sensor detection threshold, als een waarde hoger wordt dan dit, dan pakt hij hem op.
const int tresholdDichtbij = 2700;                                                      // Vuur sensor threshold, als de waarde hierboven komt dan is de vlam dichtbij genoeg. --waarde van een lamp is: 4980--

int afstand_te_meten_voor = 25;                                                         
int afstand_te_meten_zijkant = 30;                                                      // De afstand die de auto moet meten in CM aan de voorkant en de zijkant.

bool SireneAan = 0;                                                                     // Waarde om te kijken of de sirene al aan staat.


void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);                                                         // Benoem voor elke pin of het een output of input is.
  pinMode(EchoPin1, INPUT);
  pinMode(EchoPin2, INPUT);

  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  pinMode(motorForwardPin2, OUTPUT);
  pinMode(motorReversePin2, OUTPUT);

  pinMode(fanPin, OUTPUT);
  analogWrite(fanPin,0);                                                                 // Zet de ventilator standaard op uit.
  
  MP3.begin(9600);
  MP3command(select_SD_card, 5);                                                         // Selecteert de SD kaart van de MP3 speler. Het laatste getal van elk MP3 command geeft aan hoeveel bytes de command is.
  MP3command(volume, 5);
}

void MP3command(int8_t command[], int len){                                              // Functie om de commands naar de MP3 speler te sturen.
  // Serial.print("\nMP3 Command => ");
  for(int i=0;i<len;i++){ MP3.write(command[i]); Serial.print(command[i], HEX); }
  delay(1000);
}

void rechtsaf(){                                                                         // Functie om de auto naar rechts te laten draaien.
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 50);
    analogWrite(motorForwardPin2, 50);
    analogWrite(motorReversePin2, 0);
}


void linksaf(){                                                                          // Functie om de auto naar links te laten draaien.
    analogWrite(motorForwardPin, 50);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 50); 
}


void rechtdoor(){                                                                         // Functie om de auto rechtdoor te laten rijden.
    analogWrite(motorForwardPin, 90);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 73);
    analogWrite(motorReversePin2, 0);
}


void achteruit(){                                                                         // Functie om de auto achteruit te laten rijden.
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 130);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 130);
}


void stoppen(){                                                                           // Functie om de auto te laten stoppen met rijden.
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 0);
}


void overwinnings_dansje(){                                                               // Een overwinninsdansje die de auto doet als hij de vlam geblust heeft.
  MP3command(overwinningsmuziekje, 6);
  rechtsaf();
  delay(400);
  linksaf();
  delay(400);
  rechtsaf();
  delay(400);
  linksaf();
  delay(400);
  rechtsaf();
  delay(400);
  linksaf();
  delay(400);
  rechtsaf();
  delay(400);
  linksaf();
  delay(400);
  rechtsaf();
  delay(3600);
  linksaf();
  delay(3600);
  MP3command(stopgeluid, 4);
  stoppen();
}


vector<int> metenVoor(){                                                                     // Functie om de voorkant van de auto te meten.
  int voorkantRechts = meten(EchoPin4);
  delay(80);
  int voorkantLinks = meten(EchoPin5);
  return {voorkantRechts,voorkantLinks};
  }

  
vector<int> metenZijkant(){                                                                  // Functie om de zijkanten van de auto te meten.
  int zijkantRechts = meten(EchoPin2);
  delay(80);
  int zijkantLinks= meten(EchoPin1);
  return {zijkantRechts,zijkantLinks};
  }


int meten(int echopinnummer){                                                                // Functie die de afstand berekent en uiteindelijk in centimeters teruggeeft.
  digitalWrite(TriggerPin1, LOW);                                                            // Afstandssensor een sonar laten sturen.
  delayMicroseconds(5);
  digitalWrite(TriggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW);                                                            
  
  int tijdgemeten = pulseIn(echopinnummer, HIGH);                                            // Meet hoelang de sonar er over deed om terug te komen bij de sensor.
  int afstand = (tijdgemeten/2) / 29.1;                                                      // Afstand berekenen is (reistijd/2 )* snelheid van geluid (je kan ook / 29.1 doen) in centimeters.
  return afstand;}


char blokkade_checker(int afstandRechts, int afstandLinks, int meetafstandvoor,              // Functie om te kijken welke kant de auto op kan rijden.
int meetafstandzijkant, int afstandRechtsVoor, int afstandLinksVoor){                        
  if(afstandRechtsVoor < meetafstandvoor || afstandLinksVoor < meetafstandvoor){             // Checkt of er meer dan 20 cm vrij is aan de voorkant.
     
    if(afstandRechts >= meetafstandzijkant && afstandLinks >= meetafstandzijkant ||
    afstandRechts >= meetafstandzijkant && afstandLinks < meetafstandzijkant){
      return 1;}                                                                             // Als er aan de linkerkant en rechterkant genoeg ruimte is OF alleen rechts genoeg ruimte, geeft hij 1 terug.
                                                                                             // Hij wilt dus standaard naar rechts als hij een blokkade vind, tenzij dat niet mogelijk is.
    else if(afstandRechts < meetafstandzijkant && afstandLinks >= meetafstandzijkant){
      return 2;}                                                                             // Als er alleen links genoeg ruimte is geeft hij 2 terug.
    else{
      return 3;                                                                              // Als er aan de voorkant en zijkanten geen ruimte is, geeft hij 3 terug.
    }
  }
  else{
    return 0;}                                                                               // Geeft 0 terug als er genoeg ruimte aan de voorkant is en dus geen blokkade.
}


void richting(int richting_getal, int afstand_te_meten){                                     // Functie die de auto een richting op laat rijden.
  if(richting_getal == 0){                                                                   // Als de eerder gekozen richting 0 was gaat de auto rechtdoor. 
    rechtdoor();
  }
    
  else if(richting_getal == 1){                                                              // Als de eerder gekozen richting 1 was gaat de auto rechtsaf.
    stoppen();
    delay(100);
    achteruit();
    delay(300);
    rechtsaf();
    delay(400);
  }
  else if(richting_getal == 2){                                                              // Als de eerder gekozen richting 2 was gaat de auto linksaf.
    stoppen();
    delay(100);
    achteruit();
    delay(300);
    linksaf();
    delay(400);
  }
  else if(richting_getal == 3){                                                               // Als de eerder gekozen richting 3 was gaat de auto 1 seconde achteruit.
    achteruit();
    delay(1000);                                            
    int nieuwe_links = meten(EchoPin1);                                                       // Tussentijdse zijkant metingen om te kijken of hij achteruit moet blijven rijden.
    int nieuwe_rechts = meten(EchoPin2);

    if(nieuwe_rechts >= afstand_te_meten){                                                    // Als er rechts genoeg ruimte is dan gaat hij naar rechts.
      rechtsaf();
      delay(400);
    }
    else if(nieuwe_rechts < afstand_te_meten && nieuwe_links >= afstand_te_meten){            // Als er links genoeg ruimte is dan gaat hij naar links.
      linksaf();
      delay(400);
    }
    else if(nieuwe_rechts < afstand_te_meten && nieuwe_links < afstand_te_meten){             // Als er na 1 seconde achteruit rijden nog steeds niet genoeg ruimte is aan de zijkant, dan roept de functie
      richting(richting_getal, afstand_te_meten);                                             // zichzelf weer aan en rijd hij nogmaals een seconde achteruit.
    }
  }
}



vector<int> flameSensorReadings(){                                                            // Functie om de 5 vlamsensoren aan de voorkant te meten.
  int sensorReading1 = analogRead(A5);
  int sensorReading2 = analogRead(A4);
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A2);
  int sensorReading5 = analogRead(A1);
  return {sensorReading1,sensorReading2,sensorReading3,sensorReading4,sensorReading5};
  }


int flameSensorReadingsTotaal(){                                                              // Functie die de waardes van de vlamsensoren bij elkaar optelt, deze is nodig om te vergelijken met de 
  int sensorReading1 = analogRead(A5);                                                        // eerder vastgestelde threshold.
  int sensorReading2 = analogRead(A4);                                                         
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A2);
  int sensorReading5 = analogRead(A1);
  return sensorReading1+sensorReading2+sensorReading3+sensorReading4+sensorReading5;
  }


void flameCheck(){                                                                            // Functie om te kijken of 1 van de vlamsensoren een waarde heeft die groter is dan de threshold.
  vector<int> sensorReading = flameSensorReadings();                                          // zo ja, dan roept hij flameLocaliser aan. Deze bepaalt hoe hij naar de vlam toe rijd.
  if (sensorReading[0]>treshold || sensorReading[1]>treshold || sensorReading[2]>treshold
  || sensorReading[3]>treshold || sensorReading[4]>treshold){
    flameLocaliser();
    }
  }


void vlamUitblazen(){                                                                         // Functie die ventilator aanzet om de vlam te blussen. Hij blijft doorgaan totdat de vlam uit is.
  int sensorReadingsTotaal = flameSensorReadingsTotaal();
  analogWrite(fanPin,255);
  while (sensorReadingsTotaal > treshold){
    delay(3000);
    sensorReadingsTotaal = flameSensorReadingsTotaal();
    }
  analogWrite(fanPin,0);
  }


void vlamGevonden(){                                                                          // Functie om te kijken of de vlam dichtbij genoeg is. Hiervoor word de eerder genoemde totaalwaarde gebruikt.
  int sensorReadingsTotaal = flameSensorReadingsTotaal();                                     
  stoppen();
  while(sensorReadingsTotaal > treshold){                                                     // Zolang er vuur is blijft hij vlamUitblazen aanroepen. Checkt eens per 5 seconde of er nog steeds vuur is.
    vlamUitblazen();
    delay(5000);
    sensorReadingsTotaal = flameSensorReadingsTotaal();
    }
  MP3command(stopgeluid, 4);                                                                  // Zet sirene uit als het vuur is geblust.
  SireneAan = 0;                                                                              // Reset de SireneAan waarde weer naar 0 zodat later de sirene opnieuw aangezet kan worden.
  achteruit();
  delay(500);
  stoppen();
  overwinnings_dansje();                                                                      // Doet zijn overwinningsdansje.
  }


void flameLocaliser(){                                                                        // Functie die bepaalt hoe de auto naar de vlam kan toe rijden. 
                                                                                              // Hij draait steeds naar het vuur en rijd dan rechtdoor.
  if(SireneAan==0){                                                                           // Als de SireneAan waarde op 0 stond dan zet hij zijn sirenes aan. We doen dit met een SireneAan waarde zodat
    MP3command(sirene, 6);                                                                    // hij niet steeds opnieuw aangeroepen kan worden als hij zijn nieuwe route naar het vuur berekent.
    SireneAan = 1; 
    }
  vector<int> afstandVoor = metenVoor();                                                      // Checkt of er genoeg ruimte is om naar de vlam te rijden.
  delay(80);
  vector<int> afstandZijkant = metenZijkant();
  
  int totaalSensorReadings = flameSensorReadingsTotaal();                                     // Kijk wat de totale waarde van de vlamsensoren is om te kijken of je dichtbij de vlam bent.
  vector<int> sensorReading = flameSensorReadings();
  
  while (25 < afstandVoor[0] && 25 < afstandVoor[1] || totaalSensorReadings < tresholdDichtbij) { // Blijft in deze loop zolang er genoeg ruimte is aan de voorkant om naar de vlam te rijden of als hij
                                                                                                  // nog niet dicht genoeg is bij het vuur.
    totaalSensorReadings = flameSensorReadingsTotaal();
    sensorReading = flameSensorReadings();
    
    if (sensorReading[0]>sensorReading[1] && sensorReading[0]>sensorReading[2] &&                 // Als de rechter vlamsensor de grootste waarde heeft, rijd hij naar rechts.
    sensorReading[0]>sensorReading[3] && sensorReading[0]>sensorReading[4]){
      rechtsaf();
      delay(400);
      }
    else if (sensorReading[1]>sensorReading[0] && sensorReading[1]>sensorReading[2] &&            // Als de rechtsvoor vlamsensor de grootste waarde heeft, rijd hij schuin naar rechts.
    sensorReading[1]>sensorReading[3] && sensorReading[1]>sensorReading[4]){
      rechtsaf();
      delay(200);
      }
    else if (sensorReading[2]>sensorReading[0] && sensorReading[2]>sensorReading[1] &&            // Als de middelste vlamsensor de grootste waarde heeft, rijd hij rechtdoor. 
    sensorReading[2]>sensorReading[3] && sensorReading[2]>sensorReading[4]){    
      rechtdoor();
      if (25 < afstandVoor[0] || 25 < afstandVoor[1]){                                            // Terwijl hij rechtdoor rijd checkt hij of er geen obstakels zijn. Als er wel een obstakel is dan stop hij
        afstandVoor = metenVoor();                                                                // met naar de vlam rijden en ontwijk hij eerst het object. Daarna kan hij weer de vlam oppakken.
        delay(80);
        afstandZijkant = metenZijkant();
        
        int reactie_keuze = blokkade_checker(metenZijkant[0], metenZijkant[1], 25, 30,
        metenVoor[0], metenVoor[1]);
        richting(reactie_keuze, 30);        
        
        break;
        }
      }
    else if (sensorReading[3]>sensorReading[0] && sensorReading[3]>sensorReading[1] &&            // Als de linksvoor vlamsensor de grootste waarde heeft, rijd hij schuin naar links.
    sensorReading[3]>sensorReading[2] && sensorReading[3]>sensorReading[4]){
      linksaf();
      delay(200);
      }
    else if (sensorReading[4]>sensorReading[0] && sensorReading[4]>sensorReading[1] &&            // Als de linker vlamsensor de grootste waarde heeft, rijd hij naar links.
    sensorReading[4]>sensorReading[2] && sensorReading[4]>sensorReading[3]){
      linksaf();
      delay(400);
      }
    rechtdoor();
    delay(100);  
      
    afstandVoor = metenVoor();                                                                    // Meet de afstand aan de voorkant opnieuw voordat je de while loop opnieuw opstart.
    }

  if (totaalSensorReadings > tresholdDichtbij){                                                   // Als je dichtbij genoeg bent bij de vlam, roep dan vlamGevonden aan.
    vlamGevonden();
    }
  }

  


void loop() {                                                                                     // De main loop in ons programma.
  vector<int> afstandVoor = metenVoor();                                                          // Bereken de afstand voor de voor- en zijkanten. 
  delay(80);
  vector<int> afstandZijkant = metenZijkant();            
 
  int reactie_keuze = blokkade_checker(afstandZijkant[0], afstandZijkant[1],                      // Bereken welke kant hij op kan rijden.
  afstand_te_meten_voor, afstand_te_meten_zijkant,afstandVoor[0], afstandVoor[1]);
  
  richting(reactie_keuze, afstand_te_meten_zijkant);                                              // Rijd de kant op die vrij is.
  
  delay(80);

  flameCheck();                                                                                   // Checkt na elke keer ergens heen rijden of er vuur is. Zo niet dan blijft hij rijden. 
                                                                                                  // Als er wel vuur is dan gaat hij het vuur traject af om de vlam te blussen.
}
