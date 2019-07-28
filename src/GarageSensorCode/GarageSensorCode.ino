#define BLUE 3
#define GREEN 5
#define RED 6

#include "SR04.h"
#define TRIG_PIN 10
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

int buzzer = 12;//the pin of the active buzzer

void setup() {
  // put your setup code here, to run once: modified

pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);

Serial.begin(9600);
delay(1000);

pinMode(buzzer,OUTPUT);
}

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void loop() {
a=sr04.Distance();

if(a < 203){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  for(int i=0;i<3;i++){
    digitalWrite(buzzer,HIGH);
    delay(80);
    digitalWrite(buzzer,LOW);
  }
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
}
else if(a < 226){
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(buzzer,LOW);
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
}
else if(a < 508){
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
}
else{
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
}


}
