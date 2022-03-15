int TriggerPin1 = 11;
int EchoPin1 = 12;
int TriggerPin2 = 6;
int EchoPin2 = 7;
int TriggerPin3 = 2;
int EchoPin3 = 3;
void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TriggerPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TriggerPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
}

int afstandprinten(int centimeters, int sensornummer){
  Serial.print("De afstand voor Sensor ");
  Serial.print(sensornummer);
  Serial.print(" is: "); 
  Serial.print(centimeters);
  Serial.print(" centimeters.\n");}
  
int meten(int triggerpinnummer, int echopinnummer){
  digitalWrite(triggerpinnummer, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerpinnummer, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpinnummer, LOW);
  int tijdgemeten = pulseIn(echopinnummer, HIGH);
  return tijdgemeten;}

bool blokkade_checker(){
  
}
  
void loop() {
  int cm1, cm2, cm3;
  
  int tijd1 = meten(TriggerPin1, EchoPin1);
  cm1 = (tijd1/2) / 29.1; //Afstand berekenen is reistijd/2 * snelheid van geluid
  afstandprinten(cm1, 1);

  int tijd2 = meten(TriggerPin2, EchoPin2);
  cm2 = (tijd2/2) / 29.1;
  afstandprinten(cm2, 2);

  int tijd3 = meten(TriggerPin3, EchoPin3);
  cm3 = (tijd3/2) / 29.1;
  afstandprinten(cm3, 3);

  
  delay(500);
  exit(0);
}
