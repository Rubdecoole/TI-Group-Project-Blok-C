int TriggerPin1 = 2;
int EchoPin1 = 13;
int EchoPin2 = 4;
int EchoPin4 = 7;
int EchoPin5 = 8;

int fanPin = 3;

int motorForwardPin = 5;
int motorReversePin = 6;
int motorForwardPin2 = 10;
int motorReversePin2 = 11;

const int treshold = 600;           // sensor fire detection treshold
const int tresholdDichtbij = 2700;   // sensor fire dichtbij treshold --waarde van lamp: 4980--



void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(EchoPin2, INPUT);

  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  pinMode(motorForwardPin2, OUTPUT);
  pinMode(motorReversePin2, OUTPUT);

  pinMode(fanPin, OUTPUT);
  analogWrite(fanPin,0);


}

void rechtsaf(){
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 50);
    analogWrite(motorForwardPin2, 50);
    analogWrite(motorReversePin2, 0);
}

void linksaf(){
    analogWrite(motorForwardPin, 50);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 50);
    
}

void rechtdoor(){
    analogWrite(motorForwardPin, 90);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 66);
    analogWrite(motorReversePin2, 0);
}

void achteruit(){
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 130);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 130);
}

void stoppen(){
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 0);
}

void overwinnings_dansje(){
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
  stoppen();
  //ledjes hier nog laten knipperen? :)
}



int afstandprinten(int centimeters, int sensornummer){ //Functie om de afstand naar monitor te printen(tijdelijke functie)
  // Serial.print("De afstand voor Sensor ");
  // Serial.print(sensornummer);
  // Serial.print(" is: "); 
  // Serial.print(centimeters);
  // Serial.print(" centimeters.\n");
}



int meten(int echopinnummer){ //Berekent de afstand
  digitalWrite(TriggerPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(TriggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW); //Afstandssensor een sonar laten sturen
  
  int tijdgemeten = pulseIn(echopinnummer, HIGH);//Meet hoelang de sonar deed om weer terug te komen bij de sensor
  int afstand = (tijdgemeten/2) / 29.1; //Afstand berekenen is reistijd/2 * snelheid van geluid (je kan ook / 29.1 doen) in centimeters.
  return afstand;}



char blokkade_checker(int afstandRechts, int afstandLinks, int meetafstandvoor, int meetafstandzijkant, int afstandRechtsVoor, int afstandLinksVoor){ //Checkt als er een blokkade voor is or er links of rechts ruimte vrij is.
  if(afstandRechtsVoor < meetafstandvoor || afstandLinksVoor < meetafstandvoor){//Checkt of er meer dan 20 cm vrij is aan de voorkant
    
    if(afstandRechts >= meetafstandzijkant && afstandLinks >= meetafstandzijkant || afstandRechts >= meetafstandzijkant && afstandLinks < meetafstandzijkant){
      return 1;} //Als er aan links en rechts genoeg ruimte is OF alleen rechts genoeg ruimte, geeft hij 1 terug
      
    else if(afstandRechts < meetafstandzijkant && afstandLinks >= meetafstandzijkant){
      return 2;} //Als er alleen links ruimte is geeft hij 2 terug
    else{
      return 3;
    }
  }
  else{
    return 0;} //Geeft 0 terug als er genoeg ruimte aan de voorkant is en dus geen blokkade
}



void richting(int richting_getal, int afstand_te_meten){ //Stuurt naar de monitor welke richting de auto op moet(tijdelijke functie)
  if(richting_getal == 0){
    Serial.print("Ga rechtdoor\n"); //Als de eerder gekozen richting 0 was kan de auto rechtdoor. 
    rechtdoor();
  }
    
  else if(richting_getal == 1){
    Serial.print("Ga naar rechts\n"); //Als de eerder gekozen richting 1 was kan/moet de auto rechtsaf
    stoppen();
    delay(100);
    achteruit();
    delay(300);
    rechtsaf();
    delay(400);
  }
  else if(richting_getal == 2){
    Serial.print("Ga naar links\n"); //Als de eerder gekozen richting 2 was dan kan de auto alleen linksaf
    stoppen();
    delay(100);
    achteruit();
    delay(300);
    linksaf();
    delay(400);
  }
  else if(richting_getal == 3){
    Serial.print("Ga achteruit\n");
    achteruit();
    delay(1000);
    int nieuwe_links = meten(EchoPin1);
    int nieuwe_rechts = meten(EchoPin2);

    if(nieuwe_rechts >= afstand_te_meten){
      rechtsaf();
      delay(400);
    }
    else if(nieuwe_rechts < afstand_te_meten && nieuwe_links >= afstand_te_meten){
      linksaf();
      delay(400);
    }
    else if(nieuwe_rechts < afstand_te_meten && nieuwe_links < afstand_te_meten){
      richting(richting_getal, afstand_te_meten);
    }
  }
}




void flameCheck(){
  // read the sensor on analog A0:
  int sensorReading1 = analogRead(A5);
  int sensorReading2 = analogRead(A4);
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A2);
  int sensorReading5 = analogRead(A1);

  if (sensorReading1>treshold || sensorReading2>treshold || sensorReading3>treshold || sensorReading4>treshold || sensorReading5>treshold){
    flameLocaliser();
    }
  }




void flameLocaliser(){
  // Meet de afstand aan de voorkant
  int voorkant1 = meten(EchoPin4);
  delay(80);
  int voorkant2 = meten(EchoPin5);
  int zijkantRechts = 0;
  int zijkantLinks = 0;
  // Serial.println(String(voorkant1) + " en " + String(voorkant2));

  // leest de flamsensoren uit
  int sensorReading1 = analogRead(A5);
  int sensorReading2 = analogRead(A4);
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A2);
  int sensorReading5 = analogRead(A1);

  int totaalReadings = sensorReading1+sensorReading2+sensorReading3+sensorReading4+sensorReading5;
  
  while (25 < voorkant1 && 25 < voorkant2 || totaalReadings < tresholdDichtbij) {

    // leest de flamsensoren uit
    sensorReading1 = analogRead(A5);
    sensorReading2 = analogRead(A4);
    sensorReading3 = analogRead(A3);
    sensorReading4 = analogRead(A2);
    sensorReading5 = analogRead(A1);
    // Serial.println(String(voorkant1) + " en " + String(voorkant2));

    totaalReadings = sensorReading1+sensorReading2+sensorReading3+sensorReading4+sensorReading5;

    Serial.println(sensorReading1);
    Serial.println(sensorReading2);
    Serial.println(sensorReading3);
    Serial.println(sensorReading4);
    Serial.println(sensorReading5);
    
    if (sensorReading1>sensorReading2 && sensorReading1>sensorReading3 && sensorReading1>sensorReading4 && sensorReading1>sensorReading5){
      Serial.println("rechts");
      rechtsaf();
      delay(400);
      }
    else if (sensorReading2>sensorReading1 && sensorReading2>sensorReading3 && sensorReading2>sensorReading4 && sensorReading2>sensorReading5){
      Serial.println("rechts-midden");
      rechtsaf();
      delay(200);
      }
    else if (sensorReading3>sensorReading1 && sensorReading3>sensorReading2 && sensorReading3>sensorReading4 && sensorReading3>sensorReading5){
      Serial.println("midden");
      rechtdoor();
      if (25 < voorkant1 || 25 < voorkant2){
        zijkantRechts = meten(EchoPin2);
        delay(80);
        zijkantLinks= meten(EchoPin1);
        delay(80);
        voorkant1 = meten(EchoPin4);
        delay(80);
        voorkant2 = meten(EchoPin5);

        int reactie_keuze = blokkade_checker(zijkantLinks, zijkantRechts, 25, 30, voorkant1, voorkant2);

        richting(reactie_keuze, 30);        
        
        break;
        }
      }
    else if (sensorReading4>sensorReading1 && sensorReading4>sensorReading2 && sensorReading4>sensorReading3 && sensorReading4>sensorReading5){
      Serial.println("links-midden");
      linksaf();
      delay(200);
      }
    else if (sensorReading5>sensorReading1 && sensorReading5>sensorReading2 && sensorReading5>sensorReading3 && sensorReading5>sensorReading4){
      Serial.println("links");
      linksaf();
      delay(400);
      }
    rechtdoor();
    delay(100);  

      
    // meet de afstand aan de voorkant
    voorkant1 = meten(EchoPin4);
    delay(80);
    voorkant2 = meten(EchoPin5);
    // Serial.println(String(voorkant1) + " en " + String(voorkant2));
    }
    
  if (totaalReadings > tresholdDichtbij){
    Serial.println("***Vlam gevonden***");
    stoppen();
    analogWrite(fanPin,255);
    delay(7000);
    analogWrite(fanPin,0);
    achteruit();
    delay(400);
    stoppen();
    overwinnings_dansje();
    }
  }

  



void loop() {
  
  //cm 5, is linksvoor, cm4 is rechtsvoor, cm3 is de Voorkant sensor, cm2 is de rechterkant en cm1 is de linkerkant
  int afstand_te_meten_voor = 25;
  int afstand_te_meten_zijkant = 30;
  
    
  int cm1 = meten(EchoPin1); //Vraagt de afstand die sensor X meet.
  delay(80);
  afstandprinten(cm1, 1);
  
  int cm2 = meten(EchoPin2);
  delay(80);
  afstandprinten(cm2, 2);
    
  int cm4 = meten(EchoPin4);
  delay(80);
  afstandprinten(cm4, 4);
  
  int cm5 = meten(EchoPin5);
  afstandprinten(cm5, 5);
  
    
  int reactie_keuze = blokkade_checker(cm2, cm1, afstand_te_meten_voor, afstand_te_meten_zijkant, cm4, cm5);
    
  richting(reactie_keuze, afstand_te_meten_zijkant);
  
  delay(80);

  flameCheck();
 
}
