/*
 * Engelden Kaçan Robot
 * Ultrasonik sensör ile engel algılama ve kaçınma
 * 
 * Devre Bağlantısı:
 * HC-SR04 VCC -> 5V
 * HC-SR04 TRIG -> A0
 * HC-SR04 ECHO -> A1
 * HC-SR04 GND -> GND
 * 
 * Servo (Radar):
 * Kahverengi -> GND
 * Kırmızı -> 5V
 * Turuncu -> Pin 3
 * 
 * Motor A (Sol) - L298N:
 * ENA -> Pin 10 (PWM)
 * IN1 -> Pin 9
 * IN2 -> Pin 8
 * 
 * Motor B (Sağ) - L298N:
 * ENB -> Pin 5 (PWM)
 * IN3 -> Pin 7
 * IN4 -> Pin 6
 */

#include <Servo.h>

// Ultrasonik sensör pinleri
const int trigPin = A0;
const int echoPin = A1;

// Servo (radar için)
Servo radar;
const int servoPin = 3;

// Motor A (Sol)
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

// Motor B (Sağ)
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

// Ayarlar
int hiz = 180;  // Motor hızı (0-255)
const int ESIK_MESAFE = 25;  // cm - bu mesafeden yakınsa engel var

void setup() {
  // Ultrasonik sensör
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Servo
  radar.attach(servoPin);
  radar.write(90);  // İleri bak
  
  // Motor pinleri
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Engelden Kacan Robot");
  Serial.println("====================");
  
  delay(1000);  // Başlangıç gecikmesi
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

void ileri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void geri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sol() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sag() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void dur() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

float sola_bak() {
  radar.write(150);
  delay(300);
  float mesafe = mesafeOlc();
  Serial.print("Sol mesafe: ");
  Serial.println(mesafe);
  radar.write(90);
  delay(200);
  return mesafe;
}

float saga_bak() {
  radar.write(30);
  delay(300);
  float mesafe = mesafeOlc();
  Serial.print("Sag mesafe: ");
  Serial.println(mesafe);
  radar.write(90);
  delay(200);
  return mesafe;
}

void loop() {
  float mesafe = mesafeOlc();
  
  Serial.print("On mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");
  
  if (mesafe > ESIK_MESAFE || mesafe <= 0) {
    // Yol açık, ileri git
    ileri();
    Serial.println(">>> ILERI");
  } else {
    // Engel var!
    Serial.println("!!! ENGEL ALGILANDI !!!");
    
    // Dur
    dur();
    delay(200);
    
    // Biraz geri git
    geri();
    delay(300);
    dur();
    
    // Sol ve sağa bak
    float solMesafe = sola_bak();
    float sagMesafe = saga_bak();
    
    Serial.print("Sol: ");
    Serial.print(solMesafe);
    Serial.print(" cm\t Sag: ");
    Serial.print(sagMesafe);
    Serial.println(" cm");
    
    // Daha açık olan tarafa dön
    if (solMesafe > sagMesafe) {
      Serial.println(">>> SOLA DON");
      sol();
      delay(400);
    } else {
      Serial.println(">>> SAGA DON");
      sag();
      delay(400);
    }
    dur();
  }
  
  delay(50);
}
