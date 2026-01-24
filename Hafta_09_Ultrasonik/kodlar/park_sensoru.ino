/*
 * Park Sensörü Sistemi
 * Mesafeye göre LED ve buzzer kontrolü
 * 
 * Devre Bağlantısı:
 * HC-SR04 VCC -> 5V
 * HC-SR04 TRIG -> Pin 9
 * HC-SR04 ECHO -> Pin 10
 * HC-SR04 GND -> GND
 * Pin 5 -> 220Ω -> LED Yeşil -> GND
 * Pin 6 -> 220Ω -> LED Sarı -> GND
 * Pin 7 -> 220Ω -> LED Kırmızı -> GND
 * Pin 8 -> Buzzer -> GND
 */

const int trigPin = 9;
const int echoPin = 10;
const int yesil = 5;
const int sari = 6;
const int kirmizi = 7;
const int buzzer = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(yesil, OUTPUT);
  pinMode(sari, OUTPUT);
  pinMode(kirmizi, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Park Sensoru Sistemi");
  Serial.println("====================");
}

float mesafeOlc() {
  // TRIG pinine 10μs pulse gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // ECHO pininden süreyi oku (30ms timeout)
  long sure = pulseIn(echoPin, HIGH, 30000);
  
  // Mesafeyi hesapla (cm)
  return sure / 58.2;
}

void tumLedKapat() {
  digitalWrite(yesil, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(kirmizi, LOW);
}

void loop() {
  float mesafe = mesafeOlc();
  
  tumLedKapat();
  
  Serial.print("Mesafe: ");
  Serial.print(mesafe, 1);
  Serial.print(" cm\t ");
  
  if (mesafe > 100 || mesafe <= 0) {
    // Güvenli mesafe veya menzil dışı
    digitalWrite(yesil, HIGH);
    noTone(buzzer);
    Serial.println("GUVENLI");
    
  } else if (mesafe > 50) {
    // Dikkat mesafesi (50-100 cm)
    digitalWrite(sari, HIGH);
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);
    Serial.println("DIKKAT");
    
  } else if (mesafe > 20) {
    // Yakın mesafe (20-50 cm)
    digitalWrite(kirmizi, HIGH);
    tone(buzzer, 2000);
    delay(100);
    noTone(buzzer);
    Serial.println("YAKIN");
    
  } else {
    // Çok yakın mesafe (<20 cm)
    digitalWrite(kirmizi, HIGH);
    tone(buzzer, 3000);
    Serial.println("!!! COK YAKIN !!!");
    delay(50);
    noTone(buzzer);
  }
  
  delay(100);
}
