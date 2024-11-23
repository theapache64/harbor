#include <Arduino.h>
#include <Servo.h>
#include <WiFi.cpp>
#include <map>
#include <string>
#include <Config.cpp>
#include <Telegram.cpp>

const int trigPin = D6;
const int echoPin = D5;
const int servoPin = D7;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;
Servo servo;
WiFiConnection wifi;
Config config;
Telegram telegram;
bool isBirdDetectAlerted = false;

void setup() {
  Serial.begin(115200); 
  wifi.connectToWifi();
  config.loadConfig();
  String allConfigs = config.allConfigs();
  telegram.sendHealth("Device started! 🚀 -> " + allConfigs);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  servo.attach(servoPin);
}

long lastHeartbeatSentAt = 0;

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

  if(distanceCm < config.getConfig("distance_threshold_in_cm", "10").toInt()) {
    servo.write(config.getConfig("servo_on_bird", "90").toInt());
    if(isBirdDetectAlerted == false) {
      telegram.sendAlert("Bird detected! 🐦");
      isBirdDetectAlerted = true;
    }
  } else {
    servo.write(config.getConfig("servo_on_watch", "0").toInt());
    isBirdDetectAlerted = false;
  }
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (CM): ");
  Serial.println(distanceCm);

  if(millis() - lastHeartbeatSentAt > config.getConfig("heartbeat_interval_in_sec", "60").toInt() * 1000.0) {
    telegram.sendHealth("Device is running! ❤️");
    lastHeartbeatSentAt = millis();
  }
  
  delay(config.getConfig("main_delay_in_ms", "1000").toInt());
}