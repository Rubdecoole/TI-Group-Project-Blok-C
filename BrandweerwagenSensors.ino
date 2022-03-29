int TriggerPin1 = 11;
int EchoPin1 = 12;
int EchoPin2 = 7;
int EchoPin3 = 3;
int EchoPin4 = 4;
int EchoPin5 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(EchoPin3, INPUT);
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
  if(afstandVoor < 20){//Checkt of er meer dan 15 cm vrij is aan de voorkant
    
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
    Serial.print("Ga rechtdoor\n");} //Als de eerder gekozen richting 0 was kan de auto rechtdoor. 
  else if(richting_getal == 1){
    Serial.print("Ga naar rechts\n");} //Als de eerder gekozen richting 1 was kan/moet de auto rechtsaf
  else if(richting_getal == 2){
    Serial.print("Ga naar links\n");} //Als de eerder gekozen richting 2 was dan kan de auto alleen linksaf
  else if(richting_getal == 3){
    Serial.print("Ga achteruit\n");
  }
}
void loop() {
  //cm3 is de Voorkant sensor, cm2 is de rechterkant en cm1 is de linkerkant
  
  int cm1 = meten(EchoPin1); //Vraagt de afstand die sensor X meet.
  afstandprinten(cm1, 1); //Afstand naar monitor printen
  delay(150);
  
  int cm2 = meten(EchoPin2);
  afstandprinten(cm2, 2); 
  delay(150);

  int cm3 = meten(EchoPin3);
  afstandprinten(cm3, 3);
  delay(150);

  int cm4 = meten(EchoPin4);
  afstandprinten(cm4, 4);
  delay(150);

  int cm5 = meten(EchoPin5);
  afstandprinten(cm5, 5);
  delay(150);
  
  int reactie_keuze = blokkade_checker(cm3, cm2, cm1);
  
  richting(reactie_keuze);

  delay(500);
}
