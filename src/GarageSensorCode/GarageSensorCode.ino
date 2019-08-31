//Color constants
#define BLUE 3
#define GREEN 5
#define RED 6
#define OFF -1


//Distance change detection constants
#define INACTIVITY_MILLIS 120000
#define RED_ZONE 69
#define GREEN_ZONE 94
#define BLUE_ZONE 250

#include "SR04.h"
#define TRIG_PIN 10
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
int previousColor = OFF;
unsigned long previousColorChangeMillis;

int buzzer = 12;//the pin of the active buzzer

void setup() {
  // put your setup code here, to run once: modified

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  delay(1000);

  pinMode(buzzer, OUTPUT);


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
    else if((millis() - previousColorChangeMillis) >= INACTIVITY_MILLIS){
      setLightColor(LOW,LOW,LOW);
    }
}

void loop() {
  a = sr04.Distance();
   if(a > 400){
    return;
  }
  
  if (a < RED_ZONE) {
    handleDistanceChange(RED,3);
  }
  else if (a < GREEN_ZONE) {
    handleDistanceChange(GREEN,1);
  }
  else if (a < BLUE_ZONE) {
        handleDistanceChange(BLUE,1);
  }
  else{
    setLightColor(LOW,LOW,LOW);
    previousColor = OFF;
  }
   delay(1000);


}
