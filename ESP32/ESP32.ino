#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Add Your WIFI SSID";
const char* password = "Add Your WIFI Password Here";

const int ledPin1 = 2; // Replace with the actual pin number for your first LED
const int ledPin2 = 12; // Replace with the actual pin number for your second LED
const int triggerPin = 15; // Trigger pin of the ultrasonic sensor
const int echoPin = 14; // Echo pin of the ultrasonic sensor

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<html><body><h1>ESP32 Control</h1><p><a href='/on1'>Turn On LED 1</a></p><p><a href='/off1'>Turn Off LED 1</a></p><p><a href='/on2'>Turn On LED 2</a></p><p><a href='/off2'>Turn Off LED 2</a></p><p>Distance: " + String(getDistance()) + " inches</p></body></html>");
  });

  server.on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin1, HIGH);
    request->send(200, "text/plain", "LED 1 turned on");
  });

  server.on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin1, LOW);
    request->send(200, "text/plain", "LED 1 turned off");
  });

  server.on("/on2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, HIGH);
    request->send(200, "text/plain", "LED 2 turned on");
  });

  server.on("/off2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, LOW);
    request->send(200, "text/plain", "LED 2 turned off");
  });

  server.begin();
}

void loop() {
}

long getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  // Speed of sound in air at 20°C is approximately 343 meters/second
  // We divide by 2 to account for the round trip of the ultrasonic signal
  return (duration * 0.0343) / 2;
  
}
