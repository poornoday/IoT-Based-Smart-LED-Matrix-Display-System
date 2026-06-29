#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#include "effects.h"
#include "games.h"

#define MATRIX_PIN 13  // Connect to DIN on CJMCU
#define BRIGHTNESS 30  // Kept safe at ~12% power for USB safety

// Define 8x8 NeoMatrix configuration
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, MATRIX_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

WebServer server(80);

enum Mode { MODE_LIGHTING, MODE_INFO, MODE_GAME_SNAKE, MODE_GAME_PONG };
Mode currentMode = MODE_LIGHTING;

String displayText = "ESP32 MATRIX";
unsigned long lastUpdate = 0;
int textX = 8;

// Web Server Route Handlers
void handleRoot() {
  String html = "<html><head><title>Matrix Controller</title>";
  html += "<style>body{font-family:Arial; text-align:center; background:#222; color:#fff;} button{padding:15px; margin:10px; font-size:18px; width:200px; cursor:pointer;}</style></head><body>";
  html += "<h1>ESP32 8x8 Matrix Controller</h1>";
  html += "<h3>Modes</h3>";
  html += "<button onclick=\"location.href='/mode?m=0'\">Lighting Effects</button><br>";
  html += "<button onclick=\"location.href='/mode?m=1'\">Info Ticker</button><br>";
  html += "<button onclick=\"location.href='/mode?m=2'\">Play Snake</button><br>";
  html += "<button onclick=\"location.href='/mode?m=3'\">Play Pong</button><br><br>";
  html += "<h3>Update Info Ticker Text</h3>";
  html += "<form action='/msg' method='GET'><input type='text' name='text' placeholder='Type message...'><input type='submit' value='Send'></form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleMode() {
  if (server.hasArg("m")) {
    int m = server.arg("m").toInt();
    if (m == 0) currentMode = MODE_LIGHTING;
    else if (m == 1) { currentMode = MODE_INFO; textX = 8; }
    else if (m == 2) { currentMode = MODE_GAME_SNAKE; initSnake(); }
    else if (m == 3) { currentMode = MODE_GAME_PONG; initPong(); }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleMsg() {
  if (server.hasArg("text")) {
    displayText = server.arg("text");
    displayText.toUpperCase();
    textX = 8;
    currentMode = MODE_INFO;
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(BRIGHTNESS);
  matrix.setTextColor(matrix.Color(0, 255, 255));

  // Set up ESP32 as a Soft Access Point (No home Wi-Fi needed!)
  WiFi.softAP("ESP32_Matrix_Gadget", "12345678");
  Serial.println("Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/mode", handleMode);
  server.on("/msg", handleMsg);
  server.begin();
  
  randomSeed(analogRead(0));
}

void loop() {
  server.handleClient();
  unsigned long now = millis();

  switch(currentMode) {
    case MODE_LIGHTING:
      if (now - lastUpdate > 30) {
        renderPlasma(matrix);
        lastUpdate = now;
      }
      break;

    case MODE_INFO:
      if (now - lastUpdate > 80) {
        matrix.fillScreen(0);
        matrix.setCursor(textX, 0);
        matrix.print(displayText);
        textX--;
        if (textX < (int)(displayText.length() * -6)) {
          textX = 8;
        }
        matrix.show();
        lastUpdate = now;
      }
      break;

    case MODE_GAME_SNAKE:
      if (now - lastUpdate > 250) { // Game tick speed
        // Basic AI movement simulation until hardware buttons or web input overrides it
        runSnakeAI(); 
        updateSnake(matrix);
        lastUpdate = now;
      }
      break;

    case MODE_GAME_PONG:
      if (now - lastUpdate > 100) {
        updatePong(matrix);
        lastUpdate = now;
      }
      break;
  }
}
