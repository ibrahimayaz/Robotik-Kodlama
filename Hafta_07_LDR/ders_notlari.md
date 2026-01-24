# HAFTA 7: LDR (Fotoresistör) ile Işık Algılama

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** LDR sensör, gerilim bölücü, otomatik aydınlatma

---

## TEORİK KISIM (1 Saat)

### 1. LDR (Light Dependent Resistor)

#### 1.1 LDR Nedir?
- Işığa bağlı direnç (Fotoresistör)
- Işık şiddeti arttıkça direnç azalır
- Fotoelektrik etki prensibine dayanır

#### 1.2 LDR Malzemesi ve Yapısı
- **Malzeme:** Kadmiyum Sülfür (CdS) veya Kadmiyum Selenyum (CdSe)
- **Spektral yanıt:** 400-700 nm (görünür ışık)
- **Yanıt süresi:** 8-12 ms

```
    LDR Sembolü:
    
        ──┤ ├──
          │ │
    ↘   ──┴─┴──   ↙
      \          /
       ─────────
       (Işık okları)
```

#### 1.3 Direnç-Işık İlişkisi
| Ortam | Direnç | ADC Değeri (yaklaşık) |
|-------|--------|----------------------|
| Karanlık | 1MΩ - 10MΩ | 0-50 |
| Alacakaranlık | 10kΩ - 50kΩ | 50-300 |
| Oda ışığı | 5kΩ - 10kΩ | 300-700 |
| Parlak ışık | 100Ω - 1kΩ | 700-1023 |

### 2. Gerilim Bölücü Devre

#### 2.1 Neden Gerilim Bölücü?
- LDR direnç değişimini gerilim değişimine çevirir
- Arduino analog pin gerilim okur (0-5V)

#### 2.2 LDR Alt Konfigürasyon
```
        VCC (5V)
           │
          LDR (Rlight)
           │
           ├─────► Vout (A0'a)
           │
         [10kΩ] R1
           │
          GND
    
    Vout = VCC × (R1 / (Rlight + R1))
    
    Karanlıkta (Rlight yüksek): Vout düşük
    Aydınlıkta (Rlight düşük): Vout yüksek
```

#### 2.3 LDR Üst Konfigürasyon
```
        VCC (5V)
           │
         [10kΩ] R1
           │
           ├─────► Vout (A0'a)
           │
          LDR (Rlight)
           │
          GND
    
    Vout = VCC × (Rlight / (R1 + Rlight))
    
    Karanlıkta (Rlight yüksek): Vout yüksek
    Aydınlıkta (Rlight düşük): Vout düşük
```

#### 2.4 Hesaplama Örnekleri
```
    LDR Alt Konfigürasyon (R1 = 10kΩ):
    
    Karanlık (Rlight = 1MΩ):
    Vout = 5V × (10k / (1M + 10k))
    Vout = 5V × (10k / 1010k)
    Vout ≈ 0.05V → ADC ≈ 10
    
    Oda ışığı (Rlight = 10kΩ):
    Vout = 5V × (10k / (10k + 10k))
    Vout = 5V × 0.5
    Vout = 2.5V → ADC ≈ 512
    
    Parlak (Rlight = 500Ω):
    Vout = 5V × (10k / (500 + 10k))
    Vout = 5V × (10k / 10.5k)
    Vout ≈ 4.76V → ADC ≈ 975
```

### 3. Kalibrasyon ve Eşik Değerleri

#### 3.1 Kalibrasyon Neden Gerekli?
- Her LDR farklı karakteristiğe sahip
- Ortam koşulları değişken
- Direnç toleransları

#### 3.2 Kalibrasyon Yöntemi
1. Karanlık ortamda minimum değeri ölç
2. Parlak ortamda maksimum değeri ölç
3. Eşik değerlerini belirle

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| LDR (Fotoresistör) | 1 | 5mm veya 10mm |
| 10kΩ Direnç | 1 | LDR için gerilim bölücü |
| LED | 1 | Herhangi renk |
| 220Ω Direnç | 1 | LED için |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 6+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────┐
    │              BREADBOARD                 │
    │                                         │
    │    5V ──── LDR ────┬──── A0             │
    │                    │                    │
    │                 [10kΩ]                  │
    │                    │                    │
    │                   GND                   │
    │                                         │
    │    Pin 9 (PWM) ──[220Ω]──►LED──GND      │
    │                                         │
    └─────────────────────────────────────────┘
```

---

### Örnek Kod 1: Temel Işık Ölçümü

```cpp
/*
 * Temel Işık Ölçümü
 * LDR değerini okur ve gösterir
 */

const int ldrPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("LDR Isik Olcumu");
  Serial.println("===============");
}

void loop() {
  int isikDeger = analogRead(ldrPin);
  
  // Gerilim hesapla
  float gerilim = isikDeger * (5.0 / 1023.0);
  
  Serial.print("ADC: ");
  Serial.print(isikDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilim, 2);
  Serial.print(" V\t Durum: ");
  
  // Işık seviyesi yorumlama
  if (isikDeger < 200) {
    Serial.println("KARANLIK");
  } else if (isikDeger < 500) {
    Serial.println("LOSCH");
  } else if (isikDeger < 800) {
    Serial.println("NORMAL");
  } else {
    Serial.println("PARLAK");
  }
  
  delay(500);
}
```

---

### Örnek Kod 2: Otomatik Kalibrasyon

```cpp
/*
 * Otomatik Kalibrasyon
 * 10 saniye içinde min/max değerleri tespit eder
 */

const int ldrPin = A0;

int minDeger = 1023;
int maxDeger = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("LDR Kalibrasyon");
  Serial.println("10 saniye icinde LDR'yi karanlik ve aydinlik ortama tutun...");
  
  unsigned long baslangic = millis();
  
  // 10 saniye kalibrasyon
  while (millis() - baslangic < 10000) {
    int okunan = analogRead(ldrPin);
    
    if (okunan > maxDeger) maxDeger = okunan;
    if (okunan < minDeger) minDeger = okunan;
    
    // Kalan süreyi göster
    int kalanSure = 10 - ((millis() - baslangic) / 1000);
    Serial.print("Kalan: ");
    Serial.print(kalanSure);
    Serial.print(" sn - Min: ");
    Serial.print(minDeger);
    Serial.print(" Max: ");
    Serial.println(maxDeger);
    
    delay(100);
  }
  
  Serial.println("\nKalibrasyon Tamamlandi!");
  Serial.print("Minimum: ");
  Serial.println(minDeger);
  Serial.print("Maksimum: ");
  Serial.println(maxDeger);
  Serial.println("\nOlcum basliyor...");
}

void loop() {
  int isik = analogRead(ldrPin);
  
  // Kalibre edilmiş değeri yüzdeye çevir
  int yuzde = map(isik, minDeger, maxDeger, 0, 100);
  yuzde = constrain(yuzde, 0, 100);  // 0-100 arasında sınırla
  
  Serial.print("Ham: ");
  Serial.print(isik);
  Serial.print("\t Isik: %");
  Serial.println(yuzde);
  
  delay(250);
}
```

---

### Örnek Kod 3: Otomatik Aydınlatma (Akıllı Sokak Lambası)

```cpp
/*
 * Otomatik Aydınlatma
 * Karanlık olunca LED yanar (ters orantılı)
 */

const int ldrPin = A0;
const int ledPin = 9;
const int esikDeger = 500;  // Kalibrasyon sonrası ayarlanmalı

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Otomatik Aydinlatma Sistemi");
}

void loop() {
  int isikSeviyesi = analogRead(ldrPin);
  
  Serial.print("Isik: ");
  Serial.print(isikSeviyesi);
  
  if (isikSeviyesi < esikDeger) {
    // Karanlık - LED parlaklığı ters orantılı
    int parlaklik = map(isikSeviyesi, 0, esikDeger, 255, 0);
    parlaklik = constrain(parlaklik, 0, 255);
    
    analogWrite(ledPin, parlaklik);
    
    Serial.print("\t LED: ");
    Serial.print(parlaklik);
    Serial.println(" (ACIK)");
  } else {
    // Aydınlık - LED kapalı
    analogWrite(ledPin, 0);
    Serial.println("\t LED: KAPALI");
  }
  
  delay(200);
}
```

---

### Örnek Kod 4: Işık Alarm Sistemi

```cpp
/*
 * Işık Alarm Sistemi
 * Ani ışık değişiminde alarm verir
 */

const int ldrPin = A0;
const int ledPin = 13;
const int buzzerPin = 8;

int oncekiDeger = 0;
const int degisimEsik = 100;  // Hassasiyet

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Isik Alarm Sistemi");
  
  // İlk okuma
  oncekiDeger = analogRead(ldrPin);
}

void loop() {
  int simdikiDeger = analogRead(ldrPin);
  int fark = abs(simdikiDeger - oncekiDeger);
  
  Serial.print("Deger: ");
  Serial.print(simdikiDeger);
  Serial.print("\t Fark: ");
  Serial.print(fark);
  
  if (fark > degisimEsik) {
    Serial.println("\t !!! ALARM !!!");
    
    // Alarm ver
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 2000, 200);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(100);
  } else {
    Serial.println("\t Normal");
  }
  
  oncekiDeger = simdikiDeger;
  delay(100);
}
```

---

### Örnek Kod 5: Işık Takipçi (Light Follower)

```cpp
/*
 * Işık Takipçi
 * İki LDR ile ışığın yönünü tespit et
 * Servo motor eklenebilir (opsiyonel)
 */

const int ldrSol = A0;
const int ldrSag = A1;
const int ledSol = 12;
const int ledSag = 13;

const int tolerans = 50;  // Fark toleransı

void setup() {
  pinMode(ledSol, OUTPUT);
  pinMode(ledSag, OUTPUT);
  Serial.begin(9600);
  Serial.println("Isik Takipci");
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
  Serial.print(fark);
  Serial.print("\t Yon: ");
  
  if (abs(fark) < tolerans) {
    // Merkez
    digitalWrite(ledSol, LOW);
    digitalWrite(ledSag, LOW);
    Serial.println("MERKEZ");
  } else if (fark > 0) {
    // Sol taraf daha aydınlık
    digitalWrite(ledSol, HIGH);
    digitalWrite(ledSag, LOW);
    Serial.println("SOL");
  } else {
    // Sağ taraf daha aydınlık
    digitalWrite(ledSol, LOW);
    digitalWrite(ledSag, HIGH);
    Serial.println("SAG");
  }
  
  delay(100);
}
```

---

### Örnek Kod 6: Işık Seviyesi Göstergesi (LED Bar)

```cpp
/*
 * Işık Seviyesi Göstergesi
 * 5 LED ile ışık seviyesini gösterir
 */

const int ldrPin = A0;
int ledPinleri[] = {8, 9, 10, 11, 12};
int ledSayisi = 5;

void setup() {
  for (int i = 0; i < ledSayisi; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int isik = analogRead(ldrPin);
  
  // 0-1023 aralığını 0-5 aralığına çevir
  int seviye = map(isik, 0, 1023, 0, ledSayisi);
  
  // LED'leri güncelle
  for (int i = 0; i < ledSayisi; i++) {
    if (i < seviye) {
      digitalWrite(ledPinleri[i], HIGH);
    } else {
      digitalWrite(ledPinleri[i], LOW);
    }
  }
  
  Serial.print("Isik: ");
  Serial.print(isik);
  Serial.print("\t Seviye: ");
  Serial.print(seviye);
  Serial.println("/5");
  
  delay(100);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Okuma
- [ ] LDR devresini kur
- [ ] Işık değerlerini Serial Monitor'da gözlemle
- [ ] Karanlık ve aydınlık değerlerini kaydet

### Görev 2: Kalibrasyon
- [ ] Otomatik kalibrasyon kodunu çalıştır
- [ ] Min/Max değerlerini belirle
- [ ] Eşik değerlerini ayarla

### Görev 3: Otomatik Aydınlatma
- [ ] Akıllı sokak lambası devresini kur
- [ ] LDR'yi kapatarak LED'in yandığını gör
- [ ] Parlaklık geçişini gözlemle

### Görev 4: Işık Alarm
- [ ] Ani ışık değişim alarmını test et
- [ ] Hassasiyeti ayarla
- [ ] Buzzer ekle (varsa)

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ LDR çalışma prensibini açıklayabilir
- ✅ Gerilim bölücü devre analizi yapabilir
- ✅ Kalibrasyon tekniklerini uygulayabilir
- ✅ Eşik değeri mantığını kullanabilir
- ✅ Otomatik kontrol sistemleri tasarlayabilir

---

**Sonraki Hafta:** Sıcaklık Sensörü (DHT11/LM35) ile Çevre Ölçümü
