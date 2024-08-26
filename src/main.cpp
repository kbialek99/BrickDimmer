#include <Wire.h>
#include <BH1750.h>
#include <WiFi.h>
#include <time.h>
#include <esp_sleep.h>

const char *ssid = ""; //fill
const char *password = ""; //fill

#define THRESHOLD 5
#define SLEEPDURATIONDAY 900e6 // 1800e6
#define SLEEPDURATIONNIGHT 5000

struct tm timeinfo;


BH1750 lightMeter;
const int relayPin = 23; // GPIO pin connected to the relay or MOSFET gate

void connectToWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void initializeTime()
{
  configTime(3600, 3600, "pool.ntp.org"); // Set timezone to UTC
  while (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time, retrying...");
    delay(2000);
  }
  Serial.println("Time obtained");
}

void setup()
{

  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure the relay is off initially

  Wire.begin();
  lightMeter.begin();

  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

  if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER)
  {
    // Only connect to Wi-Fi and get time if we are not waking up from deep sleep
    connectToWiFi();
    initializeTime();
  }
}

void loop()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }

  int currentHour = timeinfo.tm_hour;
  int currentMinute = timeinfo.tm_min;
  float lux = lightMeter.readLightLevel();

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.printf("Current time: %02d:%02d\n", currentHour, currentMinute);
  if ( (currentHour == 18 && currentMinute  >= 30) || (currentHour > 18) )
  {
    Serial.println("Nighttime check");
    if (lux < 0)
    {
      digitalWrite(relayPin, LOW); // Turn off the relay (or MOSFET)
    }
    else
    {
      if (lux < THRESHOLD)
      {
        digitalWrite(relayPin, HIGH); // Turn on the relay (or MOSFET)
        Serial.print("LED is LIT\n ");
      }
      else
      {
        digitalWrite(relayPin, LOW); // Turn off the relay (or MOSFET)
        Serial.print("LED is DED\n");
      }
    }
    delay(SLEEPDURATIONNIGHT);
  }
  else
  {
    Serial.println("Daytime - entering deep sleep for 15 minutes");
    esp_sleep_enable_timer_wakeup(SLEEPDURATIONDAY);
    esp_deep_sleep_start();
  }

}
