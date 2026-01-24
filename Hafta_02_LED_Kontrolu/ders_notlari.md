# HAFTA 2: Dijital Çıkış - LED Kontrolü

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** LED teknolojisi ve Arduino dijital çıkış kontrolü

---

## TEORİK KISIM (1 Saat)

### 1. LED (Light Emitting Diode) Teknolojisi

#### 1.1 LED Nedir?
- Işık yayan yarı iletken diyot
- P-N jonksiyon yapısına sahip
- Elektrik enerjisini doğrudan ışığa çevirir (elektrolüminesans)

#### 1.2 LED Yapısı

```
         Anot (+)          Katot (-)
            │                  │
            │    ┌────────┐    │
            └────┤  LED   ├────┘
                 │Çipi    │
                 └────────┘
                 
    Uzun Bacak = Anot (+)
    Kısa Bacak = Katot (-)
    Düz Kenar (IC kenarı) = Katot (-)
```

#### 1.3 LED Elektriksel Özellikleri

| Renk | Forward Voltage (Vf) | Dalga Boyu |
|------|---------------------|------------|
| Kırmızı | 1.8 - 2.2V | 620-750 nm |
| Turuncu | 2.0 - 2.2V | 590-620 nm |
| Sarı | 2.0 - 2.2V | 570-590 nm |
| Yeşil | 2.0 - 3.0V | 495-570 nm |
| Mavi | 3.0 - 3.4V | 450-495 nm |
| Beyaz | 3.0 - 3.4V | Geniş spektrum |

**Maksimum Akım (If):** Genellikle 20mA (güvenli kullanım)

#### 1.4 Akım Sınırlama Direnci Hesaplama

```
    R = (Vs - Vf) / If
    
    Vs = Kaynak gerilimi (Arduino: 5V)
    Vf = LED ileri gerilimi
    If = LED akımı (genellikle 20mA = 0.02A)
```

**Örnek Hesaplama (Kırmızı LED):**
```
    R = (5V - 2V) / 0.02A
    R = 3V / 0.02A
    R = 150Ω
    
    → Standart değer: 220Ω kullanılır (güvenlik payı)
```

#### 1.5 LED Devre Şeması

```
    Arduino         Direnç          LED
    Pin 13 ────────[220Ω]────────►|─────── GND
                                  Anot   Katot
                                  (+)     (-)
```

### 2. Arduino Dijital I/O Fonksiyonları

#### 2.1 pinMode(pin, mode)
Pin modunu ayarlar:
- `INPUT` - Giriş olarak ayarla
- `OUTPUT` - Çıkış olarak ayarla
- `INPUT_PULLUP` - Dahili pull-up dirençli giriş

```cpp
pinMode(13, OUTPUT);  // Pin 13'ü çıkış yap
```

#### 2.2 digitalWrite(pin, value)
Dijital pin çıkışını ayarlar:
- `HIGH` - 5V (LED yanar)
- `LOW` - 0V (LED söner)

```cpp
digitalWrite(13, HIGH);  // Pin 13'e 5V ver
digitalWrite(13, LOW);   // Pin 13'e 0V ver
```

#### 2.3 delay(ms)
Programı belirtilen milisaniye kadar bekletir:
```cpp
delay(1000);  // 1 saniye (1000ms) bekle
delay(500);   // 0.5 saniye bekle
```

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| LED (5mm) | 1 | Herhangi bir renk |
| 220Ω Direnç | 1 | Kırmızı-Kırmızı-Kahverengi |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 2 | Erkek-Erkek |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────────┐
    │                 BREADBOARD                  │
    │                                             │
    │    Pin 13 ──────[220Ω]──────►LED──────GND  │
    │                            (+)  (-)        │
    │                                             │
    └─────────────────────────────────────────────┘
```

**Tinkercad Bağlantı Adımları:**
1. Arduino Uno'yu çalışma alanına ekle
2. Breadboard ekle
3. LED'i breadboard'a yerleştir (uzun bacak solda)
4. 220Ω direnci LED'in anot (+) bacağına bağla
5. Direncin diğer ucunu Arduino Pin 13'e bağla
6. LED'in katot (-) bacağını Arduino GND'ye bağla

---

### Örnek Kod 1: Temel Blink (LED Yakıp Söndürme)

```cpp
/*
 * Temel Blink Uygulaması
 * LED'i 1 saniye aralıklarla yakıp söndürür
 */

void setup() {
  // Pin 13'ü çıkış olarak ayarla
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);  // LED'i yak
  delay(1000);             // 1 saniye bekle
  digitalWrite(13, LOW);   // LED'i söndür
  delay(1000);             // 1 saniye bekle
}
```

**Çalışma Mantığı:**
```
    HIGH ─┐     ┌─────┐     ┌─────┐
          │     │     │     │     │
    LOW  ─┴─────┴─────┴─────┴─────┴─────
          1s    1s    1s    1s    1s
```

---

### Örnek Kod 2: Değişken Hız Blink

```cpp
/*
 * Değişken Hızlı Blink
 * Yanıp sönme hızını değiştirerek test eder
 */

const int ledPin = 13;  // LED pin numarası
int gecikme = 500;      // Başlangıç gecikme süresi

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Hızlı yanıp sönme (100ms)
  for(int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(1000);  // 1 saniye ara
  
  // Yavaş yanıp sönme (500ms)
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  
  delay(1000);  // 1 saniye ara
}
```

---

### Örnek Kod 3: SOS Morse Kodu

```cpp
/*
 * SOS Morse Kodu
 * S = ···  (3 kısa)
 * O = ---  (3 uzun)
 * S = ···  (3 kısa)
 */

const int ledPin = 13;
const int kisaSure = 200;   // Kısa sinyal (nokta)
const int uzunSure = 600;   // Uzun sinyal (çizgi)
const int aralik = 200;     // Sinyal arası
const int harfArasi = 400;  // Harf arası
const int kelimeArasi = 2000; // Kelime arası

void setup() {
  pinMode(ledPin, OUTPUT);
}

// LED'i belirtilen süre yak
void sinyal(int sure) {
  digitalWrite(ledPin, HIGH);
  delay(sure);
  digitalWrite(ledPin, LOW);
  delay(aralik);
}

// S harfi: 3 kısa sinyal
void harfS() {
  for(int i = 0; i < 3; i++) {
    sinyal(kisaSure);
  }
}

// O harfi: 3 uzun sinyal
void harfO() {
  for(int i = 0; i < 3; i++) {
    sinyal(uzunSure);
  }
}

void loop() {
  // S
  harfS();
  delay(harfArasi);
  
  // O
  harfO();
  delay(harfArasi);
  
  // S
  harfS();
  delay(kelimeArasi);
}
```

**Morse Kodu Zamanlaması:**
```
    S          O          S
    ▪ ▪ ▪      ▬ ▬ ▬      ▪ ▪ ▪
    ─┬─┬─      ───┬───    ─┬─┬─
     aralik      aralik    aralik
```

---

### Örnek Kod 4: Fonksiyon Kullanımı

```cpp
/*
 * Fonksiyonlarla LED Kontrolü
 * Kodu modüler ve okunabilir yapar
 */

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

// LED'i yak
void ledYak() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ACIK");
}

// LED'i söndür
void ledSondur() {
  digitalWrite(ledPin, LOW);
  Serial.println("LED: KAPALI");
}

// Belirtilen sayıda yanıp sön
void yanipSon(int tekrar, int sure) {
  for(int i = 0; i < tekrar; i++) {
    ledYak();
    delay(sure);
    ledSondur();
    delay(sure);
  }
}

void loop() {
  Serial.println("--- 3 kez hizli ---");
  yanipSon(3, 200);
  
  delay(1000);
  
  Serial.println("--- 2 kez yavas ---");
  yanipSon(2, 500);
  
  delay(2000);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Blink
- [ ] Devreyi kur
- [ ] Temel Blink kodunu yükle
- [ ] LED'in 1 saniye aralıklarla yandığını gözlemle

### Görev 2: Hız Değiştirme
- [ ] delay() değerlerini değiştir (100, 250, 500, 1000)
- [ ] Farklı hızları gözlemle
- [ ] En uygun görünen hızı belirle

### Görev 3: SOS Kodu
- [ ] SOS kodunu yükle
- [ ] Kısa ve uzun sinyalleri ayırt et
- [ ] Morse kodunu öğren

### Görev 4: Kendi Patternini Oluştur
- [ ] İsminin baş harfini Morse koduyla göster
- [ ] Kendi ritm patternini tasarla

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ LED'in çalışma prensibini açıklayabilir
- ✅ Akım sınırlama direnci hesaplayabilir
- ✅ Arduino'da dijital çıkış kontrolü yapabilir
- ✅ Temel Arduino fonksiyonlarını kullanabilir
- ✅ Basit devre kurabilir
- ✅ Tinkercad'de simülasyon yapabilir

---

## ⚠️ Dikkat Edilmesi Gerekenler

1. **LED Polaritesi:** LED'i ters bağlamayın (yanmaz, zarar görebilir)
2. **Direnç Kullanımı:** LED'i asla dirençsiz bağlamayın (LED yanar)
3. **Pin Akımı:** Tek pinden max 40mA çekin (önerilen 20mA)
4. **GND Bağlantısı:** GND bağlantısını unutmayın

---

## 🔗 Ek Kaynaklar

- [Arduino digitalWrite Referans](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)
- [LED Direnci Hesaplayıcı](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-led-series-resistor)

---

**Sonraki Hafta:** Çoklu Dijital Çıkış - LED Dizisi
