# Arduino ile Robotik Kodlama Dersi
## 14 Haftalık Ders Programı (Haftada 2.5 Saat)
### Önlisans Seviyesi

---

## HAFTA 1: Robotik Kodlama ve Arduino'ya Giriş (Teorik)

### Ders İçeriği
**Süre:** 2 saat 30 dakika (Tamamen teorik)

#### 1. Robotik ve Otomasyon Sistemleri (35 dakika)
- Robotik biliminin tanımı ve tarihçesi
- Endüstriyel robotlar, servis robotları, mobil robotlar
- Otomasyon sistemlerinin temel bileşenleri: Sensör, işlemci, aktüatör
- Geri besleme (feedback) kavramı ve kapalı döngü sistemler
- Robotik kullanım alanları: Üretim, tıp, savunma, eğitim

#### 2. Mikroişlemci ve Mikrodenetleyici Teknolojisi (40 dakika)
- Mikroişlemci vs Mikrodenetleyici farkları
- Arduino platformunun tarihi ve açık kaynak felsefesi
- Arduino donanım mimarisi:
  - ATmega328P mikrodenetleyici özellikleri
  - Flash bellek, SRAM, EEPROM kavramları
  - Clock frekansı (16 MHz)
- Arduino çeşitleri ve karşılaştırma (Uno, Nano, Mega, Due)
- GPIO (General Purpose Input/Output) pinleri

#### 3. Elektronik ve Devre Temelleri (50 dakika)
- Temel elektrik büyüklükleri:
  - Akım (I): Ampermetre ile ölçüm, DC ve AC akım
  - Gerilim (V): Voltmetre ile ölçüm, potansiyel farkı
  - Direnç (R): Ohmmetre ile ölçüm
- **Ohm Kanunu: V = I × R**
- Seri ve paralel devre bağlantıları
- Direnç renk kodları (4 ve 5 bantlı)
- Breadboard (devre tahtası) yapısı ve kullanımı
- Elektronik bileşenler:
  - Pasif elemanlar: Direnç, kondansatör, bobin
  - Aktif elemanlar: LED, transistör, diyot, IC
  - Sensörler ve aktüatörler
- Dijital mantık: HIGH (5V), LOW (0V/GND)
- Analog sinyaller: Sürekli değişen gerilim değerleri (0-5V)

#### 4. Arduino Programlama Temelleri (20 dakika)
- Arduino IDE kurulumu ve arayüz tanıtımı
- Sketch kavramı
- Temel kod yapısı:
```cpp
void setup() {
  // Başlangıç ayarları - bir kez çalışır
}

void loop() {
  // Ana program - sürekli döngü
}
```
- Değişkenler ve veri tipleri (int, float, boolean, char)
- Sabitler (const)
- Operatörler: Aritmetik (+, -, *, /), karşılaştırma (==, !=, <, >), mantıksal (&&, ||, !)
- Yorum satırları: // ve /* */

#### 5. Simülasyon Araçları ve Prototipleme (5 dakika)
- Tinkercad Circuits platformu
- Wokwi, Proteus, Fritzing alternatifleri
- Fiziksel prototipleme öncesi simülasyon avantajları

---

## HAFTA 2: Dijital Çıkış - LED Kontrolü

### Teorik Kısım (1 saat)

#### LED (Light Emitting Diode) Teknolojisi
- **Yarı iletken diyot yapısı**: P-N jonksiyonu
- **Çalışma prensibi**: Elektrolüminesans, foton emisyonu
- **Anot (+) ve Katot (-)** uçları, polarite önemi
- **Forward voltage (Vf)**: Tipik değerler (Kırmızı: 1.8-2.2V, Mavi/Beyaz: 3.0-3.4V)
- **Maksimum akım (If)**: Genellikle 20mA
- **Akım sınırlama direnci hesaplama**:
  - R = (Vs - Vf) / If
  - Örnek: (5V - 2V) / 0.02A = 150Ω (220Ω standart değer kullanılır)
- LED renkleri ve dalga boyları (nm)
- RGB LED kavramı
- LED uygulama alanları: Gösterge, aydınlatma, ekran, optik haberleşme

#### Arduino Dijital I/O Fonksiyonları
- **pinMode(pin, mode)**: INPUT, OUTPUT, INPUT_PULLUP
- **digitalWrite(pin, value)**: HIGH, LOW
- **delay(ms)**: Milisaniye cinsinden bekleme
- Pin numaralandırma sistemi

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- LED (5mm, herhangi bir renk)
- 220Ω direnç (Kırmızı-Kırmızı-Kahverengi)
- Breadboard
- Jumper kablolar (Erkek-Erkek)

**Tinkercad Devre Şeması:**
```
Arduino Pin 13 → 220Ω Direnç → LED Anot (uzun bacak)
LED Katot (kısa bacak) → GND
```

#### Örnek Kod 1: Temel Blink
```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);  // LED yak
  delay(1000);             // 1 saniye bekle
  digitalWrite(13, LOW);   // LED söndür
  delay(1000);             // 1 saniye bekle
}
```

#### Örnek Kod 2: SOS Morse Kodu
```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void yanip(int sure) {
  digitalWrite(13, HIGH);
  delay(sure);
  digitalWrite(13, LOW);
  delay(200);
}

void loop() {
  // S (· · ·)
  for(int i=0; i<3; i++) yanip(200);
  delay(400);
  
  // O (— — —)
  for(int i=0; i<3; i++) yanip(600);
  delay(400);
  
  // S (· · ·)
  for(int i=0; i<3; i++) yanip(200);
  delay(2000);
}
```

#### Öğrenme Çıktıları
- Temel Arduino fonksiyonları kullanımı
- Devre şeması okuma ve kurma becerisi
- Tinkercad simülasyonu
- Döngü mantığı

---

## HAFTA 3: Çoklu Dijital Çıkış - LED Dizisi

### Teorik Kısım (1 saat)

#### Dijital Pin Yapısı ve Özellikleri
- Arduino Uno dijital pinler: D0-D13 (14 adet)
- Her pinin maksimum akım kapasitesi: 40mA (önerilen: 20mA)
- Toplam akım limiti: 200mA
- D0 ve D1 (RX/TX): Seri haberleşme için rezerve
- D13: Dahili LED bağlantısı

#### Programlama Kavramları
- **Diziler (Arrays)**: Aynı türden verileri saklama
```cpp
int pinler[5] = {8, 9, 10, 11, 12};
```
- **For döngüsü**: Tekrarlayan işlemler
```cpp
for(int i=0; i<5; i++) {
  // İşlemler
}
```
- İndeksleme: 0'dan başlar

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- 6 adet LED (farklı renkler tercih edilebilir)
- 6 adet 220Ω direnç
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
Pin 8 → R → LED1 → GND
Pin 9 → R → LED2 → GND
Pin 10 → R → LED3 → GND
Pin 11 → R → LED4 → GND
Pin 12 → R → LED5 → GND
Pin 13 → R → LED6 → GND
```

#### Örnek Kod: Sıralı Animasyon (Knight Rider)
```cpp
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
  
  // Sola doğru
  for (int i = pinSayisi - 2; i > 0; i--) {
    digitalWrite(ledPinleri[i], HIGH);
    delay(gecikme);
    digitalWrite(ledPinleri[i], LOW);
  }
}
```

#### Bonus: Binary Counter (İkili Sayma)
```cpp
int ledPinleri[] = {8, 9, 10, 11};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPinleri[i], OUTPUT);
  }
}

void binaryGoster(int sayi) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPinleri[i], (sayi >> i) & 1);
  }
}

void loop() {
  for (int sayi = 0; sayi < 16; sayi++) {
    binaryGoster(sayi);
    delay(1000);
  }
}
```

#### Öğrenme Çıktıları
- Dizi kullanımı ve indeksleme
- For döngüsü mantığı
- Çoklu çıkış yönetimi
- Bit operasyonları (bonus)

---

## HAFTA 4: Dijital Giriş - Buton Kontrolü

### Teorik Kısım (1 saat)

#### Push Button (Takt Buton)
- **Mekanik yapı**: SPST (Single Pole Single Throw)
- **NO (Normally Open)**: Varsayılan açık kontak
- **NC (Normally Closed)**: Varsayılan kapalı kontak
- **Pull-up ve Pull-down dirençleri**:
  - Pull-down: Buton açıkken pin GND'ye çekilir (0V - LOW)
  - Pull-up: Buton açıkken pin Vcc'ye çekilir (5V - HIGH)
- **Debouncing (Titreme giderme)**:
  - Mekanik kontaklarda mikro-saniye seviyesinde titreşimler
  - Yazılımsal çözüm: delay() ile bekleme
  - Donanımsal çözüm: RC filtre devresi
- Arduino **INPUT_PULLUP** modu: Dahili 20kΩ pull-up direnci

#### Dijital Giriş Fonksiyonları
- **digitalRead(pin)**: HIGH veya LOW okur
- Karar yapıları:
```cpp
if (koşul) {
  // Doğru ise
} else {
  // Yanlış ise
}
```

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- 2 adet Push button
- 2 adet LED (farklı renk)
- 2 adet 220Ω direnç (LED için)
- 2 adet 10kΩ direnç (pull-down için)
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
Buton1 bir ucu → 5V
Buton1 diğer ucu → Pin 2 ve 10kΩ → GND

Buton2 bir ucu → 5V
Buton2 diğer ucu → Pin 3 ve 10kΩ → GND

Pin 12 → 220Ω → LED1 → GND
Pin 13 → 220Ω → LED2 → GND
```

#### Örnek Kod 1: Basit Buton-LED Kontrolü
```cpp
const int buton1Pin = 2;
const int buton2Pin = 3;
const int led1Pin = 12;
const int led2Pin = 13;

void setup() {
  pinMode(buton1Pin, INPUT);
  pinMode(buton2Pin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  if (digitalRead(buton1Pin) == HIGH) {
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }
  
  if (digitalRead(buton2Pin) == HIGH) {
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
  }
}
```

#### Örnek Kod 2: Toggle (Aç/Kapa Modu) - Debouncing ile
```cpp
const int butonPin = 2;
const int ledPin = 13;

int sonButonDurum = LOW;
int ledDurum = LOW;
unsigned long sonDebounceZaman = 0;
unsigned long debounceGecikme = 50;

void setup() {
  pinMode(butonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledDurum);
}

void loop() {
  int okunan = digitalRead(butonPin);
  
  if (okunan != sonButonDurum) {
    sonDebounceZaman = millis();
  }
  
  if ((millis() - sonDebounceZaman) > debounceGecikme) {
    if (okunan == HIGH && sonButonDurum == LOW) {
      ledDurum = !ledDurum;
      digitalWrite(ledPin, ledDurum);
    }
  }
  
  sonButonDurum = okunan;
}
```

#### Öğrenme Çıktıları
- Dijital giriş okuma
- Karar yapıları (if-else)
- State machine mantığı
- Debouncing tekniği
- millis() fonksiyonu

---

## HAFTA 5: Analog Giriş - Potansiyometre ve Seri Haberleşme

### Teorik Kısım (1 saat)

#### Potansiyometre
- **Değişken direnç prensibi**: 3 uçlu ayarlanabilir direnç bölücü
- **Dönme açısı**: Tek turlu (270°), çok turlu (10 tur)
- **Direnç değerleri**: 1kΩ, 10kΩ, 100kΩ, 1MΩ
- **Gerilim bölücü formülü**:
  - Vout = Vin × (R2 / (R1 + R2))
- **Kullanım alanları**: Ses kontrolü, servo açısı, LED parlaklığı

#### Arduino Analog Giriş Sistemi
- **Analog pinler**: A0-A5 (Arduino Uno'da 6 adet)
- **ADC (Analog-to-Digital Converter)**: Analog sinyali dijitale çevirir
- **Çözünürlük**: 10-bit → 2^10 = 1024 seviye (0-1023)
- **Referans gerilim**: Varsayılan 5V (AREF pini ile değiştirilebilir)
- **Dönüşüm formülü**: Değer = (Gerilim / 5V) × 1023
- **analogRead(pin)**: 0-1023 arası değer döner
- **Örnekleme hızı**: ~9600 örnek/saniye

#### UART Seri Haberleşme
- **UART (Universal Asynchronous Receiver-Transmitter)**
- **TX (Transmit)**: Veri gönderme pini (Pin 1)
- **RX (Receive)**: Veri alma pini (Pin 0)
- **Baud Rate**: Bit/saniye hızı (9600, 19200, 115200 vb.)
- **Veri formatı**: Start bit + 8 data bit + Stop bit
- **Serial Monitor**: Arduino IDE'de veri izleme aracı
- **Serial Plotter**: Grafik gösterim

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- 10kΩ potansiyometre (B10K)
- LED
- 220Ω direnç
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
Potansiyometre uç 1 → GND
Potansiyometre orta uç → A0
Potansiyometre uç 2 → 5V

Pin 9 → 220Ω → LED → GND
```

#### Örnek Kod: Veri İzleme ve Analiz
```cpp
const int potPin = A0;
const int ledPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Ham değer oku
  int hamDeger = analogRead(potPin);
  
  // Gerilim hesapla
  float gerilim = hamDeger * (5.0 / 1023.0);
  
  // PWM değerine dönüştür (0-255)
  int pwmDeger = map(hamDeger, 0, 1023, 0, 255);
  
  // LED parlaklığını ayarla
  analogWrite(ledPin, pwmDeger);
  
  // Seri monitöre yazdır
  Serial.print("ADC: ");
  Serial.print(hamDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilim, 2);  // 2 ondalık basamak
  Serial.print(" V\t PWM: ");
  Serial.println(pwmDeger);
  
  delay(100);
}
```

#### Bonus: Grafik Gösterim için Serial Plotter Formatı
```cpp
void loop() {
  int deger = analogRead(A0);
  float gerilim = deger * (5.0 / 1023.0);
  
  // Virgülle ayrılmış değerler
  Serial.print("ADC:");
  Serial.print(deger);
  Serial.print(",");
  Serial.print("Gerilim_x100:");
  Serial.println(gerilim * 100);
  
  delay(50);
}
```

#### Öğrenme Çıktıları
- Analog sinyal okuma
- Veri tipi dönüşümleri (int, float)
- Seri haberleşme protokolü
- map() fonksiyonu
- Gerçek zamanlı veri izleme

---

## HAFTA 6: PWM (Pulse Width Modulation) ile Analog Çıkış

### Teorik Kısım (1 saat)

#### PWM Teknolojisi
- **PWM tanımı**: Dijital sinyalle analog etki yaratma
- **Temel prensibi**: Hızlı açma-kapama (HIGH-LOW geçişleri)
- **Duty Cycle (Görev Döngüsü)**: Sinyalin HIGH olduğu sürenin yüzdesi
  - 0%: Sürekli LOW (0V ortalama)
  - 50%: Yarı süre HIGH (2.5V ortalama)
  - 100%: Sürekli HIGH (5V ortalama)
- **Frekans**: Arduino'da ~490 Hz (Pin 5 ve 6'da ~980 Hz)
- **Periyot (T)**: 1/Frekans
- **Arduino PWM pinleri**: ~işaretli pinler (3, 5, 6, 9, 10, 11)
- **analogWrite(pin, value)**: 0-255 arası değer (8-bit)
- **Kullanım alanları**: Motor hız kontrolü, LED parlaklığı, ses üretimi

#### PWM Matematiksel Analizi
```
Ortalama Gerilim = Vcc × (Duty Cycle / 100)
Örnek: 5V × (127/255) = 2.49V
```

#### Donanımsal PWM vs Yazılımsal PWM
- **Donanımsal (Hardware PWM)**: Timer/Counter kullanır, CPU'yu meşgul etmez
- **Yazılımsal (Software PWM)**: digitalWrite ve delay ile simüle edilir, CPU yükü yaratır

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- 1 adet LED (tercihen beyaz veya mavi - parlaklık değişimi daha belirgin)
- 220Ω direnç
- 10kΩ potansiyometre
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
Potansiyometre → A0
Pin 9 (PWM) → 220Ω → LED → GND
```

#### Örnek Kod 1: Manuel Parlaklık Kontrolü
```cpp
const int potPin = A0;
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potDeger = analogRead(potPin);
  int parlaklik = map(potDeger, 0, 1023, 0, 255);
  
  analogWrite(ledPin, parlaklik);
  
  // Duty cycle hesapla
  float dutyCycle = (parlaklik / 255.0) * 100.0;
  float ortalamaGerilim = 5.0 * (parlaklik / 255.0);
  
  Serial.print("Parlaklik: ");
  Serial.print(parlaklik);
  Serial.print("\t Duty Cycle: %");
  Serial.print(dutyCycle, 1);
  Serial.print("\t Ort. Gerilim: ");
  Serial.print(ortalamaGerilim, 2);
  Serial.println(" V");
  
  delay(100);
}
```

#### Örnek Kod 2: Otomatik Breathing (Soluma Efekti)
```cpp
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Yavaşça parla
  for (int parlaklik = 0; parlaklik <= 255; parlaklik++) {
    analogWrite(ledPin, parlaklik);
    delay(5);
  }
  
  // Yavaşça sön
  for (int parlaklik = 255; parlaklik >= 0; parlaklik--) {
    analogWrite(ledPin, parlaklik);
    delay(5);
  }
}
```

#### Örnek Kod 3: RGB LED Karışım Kontrolü (Bonus)
```cpp
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
  // Kırmızı
  renkAyarla(255, 0, 0);
  delay(1000);
  
  // Sarı (Kırmızı + Yeşil)
  renkAyarla(255, 255, 0);
  delay(1000);
  
  // Mor (Kırmızı + Mavi)
  renkAyarla(255, 0, 255);
  delay(1000);
  
  // Beyaz
  renkAyarla(255, 255, 255);
  delay(1000);
}
```

#### Öğrenme Çıktıları
- PWM prensibi ve uygulaması
- analogWrite() fonksiyonu
- Duty cycle hesaplama
- RGB renk karışımı (bonus)

---

## HAFTA 7: LDR (Fotoresistör) ile Işık Algılama

### Teorik Kısım (1 saat)

#### LDR (Light Dependent Resistor) - Fotoresistör
- **Malzeme**: Kadmiyum Sülfür (CdS) veya Kadmiyum Selenyum (CdSe)
- **Çalışma prensibi**: Fotoelektrik etki, fotonlar elektron-delik çifti oluşturur
- **Direnç-Işık ilişkisi**:
  - Karanlık: 1MΩ - 10MΩ
  - Oda ışığı: 5kΩ - 10kΩ
  - Parlak ışık: 100Ω - 1kΩ
- **Gerilim bölücü devre**: LDR + Sabit direnç
- **Spektral yanıt**: 400-700 nm (görünür ışık)
- **Yanıt süresi**: 8-12 ms (yavaş, hızlı uygulamalar için uygun değil)
- **Avantajları**: Ucuz, basit kullanım
- **Dezavantajları**: Doğrusal olmayan yanıt, sıcaklığa duyarlı
- **Kullanım alanları**: Otomatik aydınlatma, güneş takip, kamera pozometri

#### Gerilim Bölücü Analizi
```
        Vcc (5V)
         |
        LDR (Rlight)
         |
         +----> Vout (A0'a)
         |
        R1 (10kΩ)
         |
        GND

Vout = Vcc × (R1 / (Rlight + R1))

Karanlıkta (Rlight = 1MΩ): Vout ≈ 0.05V → ADC ≈ 10
Oda ışığında (Rlight = 10kΩ): Vout ≈ 2.5V → ADC ≈ 512
Parlak ışıkta (Rlight = 500Ω): Vout ≈ 4.76V → ADC ≈ 975
```

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- LDR (fotoresistör)
- 10kΩ direnç (LDR için)
- LED
- 220Ω direnç (LED için)
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
5V → LDR → A0 → 10kΩ → GND
Pin 9 (PWM) → 220Ω → LED → GND
```

#### Örnek Kod 1: Basit Işık Ölçüm ve Kalibrasyon
```cpp
const int ldrPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("LDR Kalibrasyon - 10 saniye");
  
  int minDeger = 1023;
  int maxDeger = 0;
  
  unsigned long baslangic = millis();
  while (millis() - baslangic < 10000) {
    int okunan = analogRead(ldrPin);
    if (okunan > maxDeger) maxDeger = okunan;
    if (okunan < minDeger) minDeger = okunan;
    delay(10);
  }
  
  Serial.print("Min: ");
  Serial.print(minDeger);
  Serial.print(" - Max: ");
  Serial.println(maxDeger);
}

void loop() {
  int isik = analogRead(ldrPin);
  
  Serial.print("Isik Seviyesi: ");
  Serial.print(isik);
  
  if (isik < 300) Serial.println(" - Karanlik");
  else if (isik < 700) Serial.println(" - Normal");
  else Serial.println(" - Parlak");
  
  delay(500);
}
```

#### Örnek Kod 2: Otomatik Aydınlatma Sistemi (Akıllı Sokak Lambası)
```cpp
const int ldrPin = A0;
const int ledPin = 9;
const int esikDeger = 500;  // Kalibrasyon sonrası ayarlanmalı

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int isikSeviyesi = analogRead(ldrPin);
  
  Serial.print("Isik Seviyesi: ");
  Serial.print(isikSeviyesi);
  
  if (isikSeviyesi < esikDeger) {
    // Karanlık - LED'i parlat (ters orantılı)
    int parlaklik = map(isikSeviyesi, 0, esikDeger, 255, 0);
    analogWrite(ledPin, parlaklik);
    Serial.print("\t LED Parlaklik: ");
    Serial.println(parlaklik);
  } else {
    // Aydınlık - LED'i söndür
    analogWrite(ledPin, 0);
    Serial.println("\t LED: Kapali");
  }
  
  delay(200);
}
```

#### Öğrenme Çıktıları
- Fotoresistör çalışma prensibi
- Gerilim bölücü devre analizi
- Eşik değeri mantığı
- Otomatik kontrol sistemleri
- Kalibrasyon teknikleri

---

## HAFTA 8: Sıcaklık Sensörü (DHT11/LM35) ile Çevre Ölçümü

### Teorik Kısım (1 saat)

#### LM35 Analog Sıcaklık Sensörü
- **Çalışma prensibi**: Silikon tabanlı entegre devre, sıcaklığa bağlı gerilim üretir
- **Çıkış karakteristiği**: 10mV/°C (lineer)
- **Ölçüm aralığı**: -55°C ile +150°C
- **Doğruluk**: ±0.5°C (25°C'de)
- **Çalışma gerilimi**: 4V - 30V
- **Çıkış empedansı**: Düşük (doğrudan ADC'ye bağlanabilir)
- **Formül**: Sıcaklık (°C) = (Vout × 1000) / 10 = Vout × 100
- **Örnek**: 0.25V → 25°C, 0.50V → 50°C

#### DHT11 Dijital Sıcaklık ve Nem Sensörü
- **Sensör tipi**: Kapasitif nem sensörü + NTC termistör
- **Haberleşme**: Tek hat dijital protokol (1-Wire benzeri)
- **Sıcaklık aralığı**: 0°C - 50°C (±2°C doğruluk)
- **Nem aralığı**: 20% - 90% RH (±5% doğruluk)
- **Örnekleme hızı**: 1 Hz (saniyede 1 okuma)
- **Kütüphane**: DHT sensor library (Adafruit)

#### Termistör ve NTC Prensibi
- **NTC (Negative Temperature Coefficient)**: Sıcaklık arttıkça direnç azalır
- **Steinhart-Hart denklemi**: Sıcaklık-direnç ilişkisi

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu 1: LM35
**Gerekli Malzemeler:**
- Arduino Uno
- LM35 sıcaklık sensörü
- LED (kırmızı ve mavi)
- 2 adet 220Ω direnç
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
LM35 Pin 1 (Vcc) → 5V
LM35 Pin 2 (Vout) → A0
LM35 Pin 3 (GND) → GND

Pin 12 → 220Ω → LED Kırmızı → GND (Sıcak uyarısı)
Pin 13 → 220Ω → LED Mavi → GND (Soğuk uyarısı)
```

#### Örnek Kod 1: LM35 ile Sıcaklık Ölçümü
```cpp
const int lm35Pin = A0;
const int sicakLED = 12;
const int sogukLED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(sicakLED, OUTPUT);
  pinMode(sogukLED, OUTPUT);
}

void loop() {
  // ADC değerini oku
  int adcDeger = analogRead(lm35Pin);
  
  // Gerilime çevir
  float gerilim = adcDeger * (5.0 / 1023.0);
  
  // Sıcaklığa çevir (LM35: 10mV/°C)
  float sicaklik = gerilim * 100.0;
  
  // Seri monitöre yazdır
  Serial.print("ADC: ");
  Serial.print(adcDeger);
  Serial.print("\t Gerilim: ");
  Serial.print(gerilim, 3);
  Serial.print(" V\t Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.println(" C");
  
  // LED kontrolü
  if (sicaklik > 30) {
    digitalWrite(sicakLED, HIGH);
    digitalWrite(sogukLED, LOW);
  } else if (sicaklik < 20) {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, HIGH);
  } else {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, LOW);
  }
  
  delay(1000);
}
```

#### Devre Kurulumu 2: DHT11
**Gerekli Malzemeler:**
- Arduino Uno
- DHT11 sensörü (modül veya IC)
- 10kΩ pull-up direnci (modülde yoksa)
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
DHT11 VCC → 5V
DHT11 DATA → Pin 2 (10kΩ ile 5V'ye çekilir)
DHT11 GND → GND
```

#### Örnek Kod 2: DHT11 ile Sıcaklık ve Nem Ölçümü
```cpp
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sensoru Baslatildi");
}

void loop() {
  delay(2000);  // DHT11 minimum 2 saniye bekleme gerektirir
  
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();
  
  // Okuma hatası kontrolü
  if (isnan(nem) || isnan(sicaklik)) {
    Serial.println("DHT sensoru okunamadi!");
    return;
  }
  
  // Heat index (Hissedilen sıcaklık) hesapla
  float hissedilen = dht.computeHeatIndex(sicaklik, nem, false);
  
  Serial.print("Nem: ");
  Serial.print(nem);
  Serial.print(" %\t Sicaklik: ");
  Serial.print(sicaklik);
  Serial.print(" C\t Hissedilen: ");
  Serial.print(hissedilen);
  Serial.println(" C");
  
  // Konfor seviyesi analizi
  if (sicaklik >= 22 && sicaklik <= 26 && nem >= 40 && nem <= 60) {
    Serial.println(">>> KONFORLU");
  } else if (sicaklik > 30 || nem > 70) {
    Serial.println(">>> SICAK/NEMLI");
  } else {
    Serial.println(">>> SOĞUK/KURU");
  }
}
```

#### Öğrenme Çıktıları
- Analog ve dijital sensör farkları
- Kütüphane kullanımı
- Veri doğrulama (error handling)
- Fiziksel büyüklük ölçümü
- Heat index kavramı

---

## HAFTA 9: Ultrasonik Mesafe Sensörü (HC-SR04)

### Teorik Kısım (1 saat)

#### HC-SR04 Ultrasonik Sensör
- **Çalışma prensibi**: Sonar sistemi (ses dalgası yankı ölçümü)
- **Frekans**: 40 kHz (ultrasonik, insan kulağının duyamayacağı)
- **Ölçüm aralığı**: 2cm - 400cm
- **Doğruluk**: ±3mm
- **Açı**: 15° konik alan
- **Pinler**: VCC, TRIG (Tetik), ECHO (Yankı), GND

#### Mesafe Ölçüm Algoritması
1. TRIG pinine 10μs HIGH sinyali gönder (ultrasonik burst)
2. Sensör 8 adet 40kHz ses dalgası gönderir
3. ECHO pini HIGH olur ve yankı beklenir
4. Yankı geldiğinde ECHO pini LOW olur
5. ECHO'nun HIGH kalma süresi = Ses dalgasının gidiş-dönüş süresi

**Mesafe Formülü:**
```
Mesafe (cm) = (Süre (μs) × Ses Hızı) / 2
Ses Hızı = 0.0343 cm/μs (20°C'de)
Mesafe (cm) = (Süre × 0.0343) / 2 = Süre / 58.2
```

#### pulseIn() Fonksiyonu
- **Kullanımı**: `pulseIn(pin, value, timeout)`
- **Dönüş değeri**: Mikrosaniye cinsinden süre
- **Timeout**: Maksimum bekleme süresi (varsayılan 1 saniye)

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- HC-SR04 ultrasonik sensör
- 3 adet LED (Yeşil, Sarı, Kırmızı)
- 3 adet 220Ω direnç
- Buzzer (opsiyonel)
- Breadboard
- Jumper kablolar

**Tinkercad Devre Şeması:**
```
HC-SR04 VCC → 5V
HC-SR04 TRIG → Pin 9
HC-SR04 ECHO → Pin 10
HC-SR04 GND → GND

Pin 5 → 220Ω → LED Yeşil → GND (Uzak: >100cm)
Pin 6 → 220Ω → LED Sarı → GND (Orta: 50-100cm)
Pin 7 → 220Ω → LED Kırmızı → GND (Yakın: <50cm)
Pin 8 → Buzzer → GND
```

#### Örnek Kod 1: Temel Mesafe Ölçümü
```cpp
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

float mesafeOlc() {
  // TRIG pinine 10μs pulse gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // ECHO pininden süreyi oku
  long sure = pulseIn(echoPin, HIGH);
  
  // Mesafeyi hesapla
  float mesafe = sure / 58.2;
  
  return mesafe;
}

void loop() {
  float mesafe = mesafeOlc();
  
  if (mesafe >= 400 || mesafe <= 2) {
    Serial.println("Menzil dışı!");
  } else {
    Serial.print("Mesafe: ");
    Serial.print(mesafe);
    Serial.println(" cm");
  }
  
  delay(500);
}
```

#### Örnek Kod 2: Park Sensörü Sistemi
```cpp
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
}

float mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long sure = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  float mesafe = sure / 58.2;
  
  return mesafe;
}

void loop() {
  float mesafe = mesafeOlc();
  
  // Tüm LED'leri söndür
  digitalWrite(yesil, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(kirmizi, LOW);
  
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.print(" cm\t ");
  
  if (mesafe > 100) {
    digitalWrite(yesil, HIGH);
    Serial.println("GUVENLI");
    noTone(buzzer);
    
  } else if (mesafe > 50) {
    digitalWrite(sari, HIGH);
    Serial.println("DIKKAT");
    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    delay(500);
    return;
    
  } else if (mesafe > 20) {
    digitalWrite(kirmizi, HIGH);
    Serial.println("YAKIN");
    tone(buzzer, 2000);
    delay(200);
    noTone(buzzer);
    delay(200);
    return;
    
  } else {
    digitalWrite(kirmizi, HIGH);
    Serial.println("!!! COK YAKIN !!!");
    tone(buzzer, 3000);
    delay(100);
    noTone(buzzer);
    delay(100);
    return;
  }
  
  delay(100);
}
```

#### Öğrenme Çıktıları
- Ultrasonik sensör prensibi
- Pulse genişlik ölçümü
- Mikrosaniye zamanlama
- Çok seviyeli uyarı sistemi
- tone() ve noTone() fonksiyonları

---

## HAFTA 10: Servo Motor Kontrolü

### Teorik Kısım (1 saat)

#### Servo Motor Teknolojisi
- **Tanım**: Açı kontrolü yapılabilen motor (180° veya 360° sürekli dönüş)
- **İç yapı**: DC motor + Potansiyometre + Kontrol devresi
- **Kapalı döngü kontrol**: Geri besleme ile hedef açıya kilitlenme
- **PWM kontrol sinyali**:
  - Frekans: 50 Hz (20ms periyot)
  - Pulse genişliği: 1ms - 2ms
  - 1ms (5%) → 0°
  - 1.5ms (7.5%) → 90°
  - 2ms (10%) → 180°

#### SG90 Servo Motor Özellikleri
- **Açı aralığı**: 0° - 180°
- **Tork**: 1.8 kg·cm (4.8V'de)
- **Hız**: 0.1 s/60° (4.8V'de)
- **Çalışma gerilimi**: 4.8V - 6V
- **Akım**: Durağan ~10mA, Çalışma ~100-250mA, Bloke ~600mA
- **Pinler**: Kahverengi (GND), Kırmızı (VCC), Turuncu/Sarı (Sinyal)

#### Servo Kütüphanesi
- **#include <Servo.h>**: Arduino dahili kütüphane
- **attach(pin)**: Servo pini tanımlama
- **write(açı)**: 0-180 arası açı yazma
- **writeMicroseconds(μs)**: 1000-2000μs pulse genişliği
- **read()**: Mevcut açıyı okuma
- **detach()**: PWM sinyalini durdurma

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- SG90 Servo motor
- 10kΩ potansiyometre
- HC-SR04 ultrasonik sensör (opsiyonel)
- Breadboard
- Jumper kablolar
- **NOT**: Servo harici güç kaynağı kullanılabilir (1A+)

**Tinkercad Devre Şeması:**
```
Servo Kahverengi → GND
Servo Kırmızı → 5V (veya harici kaynak)
Servo Turuncu → Pin 9

Potansiyometre → A0 (orta pin)
Potansiyometre yan pinler → 5V ve GND
```

#### Örnek Kod 1: Manuel Açı Kontrolü
```cpp
#include <Servo.h>

Servo motor;
const int servoPin = 9;
const int potPin = A0;

void setup() {
  motor.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int potDeger = analogRead(potPin);
  int aci = map(potDeger, 0, 1023, 0, 180);
  
  motor.write(aci);
  
  Serial.print("Potansiyometre: ");
  Serial.print(potDeger);
  Serial.print("\t Aci: ");
  Serial.print(aci);
  Serial.println("°");
  
  delay(15);  // Servo stabilizasyon
}
```

#### Örnek Kod 2: Otomatik Tarama (Sweep)
```cpp
#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(9);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Sağa tarama...");
  for (int aci = 0; aci <= 180; aci++) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);
  
  Serial.println("Sola tarama...");
  for (int aci = 180; aci >= 0; aci--) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);
}
```

#### Örnek Kod 3: Radar Sistemi (Servo + Ultrasonik)
```cpp
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
  // 0° - 180° tarama
  for (int aci = 0; aci <= 180; aci += 5) {
    motor.write(aci);
    delay(100);  // Servo konumlanması + sensör stabilizasyon
    
    float mesafe = mesafeOlc();
    
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
  
  // 180° - 0° tarama
  for (int aci = 180; aci >= 0; aci -= 5) {
    motor.write(aci);
    delay(100);
    
    float mesafe = mesafeOlc();
    
    Serial.print(aci);
    Serial.print(",");
    Serial.println(mesafe);
  }
}
```

#### Öğrenme Çıktıları
- Servo motor çalışma prensibi
- PWM açı kontrolü
- Kütüphane kullanımı
- Sensör-aktüatör entegrasyonu
- Radar/tarama sistemleri

---

## HAFTA 11: DC Motor Kontrolü ve L298N Motor Sürücü

### Teorik Kısım (1 saat)

#### DC Motor Temelleri
- **Çalışma prensibi**: Fleming sol el kuralı, elektromanyetik indüksiyon
- **Fırçalı (Brushed) motor**: Komütatör + Karbon fırça
- **Fırçasız (Brushless) motor**: Elektronik komütasyon (ESC gerekli)
- **Tork**: T = K × I (Akıma orantılı)
- **Hız**: ω = K × V (Gerilime orantılı)
- **Back-EMF (Ters EMK)**: Motor dönerken oluşan ters gerilim
- **Stall current (Bloke akımı)**: Motor bloke olduğunda çekilen yüksek akım

#### L298N Motor Sürücü Modülü
- **H-Bridge** (H-Köprü) prensibi: 4 anahtarlama素子 ile iki yönlü kontrol
- **Çift kanallı**: 2 DC motor veya 1 step motor kontrolü
- **Maksimum akım**: 2A (sürekli), 3A (pik)
- **Çalışma gerilimi**: 5V - 35V
- **Mantık gerilimi**: 5V (Arduino ile uyumlu)
- **Pinler**:
  - **ENA, ENB**: PWM (hız kontrolü) - Enable pinleri
  - **IN1, IN2**: Motor A yön kontrolü
  - **IN3, IN4**: Motor B yön kontrolü
  - **12V**: Motor güç girişi
  - **GND**: Ortak toprak (Arduino GND ile birleştirilmeli!)
  - **5V**: Dahili regülatör çıkışı (jumper ile aktif)

#### Motor Yön Kontrolü Tablosu
```
Motor A:
IN1=HIGH, IN2=LOW  → İleri
IN1=LOW,  IN2=HIGH → Geri
IN1=LOW,  IN2=LOW  → Fren (kısa devre freni)
IN1=HIGH, IN2=HIGH → Fren

ENA = PWM (0-255) → Hız kontrolü
```

### Uygulama Kısmı (1 saat 30 dakika)

#### Devre Kurulumu
**Gerekli Malzemeler:**
- Arduino Uno
- L298N motor sürücü modülü
- 2 adet DC motor (6V)
- 12V güç kaynağı (veya 4x AA pil kutusu = 6V)
- Jumper kablolar
- **DİKKAT**: Arduino ve motor sürücü GND'leri birleştirilmeli!

**Tinkercad Devre Şeması:**
```
L298N 12V → Harici güç kaynağı (+)
L298N GND → Harici güç (-) + Arduino GND
L298N 5V Jumper → TAKILI (Arduino'dan besleme için)

Motor A:
L298N OUT1, OUT2 → Motor A terminalleri

Motor B:
L298N OUT3, OUT4 → Motor B terminalleri

Arduino Pin bağlantıları:
Pin 5 (PWM) → L298N ENA
Pin 6 → L298N IN1
Pin 7 → L298N IN2
Pin 10 (PWM) → L298N ENB
Pin 8 → L298N IN3
Pin 9 → L298N IN4
```

#### Örnek Kod 1: Tek Motor Kontrolü
```cpp
// Motor A pinleri
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
}

void motorIleri(int hiz) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, hiz);
}

void motorGeri(int hiz) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, hiz);
}

void motorDur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void loop() {
  Serial.println("İleri - Tam hız");
  motorIleri(255);
  delay(2000);
  
  Serial.println("İleri - Yarım hız");
  motorIleri(128);
  delay(2000);
  
  Serial.println("Dur");
  motorDur();
  delay(1000);
  
  Serial.println("Geri - Tam hız");
  motorGeri(255);
  delay(2000);
  
  Serial.println("Dur");
  motorDur();
  delay(2000);
}
```

#### Örnek Kod 2: Robot Araç Kontrolü (2 Motor)
```cpp
// Motor A (Sol)
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;

// Motor B (Sağ)
const int ENB = 10;
const int IN3 = 8;
const int IN4 = 9;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void ileri(int hiz) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void geri(int hiz) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void saga(int hiz) {
  // Sol motor ileri, sağ motor geri
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void sola(int hiz) {
  // Sol motor geri, sağ motor ileri
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
}

void dur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  Serial.println("İleri");
  ileri(200);
  delay(2000);
  
  Serial.println("Sağa dön");
  saga(150);
  delay(1000);
  
  Serial.println("İleri");
  ileri(200);
  delay(2000);
  
  Serial.println("Sola dön");
  sola(150);
  delay(1000);
  
  Serial.println("Geri");
  geri(200);
  delay(2000);
  
  Serial.println("Dur");
  dur();
  delay(3000);
}
```

#### Bonus: Engelden Kaçan Robot (Ultrasonik + Motor)
```cpp
const int trigPin = 11;
const int echoPin = 12;

// Motor pinleri (önceki kod ile aynı)
// ... motor fonksiyonları ...

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
  
  Serial.print("Mesafe: ");
  Serial.println(mesafe);
  
  if (mesafe > 30) {
    // Yol açık - İleri git
    ileri(180);
  } else if (mesafe > 15) {
    // Yaklaşıyor - Yavaşla
    ileri(100);
  } else {
    // Engel - Geri git ve dön
    dur();
    delay(200);
    geri(150);
    delay(500);
    saga(150);
    delay(700);
  }
  
  delay(50);
}
```

#### Öğrenme Çıktıları
- DC motor çalışma prensibi
- H-Bridge devre mantığı
- Yüksek akım kontrolü ve güvenlik
- İki motorlu robot kontrolü
- Sensör-aktüatör entegrasyonu

---

## HAFTA 12: Entegre Proje Planlama ve Tasarım

### Ders İçeriği (2 saat 30 dakika)

#### Bölüm 1: Proje Örnekleri ve Analiz (45 dakika)

**Örnek Proje 1: Akıllı Ev Otomasyonu**
- Sıcaklık kontrolü (DHT11)
- Işık sensörlü aydınlatma (LDR + LED)
- Kapı güvenlik sistemi (Ultrasonik + Buzzer)

**Örnek Proje 2: Otonom Engelden Kaçan Robot**
- Hareket sistemi (L298N + DC motorlar)
- Engel algılama (HC-SR04)
- Yön bulma algoritması

**Örnek Proje 3: Çevre İzleme İstasyonu**
- Sıcaklık ve nem ölçümü
- Işık seviyesi izleme
- Veri kaydı ve Serial Monitor görselleştirme

#### Bölüm 2: Öğrenci Proje Grupları Oluşturma (30 dakika)

**Gruplar (3-4 kişilik):**
- Her grup bir proje konusu seçer
- Roller belirlenir: Kodlama, devre kurulumu, test, dokümantasyon
- Proje hedefleri ve başarı kriterleri tanımlanır

#### Bölüm 3: Proje Geliştirme Metodolojisi (45 dakika)

**Aşama 1: Gereksinim Analizi**
- Problem tanımı
- Hangi sensörler gerekli?
- Hangi aktüatörler kullanılacak?
- Güç kaynağı ihtiyacı

**Aşama 2: Sistem Tasarımı**
- Blok diyagram çizimi
- Devre şeması (Tinkercad/Fritzing)
- Algoritma akış diyagramı
- Pin dağılımı tablosu

**Aşama 3: Prototipleme**
- Breadboard üzerinde test
- Modüler kod yapısı
- Her sensör/aktüatör ayrı test

**Aşama 4: Entegrasyon ve Test**
- Tüm bileşenleri birleştirme
- Hata ayıklama (debugging)
- Performans optimizasyonu

#### Bölüm 4: Pratik Uygulama - Mini Proje (30 dakika)

**Görev**: Işık ve Sıcaklık Kontrollü Sistem

**Gereksinimler:**
- LDR ile ışık ölçümü
- LM35 ile sıcaklık ölçümü
- 2 LED (kırmızı/mavi) sıcaklık göstergesi
- 1 LED (yeşil) ışık göstergesi
- Serial Monitor çıktısı

**Örnek Kod Yapısı:**
```cpp
// Pin tanımlamaları
const int ldrPin = A0;
const int lm35Pin = A1;
const int sicakLED = 12;
const int sogukLED = 13;
const int isikLED = 11;

// Global değişkenler
float sicaklik;
int isikSeviyesi;

void setup() {
  Serial.begin(9600);
  pinMode(sicakLED, OUTPUT);
  pinMode(sogukLED, OUTPUT);
  pinMode(isikLED, OUTPUT);
}

void sicaklikOku() {
  int adcDeger = analogRead(lm35Pin);
  float gerilim = adcDeger * (5.0 / 1023.0);
  sicaklik = gerilim * 100.0;
}

void isikOku() {
  isikSeviyesi = analogRead(ldrPin);
}

void sicaklikKontrol() {
  if (sicaklik > 28) {
    digitalWrite(sicakLED, HIGH);
    digitalWrite(sogukLED, LOW);
  } else if (sicaklik < 20) {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, HIGH);
  } else {
    digitalWrite(sicakLED, LOW);
    digitalWrite(sogukLED, LOW);
  }
}

void isikKontrol() {
  if (isikSeviyesi < 500) {
    digitalWrite(isikLED, HIGH);
  } else {
    digitalWrite(isikLED, LOW);
  }
}

void veriGoster() {
  Serial.print("Sicaklik: ");
  Serial.print(sicaklik, 1);
  Serial.print(" C\t Isik: ");
  Serial.println(isikSeviyesi);
}

void loop() {
  sicaklikOku();
  isikOku();
  sicaklikKontrol();
  isikKontrol();
  veriGoster();
  delay(1000);
}
```

#### Öğrenme Çıktıları
- Proje planlama ve yönetim
- Modüler programlama
- Sistem entegrasyonu
- Takım çalışması
- Dokümantasyon

---

## HAFTA 13: Proje Geliştirme ve Uygulama

### Ders İçeriği (2 saat 30 dakika)

#### Bölüm 1: Grup Çalışması - Proje Geliştirme (2 saat)

**Her Grup İçin Görevler:**

1. **Devre Kurulumu (30 dakika)**
   - Tinkercad'de simülasyon
   - Fiziksel breadboard kurulumu
   - Pin bağlantılarını kontrol

2. **Kod Geliştirme (45 dakika)**
   - Modüler fonksiyonlar yazma
   - Sensör okuma fonksiyonları
   - Kontrol algoritmaları
   - Hata ayıklama

3. **Test ve Optimizasyon (30 dakika)**
   - Her modülü ayrı test
   - Entegre sistem testi
   - Performans ölçümü
   - Hata senaryoları

4. **Dokümantasyon (15 dakika)**
   - Devre şeması kaydetme
   - Kod yorumları ekleme
   - Kullanılan malzeme listesi
   - Test sonuçları

#### Bölüm 2: Teknik Destek ve Troubleshooting (30 dakika)

**Sık Karşılaşılan Problemler ve Çözümleri:**

**Problem 1: Sensör Yanlış Değer Okuyor**
- Bağlantıları kontrol et
- Pull-up/pull-down dirençleri ekle
- Güç kaynağını kontrol et
- Serial Monitor ile debug yap

**Problem 2: Motor Çalışmıyor**
- Güç kaynağı yeterli mi? (min 1A)
- GND ortak mı?
- L298N jumper'ları doğru mu?
- Enable pinleri HIGH mı?

**Problem 3: Arduino Kitlendi (Freeze)**
- delay() çok uzun mu?
- Sonsuz döngü var mı?
- Akım aşırı çekilmiş olabilir
- Reset butonu ile yeniden başlat

**Problem 4: Kod Yükleme Hatası**
- Port seçimi doğru mu?
- USB kablosu data destekliyor mu?
- Pin 0 ve 1 kullanımda mı?
- Başka program portı kullanıyor mu?

**Debugging Teknikleri:**
```cpp
// 1. Serial Print ile debug
Serial.println("Buraya geldi mi?");

// 2. Değişken kontrolü
Serial.print("deger = ");
Serial.println(deger);

// 3. Koşul kontrolü
if (koşul) {
  Serial.println("Kosul DOGRU");
} else {
  Serial.println("Kosul YANLIS");
}

// 4. Adım adım test
void loop() {
  // Her satırı yoruma al ve teker teker aç
  // fonksiyon1();
  // fonksiyon2();
  fonksiyon3();  // Sadece bunu test et
}
```

#### Öğrenme Çıktıları
- Pratik proje geliştirme deneyimi
- Problem çözme becerileri
- Debugging ve test metodolojileri
- Takım içi işbirliği

---

## HAFTA 14: Proje Sunumları ve Değerlendirme

### Ders İçeriği (2 saat 30 dakika)

#### Bölüm 1: Proje Sunumları (2 saat)

**Her Grup İçin Sunum Formatı (15 dakika/grup):**

1. **Proje Tanıtımı (3 dakika)**
   - Proje adı ve amacı
   - Çözdüğü problem
   - Kullanım senaryosu

2. **Teknik Detaylar (4 dakika)**
   - Kullanılan donanım (sensörler, aktüatörler, modüller)
   - Devre şeması gösterimi (Tinkercad/Fritzing)
   - Algoritma akış diyagramı
   - Pin konfigürasyonu

3. **Canlı Demo (5 dakika)**
   - Fiziksel prototip gösterimi
   - Farklı senaryolarda test
   - Serial Monitor çıktıları
   - Video kaydı (opsiyonel)

4. **Karşılaşılan Zorluklar ve Çözümler (2 dakika)**
   - Teknik problemler
   - Nasıl çözüldü?
   - Öğrenilen dersler

5. **Soru-Cevap (1 dakika)**

**Değerlendirme Kriterleri:**
- İşlevsellik (30%): Proje çalışıyor mu?
- Teknik karmaşıklık (20%): Kaç farklı sensör/aktüatör entegre edilmiş?
- Kod kalitesi (20%): Modüler, yorumlu, okunabilir kod
- Sunum (15%): Açık ve anlaşılır anlatım
- Yaratıcılık (10%): Orijinal fikir ve uygulama
- Dokümantasyon (5%): Şema, kod yorumları, test sonuçları

#### Bölüm 2: Genel Değerlendirme ve Gelecek Adımlar (30 dakika)

**14 Haftalık Özet:**
- Hafta 1: Teorik temel (robotik, Arduino, elektronik)
- Hafta 2-3: Dijital I/O (LED, buton)
- Hafta 4-6: Analog I/O (potansiyometre, PWM)
- Hafta 7-9: Sensörler (LDR, sıcaklık, ultrasonik)
- Hafta 10-11: Aktüatörler (servo, DC motor)
- Hafta 12-14: Proje geliştirme

**Gelecek Öğrenim Yolları:**

**1. İleri Seviye Arduino:**
- Interrupt (kesme) sistemleri
- Timer/Counter programlama
- EEPROM veri saklama
- Watchdog timer
- Sleep modları (güç tasarrufu)

**2. Haberleşme Protokolleri:**
- I2C (OLED ekran, RTC modülü)
- SPI (SD kart, RF modüller)
- UART (Bluetooth HC-05, GPS)
- OneWire (DS18B20 sıcaklık sensörü)

**3. Kablosuz İletişim:**
- Bluetooth (HC-05/HC-06)
- WiFi (ESP8266, ESP32)
- RF 433MHz modüller
- NRF24L01 transceiver
- LoRa (uzun menzil)

**4. İleri Sensörler:**
- IMU (MPU6050): İvme + jiroskop
- Ultrasonik dizi (engel haritası)
- Kamera modüller (görüntü işleme)
- GPS (konum takibi)
- Gaz sensörleri (MQ serisi)

**5. Robot Platformları:**
- 2 tekerlekli dengeli robot (balancing)
- 4 tekerlekli araç (differential drive)
- Robot kol (3-6 servo eksen)
- Drone (quadcopter temel)
- Çizgi izleyen robot (line follower)

**6. Gelişmiş Programlama:**
- PID kontrol algoritması
- State machine (durum makinesi)
- Dijital filtreler (Kalman, low-pass)
- RTOS (Real-Time Operating System)
- Object-oriented programlama

**7. PCB Tasarımı:**
- Eagle/KiCad ile şematik çizimi
- PCB layout tasarımı
- Üretim için Gerber dosyaları
- SMD lehimleme

**8. Alternatif Platformlar:**
- Raspberry Pi (Linux tabanlı)
- ESP32 (WiFi + Bluetooth)
- STM32 (ARM Cortex-M)
- Teensy (yüksek performans)
- PIC mikrodenetleyiciler

#### Kaynaklar ve Topluluklar:

**Online Platformlar:**
- Arduino Project Hub (project ideas)
- Instructables (DIY tutorials)
- Hackster.io (maker projects)
- GitHub (open source kod)

**Türkçe Kaynaklar:**
- Arduino.cc Türkçe forum
- Robotistan blog
- Direnc.net dökümanlar
- YouTube Arduino Türkiye kanalları

**Yarışmalar:**
- Teknofest Robotik Kategorileri
- Line Follower Yarışmaları
- Sumo Robot Yarışmaları
- Drone Yarışmaları

**Önerilen Kitaplar:**
- "Arduino Cookbook" - Michael Margolis
- "Programming Arduino" - Simon Monk
- "Make: Electronics" - Charles Platt

#### Sertifika ve Başarı Belgesi

**Başarı Kriterleri:**
- Tüm haftalara %80+ katılım
- Proje tamamlanmış ve çalışıyor
- Final sunumu yapılmış
- Kod ve dokümantasyon teslim edilmiş

**Sertifika İçeriği:**
- "Arduino ile Robotik Kodlama" 14 haftalık eğitim tamamlanmıştır
- Öğrenilen konular listesi
- Tamamlanan proje açıklaması

---

## EK BÖLÜM: Faydalı Kod Şablonları

### 1. Genel Proje Şablonu
```cpp
/*
 * Proje Adı: [Buraya proje adını yaz]
 * Yazar: [İsim]
 * Tarih: [TT/AA/YYYY]
 * Açıklama: [Projenin ne yaptığını kısaca açıkla]
 * 
 * Kullanılan Donanım:
 * - Arduino Uno
 * - [Sensör/Aktüatör listesi]
 */

// Kütüphaneler
#include <Servo.h>
// #include <DHT.h>

// Pin tanımlamaları
const int pinAdi = 2;

// Global değişkenler
int deger = 0;

// Nesne oluşturma
// Servo motor;

void setup() {
  Serial.begin(9600);
  pinMode(pinAdi, OUTPUT);
  
  // Başlangıç mesajı
  Serial.println("Program baslatildi");
}

void loop() {
  // Ana döngü
  
  delay(100);
}

// Yardımcı fonksiyonlar
```

### 2. Buton Debounce Şablonu
```cpp
const int butonPin = 2;
int sonDurum = LOW;
int mevcutDurum = LOW;
unsigned long sonDebounceZaman = 0;
const unsigned long debounceGecikme = 50;

void setup() {
  pinMode(butonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int okunan = digitalRead(butonPin);
  
  if (okunan != sonDurum) {
    sonDebounceZaman = millis();
  }
  
  if ((millis() - sonDebounceZaman) > debounceGecikme) {
    if (okunan != mevcutDurum) {
      mevcutDurum = okunan;
      
      if (mevcutDurum == HIGH) {
        Serial.println("Buton basildi");
        // Buraya basma eventi kodu
      }
    }
  }
  
  sonDurum = okunan;
}
```

### 3. Non-Blocking Delay Şablonu
```cpp
// delay() kullanmadan zamanlama
unsigned long oncekiZaman = 0;
const long aralik = 1000;  // 1 saniye

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long simdikiZaman = millis();
  
  if (simdikiZaman - oncekiZaman >= aralik) {
    oncekiZaman = simdikiZaman;
    
    // Her 1 saniyede bir yapılacak işlem
    Serial.println("1 saniye geçti");
  }
  
  // Burada başka kodlar çalışabilir (non-blocking)
}
```

### 4. Ortalama Filtreleme Şablonu
```cpp
const int ornekSayisi = 10;
int ornekler[ornekSayisi];
int ornekIndex = 0;
int toplam = 0;
int ortalama = 0;

void setup() {
  Serial.begin(9600);
  // Diziyi sıfırla
  for (int i = 0; i < ornekSayisi; i++) {
    ornekler[i] = 0;
  }
}

void loop() {
  // Eski değeri çıkar
  toplam = toplam - ornekler[ornekIndex];
  
  // Yeni değer oku
  ornekler[ornekIndex] = analogRead(A0);
  
  // Yeni değeri ekle
  toplam = toplam + ornekler[ornekIndex];
  
  // İndeksi ilerlet
  ornekIndex = (ornekIndex + 1) % ornekSayisi;
  
  // Ortalamayı hesapla
  ortalama = toplam / ornekSayisi;
  
  Serial.println(ortalama);
  delay(10);
}
```

---

## Sonuç

Bu 14 haftalık Arduino ile Robotik Kodlama dersi, öğrencilere:
- Elektronik ve robotik temellerini öğretmiştir
- Pratik devre kurma ve problem çözme becerileri kazandırmıştır
- Programlama mantığını sensör-aktüatör kontrolü ile pekiştirmiştir
- Gerçek dünya projelerinde ekip çalışması deneyimi sağlamıştır

Öğrenciler artık:
- Kendi Arduino projelerini baştan sona geliştirebilirler
- Sensör verilerini okuyup yorumlayabilirler
- Motorları ve aktüatörleri kontrol edebilirler
- Basit otomasyon sistemleri tasarlayabilirler

**Başarılar dileriz!**

---

**Not:** Bu doküman Tinkercad, Arduino IDE ve fiziksel donanım kullanımını içermektedir. Her hafta için simülasyon ve gerçek devre kurulumu yapılması önerilir.