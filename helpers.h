#ifndef HELPERS_H
#define HELPERS_H

#include <ESP8266WiFi.h>
#include <time.h>

extern float progress;

const float START_LATITUDE = 23.945217;
const float START_LONGITUDE = 90.382654;
const float END_LATITUDE = 23.910331;
const float END_LONGITUDE = 90.397197;
const float DURATION_SECONDS = 60.0f;
const float STEP_INCREMENT = 1.0f / (DURATION_SECONDS * 1.0f);

void connect_to_wifi(const char *ssid, const char *password);
void mqtt_callback(char *topic, byte *payload, unsigned int length);
float interpolate(float start, float end, float t);
float get_latitude();
float get_longitude();
float get_speed();
float get_heading();
void sync_time(long gmt_offset_sec, int daylight_offset_sec, const char *ntp_server);
String get_current_timestamp_ISO8601();

#endif