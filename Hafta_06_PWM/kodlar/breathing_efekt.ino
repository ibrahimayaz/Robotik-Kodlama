/*
 * Breathing (Soluma) Efekti
 * LED yavaşça parlar ve söner
 * 
 * Devre Bağlantısı:
 * Pin 9 (PWM) -> 220Ω -> LED -> GND
 */

const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Breathing Efekti Baslatildi");
}

void loop() {
  // Yavaşça parla
  Serial.println("Parlatiyor...");
  for (int parlaklik = 0; parlaklik <= 255; parlaklik++) {
    analogWrite(ledPin, parlaklik);
    delay(10);
  }
  
  // Yavaşça sön
  Serial.println("Sonduruyor...");
  for (int parlaklik = 255; parlaklik >= 0; parlaklik--) {
    analogWrite(ledPin, parlaklik);
    delay(10);
  }
}
