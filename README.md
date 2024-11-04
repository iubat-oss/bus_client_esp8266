# ESP8266 Bus Location Tracker

This project uses an ESP8266 to publish real-time bus location data to an MQTT broker. This setup can be used to simulate or develop a real-time tracking system for buses or other vehicles.

## Hardware Requirements

- ESP8266 board (e.g., NodeMCU)
- Wi-Fi connection>
- EMQX MQTT Broker (or any MQTT broker with TLS support)

## Setup

### 1. Configure Project Constants

Rename `config.example.h` into `config.h` file to store your Wi-Fi and MQTT credentials and any server-specific details:

```cpp
// Wi-Fi settings
const char *ssid = "Your_WiFi_SSID";
const char *password = "Your_WiFi_Password";

// MQTT Broker settings
const char *mqtt_broker = "broker.emqx.io";
const int mqtt_port = 8883;
const char *mqtt_username = "your_username";
const char *mqtt_password = "your_password";
const char *mqtt_topic = "foo/bar";

// NTP Server settings
const char *ntp_server = "pool.ntp.org";
const long gmt_offset_sec = 6 * 3600;  // Bangladesh Standard Time (BST)
const int daylight_offset_sec = 0;
```

### 2. Install Required Libraries

- **ArduinoJson**: For formatting data in JSON.
- **PubSubClient**: For MQTT communication.

Install these via the Arduino Library Manager.

### 3. Upload the Code

Connect your ESP8266 to your computer, select the correct board and port in the Arduino IDE, and upload `bus_client_esp8266.ino`.

## Usage

1. The ESP8266 will connect to the specified Wi-Fi network.
2. It will synchronize the time with the NTP server.
3. After connecting to the MQTT broker, it will publish mock GPS location data every 3 seconds to the specified MQTT topic.

### Example Output

Upon successful connection, the serial monitor will display logs similar to:

```plaintext
Connecting to WiFi...
Connected to the WiFi network.
Waiting for NTP time sync...
Time synchronized.
Connecting to MQTT Broker as esp8266-client-XX:XX:XX:XX:XX...
Connected to MQTT broker.
Published location data.
```

### MQTT Message Format

Each message sent to the MQTT topic is a JSON object with the following structure:

```json
{
  "bus_id": "1",
  "latitude": 23.76,
  "longitude": 90.39,
  "timestamp": "2024-11-04T23:16:30Z",
  "speed": 45,
  "heading": 180
}
```

## Troubleshooting

- **Frequent Reconnection to MQTT**: Ensure Wi-Fi stability and check the broker configuration for issues like rate limits.
- **SSL Errors**: Verify that the correct root CA certificate is loaded in `config.h`.
- **Time Sync Issues**: Check your NTP server settings and network time accuracy.
