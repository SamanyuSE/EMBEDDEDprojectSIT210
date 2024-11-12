#include <WiFiNINA.h>
#include <SPI.h>

const char* ssid = "DESKTOP-770LUMN 7689";
const char* password = "71Z&622h";

WiFiClient client;
const char* serverIP = "192.168.137.163";  // IP of your Raspberry Pi
const int port = 12345;

int soilMoisturePin1 = A0;
int soilMoisturePin2 = A1;

void setup() {
  Serial.begin(9600);
  pinMode(soilMoisturePin1, INPUT);
  pinMode(soilMoisturePin2, INPUT);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
  }
  Serial.println("Connected to WiFi.");
}

void loop() {
  int moisture1 = analogRead(soilMoisturePin1);
  int moisture2 = analogRead(soilMoisturePin2);

  if (client.connect(serverIP, port)) {
    client.print(String(moisture1) + "," + String(moisture2));
    client.stop();
  }

  delay(5000);  // Send data every 5 seconds
}
