# ESP8266 GarageDoorOpener
A garage door opener project and how I did it


### Parts to this project:

I chose to use the ESP8266 for the project because of how easy it is to program and it has wifi built in.
So the first thing we must do is create [a webserver on the ESP8266](https://github.com/Jarmahent/GarageDoorOpener/blob/master/Arduino/arduinServer/arduinServer.ino)


## Next to the code we can add a way to check if the garage door is open by using an ultrasonic sensor 

![alt text](https://i.imgur.com/N3APFxb.png "Logo Title Text 1")

## Heres the code to get distance
```c++
 
const int trigPin = 5;
const int echoPin = 4;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Set up complete");
  Serial.begin(38400);
}




int getDistance(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  
  return distance;
  }


void loop() {
  int actualDistance = getDistance();
  Serial.print("Distance: ");
  Serial.println(actualDistance);
  
}
```
