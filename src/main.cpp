#include <Arduino.h>
#include <DHT.h>
#include <Rtc_Pcf8563.h>
#include <LiquidCrystal.h>

DHT sensor(8, DHT11);
Rtc_Pcf8563 rtc;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
    // TODO: при первом запуске установить время, а затем закомментировать
    // rtc.initClock();
    // rtc.setDate(29, 1, 7, false, 25);
    // rtc.setTime(0, 0, 0);
    lcd.begin(16, 2);

    Serial.begin(115200);
}

void loop() {
    delay(1000);

    const int humidity = int(sensor.readHumidity());
    const int temperature = int(sensor.readTemperature());

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("An error occurred!");
        Serial.println(humidity);
        Serial.println(temperature);
        return;
    }

    String humidity_string = "Hum:  $HUM%";
    String temperature_string = "Temp: $TEMPC";

    humidity_string.replace("$HUM", String(humidity));
    temperature_string.replace("$TEMP", String(temperature));

    Serial.println(humidity_string);
    Serial.println(temperature_string);

    lcd.home();
    lcd.print(humidity_string);
    lcd.setCursor(11, 0);
    lcd.print(rtc.formatTime(2));
    lcd.setCursor(0, 1);
    lcd.print(temperature_string);
    lcd.setCursor(11, 1);
    lcd.print(rtc.formatDate());
}
