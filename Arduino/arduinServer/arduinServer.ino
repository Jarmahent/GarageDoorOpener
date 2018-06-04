#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);

const char* ssid = "Hernandez2.4Ghz";
const char* password = "leoht777";
int pin0 = 5;
int pin1 = 4;
int pin2 = 0;
int pin3 = 14;

String webPage = "";
void setup() {
  
  webPage += 
  "<h1>ESP8266 Web Server</h1>"
  "<p>Relay Switch"
  "<a href='socket1Fwd'>"
  "<button>FORWARD</button>"
  "</a>&nbsp;"
  "<a href='socket1Bkwd'>"
  "<button>BACKWARDS</button>"
  "</a>&nbsp;"
  "<a href='pinOn'>"
  "<button>ON</button>"
  "</a>&nbsp;"
  "<a href='socket1Rgt'>"
  "<button>RIGHT</button>"
  "</a>&nbsp;"
  "<a href='pinOff'>"
  "<button>OFF</button>"
  "</a>"
  "</p>";

  pinMode(pin0, OUTPUT);
  digitalWrite(pin0, LOW);

  pinMode(pin1, OUTPUT);
  digitalWrite(pin0, LOW);

  pinMode(pin2, OUTPUT);
  digitalWrite(pin0, LOW);

  pinMode(pin3, OUTPUT);
  digitalWrite(pin3, LOW);
  
  
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while( WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
     }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  if(mdns.begin("Esp8266", WiFi.localIP())){
      Serial.println("MDNS Responder started");
    }

  server.on("/", [](){
      server.send(200, "text/html", webPage);
    }); 
  server.on("/socket1Fwd", [](){
      server.send(200, "text/html", webPage);
      digitalWrite(pin0, HIGH);
      delay(500);
      digitalWrite(pin0, LOW);
      Serial.println("FORWARD");
      delay(500);
    });
  server.on("/socket1Bkwd", [](){
      server.send(200, "text/html", webPage);
      digitalWrite(pin1, HIGH);
      delay(500);
      digitalWrite(pin1, LOW);
      Serial.println("BACKWARDS");
      delay(500);
    });
  server.on("/pinOn", [](){
      server.send(200, "text/html", webPage);
      digitalWrite(pin2, HIGH);
      Serial.println(" STEER LEFT");
      delay(500);
    });
  server.on("/socket1Rgt", [](){
      server.send(200, "text/html", webPage);
      digitalWrite(pin3, HIGH);
      Serial.println(" STEER RIGHT ");
      delay(500);
    });
  server.on("/pinOff", [](){
      server.send(200, "text/html", webPage);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      Serial.println(" POINTING STRAIGHT ");
      delay(500);
    });      
  server.begin();
  Serial.println("HTTP Server started");

}

int value = 0;


void loop() {
   server.handleClient();

}
