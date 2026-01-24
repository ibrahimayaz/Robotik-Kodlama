# HAFTA 6: PWM (Pulse Width Modulation) ile Analog Çıkış

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** PWM teknolojisi, duty cycle, analog çıkış

---

## TEORİK KISIM (1 Saat)

### 1. PWM Teknolojisi

#### 1.1 PWM Nedir?
- **P**ulse **W**idth **M**odulation (Darbe Genişlik Modülasyonu)
- Dijital sinyalle analog etki yaratma tekniği
- Hızlı açma-kapama (HIGH-LOW geçişleri) ile ortalama değer kontrolü

#### 1.2 PWM Çalışma Prensibi
```
    100% Duty Cycle (Sürekli HIGH - 5V ortalama)
    ───────────────────────────────────────
    
    75% Duty Cycle (3.75V ortalama)
    ████████████░░░░████████████░░░░████████
    
    50% Duty Cycle (2.5V ortalama)
    ████████░░░░░░░░████████░░░░░░░░████████
    
    25% Duty Cycle (1.25V ortalama)
    ████░░░░░░░░░░░░████░░░░░░░░░░░░████░░░░
    
    0% Duty Cycle (Sürekli LOW - 0V ortalama)
    ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
```

#### 1.3 Duty Cycle (Görev Döngüsü)
- Sinyalin HIGH olduğu sürenin yüzdesi
- Formül: Duty Cycle = (T_HIGH / T_PERIOD) × 100%

```
         T_HIGH
    ├──────────────┤
    ████████████████░░░░░░░░░░░░░░░░░░░░░░░░
    │                                      │
    ├──────────────────────────────────────┤
                    T_PERIOD
    
    Duty Cycle = (T_HIGH / T_PERIOD) × 100%
```

#### 1.4 Ortalama Gerilim Hesaplama
```
    V_ortalama = V_max × (Duty Cycle / 100)
    
    Örnek: Duty Cycle = %50
    V_ortalama = 5V × 0.50 = 2.5V
    
    Arduino'da:
    PWM değeri = 127 (0-255 arası)
    Duty Cycle = 127/255 = %49.8
    V_ortalama = 5V × 0.498 = 2.49V
```

### 2. Arduino PWM Sistemi

#### 2.1 PWM Pinleri
Arduino Uno'da ~ işaretli pinler:
| Pin | Timer | Frekans |
|-----|-------|---------|
| 3, 11 | Timer 2 | ~490 Hz |
| 5, 6 | Timer 0 | ~980 Hz |
| 9, 10 | Timer 1 | ~490 Hz |

#### 2.2 analogWrite() Fonksiyonu
```cpp
// Sözdizimi
analogWrite(pin, değer);

// Değer: 0-255 (8-bit)
analogWrite(9, 0);     // %0 - LED kapalı
analogWrite(9, 64);    // %25 - Hafif parlaklık
analogWrite(9, 127);   // %50 - Yarım parlaklık
analogWrite(9, 191);   // %75 - Yüksek parlaklık
analogWrite(9, 255);   // %100 - Tam parlaklık
```

#### 2.3 PWM vs DAC
| Özellik | PWM | DAC |
|---------|-----|-----|
| Çıkış tipi | Dijital pulse | Gerçek analog |
| Arduino Uno | Mevcut | Yok |
| Kullanım | Motor, LED | Ses, hassas kontrol |
| Maliyet | Düşük | Yüksek |

### 3. PWM Uygulamaları

#### 3.1 LED Parlaklık Kontrolü
- İnsan gözü ortalama parlaklığı algılar
- Yüksek frekans (490Hz+) titreme görünmez yapar

#### 3.2 Motor Hız Kontrolü
- PWM ile DC motor hızı ayarlanır
- H-Bridge sürücü ile yön kontrolü

#### 3.3 Servo Motor Kontrolü
- Özel PWM formatı: 50Hz, 1-2ms pulse
- Açı kontrolü için kullanılır

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| LED | 1 | Beyaz veya mavi tercih |
| 220Ω Direnç | 1 | LED için |
| Potansiyometre | 1 | 10kΩ |
| RGB LED | 1 | Ortak katot (opsiyonel) |
| 220Ω Direnç | 3 | RGB LED için (opsiyonel) |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 8+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │    Potansiyometre → A0                  │
    │                                         │
    │    Pin 9 (PWM) ──[220Ω]──►LED──GND      │
    │                                         │
    │    RGB LED (opsiyonel):                 │
    │    Pin 9  ──[220Ω]──► R                 │
    │    Pin 10 ──[220Ω]──► G  ├── Katot→GND  │
    │    Pin 11 ──[220Ω]──► B                 │
    │                                         │
    └─────────────────────────────────────────┘
```

---

### Örnek Kod 1: Manuel Parlaklık Kontrolü

```cpp
/*
 * Manuel Parlaklık Kontrolü
 * Potansiyometre ile LED parlaklığını ayarla
 */

const int potPin = A0;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("PWM Parlaklik Kontrolu");
}

void loop() {
  int potDeger = analogRead(potPin);
  int parlaklik = map(potDeger, 0, 1023, 0, 255);
  
  analogWrite(ledPin, parlaklik);
  
  // Duty cycle hesapla
  float dutyCycle = (parlaklik / 255.0) * 100.0;
  float ortalamaGerilim = 5.0 * (parlaklik / 255.0);
  
  Serial.print("PWM: ");
  Serial.print(parlaklik);
  Serial.print("\t Duty Cycle: %");
  Serial.print(dutyCycle, 1);
  Serial.print("\t Ort. Gerilim: ");
  Serial.print(ortalamaGerilim, 2);
  Serial.println(" V");
  
  delay(100);
}
```

---

### Örnek Kod 2: Breathing (Soluma) Efekti

```cpp
/*
 * Breathing (Soluma) Efekti
 * LED yavaşça parlar ve söner
 */

const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Yavaşça parla
  Serial.println("Parlatiyor...");
  for (int parlaklik = 0; parlaklik <= 255; parlaklik++) {
    analogWrite(ledPin, parlaklik);
    delay(10);
  }
  
  // Yavaşça sön
  Serial.println("Sonduruyor...");
  for (int parlaklik = 255; parlaklik >= 0; parlaklik--) {
    analogWrite(ledPin, parlaklik);
    delay(10);
  }
}
```

---

### Örnek Kod 3: Sinüs Dalga Efekti

```cpp
/*
 * Sinüs Dalga Efekti
 * Doğal görünümlü parlaklık değişimi
 */

const int ledPin = 9;
float aci = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Sinüs değerini hesapla (0 ile 1 arası)
  float sinDeger = (sin(aci) + 1.0) / 2.0;
  
  // PWM değerine dönüştür
  int parlaklik = sinDeger * 255;
  
  analogWrite(ledPin, parlaklik);
  
  Serial.print("Aci: ");
  Serial.print(aci, 2);
  Serial.print("\t Sin: ");
  Serial.print(sinDeger, 2);
  Serial.print("\t PWM: ");
  Serial.println(parlaklik);
  
  // Açıyı artır
  aci += 0.05;
  if (aci > 2 * PI) {
    aci = 0;
  }
  
  delay(20);
}
```

---

### Örnek Kod 4: RGB LED Renk Kontrolü

```cpp
/*
 * RGB LED Renk Kontrolü
 * Gökkuşağı renkleri arasında geçiş
 */

const int kirmizi = 9;
const int yesil = 10;
const int mavi = 11;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
  Serial.begin(9600);
}

void renkAyarla(int r, int g, int b) {
  analogWrite(kirmizi, r);
  analogWrite(yesil, g);
  analogWrite(mavi, b);
  
  Serial.print("R:");
  Serial.print(r);
  Serial.print(" G:");
  Serial.print(g);
  Serial.print(" B:");
  Serial.println(b);
}

void loop() {
  // Kırmızı
  Serial.println("Kirmizi");
  renkAyarla(255, 0, 0);
  delay(1000);
  
  // Turuncu
  Serial.println("Turuncu");
  renkAyarla(255, 128, 0);
  delay(1000);
  
  // Sarı
  Serial.println("Sari");
  renkAyarla(255, 255, 0);
  delay(1000);
  
  // Yeşil
  Serial.println("Yesil");
  renkAyarla(0, 255, 0);
  delay(1000);
  
  // Cyan
  Serial.println("Cyan");
  renkAyarla(0, 255, 255);
  delay(1000);
  
  // Mavi
  Serial.println("Mavi");
  renkAyarla(0, 0, 255);
  delay(1000);
  
  // Mor
  Serial.println("Mor");
  renkAyarla(255, 0, 255);
  delay(1000);
  
  // Beyaz
  Serial.println("Beyaz");
  renkAyarla(255, 255, 255);
  delay(1000);
}
```

---

### Örnek Kod 5: Gökkuşağı Geçiş Efekti

```cpp
/*
 * Gökkuşağı Geçiş Efekti
 * Yumuşak renk geçişleri
 */

const int kirmizi = 9;
const int yesil = 10;
const int mavi = 11;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
}

void renkAyarla(int r, int g, int b) {
  analogWrite(kirmizi, r);
  analogWrite(yesil, g);
  analogWrite(mavi, b);
}

void loop() {
  int r, g, b;
  
  // Kırmızı -> Yeşil
  for (int i = 0; i <= 255; i++) {
    r = 255 - i;
    g = i;
    b = 0;
    renkAyarla(r, g, b);
    delay(10);
  }
  
  // Yeşil -> Mavi
  for (int i = 0; i <= 255; i++) {
    r = 0;
    g = 255 - i;
    b = i;
    renkAyarla(r, g, b);
    delay(10);
  }
  
  // Mavi -> Kırmızı
  for (int i = 0; i <= 255; i++) {
    r = i;
    g = 0;
    b = 255 - i;
    renkAyarla(r, g, b);
    delay(10);
  }
}
```

---

### Örnek Kod 6: Potansiyometre ile RGB Kontrolü

```cpp
/*
 * Potansiyometre ile RGB Kontrolü
 * Tek pot ile tüm renkleri döngüsel seç
 */

const int potPin = A0;
const int kirmizi = 9;
const int yesil = 10;
const int mavi = 11;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potDeger = analogRead(potPin);
  
  // Pot değerini 0-767 aralığına map et (3 renk geçişi)
  int renkDeger = map(potDeger, 0, 1023, 0, 767);
  
  int r, g, b;
  
  if (renkDeger <= 255) {
    // Kırmızı -> Yeşil
    r = 255 - renkDeger;
    g = renkDeger;
    b = 0;
  } else if (renkDeger <= 511) {
    // Yeşil -> Mavi
    r = 0;
    g = 255 - (renkDeger - 256);
    b = renkDeger - 256;
  } else {
    // Mavi -> Kırmızı
    r = renkDeger - 512;
    g = 0;
    b = 255 - (renkDeger - 512);
  }
  
  analogWrite(kirmizi, r);
  analogWrite(yesil, g);
  analogWrite(mavi, b);
  
  Serial.print("Pot:");
  Serial.print(potDeger);
  Serial.print(" R:");
  Serial.print(r);
  Serial.print(" G:");
  Serial.print(g);
  Serial.print(" B:");
  Serial.println(b);
  
  delay(50);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Manuel Kontrol
- [ ] Potansiyometre ile LED parlaklığını kontrol et
- [ ] Duty cycle değerlerini gözlemle
- [ ] Ortalama gerilim hesaplamalarını doğrula

### Görev 2: Breathing Efekti
- [ ] Soluma efektini çalıştır
- [ ] Hızı değiştir (delay ayarla)
- [ ] Sinüs dalga efektini dene

### Görev 3: RGB LED (varsa)
- [ ] RGB LED bağla
- [ ] Temel renkleri test et
- [ ] Gökkuşağı efektini çalıştır

### Görev 4: Kendi Efektini Oluştur
- [ ] Yeni bir LED efekti tasarla
- [ ] Potansiyometre ile kontrollü efekt

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ PWM prensibini açıklayabilir
- ✅ Duty cycle hesaplayabilir
- ✅ analogWrite() fonksiyonunu kullanabilir
- ✅ LED parlaklık kontrolü yapabilir
- ✅ RGB renk karışımı oluşturabilir

---

**Sonraki Hafta:** LDR (Fotoresistör) ile Işık Algılama
