#define BLUE 3
#define GREEN 5
#define RED 6

#include "SR04.h"
#include <LiquidCrystal.h>
#define TRIG_PIN 10
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
String previousColor = "off";

int buzzer = 12;//the pin of the active buzzer

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 13, 4, 2);

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

  pinMode(buzzer, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void setLightColor(int redVal, int greenVal, int blueVal) {
  digitalWrite(RED,redVal);
  digitalWrite(GREEN,greenVal);
  digitalWrite(BLUE,blueVal);
}

void loop() {
  a = sr04.Distance();
   if(a > 400){
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(a);


  if (a < 69) {
    setLightColor(HIGH,LOW,LOW);
    if(!previousColor.equals("red")){
      for(int i=0;i<3;i++){
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer,LOW);
        delay(300);
      }
    }
    previousColor = "red";
  }
  else if (a < 94) {
    setLightColor(LOW,HIGH,LOW);
    if(!previousColor.equals("green")){
      digitalWrite(buzzer,HIGH);
      delay(300);
      digitalWrite(buzzer,LOW);
      delay(300);
    }
    previousColor = "green";
  }
  else if (a < 250) {
    setLightColor(LOW,LOW,HIGH);
    if(!previousColor.equals("blue")){
      digitalWrite(buzzer,HIGH);
      delay(300);
      digitalWrite(buzzer,LOW);
      delay(300);
    }
    previousColor = "blue";
  }
  else{
    setLightColor(LOW,LOW,LOW);
    previousColor = "off";
  }

   Serial.print(a);
   Serial.println("cm");
   delay(1000);


}
