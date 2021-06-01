/*  NETPIE ESP8266 basic sample                            */
/*  More information visit : https://netpie.io             */
#include <Arduino.h>
#include <MicroGear.h>
#include <ESP8266WiFi.h>
//#include<ArduinoBearSSL.h>

//ฝากใส่ username กับ pass wifi ด้วยนะ
const char* ssid     = "a";
const char* password = "00000000";

#define APPID   "SocialDistancingEscalator"
#define KEY     "bBdIKogslWHhcGs"
#define SECRET  "2cRbYPdx9Zt1yEy81Nmkxi67b"
#define ALIAS   "NodeMCU"
#define TargetWeb "HTML_web"

WiFiClient client;

MicroGear microgear(client);

int8_t isFull = 0;
int8_t out;

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    char strState[msglen];
    for ( int i=0; i<msglen; i++) {
      strState[i] = (char)msg[i];
    }

    String stateStr = String(strState).substring(0,msglen);
    
    if (stateStr == "YELLOW") {
      Serial.println("Y");
      delay(100);
      isFull = 0;
    }
    else if (stateStr == "RED") {
      Serial.println("R");
      delay(50);
      isFull = 1;
   }
}


/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}

void setup() {
    /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}

void loop() {
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        //Serial.println("cnct");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();

        /* น่าจะต้องใส่โค้ดการอ่านค่าอะไรซักอย่างจาก senser */
        
        /*char test[2];
        test[0] = '+';
        test[1] = '1';
        //microgear.publish("/test","1");
        microgear.chat(TargetWeb,test);*/
        
        if (Serial.available()) {
          //Serial.println("still connect");
          int data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd
          //if (isFull==0 && data_rcvd == 1) {
          if (data_rcvd == 1) {
              //Serial.write(1);
              delay(50);
              //Serial.println("get 1");
              delay(50);
              // เอาค่า +1 หรือ -1 ใส่ msg
              // ตัวอย่าง
              char msg[10];
              msg[0] = '+';
              msg[1] = '1';  
              microgear.chat(TargetWeb,msg);
          }
          else if (data_rcvd == 11) {
              delay(50);
              //Serial.println("get -1");
              delay(50);
              char msg[10];
              msg[0] = '-';
              msg[1] = '1';  
              if (isFull == 1) isFull = 0;
              microgear.chat(TargetWeb,msg);
          }
          //else {
            //while (!Serial.available());
            //if (isFull == 0) Serial.write(8);
            if (isFull == 1){
              out = 9;
              Serial.write(9);
            }
          //}
          /*else {
            Serial.write(0);
          }*/
          
        }
        
    }
    else {
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("netpie connection lost");
        }
        else Serial.println("wifi connection lost, reconnect...");
        microgear.connect(APPID);
    }
    //delay(200);
    //delay(1000);
    if (isFull == 1){
      out = 9;
      Serial.write(9);
    }
    delay(500);
}
