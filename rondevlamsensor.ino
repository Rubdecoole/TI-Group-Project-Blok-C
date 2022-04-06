void setup() {
  Serial.begin(9600);  
}
void loop() {
  // read the sensor on analog A0:
  int sensor0 = analogRead(A0);
  int sensor1 = analogRead(A1);
  int sensor2 = analogRead(A2);
  int sensor3 = analogRead(A3);
  int sensor4 = analogRead(A4);

  Serial.println("Sensor 0 geeft: " + sensor0);
  Serial.println("Sensor 1 geeft: " + sensor1);
  Serial.println("Sensor 2 geeft: " + sensor2);
  Serial.println("Sensor 3 geeft: " + sensor3);
  Serial.println("Sensor 4 geeft: " + sensor4);
  delay(1000); 
}
