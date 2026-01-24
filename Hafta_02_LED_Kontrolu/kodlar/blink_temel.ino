/*
 * Temel Blink Uygulaması
 * LED'i 1 saniye aralıklarla yakıp söndürür
 * 
 * Devre Bağlantısı:
 * Pin 13 -> 220Ω Direnç -> LED Anot (+)
 * LED Katot (-) -> GND
 */

void setup() {
  // Pin 13'ü çıkış olarak ayarla
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);  // LED'i yak
  delay(1000);             // 1 saniye bekle
  digitalWrite(13, LOW);   // LED'i söndür
  delay(1000);             // 1 saniye bekle
}
