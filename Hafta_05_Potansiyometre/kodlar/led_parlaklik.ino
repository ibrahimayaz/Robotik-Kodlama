/*
 * LED Parlaklık Kontrolü
 * Potansiyometre ile LED parlaklığını ayarla
 * 
 * Devre Bağlantısı:
 * Pot Uç 1 -> 5V
 * Pot Orta -> A0
 * Pot Uç 2 -> GND
 * Pin 9 -> 220Ω -> LED -> GND
 */

const int potPin = A0;
const int ledPin = 9;  // PWM pin

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("LED Parlaklik Kontrolu");
  Serial.println("======================");
}

void loop() {
  // Potansiyometre değerini oku
  int potDeger = analogRead(potPin);
  
  // PWM değerine dönüştür (0-255)
  int pwmDeger = map(potDeger, 0, 1023, 0, 255);
  
  // Gerilim hesapla
  float gerilim = potDeger * (5.0 / 1023.0);
  
  // LED parlaklığını ayarla
  analogWrite(ledPin, pwmDeger);
  
  // Serial Monitor'a yazdır
  Serial.print("ADC: ");
  Serial.print(potDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilim, 2);
  Serial.print(" V\t PWM: ");
  Serial.print(pwmDeger);
  Serial.print("\t Parlaklik: %");
  Serial.println((pwmDeger * 100) / 255);
  
  delay(100);
}
