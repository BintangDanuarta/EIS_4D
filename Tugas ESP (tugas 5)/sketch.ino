/**
   ESP32 + DHT22 + ThingSpeak Example using Wokwi
   By IoT Frontier
*/

#include <WiFi.h>
#include <DHTesp.h>
#include <UrlEncode.h>
#include <HTTPClient.h>

const int DHT_PIN = 15; // DHT22 sensor GPIO Pin
const char* WIFI_NAME = "Wokwi-GUEST"; // WiFi SSID
const char* WIFI_PASSWORD = ""; // WiFI Password
float suhu = 0;
float kelembaban = 0;

// Create an instance of the DHTesp library
DHTesp dhtSensor; 
// Create a WiFi client object
WiFiClient client; 

void sendMessage(String message){

  HTTPClient http;

    // URL yang akan diakses
    http.begin("https://wassup.codinginan.com/send-message?api_key=7vjF9ac0zIuclLXboUI1GvBeNmhyJW&sender=6281292200561&number=6285161740004|082110677645&message=" + urlEncode(message));

    // Melakukan HTTP GET
    int httpCode = http.GET();

    if (httpCode > 0) { // Jika berhasil terhubung
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Gagal melakukan request");
    }
}


void setup() {
  // Initialize the serial communication at a baud rate of 115200
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22); // Initialize the DHT22 sensor
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD); // Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Wifi not connected"); // Print a message if WiFi is not connected
  }
  Serial.println("Wifi connected !"); // Print a message if WiFi is connected
  Serial.println("Local IP: " + String(WiFi.localIP())); // Print the local IP address
  WiFi.mode(WIFI_STA); // Set the WiFi mode to station mode
}

void loop() {
  Serial.print("Temp: ");
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  suhu=data.temperature;
  kelembaban=data.humidity;
  Serial.print("Temp: ");
  Serial.print(suhu);
  Serial.println("C");
  Serial.print("Hum: ");
  Serial.print(kelembaban);
  Serial.println("%");
  delay(2000); // Wait for a new reading from the sensor (DHT22 has ~0.5Hz sample rate)

  if (suhu > 38) {
    Serial.println("Temperature Tinggi");
    sendMessage("SUHUNYA KETINGGIAAAAAAAAAAAAANNN AWAS ANAK AYAM MATI DOSA TANGGUNG SENDIRI");
  }
}