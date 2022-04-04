#include <Servo.h>
#define FLAME 2

Servo servo;

int pos = 0; 
int vuurdetectie = 0;
bool vuur(){
  int fire = digitalRead(FLAME);

  if(fire == HIGH){

    return true;
  }
  else{

    return false;
  }
}

void setup() {
Serial.begin(9600);
pinMode(FLAME, INPUT);


servo.attach(9);
servo.write(0);
}

void spotter () {
for (pos = 0 ; pos <= 160 ; pos+=2){
   bool vuur2 = vuur();
   if(vuur2 == true){
      vuurdetectie = 1;
      Serial.print("Wow, vuur op positie: ");
      Serial.print(analogRead(A0));
      Serial.print("\n");
      Serial.print("Servo positie is op: ");
      Serial.print(pos);
      Serial.print(" graden");
      break;
   }
 else{
  Serial.print("Niets aan de hand....\n");
 }
 
   servo.write(pos);
}}


void loop() {
  if(vuurdetectie == 0){
    spotter ();
  }



  delay(10);
  
}
