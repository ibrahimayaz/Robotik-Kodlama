# HAFTA 1: Robotik Kodlama ve Arduino'ya Giriş (Teorik)

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Ders Tipi:** Teorik
- **Seviye:** Önlisans

---

## 1. Robotik ve Otomasyon Sistemleri (35 dakika)

### 1.1 Robotik Biliminin Tanımı
- Robotik, mekanik, elektronik ve bilgisayar bilimlerinin kesişim noktasında yer alan disiplinler arası bir bilim dalıdır.
- **Robot** kelimesi, Çekçe "robota" (zorunlu iş) kelimesinden türemiştir.
- 1920 yılında Karel Čapek'in "R.U.R." oyununda ilk kez kullanılmıştır.

### 1.2 Robot Türleri
| Tür | Özellikler | Kullanım Alanı |
|-----|-----------|----------------|
| Endüstriyel Robotlar | Yüksek hassasiyet, tekrarlı iş | Üretim hatları, kaynak |
| Servis Robotları | İnsan etkileşimi | Sağlık, temizlik, eğlence |
| Mobil Robotlar | Hareket kabiliyeti | Keşif, lojistik |
| Otonom Robotlar | Kendi kararlarını verir | Otonom araçlar, drone |

### 1.3 Otomasyon Sistemlerinin Temel Bileşenleri
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   SENSÖR    │───▶│   İŞLEMCİ   │───▶│  AKTÜATÖR   │
│  (Algılama) │    │   (Karar)   │    │  (Eylem)    │
└─────────────┘    └─────────────┘    └─────────────┘
       ▲                                      │
       │              GERİ BESLEme            │
       └──────────────────────────────────────┘
```

### 1.4 Geri Besleme (Feedback) Kavramı
- **Açık Döngü Sistem:** Çıkış kontrolü yok (örn: fırın zamanlayıcısı)
- **Kapalı Döngü Sistem:** Çıkış sürekli izlenir ve ayarlanır (örn: klima termostatı)

### 1.5 Robotik Kullanım Alanları
- ✅ Üretim ve Montaj
- ✅ Tıp ve Cerrahi
- ✅ Savunma ve Güvenlik
- ✅ Eğitim ve Araştırma
- ✅ Ev Otomasyonu
- ✅ Tarım ve Hayvancılık

---

## 2. Mikroişlemci ve Mikrodenetleyici Teknolojisi (40 dakika)

### 2.1 Mikroişlemci vs Mikrodenetleyici
**Mikroişlemci**, yalnızca CPU (Merkezi İşlem Birimi) içeren bir entegre devredir. Bellek (RAM/ROM), giriş-çıkış birimleri ve diğer çevre bileşenleri harici olarak bağlanır.
**Mikrodenetleyici**; CPU + RAM + ROM + giriş/çıkış portları + zamanlayıcılar gibi birimleri tek çip üzerinde barındıran entegre devredir.

Kısaca mikroişlemci; Güçlü beyin (ama organları dışarıda), mikrodenetleyici ise Küçük ama kendi içinde tam sistemdir.

| Özellik | Mikroişlemci | Mikrodenetleyici |
|---------|--------------|------------------|
| Bellek | Harici | Dahili (Flash, RAM) |
| I/O Pinleri | Harici çip gerekir | Dahili |
| Maliyet | Yüksek | Düşük |
| Güç Tüketimi | Yüksek | Düşük |
| Kullanım | PC, Sunucu | Gömülü sistemler |
| Örnek | Intel i7, AMD Ryzen | ATmega328P, STM32 |

### 2.2 Arduino Platformu
- **2005** yılında İtalya'da geliştirildi
- **Açık kaynak** donanım ve yazılım
- Eğitim ve prototipleme odaklı
- Geniş topluluk desteği

### 2.3 Arduino Uno Donanım Mimarisi

["Arduino"](https://cdn-blog.adafruit.com/uploads/2012/05/ArduinoUno_R3_Pinouts_600.png)


### 2.4 ATmega328P Teknik Özellikleri
- **Flash Bellek:** 32 KB (program depolama)
- **SRAM:** 2 KB (çalışma belleği)
- **EEPROM:** 1 KB (kalıcı veri)
- **Clock Frekansı:** 16 MHz
- **Çalışma Gerilimi:** 5V
- **Dijital I/O Pinleri:** 14 (6 tanesi PWM)
- **Analog Giriş Pinleri:** 6

### 2.5 Arduino Çeşitleri Karşılaştırma

| Model | İşlemci | Flash | Dijital Pin | Analog Pin | Özellik |
|-------|---------|-------|-------------|------------|---------|
| Uno | ATmega328P | 32KB | 14 | 6 | Başlangıç için ideal |
| Nano | ATmega328P | 32KB | 14 | 8 | Küçük boyut |
| Mega | ATmega2560 | 256KB | 54 | 16 | Büyük projeler |
| Due | SAM3X8E | 512KB | 54 | 12 | 32-bit ARM |

### 2.6 GPIO (General Purpose Input/Output)
- Her pin giriş veya çıkış olarak yapılandırılabilir
- **OUTPUT:** LED, motor, röle kontrolü
- **INPUT:** Buton, sensör okuma
- **INPUT_PULLUP:** Dahili pull-up direnç ile giriş

---

## 3. Elektronik ve Devre Temelleri (50 dakika)

### 3.1 Temel Elektrik Büyüklükleri

#### Akım (I) - Ampere (A)
- Elektrik yüklerinin hareketi
- **DC (Direct Current):** Tek yönlü akım
- **AC (Alternating Current):** Değişken yönlü akım
- Arduino DC ile çalışır

#### Gerilim (V) - Volt (V)
- İki nokta arasındaki potansiyel fark
- Elektrik akışının "itici gücü"
- Arduino: 5V mantık seviyesi

#### Direnç (R) - Ohm (Ω)
- Akıma karşı gösterilen zorluk
- Isıya dönüşen enerji

### 3.2 Ohm Kanunu

```
        V = I × R
        
    ┌───────────┐
    │     V     │    V: Gerilim (Volt)
    │   ─────   │    I: Akım (Amper)
    │   I × R   │    R: Direnç (Ohm)
    └───────────┘
```

**Örnek Hesaplamalar:**
- 5V gerilim, 220Ω direnç → I = 5/220 = 0.023A = 23mA
- 5V gerilim, 20mA akım → R = 5/0.02 = 250Ω

### 3.3 Seri ve Paralel Bağlantı

**Seri Bağlantı:**
```
    ─── [R1] ─── [R2] ─── [R3] ───
    
    R_toplam = R1 + R2 + R3
    Akım her yerde aynı
```

**Paralel Bağlantı:**
```
       ┌─── [R1] ───┐
    ───┼─── [R2] ───┼───
       └─── [R3] ───┘
    
    1/R_toplam = 1/R1 + 1/R2 + 1/R3
    Gerilim her yerde aynı
```

### 3.4 Direnç Renk Kodları (4 Bantlı)

| Renk | Değer | Çarpan |
|------|-------|--------|
| Siyah | 0 | ×1 |
| Kahverengi | 1 | ×10 |
| Kırmızı | 2 | ×100 |
| Turuncu | 3 | ×1K |
| Sarı | 4 | ×10K |
| Yeşil | 5 | ×100K |
| Mavi | 6 | ×1M |
| Mor | 7 | - |
| Gri | 8 | - |
| Beyaz | 9 | - |

**Örnek: Kırmızı-Kırmızı-Kahverengi-Altın = 220Ω ±5%**

### 3.5 Breadboard Yapısı

```
    ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  (+) Güç rayı
    ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  (-) GND rayı
    
    a b c d e     f g h i j
    ○ ○ ○ ○ ○     ○ ○ ○ ○ ○  1
    ○ ○ ○ ○ ○     ○ ○ ○ ○ ○  2
    ○ ○ ○ ○ ○     ○ ○ ○ ○ ○  3
    ...          ...
    
    Aynı satırdaki a-e ve f-j delikleri birbirine bağlıdır
```

### 3.6 Elektronik Bileşenler

**Pasif Elemanlar:**
- **Direnç:** Akımı sınırlar
- **Kondansatör:** Enerji depolar, filtreleme
- **Bobin:** Manyetik alan oluşturur

**Aktif Elemanlar:**
- **LED:** Işık yayan diyot
- **Transistör:** Elektronik anahtar/amplifikatör
- **Diyot:** Tek yönlü akım geçişi
- **IC:** Entegre devre

### 3.7 Dijital ve Analog Sinyaller

**Dijital Sinyal:**
```
    5V ─┐     ┌───┐     ┌───  HIGH (1)
        │     │   │     │
    0V ─┴─────┴───┴─────┴───  LOW (0)
```

**Analog Sinyal:**
```
    5V ─      ╱╲      ╱╲
        ╲    ╱  ╲    ╱  ╲    Sürekli değişen
    0V ─ ╲╱╲╱    ╲╱╲╱    ╲   (0V - 5V arası)
```

---

## 4. Arduino Programlama Temelleri (20 dakika)

### 4.1 Arduino IDE Kurulumu
1. [arduino.cc](https://www.arduino.cc/en/software) adresinden indir
2. Kurulumu tamamla
3. USB sürücülerini yükle
4. Board ve Port seçimi yap

### 4.2 Temel Kod Yapısı

```cpp
// Kütüphaneler (gerekirse)
#include <Servo.h>

// Sabitler
const int LED_PIN = 13;

// Global değişkenler
int sayac = 0;

void setup() {
  // Başlangıç ayarları - sadece 1 kez çalışır
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Ana program - sürekli tekrar eder
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
```

### 4.3 Veri Tipleri

| Tip | Boyut | Aralık | Kullanım |
|-----|-------|--------|----------|
| `boolean` | 1 bit | true/false | Mantıksal |
| `byte` | 8 bit | 0-255 | Küçük pozitif sayılar |
| `int` | 16 bit | -32768 to 32767 | Tam sayılar |
| `unsigned int` | 16 bit | 0-65535 | Pozitif tam sayılar |
| `long` | 32 bit | ±2 milyar | Büyük sayılar |
| `float` | 32 bit | ±3.4×10³⁸ | Ondalıklı sayılar |
| `char` | 8 bit | -128 to 127 | Karakterler |

### 4.4 Operatörler

**Aritmetik:** `+` `-` `*` `/` `%`
**Karşılaştırma:** `==` `!=` `<` `>` `<=` `>=`
**Mantıksal:** `&&` (VE) `||` (VEYA) `!` (DEĞİL)
**Atama:** `=` `+=` `-=` `*=` `/=`

### 4.5 Yorum Satırları

```cpp
// Bu tek satırlık yorum

/* Bu
   çok satırlı
   yorum */
```

---

## 5. Simülasyon Araçları (5 dakika)

### 5.1 Tinkercad Circuits
- **URL:** [tinkercad.com](https://www.tinkercad.com)
- Ücretsiz, web tabanlı
- Arduino simülasyonu
- Sanal breadboard ve bileşenler
- Kod yazma ve çalıştırma

### 5.2 Diğer Araçlar
- **Wokwi:** Gelişmiş Arduino simülatörü
- **Proteus:** Profesyonel PCB ve simülasyon
- **Fritzing:** Devre şeması ve PCB tasarımı

---

## 📝 Hafta 1 Kontrol Listesi

- [ ] Robotik temel kavramları anlaşıldı
- [ ] Mikrodenetleyici ve mikroişlemci farkı öğrenildi
- [ ] Arduino donanım yapısı tanındı
- [ ] Temel elektrik büyüklükleri kavrandı
- [ ] Ohm kanunu uygulamaları yapıldı
- [ ] Breadboard kullanımı öğrenildi
- [ ] Arduino IDE kuruldu
- [ ] Temel kod yapısı anlaşıldı
- [ ] Tinkercad hesabı oluşturuldu

---

## 🔗 Faydalı Kaynaklar

- [Arduino Resmi Dokümantasyon](https://docs.arduino.cc/)
- [Tinkercad Circuits](https://www.tinkercad.com/circuits)
- [Arduino Referans](https://www.arduino.cc/reference/en/)

---

**Sonraki Hafta:** Dijital Çıkış - LED Kontrolü (Pratik Uygulama)
