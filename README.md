# Arduino

## Dependencies
Maxbotix (included)  
An Arduino library to read Maxbotix ultrasonic sensors

Arduino Uno WiFi Dev Ed Library (included)  
Library for Arduino Uno WiFi Developer Edition

Arduino IDE for development 
http://www.arduino.org/downloads

## Installation
Setup the WiFi module:
http://www.arduino.org/learning/getting-started/getting-started-with-arduino-uno-wifi  

## Development
1. Install the card Arduino AVR Boards (see the `Screenshots` folder)

2. Open sketch.ino into Arduino IDE and change this line to your server address:  
`#define SERVER_ADDR   "firebaseadmin.herokuapp.com`"

3. Upload the sketch to your device.

## REST Server
Once the Arduino is setup your can change the device name at: `http://<arduinoIP>/arduino/mode/write/:name`  

And in order to check the current name: `http://<arduinoIP>/arduino/mode/read`