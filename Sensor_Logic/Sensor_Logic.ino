#include <Adafruit_NeoPixel.h>

#define IR_0_PIN 12
#define IR_1_PIN 11
#define IR_2_PIN 10
#define IR_3_PIN 9
#define IR_4_PIN 8
#define IR_5_PIN 7

void setup() {
  //Set Pins to Input
  pinMode(IR_0_PIN, INPUT);
  pinMode(IR_1_PIN, INPUT);
  pinMode(IR_2_PIN, INPUT);
  pinMode(IR_3_PIN, INPUT);
  pinMode(IR_4_PIN, INPUT);
  pinMode(IR_5_PIN, INPUT);

  //Activate Pull-Up Resistance
  digitalWrite(IR_0_PIN, HIGH);
  digitalWrite(IR_1_PIN, HIGH);
  digitalWrite(IR_2_PIN, HIGH);
  digitalWrite(IR_3_PIN, HIGH);
  digitalWrite(IR_4_PIN, HIGH);
  digitalWrite(IR_5_PIN, HIGH);
  
  Serial.begin(9600);
}

int checkSensors(){
  int ir_0 = digitalRead(IR_0_PIN);
  int ir_1 = digitalRead(IR_1_PIN);
  int ir_2 = digitalRead(IR_2_PIN);
  int ir_3 = digitalRead(IR_3_PIN);
  int ir_4 = digitalRead(IR_4_PIN);
  int ir_5 = digitalRead(IR_5_PIN);

  if(ir_0 == LOW){
    return 0;
  }
  else if(ir_1 == LOW){
    return 1;
  }
  else if(ir_2 == LOW){
    return 2;
  }
  else if(ir_3 == LOW){
    return 3;
  }
  else if(ir_4 == LOW){
    return 4;
  }
  else if(ir_5 == LOW){
    return 5;
  }
  else
  {
    return -1;
  }
}

void loop() {

  int trippedSensor = checkSensors();

  if(trippedSensor != -1){
    //Send sensor data
  }
  
  
}
