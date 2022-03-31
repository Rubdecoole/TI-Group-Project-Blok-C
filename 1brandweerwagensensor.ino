int TriggerPin1 = 2;
int EchoPin3 = 5;

int motorForwardPin = 6;
int motorReversePin = 9;
int motorForwardPin2 = 10;
int motorReversePin2 = 11;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin3, INPUT);

  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  pinMode(motorForwardPin2, OUTPUT);
  pinMode(motorReversePin2, OUTPUT);
}

int afstandprinten(int centimeters, int sensornummer){ //Functie om de afstand naar monitor te printen(tijdelijke functie)
  Serial.print("De afstand voor Sensor ");
  Serial.print(sensornummer);
  Serial.print(" is: "); 
  Serial.print(centimeters);
  Serial.print(" centimeters.\n");}
  
int meten(int echopinnummer){ //Berekent de afstand
  digitalWrite(TriggerPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(TriggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW); //Afstandssensor een sonar laten sturen
  
  int tijdgemeten = pulseIn(echopinnummer, HIGH);//Meet hoelang de sonar deed om weer terug te komen bij de sensor
  int afstand = (tijdgemeten/2) / 29.1; //Afstand berekenen is reistijd/2 * snelheid van geluid (je kan ook / 29.1 doen) in centimeters.
  return afstand;}

char blokkade_checker(int afstandVoor, int afstandRechts, int afstandLinks){ //Checkt als er een blokkade voor is or er links of rechts ruimte vrij is.
  if(afstandVoor < 20){//Checkt of er meer dan 20 cm vrij is aan de voorkant
    
    if(afstandRechts >= 20 && afstandLinks >= 20 || afstandRechts >= 20 && afstandLinks < 20){
      return 1;} //Als er aan links en rechts genoeg ruimte is OF alleen rechts genoeg ruimte, geeft hij 1 terug
      
    else if(afstandRechts < 20 && afstandLinks >= 20){
      return 2;} //Als er alleen links ruimte is geeft hij 2 terug
    else{
      return 3;
    }
  }
  else{
    return 0;} //Geeft 0 terug als er genoeg ruimte aan de voorkant is en dus geen blokkade
}

void richting(int richting_getal){ //Stuurt naar de monitor welke richting de auto op moet(tijdelijke functie)
  if(richting_getal == 0){
    Serial.print("Ga rechtdoor\n"); //Als de eerder gekozen richting 0 was kan de auto rechtdoor. 
    analogWrite(motorForwardPin, 180);
    analogWrite(motorReversePin, 0);
    analogWrite(motorForwardPin2, 140);
    analogWrite(motorReversePin2, 0);}
    
  else if(richting_getal == 1){
    Serial.print("Ga naar rechts\n");} //Als de eerder gekozen richting 1 was kan/moet de auto rechtsaf
  else if(richting_getal == 2){
    Serial.print("Ga naar links\n");} //Als de eerder gekozen richting 2 was dan kan de auto alleen linksaf
  else if(richting_getal == 3){
    Serial.print("Ga achteruit\n");
    analogWrite(motorForwardPin, 0);
    analogWrite(motorReversePin, 180);
    analogWrite(motorForwardPin2, 0);
    analogWrite(motorReversePin2, 140);
    delay(5000);
  }
}
void loop() {
  //cm 5, is linksvoor, cm4 is rechtsvor, cm3 is de Voorkant sensor, cm2 is de rechterkant en cm1 is de linkerkant

  int cm3 = meten(EchoPin3);
  afstandprinten(cm3, 3);

  int reactie_keuze = blokkade_checker(cm3, 5, 5);
  
  richting(reactie_keuze);

  delay(500);
}
