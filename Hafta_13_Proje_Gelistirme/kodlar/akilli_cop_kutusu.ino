/*
 * Akıllı Çöp Kutusu
 * El yaklaştığında kapak otomatik açılır
 * 
 * Devre Bağlantısı:
 * HC-SR04 VCC -> 5V
 * HC-SR04 TRIG -> Pin 9
 * HC-SR04 ECHO -> Pin 10
 * HC-SR04 GND -> GND
 * Servo Kahverengi -> GND
 * Servo Kırmızı -> 5V
 * Servo Turuncu -> Pin 11
 * LED -> Pin 13 (dahili LED de kullanılabilir)
 */

#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int ledPin = 13;

Servo kapak;
bool kapakAcik = false;
unsigned long sonAcilis = 0;
const int ACIK_SURE = 3000;  // 3 saniye açık kalsın
const int ALGILAMA_MESAFE = 20;  // 20 cm içinde algıla

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  kapak.attach(servoPin);
  kapak.write(0);  // Kapak kapalı başlasın
  
  Serial.begin(9600);
  Serial.println("Akilli Cop Kutusu");
  Serial.println("=================");
  Serial.println("El yaklastiginizda kapak acilir");
}

float mesafeOlc() {
  // TRIG pinine 10μs pulse gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // ECHO pininden süreyi oku
  long sure = pulseIn(echoPin, HIGH, 30000);
  
  // Mesafeyi hesapla (cm)
  return sure / 58.2;
}

void kapakAc() {
  if (!kapakAcik) {
    Serial.println(">>> Kapak aciliyor...");
    
    // Yumuşak açılış animasyonu
    for (int aci = 0; aci <= 90; aci += 5) {
      kapak.write(aci);
      delay(20);
    }
    
    kapakAcik = true;
    digitalWrite(ledPin, HIGH);
    sonAcilis = millis();
    
    Serial.println("Kapak ACIK");
  } else {
    // Kapak zaten açık, süreyi sıfırla
    sonAcilis = millis();
  }
}

void kapakKapat() {
  Serial.println(">>> Kapak kapaniyor...");
  
  // Yumuşak kapanış animasyonu
  for (int aci = 90; aci >= 0; aci -= 5) {
    kapak.write(aci);
    delay(20);
  }
  
  kapakAcik = false;
  digitalWrite(ledPin, LOW);
  
  Serial.println("Kapak KAPALI");
}

void loop() {
  float mesafe = mesafeOlc();
  
  // Debug için mesafeyi yazdır
  Serial.print("Mesafe: ");
  Serial.print(mesafe, 1);
  Serial.print(" cm\t");
  
  // El algılandı mı?
  if (mesafe > 0 && mesafe < ALGILAMA_MESAFE) {
    Serial.println("El algilandi!");
    kapakAc();
  } else {
    Serial.println("");
  }
  
  // Kapak açıksa ve süre dolduysa kontrol et
  if (kapakAcik && (millis() - sonAcilis > ACIK_SURE)) {
    // Hala el var mı kontrol et
    mesafe = mesafeOlc();
    
    if (mesafe > ALGILAMA_MESAFE || mesafe <= 0) {
      // El yok, kapağı kapat
      kapakKapat();
    } else {
      // El hala var, süreyi uzat
      sonAcilis = millis();
      Serial.println("El hala var, sure uzatildi");
    }
  }
  
  delay(100);
}
