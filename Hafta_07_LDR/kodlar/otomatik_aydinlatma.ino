/*
 * Otomatik Aydınlatma (Akıllı Sokak Lambası)
 * Karanlık olunca LED yanar
 * Parlaklık ışık seviyesiyle ters orantılı
 * 
 * Devre Bağlantısı:
 * 5V -> LDR -> A0 -> 10kΩ -> GND
 * Pin 9 -> 220Ω -> LED -> GND
 */

const int ldrPin = A0;
const int ledPin = 9;
const int esikDeger = 500;  // Kalibrasyon sonrası ayarlanmalı

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Otomatik Aydinlatma Sistemi");
  Serial.println("===========================");
}

void loop() {
  int isikSeviyesi = analogRead(ldrPin);
  
  Serial.print("Isik Seviyesi: ");
  Serial.print(isikSeviyesi);
  
  if (isikSeviyesi < esikDeger) {
    // Karanlık - LED parlaklığı ters orantılı
    int parlaklik = map(isikSeviyesi, 0, esikDeger, 255, 0);
    parlaklik = constrain(parlaklik, 0, 255);
    
    analogWrite(ledPin, parlaklik);
    
    Serial.print("\t LED Parlaklik: ");
    Serial.print(parlaklik);
    Serial.println(" (ACIK)");
  } else {
    // Aydınlık - LED kapalı
    analogWrite(ledPin, 0);
    Serial.println("\t LED: KAPALI");
  }
  
  delay(200);
}
