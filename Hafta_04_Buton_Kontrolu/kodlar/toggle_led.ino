/*
 * Toggle (Aç/Kapa) Modu
 * Her basışta LED durumu değişir
 * Gelişmiş debounce ile
 * 
 * Devre Bağlantısı:
 * Pin 2 <- Buton <- 5V
 * Pin 2 <- 10kΩ <- GND (Pull-down)
 * Pin 13 -> 220Ω -> LED -> GND
 */

const int butonPin = 2;
const int ledPin = 13;

int ledDurum = LOW;
int sonButonDurum = LOW;
int suAnkiButonDurum = LOW;

unsigned long sonDebounceZaman = 0;
unsigned long debounceGecikme = 50;

void setup() {
  pinMode(butonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Toggle Modu Baslatildi");
}

void loop() {
  int okunan = digitalRead(butonPin);
  
  // Durum değişikliği algıla
  if (okunan != sonButonDurum) {
    sonDebounceZaman = millis();
  }
  
  // Debounce süresi geçti mi kontrol et
  if ((millis() - sonDebounceZaman) > debounceGecikme) {
    
    // Stabil durum değişti mi?
    if (okunan != suAnkiButonDurum) {
      suAnkiButonDurum = okunan;
      
      // Sadece basıldığında (LOW -> HIGH geçişi)
      if (suAnkiButonDurum == HIGH) {
        ledDurum = !ledDurum;  // Durumu tersle
        digitalWrite(ledPin, ledDurum);
        
        Serial.print("LED Durumu: ");
        Serial.println(ledDurum ? "ACIK" : "KAPALI");
      }
    }
  }
  
  sonButonDurum = okunan;
}
