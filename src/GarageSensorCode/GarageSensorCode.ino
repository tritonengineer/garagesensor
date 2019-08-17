#define BLUE 3
#define GREEN 5
#define RED 6
#define OFF -1

#include "SR04.h"
#include <LiquidCrystal.h>
#define TRIG_PIN 10
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
int previousColor = OFF;
unsigned long previousColorChangeMillis;

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

void setBuzzes(int n){
  for(int i=0;i<n;i++){
    digitalWrite(buzzer,HIGH);
    delay(300);
    digitalWrite(buzzer,LOW);
    delay(300);
  }
}

void handleDistanceChange(int color, int buzzNumber){
  if(previousColor != color){
      if(color == RED){
        setLightColor(HIGH,LOW,LOW);
      }
      else if(color == GREEN){
        setLightColor(LOW,HIGH,LOW);
      }
      else if (color == BLUE){
        setLightColor(LOW,LOW,HIGH);
      }
      setBuzzes(buzzNumber);
      previousColor = color;
      previousColorChangeMillis = millis();
    }
    else if((millis() - previousColorChangeMillis) >= 10000){
      setLightColor(LOW,LOW,LOW);
    }
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
    handleDistanceChange(RED,3);
  }
  else if (a < 94) {
    handleDistanceChange(GREEN,1);
  }
  else if (a < 250) {
        handleDistanceChange(BLUE,1);
  }
  else{
    setLightColor(LOW,LOW,LOW);
    previousColor = OFF;
  }

   Serial.print(a);
   Serial.println("cm");
   delay(1000);


}
