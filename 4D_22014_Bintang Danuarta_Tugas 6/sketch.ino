const int mqPin = A0;    // Pin analog untuk sensor MQ
const int buzzerPin = 5; // Pin untuk buzzer
const int threshold = 500;  // Ambang batas deteksi gas

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(mqPin);

  Serial.print("Nilai Gas: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    tone(buzzerPin, 1000);  // Nyalakan buzzer jika gas terdeteksi
    Serial.println("Deteksi Gas!");
  } else {
    noTone(buzzerPin);   // Matikan buzzer jika tidak ada deteksi gas
  }

  delay(1000);
}
