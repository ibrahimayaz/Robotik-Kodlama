# HAFTA 4: Dijital Giriş - Buton Kontrolü

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** Push button, pull-up/pull-down, debouncing

---

## TEORİK KISIM (1 Saat)

### 1. Push Button (Takt Buton)

#### 1.1 Buton Nedir?
- Elektrik devrelerinde anahtar görevi görür
- Basıldığında devreyi açar/kapatır
- Bırakıldığında eski konumuna döner

#### 1.2 Buton Türleri
| Tür | Açıklama |
|-----|----------|
| **NO (Normally Open)** | Varsayılan açık, basınca kapanır |
| **NC (Normally Closed)** | Varsayılan kapalı, basınca açılır |
| **SPST** | Single Pole Single Throw |
| **DPDT** | Double Pole Double Throw |

#### 1.3 Takt Buton İç Yapısı
```
        ┌─────────────────┐
        │    ┌─────┐      │
    1 ──┤────┤     ├────┤── 2
        │    │     │      │
    3 ──┤────┤     ├────┤── 4
        │    └─────┘      │
        └─────────────────┘
    
    1-2 bağlı, 3-4 bağlı
    Basınca: 1-2-3-4 hepsi bağlı
```

### 2. Pull-up ve Pull-down Dirençleri

#### 2.1 Neden Gerekli?
Bağlı olmayan (floating) bir pin rastgele değerler okur!

```
    ❌ YANLIŞ (Floating Pin)
    ┌───────────┐
    │ Arduino   │
    │   Pin 2 ──┼──── Buton ──── 5V
    │           │
    └───────────┘
    
    Buton açıkken pin havada kalır (0V? 5V? Rastgele!)
```

#### 2.2 Pull-Down Direnç Konfigürasyonu
```
    ✅ DOĞRU (Pull-Down)
                              5V
                               │
    ┌───────────┐              │
    │ Arduino   │         ┌────┴────┐
    │   Pin 2 ──┼─────────┤  BUTON  │
    │           │         └─────────┘
    │           │              │
    │           │           [10kΩ]
    │           │              │
    │   GND  ───┼──────────────┘
    └───────────┘
    
    Buton AÇIK: Pin = LOW (10kΩ ile GND'ye çekili)
    Buton KAPALI: Pin = HIGH (5V bağlı)
```

#### 2.3 Pull-Up Direnç Konfigürasyonu
```
    ✅ DOĞRU (Pull-Up)
                              5V
                               │
    ┌───────────┐           [10kΩ]
    │ Arduino   │              │
    │   Pin 2 ──┼──────────────┼
    │           │              │
    │           │         ┌────┴────┐
    │           │         │  BUTON  │
    │   GND  ───┼─────────┴─────────┘
    └───────────┘
    
    Buton AÇIK: Pin = HIGH (10kΩ ile 5V'a çekili)
    Buton KAPALI: Pin = LOW (GND bağlı)
```

#### 2.4 Arduino Dahili Pull-Up
Arduino'da INPUT_PULLUP modu kullanarak harici direnç gerektirmeden pull-up sağlanabilir:
```cpp
pinMode(2, INPUT_PULLUP);  // Dahili ~20kΩ pull-up aktif
```

### 3. Debouncing (Titreme Giderme)

#### 3.1 Bouncing Nedir?
Mekanik butonlarda basma anında mikro-saniye seviyesinde titreşimler oluşur:

```
    İDEAL SİNYAL:
    HIGH ──┐           ┌──
           │           │
    LOW  ──┴───────────┴──
           ↑           ↑
         Basıldı    Bırakıldı
    
    GERÇEK SİNYAL (Bouncing):
    HIGH ──┐ ┐ ┐       ┌ ┌──
           │ │ │       │ │
    LOW  ──┴─┴─┴───────┴─┴──
           ↑           ↑
         Titreşim   Titreşim
```

#### 3.2 Yazılımsal Debounce
```cpp
// Basit debounce - delay ile
int okunan = digitalRead(butonPin);
if (okunan == HIGH) {
    delay(50);  // Titreşimin bitmesini bekle
    if (digitalRead(butonPin) == HIGH) {
        // Gerçek basma
    }
}
```

#### 3.3 millis() ile Gelişmiş Debounce
```cpp
unsigned long sonDebounceZaman = 0;
unsigned long debounceGecikme = 50;

if (okunan != sonButonDurum) {
    sonDebounceZaman = millis();
}

if ((millis() - sonDebounceZaman) > debounceGecikme) {
    // Stabil durum
}
```

### 4. Dijital Giriş Fonksiyonları

#### 4.1 digitalRead(pin)
```cpp
int durum = digitalRead(2);  // HIGH veya LOW döner

if (durum == HIGH) {
    // Buton basılı
} else {
    // Buton basılı değil
}
```

#### 4.2 Karar Yapıları
```cpp
// if-else yapısı
if (koşul) {
    // Koşul doğru ise
} else {
    // Koşul yanlış ise
}

// if-else if-else
if (koşul1) {
    // Koşul1 doğru
} else if (koşul2) {
    // Koşul2 doğru
} else {
    // Hiçbiri değil
}
```

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| Push Button | 2 | Takt buton |
| LED (5mm) | 2 | Farklı renkler |
| 220Ω Direnç | 2 | LED için |
| 10kΩ Direnç | 2 | Pull-down için |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 10+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────────────┐
    │                   BREADBOARD                    │
    │                                                 │
    │  5V ───────┬─────────────────┬                  │
    │            │                 │                  │
    │       [BUTON1]          [BUTON2]                │
    │            │                 │                  │
    │  Pin 2 ────┼───[10kΩ]───GND  │                  │
    │            │                 │                  │
    │  Pin 3 ────┴─────────────────┼───[10kΩ]───GND   │
    │                                                 │
    │  Pin 12 ────[220Ω]────►LED1────GND              │
    │  Pin 13 ────[220Ω]────►LED2────GND              │
    │                                                 │
    └─────────────────────────────────────────────────┘
```

---

### Örnek Kod 1: Basit Buton-LED Kontrolü

```cpp
/*
 * Basit Buton-LED Kontrolü
 * Buton basılıyken LED yanar
 */

const int buton1Pin = 2;
const int buton2Pin = 3;
const int led1Pin = 12;
const int led2Pin = 13;

void setup() {
  pinMode(buton1Pin, INPUT);
  pinMode(buton2Pin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Buton 1 kontrolü
  if (digitalRead(buton1Pin) == HIGH) {
    digitalWrite(led1Pin, HIGH);
    Serial.println("Buton 1 BASILI - LED 1 ACIK");
  } else {
    digitalWrite(led1Pin, LOW);
  }
  
  // Buton 2 kontrolü
  if (digitalRead(buton2Pin) == HIGH) {
    digitalWrite(led2Pin, HIGH);
    Serial.println("Buton 2 BASILI - LED 2 ACIK");
  } else {
    digitalWrite(led2Pin, LOW);
  }
  
  delay(50);  // Basit debounce
}
```

---

### Örnek Kod 2: Toggle (Aç/Kapa) Modu

```cpp
/*
 * Toggle Modu
 * Her basışta LED durumu değişir
 * Gelişmiş debounce ile
 */

const int butonPin = 2;
const int ledPin = 13;

int ledDurum = LOW;
int sonButonDurum = LOW;
int suAnkiButonDurum = LOW;

unsigned long sonDebounceZaman = 0;
unsigned long debounceGecikme = 50;

void setup() {
  pinMode(butonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Toggle Modu Baslatildi");
}

void loop() {
  int okunan = digitalRead(butonPin);
  
  // Durum değişikliği algıla
  if (okunan != sonButonDurum) {
    sonDebounceZaman = millis();
  }
  
  // Debounce süresi geçti mi kontrol et
  if ((millis() - sonDebounceZaman) > debounceGecikme) {
    
    // Stabil durum değişti mi?
    if (okunan != suAnkiButonDurum) {
      suAnkiButonDurum = okunan;
      
      // Sadece basıldığında (LOW -> HIGH geçişi)
      if (suAnkiButonDurum == HIGH) {
        ledDurum = !ledDurum;  // Durumu tersle
        digitalWrite(ledPin, ledDurum);
        
        Serial.print("LED Durumu: ");
        Serial.println(ledDurum ? "ACIK" : "KAPALI");
      }
    }
  }
  
  sonButonDurum = okunan;
}
```

---

### Örnek Kod 3: INPUT_PULLUP Kullanımı

```cpp
/*
 * INPUT_PULLUP ile Buton Kontrolü
 * Harici direnç gerektirmez
 * NOT: Mantık tersine çalışır (LOW = basılı)
 */

const int butonPin = 2;
const int ledPin = 13;

void setup() {
  pinMode(butonPin, INPUT_PULLUP);  // Dahili pull-up aktif
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // INPUT_PULLUP'ta mantık ters!
  // Basılıyken LOW, basılı değilken HIGH
  
  if (digitalRead(butonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Buton BASILI");
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(50);
}
```

---

### Örnek Kod 4: Çoklu Buton Kontrolü (State Machine)

```cpp
/*
 * Çoklu Buton ile LED Modu Değiştirme
 * Buton 1: Mod değiştir
 * Buton 2: Hızı değiştir
 */

const int buton1Pin = 2;
const int buton2Pin = 3;
const int ledPin = 13;

int mod = 0;           // 0: Kapalı, 1: Sabit, 2: Yanıp-sönen
int hiz = 500;         // Yanıp sönme hızı
int sonButon1 = LOW;
int sonButon2 = LOW;

void setup() {
  pinMode(buton1Pin, INPUT);
  pinMode(buton2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Mod: 0 - KAPALI");
}

void loop() {
  // Buton 1 - Mod değiştir
  int buton1 = digitalRead(buton1Pin);
  if (buton1 == HIGH && sonButon1 == LOW) {
    delay(50);  // Debounce
    mod = (mod + 1) % 3;  // 0, 1, 2 arasında döngü
    
    Serial.print("Mod: ");
    Serial.print(mod);
    switch(mod) {
      case 0: Serial.println(" - KAPALI"); break;
      case 1: Serial.println(" - SABIT"); break;
      case 2: Serial.println(" - YANIP SONEN"); break;
    }
  }
  sonButon1 = buton1;
  
  // Buton 2 - Hız değiştir
  int buton2 = digitalRead(buton2Pin);
  if (buton2 == HIGH && sonButon2 == LOW) {
    delay(50);  // Debounce
    hiz = hiz - 100;
    if (hiz < 100) hiz = 500;
    
    Serial.print("Hiz: ");
    Serial.print(hiz);
    Serial.println(" ms");
  }
  sonButon2 = buton2;
  
  // Mod kontrolü
  switch(mod) {
    case 0:  // Kapalı
      digitalWrite(ledPin, LOW);
      break;
      
    case 1:  // Sabit
      digitalWrite(ledPin, HIGH);
      break;
      
    case 2:  // Yanıp-sönen
      digitalWrite(ledPin, HIGH);
      delay(hiz);
      digitalWrite(ledPin, LOW);
      delay(hiz);
      break;
  }
}
```

---

### Örnek Kod 5: Sayaç Uygulaması

```cpp
/*
 * Butonla Sayaç
 * Buton 1: Artır
 * Buton 2: Sıfırla
 */

const int butonArtir = 2;
const int butonSifirla = 3;
const int ledPin = 13;

int sayac = 0;
int sonArtir = LOW;
int sonSifirla = LOW;

void setup() {
  pinMode(butonArtir, INPUT);
  pinMode(butonSifirla, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sayac: 0");
}

void loop() {
  // Artır butonu
  int artir = digitalRead(butonArtir);
  if (artir == HIGH && sonArtir == LOW) {
    delay(50);
    sayac++;
    Serial.print("Sayac: ");
    Serial.println(sayac);
    
    // LED ile sayıyı göster (yanıp sönme)
    for (int i = 0; i < sayac % 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }
  sonArtir = artir;
  
  // Sıfırla butonu
  int sifirla = digitalRead(butonSifirla);
  if (sifirla == HIGH && sonSifirla == LOW) {
    delay(50);
    sayac = 0;
    Serial.println("Sayac SIFIRLANDI");
    
    // Sıfırlama göstergesi
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(50);
      digitalWrite(ledPin, LOW);
      delay(50);
    }
  }
  sonSifirla = sifirla;
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Buton-LED
- [ ] Pull-down dirençli devreyi kur
- [ ] Basit buton-LED kodunu test et
- [ ] Buton basıldığında LED'in yandığını doğrula

### Görev 2: Toggle Modu
- [ ] Toggle kodunu yükle
- [ ] Her basışta LED'in durumunun değiştiğini gözlemle
- [ ] Debounce olmadan dene (sorunları gör)

### Görev 3: INPUT_PULLUP
- [ ] Harici direnci kaldır
- [ ] INPUT_PULLUP modunu kullan
- [ ] Mantığın tersine döndüğünü gözlemle

### Görev 4: State Machine
- [ ] Çoklu buton kontrolü kur
- [ ] Farklı modlar arasında geçiş yap
- [ ] Hız ayarını test et

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ Dijital giriş okuma yapabilir
- ✅ Pull-up ve pull-down direnç konfigürasyonunu uygulayabilir
- ✅ Debouncing tekniklerini kullanabilir
- ✅ State machine mantığını anlayabilir
- ✅ millis() fonksiyonunu kullanabilir
- ✅ if-else karar yapılarını etkin kullanabilir

---

## ⚠️ Dikkat Edilmesi Gerekenler

1. **Floating Pin:** Dirençsiz bağlantıda pin rastgele değerler okur
2. **Debounce:** Yazılımsal debounce olmadan çoklu tetikleme olur
3. **INPUT_PULLUP:** Mantık tersine çalışır (LOW = basılı)
4. **delay() sorunu:** Uzun delay'ler programı bloke eder

---

**Sonraki Hafta:** Analog Giriş - Potansiyometre ve Seri Haberleşme
