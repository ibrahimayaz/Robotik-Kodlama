/*
 * LM35 ile Sıcaklık Ölçümü ve LED Uyarı
 * 
 * Devre Bağlantısı:
 * LM35 VCC -> 5V
 * LM35 VOUT -> A0
 * LM35 GND -> GND
 * Pin 12 -> 220Ω -> LED Kırmızı -> GND
 * Pin 13 -> 220Ω -> LED Mavi -> GND
 */

const int lm35Pin = A0;
const int sicakLED = 12;
const int sogukLED = 13;

const float sicakEsik = 28.0;  // Sıcak uyarı eşiği
const float sogukEsik = 20.0;  // Soğuk uyarı eşiği

void setup() {
  Serial.begin(9600);
  pinMode(sicakLED, OUTPUT);
  pinMode(sogukLED, OUTPUT);
  Serial.println("LM35 Sicaklik Uyari Sistemi");
  Serial.println("===========================");
}

void loop() {
  // Sıcaklığı oku
  int adcDeger = analogRead(lm35Pin);
  float gerilim = adcDeger * (5.0 / 1023.0);
  float sicaklik = gerilim * 100.0;
  
  // Seri monitöre yazdır
  Serial.print("Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.print(" C\t Durum: ");
  
  // LED kontrolü
  if (sicaklik > sicakEsik) {
    digitalWrite(sicakLED, HIGH);
    digitalWrite(sogukLED, LOW);
    Serial.println("SICAK!");
  } else if (sicaklik < sogukEsik) {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, HIGH);
    Serial.println("SOGUK!");
  } else {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, LOW);
    Serial.println("Normal");
  }
  
  delay(1000);
}
