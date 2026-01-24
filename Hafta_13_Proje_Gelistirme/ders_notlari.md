# HAFTA 13: Proje Geliştirme ve Test

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 30 dakika | **Pratik:** 2 saat
- **Konu:** Proje uygulama, test, hata ayıklama

---

## TEORİK KISIM (30 Dakika)

### 1. Hata Ayıklama (Debugging) Teknikleri

#### 1.1 Serial Monitor Kullanımı
```cpp
// Her kritik noktaya Serial.print ekle
Serial.println(">>> Fonksiyon basladi");
Serial.print("Degisken degeri: ");
Serial.println(degisken);
```

#### 1.2 LED ile Debugging
```cpp
// Kod bölümlerini test etmek için LED kullan
digitalWrite(13, HIGH);  // Buraya geldi
delay(500);
digitalWrite(13, LOW);
```

#### 1.3 Yaygın Hatalar ve Çözümleri
| Hata | Olası Neden | Çözüm |
|------|-------------|-------|
| Kod yüklenmiyor | Yanlış port/kart | Tools menüsünü kontrol et |
| Sensör çalışmıyor | Yanlış bağlantı | Kabloları kontrol et |
| Motor dönmüyor | Yetersiz güç | Harici güç kullan |
| Değerler hatalı | GND bağlı değil | Ortak GND sağla |
| Servo titriyor | Yetersiz akım | Harici güç kullan |

### 2. Test Stratejileri

#### 2.1 Modüler Test
```
    1. Her sensörü ayrı ayrı test et
    2. Her aktüatörü ayrı ayrı test et
    3. Sensör + Arduino entegrasyonu
    4. Aktüatör + Arduino entegrasyonu
    5. Tüm sistem entegrasyonu
```

#### 2.2 Test Kontrol Listesi
```markdown
□ Güç bağlantıları doğru mu?
□ GND bağlantıları ortak mı?
□ Pin tanımlamaları kod ile eşleşiyor mu?
□ Serial Monitor açık mı? (baud rate doğru mu?)
□ Sensör değerleri mantıklı mı?
□ PWM değerleri 0-255 arasında mı?
□ delay() süreleri uygun mu?
□ Döngü mantığı doğru mu?
```

### 3. Kod Optimizasyonu

#### 3.1 İyi Kodlama Pratikleri
```cpp
// KÖTÜ:
void loop() {
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(1000);
}

// İYİ:
const int LED1 = 9;
const int LED2 = 10;
const int BEKLEME = 1000;

void ledleriYak() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void ledleriSondur() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {
  ledleriYak();
  delay(BEKLEME);
  ledleriSondur();
  delay(BEKLEME);
}
```

#### 3.2 Bellek Optimizasyonu
```cpp
// String yerine F() makrosu kullan
Serial.println(F("Bu yazi Flash bellekte"));

// Sabitler için const kullan
const int ESIK = 500;  // RAM'de yer kaplamaz

// Gereksiz float kullanma
// int genellikle yeterli
```

---

## UYGULAMA KISMI (2 Saat)

### Geliştirme Süreci

#### Aşama 1: Devre Kurulumu (30 dk)
1. Breadboard üzerinde devreyi kur
2. Güç bağlantılarını kontrol et
3. Her sensörü ayrı ayrı test et

#### Aşama 2: Temel Kod (30 dk)
1. Minimum çalışır kod yaz
2. Serial Monitor ile test et
3. Hataları düzelt

#### Aşama 3: Özellik Ekleme (30 dk)
1. Fonksiyonları ekle
2. Mantığı geliştir
3. Edge case'leri kontrol et

#### Aşama 4: Test ve İyileştirme (30 dk)
1. Tüm sistemi test et
2. Hataları düzelt
3. Performansı optimize et

---

## 📋 Örnek Projeler - Tam Kodlar

### Örnek 1: Akıllı Çöp Kutusu

```cpp
/*
 * Akıllı Çöp Kutusu
 * El yaklaştığında kapak otomatik açılır
 */

#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int ledPin = 13;

Servo kapak;
bool kapakAcik = false;
unsigned long sonAcilis = 0;
const int ACIK_SURE = 3000;  // 3 saniye

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  kapak.attach(servoPin);
  kapak.write(0);  // Kapak kapalı
  Serial.begin(9600);
  Serial.println("Akilli Cop Kutusu");
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

void kapakAc() {
  if (!kapakAcik) {
    Serial.println("Kapak aciliyor...");
    for (int a = 0; a <= 90; a += 5) {
      kapak.write(a);
      delay(20);
    }
    kapakAcik = true;
    digitalWrite(ledPin, HIGH);
    sonAcilis = millis();
  } else {
    sonAcilis = millis();  // Süreyi sıfırla
  }
}

void kapakKapat() {
  Serial.println("Kapak kapaniyor...");
  for (int a = 90; a >= 0; a -= 5) {
    kapak.write(a);
    delay(20);
  }
  kapakAcik = false;
  digitalWrite(ledPin, LOW);
}

void loop() {
  float mesafe = mesafeOlc();
  
  if (mesafe > 0 && mesafe < 20) {
    kapakAc();
  }
  
  // Kapak açıksa ve süre dolduysa kapat
  if (kapakAcik && (millis() - sonAcilis > ACIK_SURE)) {
    // Tekrar el var mı kontrol et
    mesafe = mesafeOlc();
    if (mesafe > 20 || mesafe <= 0) {
      kapakKapat();
    } else {
      sonAcilis = millis();  // Süreyi uzat
    }
  }
  
  delay(100);
}
```

### Örnek 2: Engelden Kaçan Robot

```cpp
/*
 * Engelden Kaçan Robot
 * Ultrasonik sensör ile engel algılama
 */

#include <Servo.h>

// Ultrasonik sensör
const int trigPin = A0;
const int echoPin = A1;

// Servo (radar için)
Servo radar;
const int servoPin = 3;

// Motor A (Sol)
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

// Motor B (Sağ)
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

int hiz = 180;
const int ESIK_MESAFE = 25;  // cm

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  radar.attach(servoPin);
  radar.write(90);  // İleri bak
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Engelden Kacan Robot");
  delay(1000);
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

void ileri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void geri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sol() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sag() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void dur() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

float sola_bak() {
  radar.write(150);
  delay(300);
  float mesafe = mesafeOlc();
  radar.write(90);
  delay(200);
  return mesafe;
}

float saga_bak() {
  radar.write(30);
  delay(300);
  float mesafe = mesafeOlc();
  radar.write(90);
  delay(200);
  return mesafe;
}

void loop() {
  float mesafe = mesafeOlc();
  
  Serial.print("Mesafe: ");
  Serial.println(mesafe);
  
  if (mesafe > ESIK_MESAFE || mesafe <= 0) {
    ileri();
  } else {
    dur();
    delay(200);
    geri();
    delay(300);
    dur();
    
    float solMesafe = sola_bak();
    float sagMesafe = saga_bak();
    
    Serial.print("Sol: ");
    Serial.print(solMesafe);
    Serial.print("  Sag: ");
    Serial.println(sagMesafe);
    
    if (solMesafe > sagMesafe) {
      sol();
      delay(400);
    } else {
      sag();
      delay(400);
    }
    dur();
  }
  
  delay(50);
}
```

### Örnek 3: Işık Takip Eden Robot

```cpp
/*
 * Işık Takip Eden Robot
 * İki LDR ile ışık kaynağını takip eder
 */

// LDR sensörler
const int ldrSol = A0;
const int ldrSag = A1;

// Motor A (Sol)
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

// Motor B (Sağ)
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

int hiz = 150;
const int TOLERANS = 50;  // Hassasiyet

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Isik Takip Eden Robot");
}

void ileri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sol() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, hiz);
}

void sag() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, 0);
}

void dur() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  int solDeger = analogRead(ldrSol);
  int sagDeger = analogRead(ldrSag);
  int fark = solDeger - sagDeger;
  
  Serial.print("Sol: ");
  Serial.print(solDeger);
  Serial.print("\t Sag: ");
  Serial.print(sagDeger);
  Serial.print("\t Fark: ");
  Serial.println(fark);
  
  if (abs(fark) < TOLERANS) {
    // Işık ortada, ileri git
    ileri();
    Serial.println("ILERI");
  } else if (fark > 0) {
    // Sol taraf daha aydınlık
    sol();
    Serial.println("SOLA DON");
  } else {
    // Sağ taraf daha aydınlık
    sag();
    Serial.println("SAGA DON");
  }
  
  delay(50);
}
```

---

## 📝 Deney Görevleri

### Proje Geliştirme Kontrol Listesi
- [ ] Devre kurulumu tamamlandı
- [ ] Tüm sensörler test edildi
- [ ] Tüm aktüatörler test edildi
- [ ] Temel kod çalışıyor
- [ ] Tüm özellikler eklendi
- [ ] Hata ayıklama yapıldı
- [ ] Performans optimize edildi

### Sorun Giderme Adımları
1. [ ] Güç kaynağını kontrol et
2. [ ] Bağlantıları kontrol et
3. [ ] Serial Monitor ile değerleri izle
4. [ ] Kodu satır satır test et
5. [ ] Modülleri ayrı ayrı test et

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Hata ayıklama tekniklerini uygulayabilir
- ✅ Modüler test yapabilir
- ✅ Kod optimizasyonu yapabilir
- ✅ Proje entegrasyonu gerçekleştirebilir
- ✅ Sorun çözme becerisi kazanır

---

**Sonraki Hafta:** Proje Sunumları ve Değerlendirme
