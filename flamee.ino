#define FLAME 2
#define ALARM 8


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("test");
pinMode(FLAME, INPUT);

}

void loop() {
  int fire = digitalRead(FLAME);

  if(fire == HIGH){
    digitalWrite(ALARM, HIGH);
    Serial.println("wow, vuur!");
        Serial.print(analogRead(A0));}
    else{
      digitalWrite(ALARM, LOW);
      Serial.println("Niets aan de hand");

     
    }

    delay(300);

}
