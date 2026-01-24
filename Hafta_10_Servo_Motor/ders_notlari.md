# HAFTA 10: Servo Motor Kontrolü

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** Servo motor, PWM açı kontrolü, Servo kütüphanesi

---

## TEORİK KISIM (1 Saat)

### 1. Servo Motor Teknolojisi

#### 1.1 Servo Motor Nedir?
- Belirli bir açıya dönebilen ve o konumda kalabilen motor
- İç yapısında: DC motor + Potansiyometre + Kontrol devresi
- Kapalı döngü kontrol sistemi (geri besleme)

#### 1.2 Servo Motor Türleri
| Tür | Dönüş Açısı | Kullanım |
|-----|-------------|----------|
| Standart Servo | 0° - 180° | Robot kol, kapak kontrolü |
| Sürekli Dönüş Servo | 360° (sürekli) | Tekerlek, konveyör |
| Lineer Servo | Doğrusal hareket | Piston benzeri |

#### 1.3 SG90 Servo Motor Özellikleri
| Özellik | Değer |
|---------|-------|
| Açı aralığı | 0° - 180° |
| Tork | 1.8 kg·cm (4.8V) |
| Hız | 0.1 s/60° (4.8V) |
| Çalışma gerilimi | 4.8V - 6V |
| Akım (boşta) | ~10mA |
| Akım (hareket) | ~100-250mA |
| Akım (bloke) | ~600mA |

#### 1.4 Servo Motor Pin Yapısı
```
    Servo Motor Kabloları:
    
    ┌─────────────────┐
    │     SG90        │
    │    ┌─────┐      │
    │    │ ─┬─ │      │
    │    └──┼──┘      │
    └───────┼─────────┘
            │
    ┌───────┼───────┐
    │   │   │   │   │
   Kahve Kırm Turunc
   (GND)(VCC)(Sinyal)
```

### 2. PWM Kontrolü

#### 2.1 Servo PWM Sinyali
- **Frekans:** 50 Hz (20ms periyot)
- **Pulse genişliği:** 1ms - 2ms
- Açı = Pulse genişliğine orantılı

```
    0° (1ms pulse):
    ┌┐                    ┌┐
    ││                    ││
    ┴┴────────────────────┴┴────────────────────
     1ms      19ms         1ms      19ms
    ├──┼─────────────────┤
          20ms (50Hz)
    
    90° (1.5ms pulse):
    ┌──┐                  ┌──┐
    │  │                  │  │
    ┴──┴──────────────────┴──┴──────────────────
    1.5ms    18.5ms
    
    180° (2ms pulse):
    ┌───┐                 ┌───┐
    │   │                 │   │
    ┴───┴─────────────────┴───┴─────────────────
     2ms     18ms
```

#### 2.2 Açı-Pulse İlişkisi
```
    Pulse (μs) = 1000 + (açı × 1000 / 180)
    
    0°   → 1000μs (1ms)
    45°  → 1250μs (1.25ms)
    90°  → 1500μs (1.5ms)
    135° → 1750μs (1.75ms)
    180° → 2000μs (2ms)
```

### 3. Servo Kütüphanesi

#### 3.1 Kütüphane Dahil Etme
```cpp
#include <Servo.h>
```

#### 3.2 Servo Nesnesi Oluşturma
```cpp
Servo motor;  // Servo nesnesi
```

#### 3.3 Temel Fonksiyonlar
| Fonksiyon | Açıklama |
|-----------|----------|
| `attach(pin)` | Servo'yu belirtilen pine bağla |
| `write(açı)` | 0-180 arası açı yaz |
| `writeMicroseconds(μs)` | 1000-2000μs pulse genişliği |
| `read()` | Mevcut açıyı oku |
| `attached()` | Bağlı mı kontrol et |
| `detach()` | Servo bağlantısını kes |

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| SG90 Servo Motor | 1 | Micro servo |
| Potansiyometre | 1 | 10kΩ |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 6+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │    Servo Motor:                         │
    │    Kahverengi ────── GND                │
    │    Kırmızı ────────── 5V                │
    │    Turuncu ────────── Pin 9             │
    │                                         │
    │    Potansiyometre:                      │
    │    Uç 1 ───────────── 5V                │
    │    Orta ───────────── A0                │
    │    Uç 2 ───────────── GND               │
    │                                         │
    └─────────────────────────────────────────┘
```

**⚠️ Güç Notu:** Birden fazla servo kullanıyorsanız harici güç kaynağı kullanın.

---

### Örnek Kod 1: Manuel Açı Kontrolü

```cpp
/*
 * Manuel Servo Açı Kontrolü
 * Potansiyometre ile servo açısını kontrol et
 */

#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int potPin = A0;

void setup() {
  motor.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Servo Aci Kontrolu");
}

void loop() {
  int potDeger = analogRead(potPin);
  int aci = map(potDeger, 0, 1023, 0, 180);
  
  motor.write(aci);
  
  Serial.print("Pot: ");
  Serial.print(potDeger);
  Serial.print("\t Aci: ");
  Serial.print(aci);
  Serial.println(" derece");
  
  delay(15);  // Servo stabilizasyon
}
```

---

### Örnek Kod 2: Otomatik Tarama (Sweep)

```cpp
/*
 * Otomatik Tarama (Sweep)
 * Servo 0-180 arasında sürekli hareket
 */

#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(9);
  Serial.begin(9600);
  Serial.println("Servo Tarama");
}

void loop() {
  // Sağa tarama (0 -> 180)
  Serial.println("Saga tarama...");
  for (int aci = 0; aci <= 180; aci++) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);  // Uçta bekle
  
  // Sola tarama (180 -> 0)
  Serial.println("Sola tarama...");
  for (int aci = 180; aci >= 0; aci--) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);  // Uçta bekle
}
```

---

### Örnek Kod 3: Butonla Adım Adım Kontrol

```cpp
/*
 * Butonla Adım Adım Servo Kontrolü
 * Buton 1: Sola dön (açı azalt)
 * Buton 2: Sağa dön (açı artır)
 */

#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int butonSol = 2;
const int butonSag = 3;

int mevcutAci = 90;  // Başlangıç açısı
const int adim = 5;  // Her basışta 5 derece

void setup() {
  motor.attach(servoPin);
  pinMode(butonSol, INPUT_PULLUP);
  pinMode(butonSag, INPUT_PULLUP);
  
  motor.write(mevcutAci);  // Başlangıç pozisyonu
  
  Serial.begin(9600);
  Serial.println("Butonlu Servo Kontrol");
  Serial.println("Sol: Aci azalt, Sag: Aci artir");
}

void loop() {
  // Sol buton kontrolü
  if (digitalRead(butonSol) == LOW) {
    mevcutAci -= adim;
    if (mevcutAci < 0) mevcutAci = 0;
    motor.write(mevcutAci);
    Serial.print("Aci: ");
    Serial.println(mevcutAci);
    delay(200);
  }
  
  // Sağ buton kontrolü
  if (digitalRead(butonSag) == LOW) {
    mevcutAci += adim;
    if (mevcutAci > 180) mevcutAci = 180;
    motor.write(mevcutAci);
    Serial.print("Aci: ");
    Serial.println(mevcutAci);
    delay(200);
  }
}
```

---

### Örnek Kod 4: Pozisyon Hafızası

```cpp
/*
 * Pozisyon Hafızası
 * Kayıtlı pozisyonlara git
 */

#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int butonPin = 2;

// Kayıtlı pozisyonlar
int pozisyonlar[] = {0, 45, 90, 135, 180};
int pozSayisi = 5;
int mevcutPoz = 0;

void setup() {
  motor.attach(servoPin);
  pinMode(butonPin, INPUT_PULLUP);
  
  motor.write(pozisyonlar[0]);
  
  Serial.begin(9600);
  Serial.println("Pozisyon Hafizasi");
  Serial.print("Baslangic pozisyonu: ");
  Serial.println(pozisyonlar[0]);
}

void loop() {
  if (digitalRead(butonPin) == LOW) {
    delay(50);  // Debounce
    
    // Sonraki pozisyona geç
    mevcutPoz = (mevcutPoz + 1) % pozSayisi;
    
    // Yumuşak geçiş
    int hedefAci = pozisyonlar[mevcutPoz];
    int simdikiAci = motor.read();
    
    if (hedefAci > simdikiAci) {
      for (int a = simdikiAci; a <= hedefAci; a++) {
        motor.write(a);
        delay(10);
      }
    } else {
      for (int a = simdikiAci; a >= hedefAci; a--) {
        motor.write(a);
        delay(10);
      }
    }
    
    Serial.print("Pozisyon ");
    Serial.print(mevcutPoz);
    Serial.print(": ");
    Serial.print(hedefAci);
    Serial.println(" derece");
    
    // Buton bırakılana kadar bekle
    while (digitalRead(butonPin) == LOW);
    delay(100);
  }
}
```

---

### Örnek Kod 5: Radar Sistemi (Servo + Ultrasonik)

```cpp
/*
 * Basit Radar Sistemi
 * Servo ile ultrasonik sensör tarama
 */

#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int trigPin = 10;
const int echoPin = 11;

void setup() {
  motor.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Radar Sistemi");
}

float mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long sure = pulseIn(echoPin, HIGH, 30000);
  return sure / 58.2;
}

void loop() {
  // 0 -> 180 tarama
  for (int aci = 0; aci <= 180; aci += 5) {
    motor.write(aci);
    delay(50);  // Servo stabilizasyon
    
    float mesafe = mesafeOlc();
    
    // Processing veya Serial Plotter için format
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
  
  // 180 -> 0 tarama
  for (int aci = 180; aci >= 0; aci -= 5) {
    motor.write(aci);
    delay(50);
    
    float mesafe = mesafeOlc();
    
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
}
```

---

### Örnek Kod 6: Serial ile Uzaktan Kontrol

```cpp
/*
 * Serial ile Servo Kontrol
 * Serial Monitor'dan açı değeri gönder
 */

#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(9);
  Serial.begin(9600);
  Serial.println("Serial Servo Kontrol");
  Serial.println("0-180 arasi aci degeri girin:");
}

void loop() {
  if (Serial.available() > 0) {
    int aci = Serial.parseInt();
    
    if (aci >= 0 && aci <= 180) {
      motor.write(aci);
      Serial.print("Servo acisi: ");
      Serial.print(aci);
      Serial.println(" derece");
    } else {
      Serial.println("Gecersiz deger! 0-180 arasi giriniz.");
    }
    
    // Buffer'ı temizle
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
```

---

## 📝 Deney Görevleri

### Görev 1: Manuel Kontrol
- [ ] Servo'yu potansiyometre ile kontrol et
- [ ] 0°, 90°, 180° pozisyonlarını test et
- [ ] Hassasiyeti gözlemle

### Görev 2: Otomatik Tarama
- [ ] Sweep kodunu çalıştır
- [ ] Hızı değiştir (delay ayarla)
- [ ] Adım büyüklüğünü değiştir

### Görev 3: Radar Sistemi
- [ ] Ultrasonik sensör ekle
- [ ] Tarama verisini Serial Monitor'da gözlemle
- [ ] Engel tespiti yap

### Görev 4: Kendi Projen
- [ ] Kapı kilidi sistemi tasarla
- [ ] Robot kol hareketi oluştur

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Servo motor çalışma prensibini anlayabilir
- ✅ PWM açı kontrolünü uygulayabilir
- ✅ Servo kütüphanesini kullanabilir
- ✅ Sensör-aktüatör entegrasyonu yapabilir
- ✅ Radar/tarama sistemleri tasarlayabilir

---

**Sonraki Hafta:** DC Motor Kontrolü ve L298N Motor Sürücü
