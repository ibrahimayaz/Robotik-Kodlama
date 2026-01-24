/*
 * SOS Morse Kodu
 * S = ···  (3 kısa)
 * O = ---  (3 uzun)
 * S = ···  (3 kısa)
 * 
 * Devre Bağlantısı:
 * Pin 13 -> 220Ω Direnç -> LED Anot (+)
 * LED Katot (-) -> GND
 */

const int ledPin = 13;
const int kisaSure = 200;     // Kısa sinyal (nokta)
const int uzunSure = 600;     // Uzun sinyal (çizgi)
const int aralik = 200;       // Sinyal arası
const int harfArasi = 400;    // Harf arası
const int kelimeArasi = 2000; // Kelime arası

void setup() {
  pinMode(ledPin, OUTPUT);
}

// LED'i belirtilen süre yak
void sinyal(int sure) {
  digitalWrite(ledPin, HIGH);
  delay(sure);
  digitalWrite(ledPin, LOW);
  delay(aralik);
}

// S harfi: 3 kısa sinyal
void harfS() {
  for(int i = 0; i < 3; i++) {
    sinyal(kisaSure);
  }
}

// O harfi: 3 uzun sinyal
void harfO() {
  for(int i = 0; i < 3; i++) {
    sinyal(uzunSure);
  }
}

void loop() {
  // S
  harfS();
  delay(harfArasi);
  
  // O
  harfO();
  delay(harfArasi);
  
  // S
  harfS();
  delay(kelimeArasi);
}
