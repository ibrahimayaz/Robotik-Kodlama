/*
 * RGB LED Gökkuşağı Efekti
 * Yumuşak renk geçişleri
 * 
 * Devre Bağlantısı (Ortak Katot RGB LED):
 * Pin 9 -> 220Ω -> R (Kırmızı)
 * Pin 10 -> 220Ω -> G (Yeşil)
 * Pin 11 -> 220Ω -> B (Mavi)
 * Katot -> GND
 */

const int kirmizi = 9;
const int yesil = 10;
const int mavi = 11;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
  Serial.begin(9600);
  Serial.println("RGB Gokkusagi Efekti");
}

void renkAyarla(int r, int g, int b) {
  analogWrite(kirmizi, r);
  analogWrite(yesil, g);
  analogWrite(mavi, b);
}

void loop() {
  int r, g, b;
  
  // Kırmızı -> Yeşil
  Serial.println("Kirmizi -> Yesil");
  for (int i = 0; i <= 255; i++) {
    r = 255 - i;
    g = i;
    b = 0;
    renkAyarla(r, g, b);
    delay(10);
  }
  
  // Yeşil -> Mavi
  Serial.println("Yesil -> Mavi");
  for (int i = 0; i <= 255; i++) {
    r = 0;
    g = 255 - i;
    b = i;
    renkAyarla(r, g, b);
    delay(10);
  }
  
  // Mavi -> Kırmızı
  Serial.println("Mavi -> Kirmizi");
  for (int i = 0; i <= 255; i++) {
    r = i;
    g = 0;
    b = 255 - i;
    renkAyarla(r, g, b);
    delay(10);
  }
}
