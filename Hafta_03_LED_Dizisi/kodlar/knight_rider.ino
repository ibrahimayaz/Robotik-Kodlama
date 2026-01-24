/*
 * Knight Rider Efekti
 * LED'ler sağa-sola hareket eder (KITT efekti)
 * 
 * Devre Bağlantısı:
 * Pin 8-13 -> 220Ω Direnç -> LED -> GND
 */

int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;
int gecikme = 100;

void setup() {
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void loop() {
  // Sağa doğru
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(gecikme);
    digitalWrite(ledPinleri[i], LOW);
  }
  
  // Sola doğru (kenar LED'leri atlayarak)
  for (int i = pinSayisi - 2; i > 0; i--) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(gecikme);
    digitalWrite(ledPinleri[i], LOW);
  }
}
