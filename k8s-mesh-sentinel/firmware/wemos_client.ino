#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- KONFIGURACJA ---
const char* ssid     = "";
const char* password = "";
const char* ws_host  = "192.168.50.203"; // IP of kubernetes
const int   ws_port  = 30000;           // Kubernetes defined port

// --- PINY ---
#define LED_PIN D5

// --- OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Wire.begin(D2, D1); // SDA na D2, SCL na D1
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Fail"));
    for(;;);
  }
  
  updateOLED("SYSTEM", "Lacznie z WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  updateOLED("WIFI OK", WiFi.localIP().toString());
  delay(2000);

  webSocket.begin(ws_host, ws_port, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      updateOLED("STATUS", "Rozlaczono z K8s");
      digitalWrite(LED_PIN, LOW);
      break;
      
    case WStype_CONNECTED:
      updateOLED("STATUS", "Polaczono z serwerem!");
      webSocket.sendTXT("{\"name\": \"Wemos_Sensor\"}");
      break;
      
    case WStype_TEXT: {
      StaticJsonDocument<256> doc;
      DeserializationError error = deserializeJson(doc, payload);
      
      if (!error) {
        String msgType = doc["type"];
        if (msgType == "chat") {
          String sender = doc["name"];
          String text = doc["msg"];
          updateOLED(sender, text);
          
          digitalWrite(LED_PIN, HIGH);
          delay(200);
          digitalWrite(LED_PIN, LOW);
        }
      }
      break;
    }
  }
}

void updateOLED(String header, String message) {
  display.clearDisplay();
  display.fillRect(0, 0, 128, 16, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(2, 4);
  display.println(header);
  
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.println(message);
  display.display();
}
