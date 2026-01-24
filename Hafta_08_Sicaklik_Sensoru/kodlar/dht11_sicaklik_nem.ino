/*
 * DHT11 ile Sıcaklık ve Nem Ölçümü
 * Kütüphane: DHT sensor library (Adafruit)
 * 
 * Kütüphane Kurulumu:
 * Sketch -> Include Library -> Manage Libraries
 * "DHT sensor library" ara ve yükle
 * 
 * Devre Bağlantısı:
 * DHT11 VCC -> 5V
 * DHT11 DATA -> Pin 2
 * DHT11 GND -> GND
 */

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sicaklik ve Nem Sensoru");
  Serial.println("==============================");
}

void loop() {
  // DHT11 minimum 2 saniye bekleme gerektirir
  delay(2000);
  
  // Nem ve sıcaklık oku
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();
  
  // Okuma hatası kontrolü
  if (isnan(nem) || isnan(sicaklik)) {
    Serial.println("DHT sensoru okunamadi!");
    return;
  }
  
  // Heat index (hissedilen sıcaklık) hesapla
  float hissedilen = dht.computeHeatIndex(sicaklik, nem, false);
  
  Serial.print("Nem: ");
  Serial.print(nem, 1);
  Serial.print(" %\t Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.print(" C\t Hissedilen: ");
  Serial.print(hissedilen, 1);
  Serial.println(" C");
  
  // Konfor analizi
  if (sicaklik >= 20 && sicaklik <= 26 && nem >= 40 && nem <= 60) {
    Serial.println(">>> Konfor: IDEAL");
  } else if (sicaklik > 30 || nem > 70) {
    Serial.println(">>> Konfor: SICAK/NEMLI");
  } else if (sicaklik < 18) {
    Serial.println(">>> Konfor: SOGUK");
  } else {
    Serial.println(">>> Konfor: KABUL EDILEBILIR");
  }
  Serial.println();
}
