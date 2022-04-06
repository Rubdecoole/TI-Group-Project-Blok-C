const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
const int treshold = 300;


void setup() {
  Serial.begin(9600);  
}
void loop() {
  // read the sensor on analog A0:
  int sensorReading1 = analogRead(A1);
  int sensorReading2 = analogRead(A2);
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A4);
  int sensorReading5 = analogRead(A5);
  // int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  if (sensorReading1>treshold || sensorReading2>treshold || sensorReading3>treshold ||sensorReading4>treshold || sensorReading5>treshold){
    if (sensorReading1>sensorReading2 && sensorReading1>sensorReading3 && sensorReading1>sensorReading4 && sensorReading1>sensorReading5){
      Serial.println("rechts");
      }
    else if (sensorReading2>sensorReading1 && sensorReading2>sensorReading3 && sensorReading2>sensorReading4 && sensorReading2>sensorReading5){
      Serial.println("rechts-midden");
      }
    else if (sensorReading3>sensorReading1 && sensorReading3>sensorReading2 && sensorReading3>sensorReading4 && sensorReading3>sensorReading5){
      Serial.println("midden");
      }
    else if (sensorReading4>sensorReading1 && sensorReading4>sensorReading2 && sensorReading4>sensorReading3 && sensorReading4>sensorReading5){
      Serial.println("links-midden");
      }
    else if (sensorReading5>sensorReading1 && sensorReading5>sensorReading2 && sensorReading5>sensorReading3 && sensorReading5>sensorReading4){
      Serial.println("links");
      }  
    }
  
//  Serial.println(sensorReading1);
//  Serial.println(sensorReading2);
//  Serial.println(sensorReading3);
//  Serial.println(sensorReading4);
//  Serial.println(sensorReading5);
  delay(1000); 
}
