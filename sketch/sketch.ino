#include <UnoWiFiDevEd.h>
#include "Maxbotix.h"

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "firebaseadmin.herokuapp.com"

Maxbotix rangeSensorPW(3, Maxbotix::PW, Maxbotix::LV, Maxbotix::BEST);
Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV, Maxbotix::BEST);

String deviceName;

unsigned long previousMillisServer = 0;
const long intervalServer = 50;

unsigned long previousMillisClient = 0;
const long intervalClient = 30000;

void setup() {
  deviceName = "ArduinoOne";

  Ciao.begin();
  Ciao.println("REST Client is up");
  
  Wifi.begin();
  Wifi.println("REST Server is up");
}
 
void loop() {
  clientLoop();
  serverLoop();
}

void clientLoop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisClient >= intervalClient) {
    previousMillisClient = currentMillis;    
    Ciao.println("Reading...");
    
    short rangePW = rangeSensorPW.getRange();
  
    Ciao.println("Sending...");

    Ciao.println(deviceName);
    String uri = "/addRange?value=" + String(rangePW) + "&name=" + deviceName;
    
    Ciao.println("Request: " + uri);
  
    CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri);
  
    if (!data.isEmpty()){
      Ciao.println( "State: " + String (data.get(1)) );
      Ciao.println( "Response: " + String (data.get(2)) );
    }
    else{ 
      Ciao.println("Write Error");
    }
  }
}

void serverLoop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisServer >= intervalServer) {
    previousMillisServer = currentMillis;
    while(Wifi.available()){
      process(Wifi);
    }
  }
}

void process(WifiData client) {
  // read the command
  String command = client.readStringUntil('/');
  // is "mode" command?
  if (command == "mode") {
    modeCommand(client);
  }
}

void modeCommand(WifiData client) {
  String command = client.readStringUntil('/');
  if (command == "read") {
    client.println("HTTP/1.1 200 OK\n");
    client.print(F("Current device name: "));
    client.print(deviceName);
  } else if (command == "write") {
    deviceName = client.readStringUntil('\r');
    client.println("HTTP/1.1 200 OK\n");
    client.print(F("Device name set to: "));
    client.print(deviceName);
  }
  client.print(EOL);    //char terminator
}


