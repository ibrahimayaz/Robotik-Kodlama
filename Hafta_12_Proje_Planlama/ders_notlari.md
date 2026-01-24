# HAFTA 12: Proje Planlama ve Tasarım

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** Proje planlama, tasarım, takım çalışması

---

## TEORİK KISIM (1 Saat)

### 1. Proje Seçimi

#### 1.1 Proje Önerileri
| Proje | Zorluk | Gerekli Malzeme |
|-------|--------|-----------------|
| Akıllı Çöp Kutusu | ⭐⭐ | Ultrasonik, Servo |
| Park Sensörü | ⭐⭐ | Ultrasonik, LED, Buzzer |
| Sıcaklık Göstergesi | ⭐⭐ | LM35/DHT11, LED Dizisi |
| Işık Takip Eden Robot | ⭐⭐⭐ | LDR, DC Motor, L298N |
| Engelden Kaçan Robot | ⭐⭐⭐ | Ultrasonik, Servo, DC Motor |
| Uzaktan Kumandalı Araba | ⭐⭐⭐ | DC Motor, L298N, IR Sensör |
| Mini Sera Sistemi | ⭐⭐⭐⭐ | DHT11, LDR, Servo, Pompa |
| Güvenlik Sistemi | ⭐⭐⭐⭐ | PIR, Buzzer, LED, Keypad |

#### 1.2 Proje Seçim Kriterleri
- ✅ Mevcut malzemelere uygunluk
- ✅ Öğrenilen konuları kapsama
- ✅ Tamamlanabilir zorluk seviyesi
- ✅ Yaratıcılık ve özgünlük
- ✅ Gerçek dünya uygulaması

### 2. Proje Planlama Süreci

#### 2.1 Proje Aşamaları
```
    1. Fikir Belirleme
           │
           ▼
    2. Gereksinim Analizi
           │
           ▼
    3. Tasarım (Devre + Kod)
           │
           ▼
    4. Prototip Oluşturma
           │
           ▼
    5. Test ve Hata Ayıklama
           │
           ▼
    6. İyileştirme
           │
           ▼
    7. Dokümantasyon
           │
           ▼
    8. Sunum
```

#### 2.2 Zaman Planlaması
| Hafta | Aktivite |
|-------|----------|
| 12 | Proje seçimi, tasarım |
| 13 | Geliştirme, test |
| 14 | Sunum, değerlendirme |

### 3. Dokümantasyon

#### 3.1 Proje Raporu Yapısı
```markdown
# PROJE ADI

## 1. Proje Tanımı
- Amaç
- Kapsam
- Hedef kitle

## 2. Malzeme Listesi
| Malzeme | Adet | Açıklama |

## 3. Devre Şeması
- Fritzing veya elle çizim

## 4. Akış Diyagramı
- Algoritma mantığı

## 5. Kaynak Kod
- Açıklamalı kod

## 6. Test Sonuçları
- Başarılar
- Karşılaşılan sorunlar

## 7. Geliştirme Önerileri
- Gelecek eklemeler
```

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Aktivite 1: Proje Beyin Fırtınası (30 dk)

#### Grup Çalışması
1. 3-4 kişilik gruplar oluşturun
2. Her grup 3 proje fikri üretsin
3. Fikirleri sınıfla paylaşın
4. En uygun projeyi seçin

#### Beyin Fırtınası Soruları
- Günlük hayatta hangi problemi çözmek istersiniz?
- Hangi sensör kombinasyonları ilginç olabilir?
- Mevcut malzemelerle neler yapılabilir?

### Aktivite 2: Proje Tasarım Belgesi (45 dk)

#### Şablon
```
┌────────────────────────────────────────────┐
│           PROJE TASARIM BELGESİ            │
├────────────────────────────────────────────┤
│ Proje Adı: ____________________________    │
│                                            │
│ Takım Üyeleri:                             │
│ 1. ____________________                    │
│ 2. ____________________                    │
│ 3. ____________________                    │
│                                            │
│ Proje Amacı:                               │
│ __________________________________________ │
│ __________________________________________ │
│                                            │
│ Kullanılacak Sensörler:                    │
│ □ LDR        □ HC-SR04    □ LM35           │
│ □ DHT11      □ Buton      □ Pot            │
│                                            │
│ Kullanılacak Aktüatörler:                  │
│ □ LED        □ Servo      □ DC Motor       │
│ □ Buzzer     □ LCD        □ Diğer:____     │
│                                            │
│ Blok Diyagram:                             │
│ ┌─────────┐    ┌─────────┐    ┌─────────┐  │
│ │ Giriş   │───►│ İşlem   │───►│ Çıkış   │  │
│ │(Sensör) │    │(Arduino)│    │(Aktüatör)│ │
│ └─────────┘    └─────────┘    └─────────┘  │
│                                            │
│ Görev Dağılımı:                            │
│ - Devre: ____________________              │
│ - Kod:   ____________________              │
│ - Test:  ____________________              │
│ - Rapor: ____________________              │
│                                            │
└────────────────────────────────────────────┘
```

### Aktivite 3: Basit Akış Diyagramı (15 dk)

#### Örnek: Park Sensörü Akış Diyagramı
```
        ┌─────────┐
        │ BAŞLA   │
        └────┬────┘
             │
             ▼
    ┌────────────────┐
    │ Mesafe ölç     │
    └───────┬────────┘
             │
             ▼
       ┌───────────┐
       │ Mesafe    │
       │ < 20cm?   │
       └─────┬─────┘
             │
      Evet   │   Hayır
        ┌────┴────┐
        ▼         ▼
   ┌────────┐ ┌────────┐
   │Kırmızı │ │Mesafe  │
   │LED Yak │ │< 50cm? │
   │Alarm   │ └───┬────┘
   └───┬────┘     │
       │    Evet  │  Hayır
       │   ┌──────┴──────┐
       │   ▼             ▼
       │ ┌────────┐ ┌────────┐
       │ │Sarı LED│ │Yeşil   │
       │ │Yak     │ │LED Yak │
       │ └───┬────┘ └───┬────┘
       │     │          │
       └─────┴────┬─────┘
                  │
                  ▼
           ┌────────────┐
           │ 100ms bekle│
           └──────┬─────┘
                  │
                  └──────► (Döngü başına)
```

---

## 📋 Örnek Proje Detayları

### Proje 1: Akıllı Çöp Kutusu

#### Genel Bakış
Eli yaklaştığında otomatik açılan çöp kutusu kapağı

#### Malzeme Listesi
- Arduino Uno
- HC-SR04 Ultrasonik Sensör
- SG90 Servo Motor
- Jumper kablolar

#### Temel Algoritma
```cpp
// Sözde Kod (Pseudocode)
void loop() {
  mesafe = ultrasonik_ölç();
  
  if (mesafe < 20cm) {
    kapak_aç();
    3_saniye_bekle();
    kapak_kapat();
  }
}
```

### Proje 2: Engelden Kaçan Robot

#### Genel Bakış
Önündeki engeli algılayıp yön değiştiren robot

#### Malzeme Listesi
- Arduino Uno
- HC-SR04 Ultrasonik
- L298N Motor Sürücü
- 2x DC Motor
- Robot şasi

#### Temel Algoritma
```cpp
// Sözde Kod
void loop() {
  mesafe = ultrasonik_ölç();
  
  if (mesafe > 30cm) {
    ileri_git();
  } else {
    dur();
    sola_bak();
    saga_bak();
    
    if (sol_mesafe > sag_mesafe) {
      sola_don();
    } else {
      saga_don();
    }
  }
}
```

### Proje 3: Mini Sera Sistemi

#### Genel Bakış
Sıcaklık ve ışık kontrollü sera otomasyonu

#### Malzeme Listesi
- Arduino Uno
- DHT11 (sıcaklık/nem)
- LDR (ışık)
- Servo (havalandırma)
- LED (aydınlatma)

#### Temel Algoritma
```cpp
// Sözde Kod
void loop() {
  sicaklik = dht_ölç();
  isik = ldr_ölç();
  
  if (sicaklik > 28) {
    havalandirma_ac();
  } else {
    havalandirma_kapat();
  }
  
  if (isik < eşik) {
    led_yak();
  } else {
    led_sondur();
  }
}
```

---

## 📝 Hafta 12 Görevleri

### Ders İçi
- [ ] Grup oluştur
- [ ] Proje seç
- [ ] Tasarım belgesi doldur
- [ ] Akış diyagramı çiz

### Hafta Sonu (Ev Ödevi)
- [ ] Malzeme listesi tamamla
- [ ] Devre şeması çiz
- [ ] Kod taslağı oluştur
- [ ] GitHub deposu aç (opsiyonel)

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Proje planlama sürecini uygulayabilir
- ✅ Takım çalışması yapabilir
- ✅ Teknik tasarım belgesi oluşturabilir
- ✅ Akış diyagramı çizebilir
- ✅ Görev dağılımı yapabilir

---

**Sonraki Hafta:** Proje Geliştirme ve Test
