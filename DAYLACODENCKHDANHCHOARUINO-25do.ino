#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3       // Chân kết nối của cảm biến DHT11 với Arduino
#define RELAYPIN 13      // Chân kết nối relay với Arduino

DHT dht(DHTPIN, DHT11);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(RELAYPIN, OUTPUT);              
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float temperature = dht.readTemperature();
  Serial.print("NHIET DO: ");
  Serial.print(temperature);

// Kiểm tra nếu nhiệt độ vượt qua ngưỡng 25 độ
   if (temperature > 25) {                                
    lcd.print("DEVICE-UET-ON");
    digitalWrite(RELAYPIN,HIGH);
  } else {
    // Tắt thiết bị
    digitalWrite(RELAYPIN, LOW);
    lcd.setCursor(0, 0);
    lcd.print("DEVICE-UET-OFF");
  }

  lcd.setCursor(0, 1);
  lcd.print("NHIET DO: ");
  lcd.setCursor(11, 1);
  lcd.print(temperature);
  lcd.setCursor(15, 1);
  lcd.print("C");

  delay(1000);
}