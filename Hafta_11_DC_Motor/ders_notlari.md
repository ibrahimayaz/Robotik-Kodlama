# HAFTA 11: DC Motor Kontrolü ve L298N Motor Sürücü

## Ders Bilgileri
- **Süre:** 2 saat 30 dakika
- **Teorik:** 1 saat | **Pratik:** 1 saat 30 dakika
- **Konu:** DC motor, H-Bridge, L298N, PWM hız kontrolü

---

## TEORİK KISIM (1 Saat)

### 1. DC Motor Teknolojisi

#### 1.1 DC Motor Nedir?
- Doğru akım ile çalışan elektrik motoru
- Döndürme yönü polariteye bağlı
- Hız, uygulanan gerilime orantılı

#### 1.2 DC Motor Çalışma Prensibi
```
    Manyetik Alan + Akım = Kuvvet (Lorentz Kuvveti)
    
    ┌─────────────────────────┐
    │    N        S           │  ← Sabit mıknatıslar
    │    ▼        ▲           │
    │  ┌─────────────┐        │
    │  │    Rotor    │ ◄──────│── Döner parça
    │  │   (Bobin)   │        │
    │  └─────────────┘        │
    │         │               │
    │    ═════╪═════          │  ← Komütatör
    │       ──┼──             │  ← Fırçalar
    └─────────┼───────────────┘
              │
         [+ -] Güç
```

#### 1.3 DC Motor'u Doğrudan Arduino'ya Bağlama Tehlikesi
- Arduino pin akımı: Maksimum 40mA
- DC motor akımı: 100mA - 2A+
- **Sonuç:** Arduino pini yanar!

### 2. H-Bridge (H-Köprüsü)

#### 2.1 H-Bridge Nedir?
Motor yön kontrolü için kullanılan transistör/MOSFET devresi.

```
       +V
        │
    ┌───┴───┐
    │       │
   Q1      Q2
    │       │
    └───┬───┘
        │
   ────[M]────  ← Motor
        │
    ┌───┴───┐
    │       │
   Q3      Q4
    │       │
    └───┬───┘
        │
       GND
```

#### 2.2 H-Bridge Çalışma Modları
| Q1 | Q2 | Q3 | Q4 | Sonuç |
|----|----|----|----|----|
| ON | OFF| OFF| ON | İleri |
| OFF| ON | ON | OFF| Geri |
| OFF| OFF| OFF| OFF| Boşta (Coast) |
| ON | OFF| ON | OFF| Fren (Brake) |

### 3. L298N Motor Sürücü

#### 3.1 L298N Özellikleri
| Özellik | Değer |
|---------|-------|
| Çift H-Bridge | 2 motor kontrolü |
| Çalışma gerilimi | 5V - 35V |
| Motor başına akım | 2A (max) |
| PWM hız kontrolü | Evet (ENA, ENB) |
| 5V regülatör | Var (motor V ≤ 12V) |

#### 3.2 L298N Pin Yapısı
```
    ┌─────────────────────────────┐
    │          L298N              │
    │                             │
    │  ┌─────┐       ┌─────┐      │
    │  │Motor│       │Motor│      │
    │  │  A  │       │  B  │      │
    │  └──┬──┘       └──┬──┘      │
    │     │             │         │
    └─────┼─────────────┼─────────┘
          │             │
    ┌─────┴─────────────┴─────┐
    │                         │
   OUT1 OUT2    OUT3 OUT4     │
    │    │        │    │      │
    │    │        │    │      │
    └────┼────────┼────┘      │
         │        │           │
        ENA      ENB          │  ← PWM hız kontrolü
        IN1      IN3          │
        IN2      IN4          │
        │        │            │
      +12V      +5V       GND │
    (Motor)   (Lojik)         │
    └─────────────────────────┘
```

#### 3.3 L298N Kontrol Tablosu (Motor A)
| ENA | IN1 | IN2 | Motor Durumu |
|-----|-----|-----|--------------|
| LOW | X | X | Durdur |
| HIGH| HIGH| LOW | İleri |
| HIGH| LOW | HIGH| Geri |
| HIGH| LOW | LOW | Fren |
| HIGH| HIGH| HIGH| Fren |
| PWM | HIGH| LOW | İleri (hız kontrollü) |

---

## UYGULAMA KISMI (1 Saat 30 Dakika)

### Gerekli Malzemeler
| Malzeme | Adet | Açıklama |
|---------|------|----------|
| Arduino Uno | 1 | Ana kontrolcü |
| L298N Motor Sürücü | 1 | Çift H-Bridge |
| DC Motor | 1-2 | 6V-12V |
| 9V/12V Pil | 1 | Motor güç kaynağı |
| Potansiyometre | 1 | 10kΩ (hız kontrolü) |
| Buton | 2 | Yön kontrolü |
| Breadboard | 1 | Devre tahtası |
| Jumper Kablo | 15+ | Bağlantılar |

### Devre Kurulumu

```
    ┌─────────────────────────────────────────────────┐
    │                   BAĞLANTILAR                   │
    │                                                 │
    │    L298N:                                       │
    │    +12V ────── Pil (+)                          │
    │    GND ─────── Pil (-) & Arduino GND            │
    │    +5V ─────── (Bağlama, kendi üretiyor)        │
    │                                                 │
    │    ENA ─────── Pin 10 (PWM)                     │
    │    IN1 ─────── Pin 9                            │
    │    IN2 ─────── Pin 8                            │
    │    OUT1, OUT2 ── Motor A                        │
    │                                                 │
    │    ENB ─────── Pin 5 (PWM)                      │
    │    IN3 ─────── Pin 7                            │
    │    IN4 ─────── Pin 6                            │
    │    OUT3, OUT4 ── Motor B                        │
    │                                                 │
    │    Potansiyometre ── A0 (hız için)              │
    │    Buton 1 ───────── Pin 2 (ileri)              │
    │    Buton 2 ───────── Pin 3 (geri)               │
    │                                                 │
    └─────────────────────────────────────────────────┘
```

**⚠️ Önemli:** 
- Arduino ve motor için ortak GND kullanın!
- 12V jumper takılıyken harici 5V bağlamayın!

---

### Örnek Kod 1: Temel Motor Kontrolü

```cpp
/*
 * Temel DC Motor Kontrolü
 * İleri, geri, dur komutları
 */

// Motor A pinleri
const int ENA = 10;  // PWM hız kontrolü
const int IN1 = 9;
const int IN2 = 8;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  Serial.println("DC Motor Kontrol");
}

void motorIleri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);  // Tam hız
  Serial.println("Ileri");
}

void motorGeri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);
  Serial.println("Geri");
}

void motorDur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  Serial.println("Dur");
}

void loop() {
  motorIleri();
  delay(2000);
  
  motorDur();
  delay(1000);
  
  motorGeri();
  delay(2000);
  
  motorDur();
  delay(1000);
}
```

---

### Örnek Kod 2: PWM Hız Kontrolü

```cpp
/*
 * PWM ile Hız Kontrolü
 * Potansiyometre ile motor hızı ayarla
 */

const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int potPin = A0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Motor yönünü ayarla (ileri)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  Serial.begin(9600);
  Serial.println("PWM Hiz Kontrolu");
}

void loop() {
  int potDeger = analogRead(potPin);
  int hiz = map(potDeger, 0, 1023, 0, 255);
  
  analogWrite(ENA, hiz);
  
  Serial.print("Pot: ");
  Serial.print(potDeger);
  Serial.print("\t Hiz: ");
  Serial.print(hiz);
  Serial.print("\t %");
  Serial.println(map(hiz, 0, 255, 0, 100));
  
  delay(100);
}
```

---

### Örnek Kod 3: Butonla Yön ve Hız Kontrolü

```cpp
/*
 * Butonla Tam Kontrol
 * Buton1: İleri, Buton2: Geri
 * Pot: Hız ayarı
 */

const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int potPin = A0;
const int butonIleri = 2;
const int butonGeri = 3;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(butonIleri, INPUT_PULLUP);
  pinMode(butonGeri, INPUT_PULLUP);
  
  Serial.begin(9600);
  Serial.println("Butonlu Motor Kontrol");
}

void loop() {
  int hiz = map(analogRead(potPin), 0, 1023, 0, 255);
  
  if (digitalRead(butonIleri) == LOW) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, hiz);
    Serial.print("ILERI - Hiz: ");
    Serial.println(hiz);
    
  } else if (digitalRead(butonGeri) == LOW) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, hiz);
    Serial.print("GERI - Hiz: ");
    Serial.println(hiz);
    
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    Serial.println("DUR");
  }
  
  delay(100);
}
```

---

### Örnek Kod 4: İki Motor Kontrolü (Robot Araba)

```cpp
/*
 * Çift Motor Kontrolü
 * Robot araba için temel hareketler
 */

// Motor A (Sol)
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

// Motor B (Sağ)
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

int hiz = 200;  // Varsayılan hız

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Robot Araba Kontrol");
  Serial.println("Komutlar: i=ileri, g=geri, l=sol, r=sag, d=dur");
}

void ileri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println("ILERI");
}

void geri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println("GERI");
}

void sol() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println("SOL");
}

void sag() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println("SAG");
}

void dur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("DUR");
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();
    
    switch (komut) {
      case 'i': ileri(); break;
      case 'g': geri(); break;
      case 'l': sol(); break;
      case 'r': sag(); break;
      case 'd': dur(); break;
      case '1': hiz = 100; Serial.println("Hiz: Dusuk"); break;
      case '2': hiz = 175; Serial.println("Hiz: Orta"); break;
      case '3': hiz = 255; Serial.println("Hiz: Yuksek"); break;
    }
  }
}
```

---

### Örnek Kod 5: Yumuşak Hızlanma/Yavaşlama

```cpp
/*
 * Yumuşak Hızlanma ve Yavaşlama
 * Motor stresini azaltır
 */

const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

int mevcutHiz = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  Serial.begin(9600);
  Serial.println("Yumusak Hiz Kontrolu");
}

void yumusak_hizlan(int hedefHiz) {
  if (hedefHiz > mevcutHiz) {
    // Hızlan
    for (int h = mevcutHiz; h <= hedefHiz; h += 5) {
      analogWrite(ENA, h);
      Serial.print("Hizlaniyor: ");
      Serial.println(h);
      delay(30);
    }
  } else {
    // Yavaşla
    for (int h = mevcutHiz; h >= hedefHiz; h -= 5) {
      analogWrite(ENA, h);
      Serial.print("Yavasliyor: ");
      Serial.println(h);
      delay(30);
    }
  }
  mevcutHiz = hedefHiz;
}

void loop() {
  Serial.println(">>> Hizlanma");
  yumusak_hizlan(255);
  delay(2000);
  
  Serial.println(">>> Yarim hiz");
  yumusak_hizlan(127);
  delay(2000);
  
  Serial.println(">>> Durdurma");
  yumusak_hizlan(0);
  delay(2000);
}
```

---

## 📝 Deney Görevleri

### Görev 1: Temel Kontrol
- [ ] Tek motor devresini kur
- [ ] İleri, geri, dur komutlarını test et
- [ ] Motor yönünü gözlemle

### Görev 2: Hız Kontrolü
- [ ] Potansiyometre ile hız ayarla
- [ ] Minimum çalışma hızını bul
- [ ] PWM değer-hız ilişkisini gözlemle

### Görev 3: Robot Araba
- [ ] İki motor devresini kur
- [ ] 4 yön hareketini test et
- [ ] Serial komutlarla kontrol et

### Görev 4: Engelden Kaçan Robot
- [ ] Ultrasonik sensör ekle
- [ ] Engel algılandığında dur ve dön
- [ ] Otonom hareket sağla

---

## 🎯 Öğrenme Çıktıları

Bu dersin sonunda öğrenci:
- ✅ DC motor çalışma prensibini anlayabilir
- ✅ H-Bridge mantığını kavrayabilir
- ✅ L298N motor sürücü kullanabilir
- ✅ PWM ile hız kontrolü yapabilir
- ✅ Robot araba temel hareketlerini programlayabilir

---

**Sonraki Hafta:** Proje Planlama ve Tasarım
