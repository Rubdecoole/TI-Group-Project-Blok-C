#include <Servo.h>
#define FLAME 2

Servo servo;

int pos = 0; 

bool vuur(){
  int fire = digitalRead(FLAME);

  if(fire == HIGH){
    Serial.print("wow, vuur!");
    return true;
  }
  else{
    Serial.print("Niets aan de hand");
    return false;
  }
}

void setup() {

pinMode(FLAME, INPUT);


servo.attach(9);
servo.write(0);
}

void loop() {
  bool vuur2 = vuur();

for (pos = 0 ; pos <= 180 ; pos++){

  if (vuur2 == true){
    break;
  }
  servo.write(pos);

  Serial.print("\n");


  delay(10);
  
}

}
