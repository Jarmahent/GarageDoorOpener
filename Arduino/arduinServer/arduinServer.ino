#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);

const char* ssid = "Hernandez2.4Ghz";
const char* password = "leoht777";
 
const int trigPin = 5;
const int echoPin = 4;

long duration;
int distance;

String webPage = "";



int getDistance(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  
  return distance;
  }

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
  server.on("/pinOn", [](){
      server.send(200, "text/html", webPage);
//      digitalWrite(pin2, HIGH);
      int actualDistance = getDistance();
      Serial.println(actualDistance);
      Serial.println("Light ON");
      delay(500);
    });
  server.on("/pinOff", [](){
      server.send(200, "text/html", webPage);
//      digitalWrite(pin2, LOW);
//      digitalWrite(pin3, LOW);
      Serial.println("Light OFF");
      delay(500);
    });      
  server.begin();
  Serial.println("HTTP Server started");

}


void loop() {
   server.handleClient();
  int actualDistance = getDistance();
      Serial.println(actualDistance);
}
