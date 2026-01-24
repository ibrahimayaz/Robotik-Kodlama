/*
 * Basit Radar Sistemi
 * Servo ile ultrasonik sensör tarama
 * 
 * Devre Bağlantısı:
 * Servo Kahverengi -> GND
 * Servo Kırmızı -> 5V
 * Servo Turuncu -> Pin 9
 * HC-SR04 VCC -> 5V
 * HC-SR04 TRIG -> Pin 10
 * HC-SR04 ECHO -> Pin 11
 * HC-SR04 GND -> GND
 */

#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int trigPin = 10;
const int echoPin = 11;

void setup() {
  motor.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Radar Sistemi Baslatildi");
  Serial.println("Format: Aci,Mesafe");
}

float mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long sure = pulseIn(echoPin, HIGH, 30000);
  return sure / 58.2;
}

void loop() {
  // 0 -> 180 tarama
  for (int aci = 0; aci <= 180; aci += 5) {
    motor.write(aci);
    delay(50);  // Servo stabilizasyon
    
    float mesafe = mesafeOlc();
    
    // CSV formatında çıktı
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
  
  // 180 -> 0 tarama
  for (int aci = 180; aci >= 0; aci -= 5) {
    motor.write(aci);
    delay(50);
    
    float mesafe = mesafeOlc();
    
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
}
