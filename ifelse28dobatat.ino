#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int DHTPIN = 4;      // Chân kết nối cảm biến DHT22 số 4 
const int DHTTYPE = DHT22; // Loại cảm biến DHT22
const int relayPin = 2;    // Chân kết nối relay số 2

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Đọc nhiệt độ từ cảm biến DHT22
  float temperature = dht.readTemperature();

  Serial.print("NHIET DO: ");
  Serial.println(temperature);

  // Kiểm tra nếu nhiệt độ vượt qua ngưỡng 28 độ
  if (temperature > 28) {                                
    lcd.print("FAT : ON ");
  } else {
    // Tắt thiết bị
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("FAT : OFF");
  }

  lcd.setCursor(0, 1);
  lcd.print("NHIET DO: ");
  lcd.setCursor(11, 1);
  lcd.print(temperature);
  lcd.setCursor(15, 1);
  lcd.print("C");

  delay(1000);
}
