// ref: https://docs.emqx.com/en/cloud/latest/connect_to_deployments/esp8266.html#connect-over-tls-ssl-port

#include <ArduinoJson.h>
#include <PubSubClient.h>

#include "ca_cert.h"
#include "config.h"
#include "helpers.h"


// WiFi and MQTT client initialization
BearSSL::WiFiClientSecure espClient;
PubSubClient mqtt_client(espClient);

void connect_to_mqtt_broker();
void publish_bus_location(PubSubClient& mqtt_client, const char *topic);

void setup() {
  Serial.begin(115200);
  connect_to_wifi(ssid, password);
  sync_time(gmt_offset_sec, daylight_offset_sec, ntp_server);  // X.509 validation requires synchronization time
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setCallback(mqtt_callback);
  connect_to_mqtt_broker();
}

void loop() {
  if (!mqtt_client.connected()) {
    connect_to_mqtt_broker();
  }
  mqtt_client.loop();

  publish_bus_location(mqtt_client, mqtt_topic);
  delay(3000);
}

void connect_to_mqtt_broker() {
  BearSSL::X509List serverTrustedCA(ca_cert);
  espClient.setTrustAnchors(&serverTrustedCA);

  while (!mqtt_client.connected()) {
    String client_id = "esp8266-client-" + String(WiFi.macAddress());
    Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      char err_buf[128];
      espClient.getLastSSLError(err_buf, sizeof(err_buf));
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(mqtt_client.state());
      Serial.print("SSL error: ");
      Serial.println(err_buf);
      Serial.println("Retrying...");
      delay(2000);
    }
  }
}

void publish_bus_location(PubSubClient& mqtt_client, const char *topic) {
  StaticJsonDocument<200> message;
  char payload[200];

  message["bus_id"] = bus_id;
  message["latitude"] = get_latitude();
  message["longitude"] = get_longitude();
  message["timestamp"] = get_current_timestamp_ISO8601();
  message["speed"] = get_speed();
  message["heading"] = get_heading();

  serializeJson(message, payload);

  if (mqtt_client.publish(topic, payload)) {
    Serial.println("Published Bus Location");
  } else {
    Serial.println("Failed to publish Bus location");
  }
}

