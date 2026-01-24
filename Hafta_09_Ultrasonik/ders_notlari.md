# HAFTA 9: Ultrasonik Mesafe Sensörü (HC-SR04)

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** HC-SR04, mesafe ölçümü, park sensörü

---

## TEORİK KISIM (1 Saat)

### 1. HC-SR04 Ultrasonik Sensör

#### 1.1 Ultrasonik Teknoloji
- **Ultrasonik:** İnsan kulağının duyamayacağı ses dalgaları (>20kHz)
- **Sonar prensibi:** Ses gönder, yankıyı ölç, mesafeyi hesapla
- **HC-SR04 frekansı:** 40 kHz

#### 1.2 HC-SR04 Özellikleri
| Özellik | Değer |
|---------|-------|
| Çalışma gerilimi | 5V DC |
| Çalışma akımı | 15mA |
| Ölçüm aralığı | 2cm - 400cm |
| Ölçüm açısı | ~15° (konik) |
| Doğruluk | ±3mm |
| Ultrasonik frekans | 40 kHz |

#### 1.3 HC-SR04 Pin Yapısı
```
    ┌─────────────────────────┐
    │        HC-SR04          │
    │    ┌────┐    ┌────┐     │
    │    │ TX │    │ RX │     │
    │    └────┘    └────┘     │
    │  (Verici)   (Alıcı)     │
    └───┬────┬────┬────┬──────┘
        │    │    │    │
       VCC  TRIG ECHO  GND
       (5V)(Tetik)(Yankı)(0V)
```

### 2. Mesafe Ölçüm Algoritması

#### 2.1 Çalışma Prensibi
```
    1. TRIG pinine 10μs HIGH sinyali gönder
    2. Sensör 8 adet 40kHz ultrasonik dalga yayar
    3. ECHO pini HIGH olur (zamanlayıcı başlar)
    4. Ses dalgası engelden yansır
    5. Yankı algılandığında ECHO pini LOW olur
    6. Geçen süre gidiş-dönüş süresidir
```

#### 2.2 Zamanlama Diyagramı
```
    TRIG:   ──┐    ┌──────────────────────
              │10μs│
    ──────────┴────┴──────────────────────
    
    ECHO:   ──────────┐                 ┌──
                      │     SÜRE (μs)   │
    ──────────────────┴─────────────────┴──
                      │←────────────────→│
                      Gidiş + Dönüş süresi
```

#### 2.3 Mesafe Hesaplama Formülü
```
    Ses hızı = 343 m/s (20°C'de)
             = 0.0343 cm/μs
             = 1/29.1 cm/μs
    
    Mesafe = (Süre × Ses Hızı) / 2
           = (Süre × 0.0343) / 2
           = Süre / 58.2 (cm)
           = Süre / 148 (inch)
```

### 3. pulseIn() Fonksiyonu

#### 3.1 Kullanımı
```cpp
// Sözdizimi
long süre = pulseIn(pin, değer, timeout);

// Parametreler
// pin: Ölçülecek pin numarası
// değer: HIGH veya LOW (hangi pulse ölçülecek)
// timeout: Maksimum bekleme süresi (μs, varsayılan 1 saniye)

// Dönüş değeri: Mikrosaniye cinsinden pulse süresi
```

#### 3.2 Örnek Kullanım
```cpp
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

long süre = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
float mesafe = süre / 58.2;
```

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| HC-SR04 | 1 | Ultrasonik sensör |
| LED (Yeşil) | 1 | Uzak göstergesi |
| LED (Sarı) | 1 | Orta göstergesi |
| LED (Kırmızı) | 1 | Yakın göstergesi |
| 220Ω Direnç | 3 | LED'ler için |
| Buzzer | 1 | Sesli uyarı (opsiyonel) |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 10+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────────────┐
    │                   BREADBOARD                    │
    │                                                 │
    │    HC-SR04:                                     │
    │    VCC ────── 5V                                │
    │    TRIG ───── Pin 9                             │
    │    ECHO ───── Pin 10                            │
    │    GND ────── GND                               │
    │                                                 │
    │    Pin 5 ───[220Ω]───►LED Yeşil───GND           │
    │    Pin 6 ───[220Ω]───►LED Sarı────GND           │
    │    Pin 7 ───[220Ω]───►LED Kırmızı─GND           │
    │    Pin 8 ─────────────Buzzer──────GND           │
    │                                                 │
    └─────────────────────────────────────────────────┘
```

---

### Örnek Kod 1: Temel Mesafe Ölçümü

```cpp
/*
 * Temel Mesafe Ölçümü
 * HC-SR04 ile mesafe ölç
 */

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("HC-SR04 Mesafe Sensoru");
  Serial.println("======================");
}

float mesafeOlc() {
  // TRIG pinine 10μs pulse gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // ECHO pininden süreyi oku
  long sure = pulseIn(echoPin, HIGH, 30000);
  
  // Mesafeyi hesapla (cm)
  float mesafe = sure / 58.2;
  
  return mesafe;
}

void loop() {
  float mesafe = mesafeOlc();
  
  if (mesafe >= 400 || mesafe <= 2) {
    Serial.println("Menzil disi!");
  } else {
    Serial.print("Mesafe: ");
    Serial.print(mesafe, 1);
    Serial.println(" cm");
  }
  
  delay(250);
}
```

---

### Örnek Kod 2: Park Sensörü Sistemi

```cpp
/*
 * Park Sensörü Sistemi
 * Mesafeye göre LED ve buzzer kontrolü
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
```

---

### Örnek Kod 3: Mesafe Göstergesi (LED Bar)

```cpp
/*
 * Mesafe Göstergesi
 * 5 LED ile mesafe seviyesi göster
 */

const int trigPin = 9;
const int echoPin = 10;
int ledPinleri[] = {3, 4, 5, 6, 7};
int ledSayisi = 5;

const int maxMesafe = 100;  // cm

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  for (int i = 0; i < ledSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
  
  Serial.begin(9600);
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
  float mesafe = mesafeOlc();
  
  // Mesafeyi 0-5 seviyeye çevir (ters orantılı)
  int seviye = 0;
  if (mesafe > 0 && mesafe < maxMesafe) {
    seviye = map(mesafe, 0, maxMesafe, ledSayisi, 0);
    seviye = constrain(seviye, 0, ledSayisi);
  }
  
  // LED'leri güncelle
  for (int i = 0; i < ledSayisi; i++) {
    if (i < seviye) {
      digitalWrite(ledPinleri[i], HIGH);
    } else {
      digitalWrite(ledPinleri[i], LOW);
    }
  }
  
  Serial.print("Mesafe: ");
  Serial.print(mesafe, 1);
  Serial.print(" cm\t Seviye: ");
  Serial.println(seviye);
  
  delay(100);
}
```

---

### Örnek Kod 4: Hareketli Ortalama Filtreleme

```cpp
/*
 * Filtrelenmiş Mesafe Ölçümü
 * Hareketli ortalama ile gürültü azaltma
 */

const int trigPin = 9;
const int echoPin = 10;

const int ornekSayisi = 5;
float okumalar[ornekSayisi];
int okumaIndex = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
  // Diziyi sıfırla
  for (int i = 0; i < ornekSayisi; i++) {
    okumalar[i] = 0;
  }
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

float filtrelenmisOku() {
  // Yeni okumayı al
  float yeniOkuma = mesafeOlc();
  
  // Geçersiz okumaları atla
  if (yeniOkuma <= 0 || yeniOkuma > 400) {
    return -1;
  }
  
  // Diziye ekle
  okumalar[okumaIndex] = yeniOkuma;
  okumaIndex = (okumaIndex + 1) % ornekSayisi;
  
  // Ortalama hesapla
  float toplam = 0;
  int gecerliSayi = 0;
  
  for (int i = 0; i < ornekSayisi; i++) {
    if (okumalar[i] > 0) {
      toplam += okumalar[i];
      gecerliSayi++;
    }
  }
  
  if (gecerliSayi > 0) {
    return toplam / gecerliSayi;
  }
  return -1;
}

void loop() {
  float hamMesafe = mesafeOlc();
  float filtrelenmis = filtrelenmisOku();
  
  Serial.print("Ham: ");
  Serial.print(hamMesafe, 1);
  Serial.print(" cm\t Filtrelenmis: ");
  
  if (filtrelenmis > 0) {
    Serial.print(filtrelenmis, 1);
    Serial.println(" cm");
  } else {
    Serial.println("Hata");
  }
  
  delay(100);
}
```

---

### Örnek Kod 5: Engel Algılama ve Sayma

```cpp
/*
 * Engel Algılama ve Sayma
 * Belirli mesafede nesne geçişini say
 */

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;

const float algilamaMesafesi = 30.0;  // cm
int engelSayisi = 0;
bool engelVar = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Engel Sayici");
  Serial.println("============");
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
  float mesafe = mesafeOlc();
  
  if (mesafe > 0 && mesafe < algilamaMesafesi) {
    if (!engelVar) {
      // Yeni engel algılandı
      engelVar = true;
      engelSayisi++;
      digitalWrite(ledPin, HIGH);
      
      Serial.print(">>> ENGEL ALGILANDI! Toplam: ");
      Serial.println(engelSayisi);
    }
  } else {
    if (engelVar) {
      // Engel ayrıldı
      engelVar = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Engel ayrildi.");
    }
  }
  
  delay(50);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Ölçüm
- [ ] HC-SR04 devresini kur
- [ ] Mesafe değerlerini Serial Monitor'da izle
- [ ] El ile yaklaşıp uzaklaşarak test et

### Görev 2: Park Sensörü
- [ ] LED ve buzzer ekle
- [ ] Mesafe eşiklerini ayarla
- [ ] Ses frekanslarını test et

### Görev 3: Filtreleme
- [ ] Filtrelenmiş kodu dene
- [ ] Ham ve filtrelenmiş değerleri karşılaştır
- [ ] Gürültü azalmasını gözlemle

### Görev 4: Engel Sayacı
- [ ] Engel sayacını çalıştır
- [ ] Elini sensör önünden geçir
- [ ] Sayacın doğru çalıştığını doğrula

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Ultrasonik sensör çalışma prensibini anlayabilir
- ✅ Mesafe hesaplama formülünü uygulayabilir
- ✅ pulseIn() fonksiyonunu kullanabilir
- ✅ Çok seviyeli uyarı sistemi tasarlayabilir
- ✅ tone() ve noTone() fonksiyonlarını kullanabilir

---

**Sonraki Hafta:** Servo Motor Kontrolü
