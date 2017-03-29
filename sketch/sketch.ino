#include <UnoWiFiDevEd.h>
#include "Maxbotix.h"

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "firebaseadmin.herokuapp.com"

Maxbotix rangeSensorPW(3, Maxbotix::PW, Maxbotix::LV, Maxbotix::BEST);
Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV, Maxbotix::BEST);

void setup() {
  Serial.begin(9600);
  Ciao.begin(); // CIAO INIT
}
 
void loop() {
  Serial.println("Reading...");
  
  short rangePW = rangeSensorPW.getRange();

  Serial.println("Sending...");

  String uri = "/addRange?name=";
  uri += "Arduino";
  uri += "&range=";
  uri += String(rangePW);
  Serial.println(uri);

  Ciao.println("Send data on Firebase"); 

  CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri);

  if (!data.isEmpty()){
    Ciao.println( "State: " + String (data.get(1)) );
    Ciao.println( "Response: " + String (data.get(2)) );
  }
  else{ 
    Ciao.println("Write Error");
  }    

  delay(30000); // Wait 30 sec

}
