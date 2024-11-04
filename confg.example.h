// rename this file "config.example.h" to "config.h"
// fill-out the empty strings with necessary credentials

#ifndef CONFIG_H
#define CONFIG_H

const char *bus_id = "";

// WiFi settings
const char *ssid = "";
const char *password = "";

// MQTT Broker settings
const int mqtt_port = 8883;    // TLS port
const char *mqtt_broker = "";  // a.e. "broker.emqx.io"
const char *mqtt_topic = "";
const char *mqtt_username = "";
const char *mqtt_password = "";

// NTP Server settings
const char *ntp_server = "pool.ntp.org";
// According to Bangladesh time
const long gmt_offset_sec = 6 * 3600;
const int daylight_offset_sec = 0;

#endif
