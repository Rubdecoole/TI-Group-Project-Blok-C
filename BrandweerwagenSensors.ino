int TriggerPin1 = 11;
int EchoPin1 = 12;
int TriggerPin2 = 6;
int EchoPin2 = 7;
int TriggerPin3 = 2;
int EchoPin3 = 3;

int lampVooruit = 8;
int lampRechts = 9;
int lampLinks = 10;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TriggerPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TriggerPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
  
  pinMode(lampVooruit, OUTPUT);
  pinMode(lampRechts, OUTPUT);
  pinMode(lampLinks, OUTPUT);
}

int afstandprinten(int centimeters, int sensornummer){ //Functie om de afstand naar monitor te printen(tijdelijke functie)
  Serial.print("De afstand voor Sensor ");
  Serial.print(sensornummer);
  Serial.print(" is: "); 
  Serial.print(centimeters);
  Serial.print(" centimeters.\n");}
  
int meten(int triggerpinnummer, int echopinnummer){ //Berekent de afstand
  digitalWrite(triggerpinnummer, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerpinnummer, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpinnummer, LOW); //Afstandssensor een sonar laten sturen
  
  int tijdgemeten = pulseIn(echopinnummer, HIGH);//Meet hoelang de sonar deed om weer terug te komen bij de sensor
  int afstand = (tijdgemeten/2) / 29.1; //Afstand berekenen is reistijd/2 * snelheid van geluid (je kan ook / 29.1 doen) in centimeters.
  return afstand;}

char blokkade_checker(int afstandVoor, int afstandRechts, int afstandLinks){ //Checkt als er een blokkade voor is or er links of rechts ruimte vrij is.
  if(afstandVoor < 15){//Checkt of er meer dan 15 cm vrij is aan de voorkant
    
    if(afstandRechts >= 15 && afstandLinks >= 15 || afstandRechts >= 10 && afstandLinks < 15){
      return 1;} //Als er aan links en rechts genoeg ruimte is OF alleen rechts genoeg ruimte, geeft hij 1 terug
      
    else if(afstandRechts < 15 && afstandLinks >= 15){
      return 2;} //Als er alleen links ruimte is geeft hij 2 terug
  }
  else{
    return 0;} //Geeft 0 terug als er genoeg ruimte aan de voorkant is en dus geen blokkade
}

void richting(int richting_getal){ //Stuurt naar de monitor welke richting de auto op moet(tijdelijke functie)
  if(richting_getal == 0){
    Serial.print("Ga rechtdoor\n"); //Als de eerder gekozen richting 0 was kan de auto rechtdoor. 
    digitalWrite(lampVooruit, HIGH); //Alleen rechtdoorlamp gaat aan
    digitalWrite(lampRechts, LOW);
    digitalWrite(lampLinks, LOW);}
  else if(richting_getal == 1){
    Serial.print("Ga naar rechts\n"); //Als de eerder gekozen richting 1 was kan/moet de auto rechtsaf
    digitalWrite(lampVooruit, LOW); //Alleen rechtsaf lamp gaat aan
    digitalWrite(lampRechts, HIGH);
    digitalWrite(lampLinks, LOW);}
  else if(richting_getal == 2){
    Serial.print("Ga naar links\n"); //Als de eerder gekozen richting 2 was dan kan de auto alleen linksaf
    digitalWrite(lampVooruit, LOW); //Alleen linksaf lamp gaat aan
    digitalWrite(lampRechts, LOW);
    digitalWrite(lampLinks, HIGH);}
}
void loop() {
  //cm3 is de Voorkant sensor, cm2 is de rechterkant en cm1 is de linkerkant
  int cm1 = meten(TriggerPin1, EchoPin1); //Vraagt de afstand die sensor X meet.
  afstandprinten(cm1, 1); //Afstand naar monitor printen

  int cm2 = meten(TriggerPin2, EchoPin2);
  afstandprinten(cm2, 2); 

  int cm3 = meten(TriggerPin3, EchoPin3);
  afstandprinten(cm3, 3);

  int reactie_keuze = blokkade_checker(cm3, cm2, cm1);
  
  richting(reactie_keuze);

  delay(500);
}
