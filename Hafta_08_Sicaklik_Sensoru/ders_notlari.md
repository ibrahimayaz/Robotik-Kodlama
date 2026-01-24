# HAFTA 8: Sıcaklık Sensörü (DHT11/LM35) ile Çevre Ölçümü

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** LM35, DHT11, sıcaklık ve nem ölçümü

---

## TEORİK KISIM (1 Saat)

### 1. LM35 Analog Sıcaklık Sensörü

#### 1.1 LM35 Özellikleri
- Entegre devre (IC) tabanlı sıcaklık sensörü
- Lineer çıkış: **10mV/°C**
- Ölçüm aralığı: -55°C ile +150°C
- Doğruluk: ±0.5°C (25°C'de)
- Çalışma gerilimi: 4V - 30V

#### 1.2 LM35 Pin Yapısı
```
        ┌─────────┐
        │  LM35   │
        │         │
        └─┬───┬───┬┘
          │   │   │
         VCC VOUT GND
        (4-30V)(Analog)(0V)
```

#### 1.3 Sıcaklık Hesaplama
```
    Çıkış Gerilimi = Sıcaklık × 10mV
    
    Örnek: 25°C için
    Vout = 25 × 0.010V = 0.25V = 250mV
    
    Ters hesaplama:
    Sıcaklık = Vout / 10mV = Vout × 100
    
    Arduino ile:
    ADC = analogRead(A0);           // 0-1023
    Gerilim = ADC × (5.0 / 1023.0); // 0-5V
    Sıcaklık = Gerilim × 100;       // °C
```

### 2. DHT11 Dijital Sıcaklık ve Nem Sensörü

#### 2.1 DHT11 Özellikleri
| Özellik | Değer |
|---------|-------|
| Sıcaklık Aralığı | 0°C - 50°C |
| Sıcaklık Doğruluğu | ±2°C |
| Nem Aralığı | 20% - 90% RH |
| Nem Doğruluğu | ±5% |
| Örnekleme Hızı | 1 Hz (saniyede 1) |
| Çalışma Gerilimi | 3.3V - 5.5V |

#### 2.2 DHT11 Pin Yapısı
```
    4 Pinli Versiyon:      3 Pinli Modül:
    ┌─────────────┐        ┌─────────────┐
    │    DHT11    │        │   DHT11     │
    │   ┌─────┐   │        │   MODÜL     │
    │   │     │   │        │             │
    └───┴─┬─┬─┴───┘        └──┬───┬───┬──┘
          │ │ │ │             │   │   │
         VCC DATA NC GND     VCC DATA GND
              │
           [10kΩ] Pull-up (modülde var)
              │
             5V
```

#### 2.3 DHT Kütüphanesi Kurulumu
1. Arduino IDE → Sketch → Include Library → Manage Libraries
2. "DHT sensor library" ara (Adafruit)
3. Install butonuna tıkla
4. Bağımlılık kütüphanesi de yüklenecek (Adafruit Unified Sensor)

### 3. Heat Index (Hissedilen Sıcaklık)

#### 3.1 Heat Index Nedir?
- Sıcaklık ve nemin birlikte etkisiyle hissedilen sıcaklık
- Nem yükseldikçe hissedilen sıcaklık artar
- Vücut terleme yoluyla soğuyamaz

#### 3.2 Heat Index Tablosu
| Gerçek (°C) | Nem %50 | Nem %70 | Nem %90 |
|-------------|---------|---------|---------|
| 25°C | 25°C | 27°C | 28°C |
| 30°C | 31°C | 35°C | 40°C |
| 35°C | 38°C | 46°C | 55°C |

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler (LM35 için)
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| LM35 | 1 | Sıcaklık sensörü |
| LED (Kırmızı) | 1 | Sıcak uyarısı |
| LED (Mavi) | 1 | Soğuk uyarısı |
| 220Ω Direnç | 2 | LED'ler için |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 6+ | Bağlantılar |

### Devre Kurulumu - LM35

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │           LM35                          │
    │         ┌─────┐                         │
    │    5V ──┤VCC  │                         │
    │    A0 ──┤VOUT │                         │
    │   GND ──┤GND  │                         │
    │         └─────┘                         │
    │                                         │
    │    Pin 12 ──[220Ω]──►LED Kırmızı──GND   │
    │    Pin 13 ──[220Ω]──►LED Mavi──GND      │
    │                                         │
    └─────────────────────────────────────────┘
```

---

### Örnek Kod 1: LM35 ile Temel Sıcaklık Ölçümü

```cpp
/*
 * LM35 ile Sıcaklık Ölçümü
 * 10mV/°C çıkış karakteristiği
 */

const int lm35Pin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("LM35 Sicaklik Sensoru");
  Serial.println("=====================");
}

void loop() {
  // ADC değerini oku
  int adcDeger = analogRead(lm35Pin);
  
  // Gerilime çevir (mV)
  float gerilimMv = adcDeger * (5000.0 / 1023.0);
  
  // Sıcaklığa çevir (10mV/°C)
  float sicaklik = gerilimMv / 10.0;
  
  Serial.print("ADC: ");
  Serial.print(adcDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilimMv, 1);
  Serial.print(" mV\t Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.println(" C");
  
  delay(1000);
}
```

---

### Örnek Kod 2: LM35 ile LED Uyarı Sistemi

```cpp
/*
 * LM35 ile LED Uyarı Sistemi
 * Sıcaklığa göre LED kontrolü
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
  Serial.println("Sicaklik Uyari Sistemi");
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
```

---

### Örnek Kod 3: LM35 ile Ortalama Okuma (Gürültü Filtreleme)

```cpp
/*
 * LM35 ile Filtrelenmiş Okuma
 * Çoklu okuma ortalaması ile gürültü azaltma
 */

const int lm35Pin = A0;
const int ornekSayisi = 20;

void setup() {
  Serial.begin(9600);
  Serial.println("Filtrelenmis Sicaklik Okuma");
}

float sicaklikOku() {
  long toplam = 0;
  
  for (int i = 0; i < ornekSayisi; i++) {
    toplam += analogRead(lm35Pin);
    delay(10);
  }
  
  float ortalama = toplam / (float)ornekSayisi;
  float gerilim = ortalama * (5.0 / 1023.0);
  float sicaklik = gerilim * 100.0;
  
  return sicaklik;
}

void loop() {
  float sicaklik = sicaklikOku();
  
  Serial.print("Sicaklik (Filtrelenmis): ");
  Serial.print(sicaklik, 1);
  Serial.println(" C");
  
  delay(1000);
}
```

---

### Gerekli Malzemeler (DHT11 için)
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| DHT11 (modül) | 1 | Sıcaklık ve nem sensörü |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 3 | Bağlantılar |

### Devre Kurulumu - DHT11

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │           DHT11 MODÜL                   │
    │         ┌─────────┐                     │
    │    5V ──┤ VCC (+) │                     │
    │  Pin 2 ─┤ DATA    │                     │
    │   GND ──┤ GND (-) │                     │
    │         └─────────┘                     │
    │                                         │
    └─────────────────────────────────────────┘
```

---

### Örnek Kod 4: DHT11 ile Sıcaklık ve Nem Ölçümü

```cpp
/*
 * DHT11 ile Sıcaklık ve Nem Ölçümü
 * Kütüphane: DHT sensor library (Adafruit)
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
}
```

---

### Örnek Kod 5: Konfor Seviyesi Analizi

```cpp
/*
 * Konfor Seviyesi Analizi
 * Sıcaklık ve nem bazlı konfor değerlendirmesi
 */

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Konfor Analizi Sistemi");
}

void konforAnaliz(float sicaklik, float nem) {
  Serial.print(">>> Konfor: ");
  
  // Konfor koşulları
  bool sicaklikUygun = (sicaklik >= 20 && sicaklik <= 26);
  bool nemUygun = (nem >= 40 && nem <= 60);
  
  if (sicaklikUygun && nemUygun) {
    Serial.println("IDEAL - Konforlu ortam");
  } else if (sicaklik > 30) {
    if (nem > 70) {
      Serial.println("COK SICAK VE NEMLI - Bunaltici");
    } else {
      Serial.println("SICAK - Serinletme gerekli");
    }
  } else if (sicaklik < 18) {
    if (nem < 30) {
      Serial.println("SOGUK VE KURU - Isitma ve nemlendirme");
    } else {
      Serial.println("SOGUK - Isitma gerekli");
    }
  } else if (nem > 70) {
    Serial.println("NEMLI - Nem alma gerekli");
  } else if (nem < 30) {
    Serial.println("KURU - Nemlendirme gerekli");
  } else {
    Serial.println("KABUL EDILEBILIR");
  }
}

void loop() {
  delay(2000);
  
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();
  
  if (isnan(nem) || isnan(sicaklik)) {
    Serial.println("Okuma hatasi!");
    return;
  }
  
  Serial.print("Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.print(" C\t Nem: ");
  Serial.print(nem, 1);
  Serial.println(" %");
  
  konforAnaliz(sicaklik, nem);
  Serial.println();
}
```

---

### Örnek Kod 6: Min/Max Kayıt

```cpp
/*
 * Sıcaklık Min/Max Kayıt
 * Günlük min ve max sıcaklıkları takip et
 */

const int lm35Pin = A0;

float minSicaklik = 100.0;
float maxSicaklik = -50.0;
unsigned long kayitSayisi = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Sicaklik Min/Max Kayit Sistemi");
  Serial.println("Sifirlamak icin Arduino'yu resetleyin");
  Serial.println();
}

float sicaklikOku() {
  int adcDeger = analogRead(lm35Pin);
  float gerilim = adcDeger * (5.0 / 1023.0);
  return gerilim * 100.0;
}

void loop() {
  float sicaklik = sicaklikOku();
  kayitSayisi++;
  
  // Min/Max güncelle
  if (sicaklik < minSicaklik) minSicaklik = sicaklik;
  if (sicaklik > maxSicaklik) maxSicaklik = sicaklik;
  
  Serial.print("Kayit #");
  Serial.print(kayitSayisi);
  Serial.print("\t Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.print(" C\t Min: ");
  Serial.print(minSicaklik, 1);
  Serial.print(" C\t Max: ");
  Serial.print(maxSicaklik, 1);
  Serial.println(" C");
  
  delay(5000);  // 5 saniyede bir kayıt
}
```

---

## 📝 Deney Görevleri

### Görev 1: LM35 Temel Okuma
- [ ] LM35 devresini kur
- [ ] Sıcaklık değerlerini oku
- [ ] Parmakla ısıtarak değişimi gözlemle

### Görev 2: LED Uyarı Sistemi
- [ ] Sıcaklık uyarı sistemi kur
- [ ] Eşik değerlerini ortama göre ayarla
- [ ] Her iki LED'i de test et

### Görev 3: DHT11 Kullanımı
- [ ] DHT kütüphanesini kur
- [ ] Nem ve sıcaklık oku
- [ ] Heat index'i hesapla

### Görev 4: Konfor Analizi
- [ ] Konfor sistemini çalıştır
- [ ] Nefes vererek nemi değiştir
- [ ] Sonuçları gözlemle

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ LM35 ve DHT11 farklarını açıklayabilir
- ✅ Analog ve dijital sensör kullanabilir
- ✅ Kütüphane kurulumu yapabilir
- ✅ Veri doğrulama (isnan) uygulayabilir
- ✅ Çevresel veri analizi yapabilir

---

**Sonraki Hafta:** Ultrasonik Mesafe Sensörü (HC-SR04)
