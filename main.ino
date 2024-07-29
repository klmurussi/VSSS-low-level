#include <WiFi.h>
#include <WebServer.h>
#include "src/motor.h"

// Motor pin definitions
Motor motor1(MOTOR1_PIN_R, MOTOR1_PIN_L, MOTOR1_PIN_ENABLE_R, MOTOR1_PIN_ENABLE_L, PWM_MOTOR1_CHANNEL_R, PWM_MOTOR1_CHANNEL_L);
Motor motor2(MOTOR2_PIN_R, MOTOR2_PIN_L, MOTOR2_PIN_ENABLE_R, MOTOR2_PIN_ENABLE_L, PWM_MOTOR2_CHANNEL_R, PWM_MOTOR2_CHANNEL_L);

const char ssid[] = "POCO M3";
const char password[] = "efoisoisso";

WebServer server(80);

void handleRoot() {
  String html = "<html><body><h1>Robot Controller</h1>"
                "<button onclick=\"fetch('/moveForward')\">Move Forward</button>"
                "<button onclick=\"fetch('/stop')\">Stop</button>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void handleMoveForward() {
  motor1.moveForward(255, -1);  // Adjust this based on your motor library
  motor2.moveForward(255, -1);  // Adjust this based on your motor library
  Serial.println("Message 1: Button MoveForward was clicked");
  server.send(200, "text/plain", "Moving forward.");
}

void handleStop() {
  motor1.moveForward(0, -1);  // Adjust this based on your motor library
  motor2.moveForward(0, -1);  // Adjust this based on your motor library
  Serial.println("Message 2: Button Stop was clicked");
  server.send(200, "text/plain", "Stopped.");
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/moveForward", handleMoveForward);
  server.on("/stop", handleStop);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
