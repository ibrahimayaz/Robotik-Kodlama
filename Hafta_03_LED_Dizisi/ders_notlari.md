# HAFTA 3: Çoklu Dijital Çıkış - LED Dizisi

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** Diziler, for döngüsü ve çoklu LED kontrolü

---

## TEORİK KISIM (1 Saat)

### 1. Dijital Pin Yapısı ve Özellikleri

#### 1.1 Arduino Uno Dijital Pinler
- **D0 - D13:** 14 adet dijital pin
- **D0 (RX) ve D1 (TX):** Seri haberleşme için rezerve
- **D13:** Dahili LED bağlı (test için kullanışlı)
- **~ işaretli pinler:** PWM destekli (3, 5, 6, 9, 10, 11)

#### 1.2 Akım Limitleri
| Özellik | Değer |
|---------|-------|
| Tek pin maksimum | 40mA |
| Tek pin önerilen | 20mA |
| Toplam (tüm pinler) | 200mA |
| 5V regülatör | 500mA |

**⚠️ Dikkat:** 6 LED × 20mA = 120mA (güvenli aralıkta)

### 2. Diziler (Arrays)

#### 2.1 Dizi Tanımlama
```cpp
// Dizi tanımlama yöntemleri
int pinler[6];                          // 6 elemanlı boş dizi
int pinler[6] = {8, 9, 10, 11, 12, 13}; // Değerlerle tanımlama
int pinler[] = {8, 9, 10, 11, 12, 13};  // Boyut otomatik belirlenir
```

#### 2.2 Dizi İndeksleme
```cpp
// İndeksler 0'dan başlar!
int pinler[] = {8, 9, 10, 11, 12, 13};

pinler[0] = 8   // İlk eleman
pinler[1] = 9   // İkinci eleman
pinler[5] = 13  // Son eleman (6. eleman)

// DİKKAT: pinler[6] HATA! (dizi dışı)
```

#### 2.3 Dizi Görselleştirme
```
    İndeks:    [0]   [1]   [2]   [3]   [4]   [5]
              ┌─────┬─────┬─────┬─────┬─────┬─────┐
    pinler:   │  8  │  9  │ 10  │ 11  │ 12  │ 13  │
              └─────┴─────┴─────┴─────┴─────┴─────┘
```

### 3. For Döngüsü

#### 3.1 For Döngüsü Yapısı
```cpp
for (başlangıç; koşul; artış) {
    // Tekrarlanacak kodlar
}

// Örnek: 0'dan 5'e kadar say
for (int i = 0; i < 6; i++) {
    Serial.println(i);  // 0, 1, 2, 3, 4, 5 yazdırır
}
```

#### 3.2 For Döngüsü Akışı
```
    ┌──────────────────┐
    │ int i = 0        │ ← Başlangıç (1 kez)
    └────────┬─────────┘
             ▼
    ┌──────────────────┐
    │ i < 6 ?          │ ← Koşul kontrolü
    └────────┬─────────┘
        EVET │     HAYIR → Döngüden çık
             ▼
    ┌──────────────────┐
    │ Döngü gövdesi    │ ← Kodları çalıştır
    │ çalışır          │
    └────────┬─────────┘
             ▼
    ┌──────────────────┐
    │ i++              │ ← Artış
    └────────┬─────────┘
             │
             └────────────→ Koşula geri dön
```

#### 3.3 Ters Sayma
```cpp
// 5'ten 0'a kadar say (geriye)
for (int i = 5; i >= 0; i--) {
    Serial.println(i);  // 5, 4, 3, 2, 1, 0 yazdırır
}
```

### 4. Dizilerle Döngü Kullanımı

```cpp
int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;

// Tüm pinleri çıkış yap
for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
}

// Tüm LED'leri yak
for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], HIGH);
}
```

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| LED (5mm) | 6 | Farklı renkler tercih edilebilir |
| 220Ω Direnç | 6 | Her LED için bir direnç |
| Breadboard | 1 | Büyük boy tercih edilir |
| Jumper Kablo | 8+ | Erkek-Erkek |

### Devre Kurulumu

```
    Arduino                 Breadboard
    ┌──────┐               
    │      │    Pin 8  ────[220Ω]────►LED1────┐
    │      │    Pin 9  ────[220Ω]────►LED2────┤
    │      │    Pin 10 ────[220Ω]────►LED3────┤
    │      │    Pin 11 ────[220Ω]────►LED4────┼──── GND
    │      │    Pin 12 ────[220Ω]────►LED5────┤
    │      │    Pin 13 ────[220Ω]────►LED6────┤
    │      │                                   │
    │ GND  │───────────────────────────────────┘
    └──────┘
```

---

### Örnek Kod 1: Sıralı LED Yakma

```cpp
/*
 * Sıralı LED Yakma
 * LED'leri sırayla yakar ve söndürür
 */

int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;

void setup() {
  // Tüm pinleri çıkış olarak ayarla
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void loop() {
  // Sırayla LED'leri yak
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(200);
  }
  
  // Sırayla LED'leri söndür
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], LOW);
    delay(200);
  }
}
```

---

### Örnek Kod 2: Knight Rider Efekti

```cpp
/*
 * Knight Rider Efekti
 * LED'ler sağa-sola hareket eder (KITT efekti)
 */

int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;
int gecikme = 100;

void setup() {
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void loop() {
  // Sağa doğru
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(gecikme);
    digitalWrite(ledPinleri[i], LOW);
  }
  
  // Sola doğru (kenar LED'leri atlayarak)
  for (int i = pinSayisi - 2; i > 0; i--) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(gecikme);
    digitalWrite(ledPinleri[i], LOW);
  }
}
```

**Animasyon Görselleştirme:**
```
    Adım 1: ● ○ ○ ○ ○ ○  (sağa)
    Adım 2: ○ ● ○ ○ ○ ○
    Adım 3: ○ ○ ● ○ ○ ○
    Adım 4: ○ ○ ○ ● ○ ○
    Adım 5: ○ ○ ○ ○ ● ○
    Adım 6: ○ ○ ○ ○ ○ ●
    Adım 7: ○ ○ ○ ○ ● ○  (sola)
    Adım 8: ○ ○ ○ ● ○ ○
    ...
```

---

### Örnek Kod 3: Binary Counter (İkili Sayaç)

```cpp
/*
 * Binary Counter
 * 4 LED ile 0-15 arası ikili sayma
 * 
 * LED düzeni: LED3 LED2 LED1 LED0
 *              8    4    2    1
 */

int ledPinleri[] = {8, 9, 10, 11};  // 4 LED
int pinSayisi = 4;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void binaryGoster(int sayi) {
  for (int i = 0; i < pinSayisi; i++) {
    // Bit kaydırma ile her bitin değerini al
    int bitDegeri = (sayi >> i) & 1;
    digitalWrite(ledPinleri[i], bitDegeri);
  }
}

void loop() {
  for (int sayi = 0; sayi < 16; sayi++) {
    binaryGoster(sayi);
    
    // Seri monitöre yazdır
    Serial.print("Sayi: ");
    Serial.print(sayi);
    Serial.print(" -> Binary: ");
    
    for (int i = pinSayisi - 1; i >= 0; i--) {
      Serial.print((sayi >> i) & 1);
    }
    Serial.println();
    
    delay(1000);
  }
}
```

**Binary Sayma Tablosu:**
```
    Sayı | LED3 | LED2 | LED1 | LED0 | Binary
    -----|------|------|------|------|--------
      0  |  ○   |  ○   |  ○   |  ○   | 0000
      1  |  ○   |  ○   |  ○   |  ●   | 0001
      2  |  ○   |  ○   |  ●   |  ○   | 0010
      3  |  ○   |  ○   |  ●   |  ●   | 0011
      4  |  ○   |  ●   |  ○   |  ○   | 0100
      5  |  ○   |  ●   |  ○   |  ●   | 0101
      ...
     15  |  ●   |  ●   |  ●   |  ●   | 1111
```

---

### Örnek Kod 4: Rastgele LED Efekti

```cpp
/*
 * Rastgele LED Efekti
 * Rastgele LED'leri yakar ve söndürür
 */

int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;

void setup() {
  // Rastgele sayı üreteci için seed
  randomSeed(analogRead(0));
  
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void tumunuSondur() {
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], LOW);
  }
}

void loop() {
  // Rastgele bir LED seç (0-5 arası)
  int rastgeleLED = random(0, pinSayisi);
  
  // Tüm LED'leri söndür
  tumunuSondur();
  
  // Seçilen LED'i yak
  digitalWrite(ledPinleri[rastgeleLED], HIGH);
  
  // Rastgele gecikme (100-500ms arası)
  int gecikme = random(100, 500);
  delay(gecikme);
}
```

---

### Örnek Kod 5: LED Dalgası (Wave Effect)

```cpp
/*
 * LED Dalgası
 * Kayan dalga efekti - birden fazla LED aynı anda yanar
 */

int ledPinleri[] = {8, 9, 10, 11, 12, 13};
int pinSayisi = 6;
int dalgaGenisligi = 3;  // Kaç LED aynı anda yanacak
int gecikme = 150;

void setup() {
  for (int i = 0; i < pinSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void tumunuSondur() {
  for (int i = 0; i < pinSayisi; i++) {
    digitalWrite(ledPinleri[i], LOW);
  }
}

void loop() {
  // Sağa doğru dalga
  for (int pos = 0; pos < pinSayisi; pos++) {
    tumunuSondur();
    
    // Dalga genişliği kadar LED yak
    for (int j = 0; j < dalgaGenisligi; j++) {
      int ledIndex = pos + j;
      if (ledIndex < pinSayisi) {
        digitalWrite(ledPinleri[ledIndex], HIGH);
      }
    }
    delay(gecikme);
  }
  
  // Sola doğru dalga
  for (int pos = pinSayisi - 1; pos >= 0; pos--) {
    tumunuSondur();
    
    for (int j = 0; j < dalgaGenisligi; j++) {
      int ledIndex = pos - j;
      if (ledIndex >= 0) {
        digitalWrite(ledPinleri[ledIndex], HIGH);
      }
    }
    delay(gecikme);
  }
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Kurulum
- [ ] 6 LED'li devreyi kur
- [ ] Sıralı LED yakma kodunu test et
- [ ] Gecikme süresini değiştir (50ms, 100ms, 200ms)

### Görev 2: Knight Rider
- [ ] Knight Rider efektini çalıştır
- [ ] Hızı artır/azalt
- [ ] Kuyruk efekti ekle (sönmesi yavaş)

### Görev 3: Binary Counter
- [ ] 4 LED ile ikili sayaç kur
- [ ] 0-15 arası sayımı gözlemle
- [ ] Seri monitörde çıktıyı kontrol et

### Görev 4: Kendi Patternini Oluştur
- [ ] Yeni bir LED animasyonu tasarla
- [ ] Birden fazla efekti birleştir

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Dizi (array) tanımlayıp kullanabilir
- ✅ For döngüsü ile tekrarlı işlem yapabilir
- ✅ Çoklu LED kontrolü gerçekleştirebilir
- ✅ İndeks kavramını anlayabilir
- ✅ Bit operasyonlarını temel seviyede kullanabilir
- ✅ Karmaşık LED animasyonları oluşturabilir

---

## 💡 İpuçları

1. **sizeof() kullanımı:** Dizi boyutunu otomatik hesaplama
   ```cpp
   int pinSayisi = sizeof(ledPinleri) / sizeof(ledPinleri[0]);
   ```

2. **Kuyruk efekti:** LED'i söndürmeden önce kısa gecikme
   ```cpp
   digitalWrite(ledPinleri[i], HIGH);
   delay(50);
   digitalWrite(ledPinleri[i-1], LOW);  // Önceki LED'i söndür
   ```

3. **Hız ayarı:** Değişken ile hızı kontrol et
   ```cpp
   int hiz = analogRead(A0);  // Potansiyometre ile hız ayarı
   gecikme = map(hiz, 0, 1023, 50, 500);
   ```

---

**Sonraki Hafta:** Dijital Giriş - Buton Kontrolü
