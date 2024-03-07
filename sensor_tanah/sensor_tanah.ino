const int sensorPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  Serial.print("Nilai kelembaban tanah : ");
  Serial.println(sensorValue);

  delay(1000);
}
