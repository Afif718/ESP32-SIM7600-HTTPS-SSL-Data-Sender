#define TINY_GSM_MODEM_SIM7600
#define SerialMon Serial
#define SerialAT Serial2
#define TINY_GSM_DEBUG SerialMon
#define GSM_PIN "" // Uncomment and enter your SIM PIN if applicable

// GPRS credentials
const char apn[] = "your_apn"; // Your APN
const char gprsUser[] = ""; // Your GPRS username, if any
const char gprsPass[] = ""; // Your GPRS password, if any

#define uS_TO_S_FACTOR 1000000ULL // Conversion factor for microseconds to seconds
#define TIME_TO_SLEEP 600         // Time ESP32 will go to sleep (in seconds)

// ESP32 and SIM7600 pins
#define MODEM_TX 16
#define MODEM_RX 17
#define PKEY 5
#define RST 4

#include <Arduino.h>
#include <TinyGsmClient.h>
#include <ESP_SSLClient.h> // For SSL connections
#include <ArduinoJson.h>   // For JSON handling

// Server details
const char* server = "your_server_address"; // Your server address
const int port = 443; // Server port
const char* url = "/your_api_end_point"; // Your endpoint

// API key used for security
const char* apiKey = "your_api_key"; // Your API key

// Hardcoded sensor data
const char* sHumidity = "55.2"; // Sensor data
const char* sTemperature = "22.3"; // Sensor data
const char* sConductivity = "8.5"; // Sensor data
const char* soilPH = "6.7"; // Sensor data
const char* nitrogen = "10.2"; // Sensor data
const char* phosphorus = "3.1"; // Sensor data
const char* potassium = "5.8"; // Sensor data
const char* batteryVoltage = "3.7"; // Sensor data
const char* solarVoltage = "4.2"; // Sensor data

// Initialize the modem
TinyGsm modem(SerialAT);
TinyGsmClient gsm_client(modem);

// Initialize SSL client
ESP_SSLClient ssl_client;

// Timing
unsigned long ms = 0;
const int maxRetries = 5; // Maximum retries for network connection

void setup() {
  // Initialize serial for debug
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Initializing...");

  // Initialize modem serial
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  SerialMon.println("Restarting modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN if needed
  if (strlen(GSM_PIN) && modem.getSimStatus() != 3) {
    modem.simUnlock(GSM_PIN);
  }

  if (!connectToNetwork()) {
    SerialMon.println("Failed to connect to network. Please check your SIM card and signal.");
  }

  // Initialize SSL client
  ssl_client.setInsecure();              // Disable SSL certificate verification (use with caution)
  ssl_client.setBufferSizes(2048, 1024); // Set buffer sizes (adjust as needed)
  ssl_client.setSessionTimeout(300);     // Set session timeout to 5 minutes

  // Attach GSM client to SSL client
  ssl_client.setClient(&gsm_client);

  SerialMon.println("Initialization complete.");
}

void loop() {
  SerialMon.println("---------------------------------");
  
  // Check if the network is still connected
  if (!modem.isNetworkConnected()) {
    SerialMon.println("Network disconnected, reconnecting...");
    if (!connectToNetwork()) {
      SerialMon.println("Failed to reconnect to network.");
      return; // Skip sending data if network is still down
    }
  }

  // Send data
  sendData();

  delay(5000); // Delay before retrying
}

bool connectToNetwork() {
  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" Failed to connect to network.");
    delay(10000); // Wait before trying again
    return false;
  }
  SerialMon.println(" Connected to network");

  SerialMon.print("Connecting to APN: ");
  SerialMon.print(apn);

  for (int attempt = 0; attempt < maxRetries; attempt++) {
    if (modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" GPRS connected");
      return true;
    } else {
      SerialMon.println(" Failed to connect to GPRS. Retrying...");
      delay((attempt + 1) * 2000); // Exponential backoff delay
    }
  }
  
  SerialMon.println(" Max retries reached. GPRS connection failed.");
  return false;
}

void sendData() {
  SerialMon.print("Connecting to server...");

  // Reassign the GSM client to the SSL client
  ssl_client.setClient(&gsm_client);

  // Create JSON payload
  StaticJsonDocument<512> jsonDoc;
  jsonDoc["api_key"] = apiKey; // API key
  jsonDoc["sensor"] = "plot1"; // Sensor identifier
  jsonDoc["sHumidity"] = sHumidity; // Humidity data
  jsonDoc["sTemperature"] = sTemperature; // Temperature data
  jsonDoc["sConductivity"] = sConductivity; // Conductivity data
  jsonDoc["soilPH"] = soilPH; // Soil pH data
  jsonDoc["nitrogen"] = nitrogen; // Nitrogen data
  jsonDoc["phosphorus"] = phosphorus; // Phosphorus data
  jsonDoc["potassium"] = potassium; // Potassium data
  jsonDoc["batteryVoltage"] = batteryVoltage; // Battery voltage data
  jsonDoc["solarVoltage"] = solarVoltage; // Solar voltage data

  String json;
  serializeJson(jsonDoc, json);

  if (ssl_client.connect(server, port)) {
    SerialMon.println(" ok");
    SerialMon.println("Sending POST request...");
    ssl_client.print("POST " + String(url) + " HTTP/1.1\r\n");
    ssl_client.print("Host: " + String(server) + "\r\n");
    ssl_client.print("Content-Type: application/json\r\n");
    ssl_client.print("Content-Length: " + String(json.length()) + "\r\n");
    ssl_client.print("Connection: close\r\n\r\n");
    ssl_client.print(json);

    SerialMon.print("Reading response...");
    unsigned long ms = millis();
    while (!ssl_client.available() && millis() - ms < 3000) {
      delay(0);
    }
    SerialMon.println();
    while (ssl_client.available()) {
      SerialMon.print((char)ssl_client.read());
    }
    SerialMon.println();

    ssl_client.stop();
    SerialMon.println("Connection closed.");
  } else {
    SerialMon.println(" failed to connect to server.");
  }
}
