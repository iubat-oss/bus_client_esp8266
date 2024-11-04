#ifndef HELPERS_H
#define HELPERS_H

#include <ESP8266WiFi.h>
#include <time.h>

void connect_to_wifi(const char *ssid, const char *password);
void mqtt_callback(char *topic, byte *payload, unsigned int length);
float get_latitude();
float get_longitude();
float get_speed();
float get_heading();
void sync_time(long gmt_offset_sec, int daylight_offset_sec, const char* ntp_server);
String get_current_timestamp_ISO8601();

#endif