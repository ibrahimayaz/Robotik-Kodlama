/*
 * Binary Counter (İkili Sayaç)
 * 4 LED ile 0-15 arası ikili sayma
 * 
 * Devre Bağlantısı:
 * Pin 8-11 -> 220Ω Direnç -> LED -> GND
 * 
 * LED düzeni: LED3 LED2 LED1 LED0
 *              8    4    2    1
 */

int ledPinleri[] = {8, 9, 10, 11};  // 4 LED
int pinSayisi = 4;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
  
  Serial.println("Binary Counter Baslatildi");
}

void binaryGoster(int sayi) {
  for (int i = 0; i < pinSayisi; i++) {
    // Bit kaydırma ile her bitin değerini al
    int bitDegeri = (sayi >> i) & 1;
    digitalWrite(ledPinleri[i], bitDegeri);
  }
}

void loop() {
  for (int sayi = 0; sayi < 16; sayi++) {
    binaryGoster(sayi);
    
    // Seri monitöre yazdır
    Serial.print("Sayi: ");
    if (sayi < 10) Serial.print(" ");
    Serial.print(sayi);
    Serial.print(" -> Binary: ");
    
    for (int i = pinSayisi - 1; i >= 0; i--) {
      Serial.print((sayi >> i) & 1);
    }
    Serial.println();
    
    delay(1000);
  }
  
  Serial.println("--- Tekrar ---");
}
