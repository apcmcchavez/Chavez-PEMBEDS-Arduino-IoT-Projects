/*
 * SMART HOME CONTROLLER - PRODUCTION
 * Board: Arduino Uno R4 WiFi
 * Features: 5 LEDs + 1 Motor (Connected to Django Backend)
 */

#include <WiFiS3.h>
#include <ArduinoJson.h> // Ensure "ArduinoJson" library is installed

// --- 📶 NETWORK CONFIGURATION ---
const char ssid[] = "YOUR_WIFI_NAME";     // ⚠️ CHANGE THIS
const char pass[] = "YOUR_WIFI_PASSWORD"; // ⚠️ CHANGE THIS
char server[] = "192.168.X.X";            // ⚠️ CHANGE THIS TO YOUR LAPTOP IP
int port = 8000;

WiFiClient client;

// --- 🔌 PIN DEFINITIONS (MATCHING YOUR TINKERCAD) ---
const int LED1_PIN = 7;  // Note: No PWM (On/Off only)
const int LED2_PIN = 8;  // Note: No PWM (On/Off only)
const int LED3_PIN = 9;  // PWM OK
const int LED4_PIN = 10; // PWM OK
const int LED5_PIN = 11; // PWM OK

// --- ⚙️ MOTOR DRIVER PINS (MATCHING YOUR TINKERCAD) ---
const int MOTOR_ENABLE = 6; // PWM Speed Control
const int MOTOR_IN1 = 5;    // Direction A
const int MOTOR_IN2 = 3;    // Direction B

// --- ⏱️ TIMING VARIABLES ---
unsigned long lastPollTime = 0;
const long POLL_INTERVAL = 200; // Check fast (0.2s) for smooth sliders

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // 1. Set Pin Modes
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);

  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // 2. Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Non-blocking delay loop
  if (millis() - lastPollTime > POLL_INTERVAL)
  {
    fetchControls();
    lastPollTime = millis();
  }
}

void fetchControls()
{
  if (client.connect(server, port))
  {
    // 1. Send GET Request
    client.println("GET /api/controls/ HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    // 2. Skip HTTP Headers
    bool headerEnded = false;
    while (client.connected())
    {
      String line = client.readStringUntil('\n');
      if (line == "\r")
      {
        headerEnded = true;
        break;
      }
    }

    if (!headerEnded)
      return;

    // 3. Parse JSON Response
    // Allocate memory for the JSON document
    JsonDocument doc;
    String payload = client.readString();

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
      Serial.print("JSON Failed: ");
      Serial.println(error.c_str());
      return;
    }

    // 4. Update Hardware based on Data
    JsonArray devices = doc.as<JsonArray>();

    for (JsonObject device : devices)
    {
      const char *name = device["name"]; // e.g., "LED 1", "DC Motor"
      bool isActive = device["is_active"];
      int value = device["value"]; // 0 - 255

      // Calculate final output
      int finalOutput = isActive ? value : 0;

      // --- UPDATE LEDS ---
      if (strcmp(name, "LED 1") == 0)
        analogWrite(LED1_PIN, finalOutput);
      else if (strcmp(name, "LED 2") == 0)
        analogWrite(LED2_PIN, finalOutput);
      else if (strcmp(name, "LED 3") == 0)
        analogWrite(LED3_PIN, finalOutput);
      else if (strcmp(name, "LED 4") == 0)
        analogWrite(LED4_PIN, finalOutput);
      else if (strcmp(name, "LED 5") == 0)
        analogWrite(LED5_PIN, finalOutput);

      // --- UPDATE MOTOR ---
      else if (strcmp(name, "DC Motor") == 0)
      {
        if (finalOutput > 0)
        {
          // Motor ON
          digitalWrite(MOTOR_IN1, HIGH);          // Pin 5
          digitalWrite(MOTOR_IN2, LOW);           // Pin 3
          analogWrite(MOTOR_ENABLE, finalOutput); // Pin 6
        }
        else
        {
          // Motor OFF
          digitalWrite(MOTOR_IN1, LOW);
          digitalWrite(MOTOR_IN2, LOW);
          analogWrite(MOTOR_ENABLE, 0);
        }
      }
    }
    client.stop();
  }
  else
  {
    Serial.println("❌ Connection to Backend Failed (Check IP/Server)");
  }
}