#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

const char* ssid = "SSID";
const char* password = "Pass";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 0;

const int I2C_ADDR = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

int last_second, second_, minute_, hour_, day_, month_;
int year_;

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  timeClient.begin();
}

void loop() {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  second_ = second(epochTime);
  minute_ = minute(epochTime);
  hour_ = hour(epochTime);
  day_ = day(epochTime);
  month_ = month(epochTime);
  year_ = year(epochTime);

  char timeString[] = "HH:MM:SS";
  sprintf(timeString, "%02d:%02d:%02d", hour_, minute_, second_);


  char dateString[] = "DD/MM/YYYY";
  sprintf(dateString, "%02d/%02d/%04d", day_, month_, year_);

  lcd.setCursor(0, 0);
  lcd.print(timeString);
  lcd.setCursor(0, 1);
  lcd.print(dateString);

  delay(1000);
}
