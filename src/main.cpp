#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <Adafruit_MCP4725.h>
#include "index.h"


const int no_steering = 2040, right_steer = 0, left_steer = 4094;
const int forward_speed = 2000, turn_speed = 1350, back_speed = 1100, stop_speed = 0;

// Set web server port number to 80
ESP8266WebServer server(80); //Server on port 80

ESP8266WiFiMulti wifiMulti;

/*
VCC – Wemos Mini 3.3v
GND – Wemos Mini Gnd
SCL – Wemos Mini D1
SDA – Wemos Mini D2
*/
Adafruit_MCP4725 DAC_Steer;
Adafruit_MCP4725 DAC_Speed;

/* Temp Sensor */
//Adafruit_MLX90614 Temp = Adafruit_MLX90614(MLX90614_I2CADDR);


//Static IP address configuration
IPAddress local_IP(192, 168, 1, 200);
IPAddress gateway(192, 168, 1 , 1);  
IPAddress subnet(255, 255, 255, 0); 
IPAddress dns(8, 8, 8, 8);          


void Scan_Available_Networks();
//void display_web_page();
//void handleClientRequest();
void handleRoot(); //View html page
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void stop();

void setup()
{
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  wifiMulti.addAP("SSID", "PASS");


  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  if (!WiFi.config(local_IP, gateway, subnet, dns))
  { // Static IP configutration
    Serial.println("STA Failed to configure");
  }

  // Relays Pulse
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);

  delay(1000);

  digitalWrite(D4, LOW);
  digitalWrite(D6, LOW);
  delay(100);
  digitalWrite(D4, HIGH);
  server.on("/", handleRoot);
  server.on("/f", moveForward);
  server.on("/b", moveBackward);
  server.on("/r", turnRight);
  server.on("/l", turnLeft);
  server.on("/s", stop);
  server.begin(); //Start server
  DAC_Steer.begin(0x60);
  DAC_Speed.begin(0x61);
  stop();
  //Temp.begin();
}

void loop()
{
  if (wifiMulti.run() != WL_CONNECTED)
  {
    Scan_Available_Networks();
  }
  server.handleClient(); //Handle client requests
}

void handleRoot()
{
  String s = MAIN_page;
  server.send(200, "text/html", s); //Send web page
  Serial.println("WebPage Sent.");
}
void moveForward()
{
  DAC_Steer.setVoltage(no_steering, false);
  DAC_Speed.setVoltage(forward_speed, false);
  Serial.println("Forward");
  server.send(200, "text/plane", "F");
}

void moveBackward()
{
  DAC_Steer.setVoltage(no_steering, false);
  DAC_Speed.setVoltage(back_speed, false);
  Serial.println("Backward");
  server.send(200, "text/plane", "B");
}

void turnLeft()
{
  DAC_Steer.setVoltage(left_steer, false);
  DAC_Speed.setVoltage(turn_speed, false);
  Serial.println("Left");
  server.send(200, "text/plane", "L");
}

void turnRight()
{
  DAC_Steer.setVoltage(right_steer, false);
  DAC_Speed.setVoltage(turn_speed, false);
  Serial.println("Right");
  server.send(200, "text/plane", "R");
}

void stop()
{
  DAC_Steer.setVoltage(no_steering, false);
  DAC_Speed.setVoltage(stop_speed, false);
  Serial.println("Stop");
  server.send(200, "text/plane", "S");
}

void Scan_Available_Networks()
{

  Serial.println("Scan Networks");
  while (wifiMulti.run() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(500);
    Serial.print('.');
  }
  Serial.printf("\nConnected to: %s\n", WiFi.SSID().c_str());

  IPAddress IP = WiFi.localIP();
  Serial.print("Local IP address: ");
  Serial.println(IP);
  
}
