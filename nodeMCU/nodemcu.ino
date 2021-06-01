/*  NETPIE ESP8266 basic sample                            */
/*  More information visit : https://netpie.io             */

#include <MicroGear.h>
#include <ESP8266WiFi.h>

//ฝากใส่ username กับ pass wifi ด้วยนะ
const char* ssid     = <WIFI_SSID>;
const char* password = <WIFI_KEY>;

#define APPID   "SocialDistancingEscalator"
#define KEY     "bBdIKogslWHhcGs"
#define SECRET  "2cRbYPdx9Zt1yEy81Nmkxi67b"
#define ALIAS   "NodeMCU"
#define TargrtWeb = "HTML_Web"

WiFiClient client;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
//    Serial.print("Incoming message --> ");
//    msg[msglen] = '\0';
//    Serial.println((char *)msg);

    Serial.print("Incoming message --> ");
    Serial.println(topic);
    Serial.println(" : ");
    char strState[msglen];
    for ( int i=0; i<msglen; i++) {
      strState[i] = (char)msg[i];
      Serial.print((char)msg[i]);
    }
    Serial.println();

    String stateStr = String(strState).subString(0,msglen);

    if (stateStr == "YELLOW") {
      digitalWrite(ledPin,HIGH) /* ไฟเหลืองเปิด ไม่รู้เขียนยังไง */
      digitalWrite(ledPin,LOW) /* ไฟแดงปิด ไม่รู้เขียนยังไง */
    } else if (stateStr == "RED") {
      digitalWrite(ledPin,HIGH) /* ไฟแดงเปิด ไม่รู้เขียนยังไง */
      digitalWrite(ledPin,LOW) /* ไฟเหลืองปิด ไม่รู้เขียนยังไง */
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
        Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();

        /* น่าจะต้องใส่โค้ดการอ่านค่าอะไรซักอย่างจาก senser */

        char msg[128];
        /* เอาค่า +1 หรือ -1 ใส่ msg */
        /* ตัวอย่าง */
//        String data = "+1";
//        data.toCharArray(msg,data.length());
        
        microgear.chat(TargetWeb,msg);
    }
    else {
        Serial.println("connection lost, reconnect...");
        microgear.connect(APPID);
    }
    delay(100);
}
