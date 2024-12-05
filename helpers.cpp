#include "helpers.h"

float progress = 0.0f;

void connect_to_wifi(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to the WiFi network");
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received on topic: ");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

float interpolate(float start, float end, float t)
{
  return start + t * (end - start);
}

float get_latitude()
{
  return interpolate(START_LATITUDE, END_LATITUDE, progress);
}

float get_longitude()
{
  return interpolate(START_LONGITUDE, END_LONGITUDE, progress);
}

float get_speed()
{
  // mock data
  return 40.0f;
}

float get_heading()
{
  // mock data
  return 90.0f;
}

void sync_time(long gmt_offset_sec, int daylight_offset_sec, const char *ntp_server)
{
  configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
  Serial.print("Waiting for NTP time sync: ");
  while (time(nullptr) < 8 * 3600 * 2)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Time synchronized");
  struct tm timeinfo;
  if (getLocalTime(&timeinfo))
  {
    Serial.print("Current time: ");
    Serial.println(asctime(&timeinfo));
  }
  else
  {
    Serial.println("Failed to obtain local time");
  }
}

String get_current_timestamp_ISO8601()
{
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(buffer);
}
