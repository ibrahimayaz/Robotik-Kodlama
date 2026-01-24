/*
 * Robot Araba Kontrolü
 * L298N ile çift DC motor kontrolü
 * 
 * Devre Bağlantısı:
 * L298N +12V -> Pil (+)
 * L298N GND -> Pil (-) & Arduino GND
 * 
 * Motor A (Sol):
 * ENA -> Pin 10 (PWM)
 * IN1 -> Pin 9
 * IN2 -> Pin 8
 * OUT1, OUT2 -> Motor A
 * 
 * Motor B (Sağ):
 * ENB -> Pin 5 (PWM)
 * IN3 -> Pin 7
 * IN4 -> Pin 6
 * OUT3, OUT4 -> Motor B
 * 
 * Serial Komutlar:
 * i = ileri, g = geri, l = sol, r = sag, d = dur
 * 1 = düşük hız, 2 = orta hız, 3 = yüksek hız
 */

// Motor A (Sol)
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

// Motor B (Sağ)
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

int hiz = 200;  // Varsayılan hız (0-255)

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Robot Araba Kontrol Sistemi");
  Serial.println("===========================");
  Serial.println("Komutlar:");
  Serial.println("  i = Ileri");
  Serial.println("  g = Geri");
  Serial.println("  l = Sol");
  Serial.println("  r = Sag");
  Serial.println("  d = Dur");
  Serial.println("  1/2/3 = Dusuk/Orta/Yuksek hiz");
}

void ileri() {
  // Her iki motor ileri
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println(">>> ILERI");
}

void geri() {
  // Her iki motor geri
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println(">>> GERI");
}

void sol() {
  // Sol motor geri, sağ motor ileri
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println(">>> SOLA DON");
}

void sag() {
  // Sol motor ileri, sağ motor geri
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, hiz);
  analogWrite(ENB, hiz);
  Serial.println(">>> SAGA DON");
}

void dur() {
  // Tüm motorları durdur
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println(">>> DUR");
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();
    
    switch (komut) {
      case 'i':
      case 'I':
        ileri();
        break;
        
      case 'g':
      case 'G':
        geri();
        break;
        
      case 'l':
      case 'L':
        sol();
        break;
        
      case 'r':
      case 'R':
        sag();
        break;
        
      case 'd':
      case 'D':
        dur();
        break;
        
      case '1':
        hiz = 100;
        Serial.println("Hiz: DUSUK (100)");
        break;
        
      case '2':
        hiz = 175;
        Serial.println("Hiz: ORTA (175)");
        break;
        
      case '3':
        hiz = 255;
        Serial.println("Hiz: YUKSEK (255)");
        break;
    }
  }
}
