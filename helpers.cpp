#include "helpers.h"

void connect_to_wifi(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to the WiFi network");
}

void mqtt_callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

float get_latitude() {
  // random latitude
  return 23.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.5)));  // Range: 23.5 to 24.0
}

float get_longitude() {
  // random longitude
  return 90.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.5)));  // Range: 90.0 to 90.5
}

float get_speed() {
  // mock data
  return 45;
}

float get_heading() {
  // mock data
  return 180;
}

void sync_time(long gmt_offset_sec, int daylight_offset_sec, const char *ntp_server) {
  configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
  Serial.print("Waiting for NTP time sync: ");
  while (time(nullptr) < 8 * 3600 * 2) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Time synchronized");
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    Serial.print("Current time: ");
    Serial.println(asctime(&timeinfo));
  } else {
    Serial.println("Failed to obtain local time");
  }
}

String get_current_timestamp_ISO8601() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(buffer);
}
