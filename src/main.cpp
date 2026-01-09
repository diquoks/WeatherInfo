#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Rtc_Pcf8563.h>

DHT sensor(8, DHT11);
Rtc_Pcf8563 rtc;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
    // TODO: set on first startup
    // rtc.initClock();
    // rtc.setDate(29, 1, 7, false, 25);
    // rtc.setTime(0, 0, 0);

    lcd.begin(16, 2);

    Serial.begin(115200);
}

void loop() {
    delay(1000);

    const float humidity = sensor.readHumidity();
    const float temperature = sensor.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("An error occurred!");
        Serial.println(humidity);
        Serial.println(temperature);
        return;
    }

    char humidity_char[16];
    char temperature_char[16];

    sprintf(humidity_char, "Hum:  %ld%%", round(humidity)); // NOLINT(*-incorrect-roundings)
    sprintf(temperature_char, "Temp: %ldC", round(temperature)); // NOLINT(*-incorrect-roundings)

    Serial.println(humidity_char);
    Serial.println(temperature_char);

    lcd.home();
    lcd.print(humidity_char);
    lcd.setCursor(11, 0);
    lcd.print(rtc.formatTime(2));
    lcd.setCursor(0, 1);
    lcd.print(temperature_char);
    lcd.setCursor(11, 1);
    lcd.print(rtc.formatDate());
}
