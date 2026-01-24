# HAFTA 5: Analog Giriş - Potansiyometre ve Seri Haberleşme

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** Potansiyometre, ADC, UART seri haberleşme

---

## TEORİK KISIM (1 Saat)

### 1. Potansiyometre

#### 1.1 Potansiyometre Nedir?
- 3 uçlu ayarlanabilir direnç
- Gerilim bölücü olarak çalışır
- Analog giriş için mükemmel test aracı

#### 1.2 Potansiyometre Yapısı
```
                 VCC (5V)
                   │
                   └─── Uç 1
                        │
    ┌────────────────────────────────────┐
    │         Rezistif Yol               │
    │    ═════════════════════════       │
    │              │                     │
    │           Sürgü ───────────────────┼─── Orta Uç (Wiper) → A0
    │                                    │
    └────────────────────────────────────┘
                        │
                   └─── Uç 2
                   │
                  GND
```

#### 1.3 Gerilim Bölücü Formülü
```
    VCC ───┬───
           │
          [R1]  (Üst kısım)
           │
           ├─── Vout = VCC × (R2 / (R1 + R2))
           │
          [R2]  (Alt kısım)
           │
    GND ───┴───
```

**Örnek:**
- Potansiyometre: 10kΩ
- Sürgü ortada: R1 = R2 = 5kΩ
- Vout = 5V × (5k / 10k) = 2.5V

### 2. Arduino Analog Giriş Sistemi

#### 2.1 ADC (Analog-to-Digital Converter)
- Analog sinyali dijital değere çevirir
- Arduino Uno: 10-bit çözünürlük
- 2^10 = 1024 seviye (0-1023)

```
    Analog Gerilim    →    ADC Değeri
    0V                →    0
    1.25V             →    255
    2.5V              →    511
    3.75V             →    767
    5V                →    1023
```

#### 2.2 Dönüşüm Formülü
```
    ADC Değeri = (Gerilim / Referans) × 1023
    
    Örnek: 3.3V gerilim
    ADC = (3.3 / 5.0) × 1023 = 675
    
    Ters dönüşüm:
    Gerilim = (ADC Değeri / 1023) × 5.0
```

#### 2.3 analogRead() Fonksiyonu
```cpp
int deger = analogRead(A0);  // 0-1023 arası değer döner
```

#### 2.4 map() Fonksiyonu
Değer aralığını dönüştürür:
```cpp
// Sözdizimi: map(değer, girişMin, girişMax, çıkışMin, çıkışMax)

int potDeger = analogRead(A0);           // 0-1023
int pwmDeger = map(potDeger, 0, 1023, 0, 255);  // 0-255
int aci = map(potDeger, 0, 1023, 0, 180);       // 0-180
```

### 3. UART Seri Haberleşme

#### 3.1 UART Nedir?
- **U**niversal **A**synchronous **R**eceiver-**T**ransmitter
- Asenkron seri iletişim protokolü
- Arduino ile PC arasında veri transferi

#### 3.2 UART Pinleri
| Pin | Fonksiyon | Açıklama |
|-----|-----------|----------|
| D0 | RX | Veri alma (Receive) |
| D1 | TX | Veri gönderme (Transmit) |

#### 3.3 Baud Rate
- Saniyede iletilen bit sayısı
- Yaygın değerler: 9600, 19200, 115200
- Her iki taraf aynı hızda olmalı

#### 3.4 Serial Fonksiyonları
```cpp
Serial.begin(9600);           // Seri portu başlat
Serial.print("Merhaba");      // Yazdır (satır sonu yok)
Serial.println("Merhaba");    // Yazdır + satır sonu
Serial.print(deger);          // Sayı yazdır
Serial.print(deger, BIN);     // İkili formatta
Serial.print(deger, HEX);     // Onaltılık formatta
Serial.print(deger, 2);       // 2 ondalık basamak (float için)
```

#### 3.5 Serial Monitor ve Serial Plotter
- **Serial Monitor:** Metin tabanlı veri görüntüleme
- **Serial Plotter:** Grafik tabanlı veri görüntüleme

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| Potansiyometre | 1 | 10kΩ (B10K) |
| LED | 1 | Herhangi renk |
| 220Ω Direnç | 1 | LED için |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 5+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │        POTANSİYOMETRE                   │
    │         ┌─────────┐                     │
    │    5V ──┤ 1     3 ├── GND               │
    │         │    2    │                     │
    │         └────┬────┘                     │
    │              │                          │
    │    A0 ───────┘                          │
    │                                         │
    │    Pin 9 (PWM) ──[220Ω]──►LED──GND      │
    │                                         │
    └─────────────────────────────────────────┘
```

---

### Örnek Kod 1: Temel Analog Okuma

```cpp
/*
 * Temel Analog Okuma
 * Potansiyometre değerini Serial Monitor'da göster
 */

const int potPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Analog Okuma Baslatildi");
  Serial.println("------------------------");
}

void loop() {
  int hamDeger = analogRead(potPin);
  
  Serial.print("ADC Degeri: ");
  Serial.println(hamDeger);
  
  delay(250);
}
```

---

### Örnek Kod 2: Gerilim Hesaplama

```cpp
/*
 * Gerilim Hesaplama
 * ADC değerini gerilime çevirir
 */

const int potPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Gerilim Olcumu");
  Serial.println("==============");
}

void loop() {
  int hamDeger = analogRead(potPin);
  
  // Gerilim hesapla
  float gerilim = hamDeger * (5.0 / 1023.0);
  
  // Yüzde hesapla
  float yuzde = (hamDeger / 1023.0) * 100.0;
  
  Serial.print("ADC: ");
  Serial.print(hamDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilim, 2);  // 2 ondalık basamak
  Serial.print(" V\t Yuzde: %");
  Serial.println(yuzde, 1);  // 1 ondalık basamak
  
  delay(200);
}
```

---

### Örnek Kod 3: LED Parlaklık Kontrolü

```cpp
/*
 * LED Parlaklık Kontrolü
 * Potansiyometre ile LED parlaklığını ayarla
 */

const int potPin = A0;
const int ledPin = 9;  // PWM pin

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
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
```

---

### Örnek Kod 4: Serial Plotter için Format

```cpp
/*
 * Serial Plotter Formatı
 * Grafik görselleştirme için veri gönderimi
 */

const int potPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int deger = analogRead(potPin);
  float gerilim = deger * (5.0 / 1023.0);
  
  // Serial Plotter için format
  // Her değer virgülle ayrılır
  Serial.print("ADC:");
  Serial.print(deger);
  Serial.print(",");
  Serial.print("Gerilim_x100:");
  Serial.println((int)(gerilim * 100));
  
  delay(50);
}
```

**Serial Plotter Kullanımı:**
1. Tools → Serial Plotter seçin
2. Baud rate'i doğru ayarlayın (9600)
3. Potansiyometreyi çevirin ve grafiği izleyin

---

### Örnek Kod 5: Çoklu Analog Giriş

```cpp
/*
 * Çoklu Analog Giriş
 * Birden fazla potansiyometre/sensör okuma
 */

const int pot1Pin = A0;
const int pot2Pin = A1;

void setup() {
  Serial.begin(9600);
  Serial.println("Coklu Analog Giris");
  Serial.println("==================");
}

void loop() {
  int pot1 = analogRead(pot1Pin);
  int pot2 = analogRead(pot2Pin);
  
  float gerilim1 = pot1 * (5.0 / 1023.0);
  float gerilim2 = pot2 * (5.0 / 1023.0);
  
  Serial.print("Pot1: ");
  Serial.print(pot1);
  Serial.print(" (");
  Serial.print(gerilim1, 2);
  Serial.print("V)\t");
  
  Serial.print("Pot2: ");
  Serial.print(pot2);
  Serial.print(" (");
  Serial.print(gerilim2, 2);
  Serial.println("V)");
  
  delay(200);
}
```

---

### Örnek Kod 6: Veri Filtreleme (Ortalama)

```cpp
/*
 * Veri Filtreleme
 * Gürültüyü azaltmak için ortalama alma
 */

const int potPin = A0;
const int ornekSayisi = 10;

void setup() {
  Serial.begin(9600);
}

int ortalamaOku(int pin, int ornek) {
  long toplam = 0;
  
  for (int i = 0; i < ornek; i++) {
    toplam += analogRead(pin);
    delay(2);  // ADC stabilizasyonu için kısa bekleme
  }
  
  return toplam / ornek;
}

void loop() {
  // Ham değer
  int hamDeger = analogRead(potPin);
  
  // Filtrelenmiş değer
  int filtrelenmis = ortalamaOku(potPin, ornekSayisi);
  
  Serial.print("Ham: ");
  Serial.print(hamDeger);
  Serial.print("\t Filtrelenmis: ");
  Serial.println(filtrelenmis);
  
  delay(100);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Okuma
- [ ] Potansiyometreyi bağla
- [ ] Serial Monitor'da değerleri gözlemle
- [ ] Min ve max değerleri kontrol et (0-1023)

### Görev 2: Gerilim Ölçümü
- [ ] Gerilim hesaplamasını test et
- [ ] Multimetre ile doğrula (varsa)
- [ ] Yüzde hesaplamasını kontrol et

### Görev 3: LED Kontrolü
- [ ] LED parlaklık kontrolünü uygula
- [ ] Potansiyometre ile LED parlaklığını değiştir
- [ ] PWM değerlerini gözlemle

### Görev 4: Serial Plotter
- [ ] Serial Plotter'ı aç
- [ ] Potansiyometre değişimlerini grafik olarak izle
- [ ] Veri filtrelemenin etkisini gözlemle

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Analog sinyal okuyabilir
- ✅ ADC çalışma prensibini anlayabilir
- ✅ Veri tipi dönüşümlerini yapabilir
- ✅ Seri haberleşme protokolünü kullanabilir
- ✅ map() fonksiyonunu etkin kullanabilir
- ✅ Serial Monitor ve Plotter'ı kullanabilir

---

## 💡 İpuçları

1. **ADC Hassasiyeti:** 5V / 1024 = ~4.88mV adım
2. **Stabilizasyon:** Okuma arası küçük delay ekleyin
3. **Filtreleme:** Gürültülü ortamlarda ortalama alın
4. **Serial Hızı:** Daha hızlı güncelleme için 115200 baud kullanın

---

**Sonraki Hafta:** PWM (Pulse Width Modulation) ile Analog Çıkış
