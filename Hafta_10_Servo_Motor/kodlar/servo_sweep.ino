/*
 * Otomatik Servo Tarama (Sweep)
 * Servo 0-180 derece arasında sürekli hareket
 * 
 * Devre Bağlantısı:
 * Servo Kahverengi -> GND
 * Servo Kırmızı -> 5V
 * Servo Turuncu -> Pin 9
 */

#include <Servo.h>

Servo motor;

void setup() {
  motor.attach(9);
  Serial.begin(9600);
  Serial.println("Servo Tarama (Sweep)");
  Serial.println("====================");
}

void loop() {
  // Sağa tarama (0 -> 180)
  Serial.println("Saga tarama...");
  for (int aci = 0; aci <= 180; aci++) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);  // Uçta bekle
  
  // Sola tarama (180 -> 0)
  Serial.println("Sola tarama...");
  for (int aci = 180; aci >= 0; aci--) {
    motor.write(aci);
    Serial.println(aci);
    delay(15);
  }
  
  delay(500);  // Uçta bekle
}
