#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "SSID";
const char* password = "Pass";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting");

  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected!");
    lcd.setCursor(0, 1);
    lcd.print("IP: ");
    lcd.print(WiFi.localIP());
    Serial.println("Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed 2 connect");
    Serial.println("Failed to connect to WiFi");
  }
}

void loop() {

}
