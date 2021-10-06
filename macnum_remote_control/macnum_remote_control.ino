#include <MePS2.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeMegaPiDCMotor motor3(PORT3B);
MeMegaPiDCMotor motor4(PORT4B);

MeMegaPiDCMotor motor_11(11);
MeMegaPiDCMotor motor_12(12);
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeEncoderOnBoard Encoder_3(SLOT3);
MeEncoderOnBoard Encoder_4(SLOT4);

float speed = 0;
float CRR_x = 0;
float CRR_y = 0;
float CRL_x = 0;
float CRL_y = 0;
float  DCmotor1 = 0,DCmotor2 = 0, DCmotor3 = 0,DCmotor4 = 0;


MePS2 MePS2(PORT_15);
void move(int direction, int speed){
  if(direction == 1){        //backward
    DCmotor1 = -speed;
    DCmotor2 = -speed;
    DCmotor3 = speed;
    DCmotor4 = speed;
  }else if(direction == 2){ //forward
    DCmotor1 = speed;
    DCmotor2 = speed;
    DCmotor3 = -speed;
    DCmotor4 = -speed;
  }else if(direction == 3){ //left
    DCmotor1 = -speed;
    DCmotor2 = -speed;
    DCmotor3 = -speed;
    DCmotor4 = -speed;
  }else if(direction == 4){ //right
    DCmotor1 = speed;
    DCmotor2 = speed;
    DCmotor3 = speed;
    DCmotor4 = speed;
  }
  motor1.run(DCmotor1);
  motor2.run(DCmotor2);
  motor3.run(DCmotor3);
  motor4.run(DCmotor4);
}

void Contro(){
  if(MePS2.ButtonPressed(1)){   //R1
    speed = 250;
  }
  else if(MePS2.ButtonPressed(5)){   //L1
    speed = 40;
  }
  else{
    speed = 60;
  }

  if(MePS2.ButtonPressed(14)){    //↑
    move(2,speed / 100.0 * 255);
  }
  else if(MePS2.ButtonPressed(15)){ //↓
    move(1,speed / 100.0 * 255);
  }
  else if(MePS2.ButtonPressed(16)){ //←
    move(3,speed / 100.0 * 255);
  }
  else if(MePS2.ButtonPressed(17)){ //→
    move(4,speed / 100.0 * 255);
  }
  else{
  motor1.run(0);
  motor2.run(0);
  motor3.run(0);
  motor4.run(0);
  }
}

void isr_process_encoder1(void){
  if(digitalRead(Encoder_1.getPortB()) == 0){
    Encoder_1.pulsePosMinus();
  }else{
    Encoder_1.pulsePosPlus();
  }
}

void isr_process_encoder2(void){
  if(digitalRead(Encoder_2.getPortB()) == 0){
    Encoder_2.pulsePosMinus();
  }else{
    Encoder_2.pulsePosPlus();
  }
}

void isr_process_encoder3(void){
  if(digitalRead(Encoder_3.getPortB()) == 0){
    Encoder_3.pulsePosMinus();
  }else{
    Encoder_3.pulsePosPlus();
  }
}

void isr_process_encoder4(void){
  if(digitalRead(Encoder_4.getPortB()) == 0){
    Encoder_4.pulsePosMinus();
  }else{
    Encoder_4.pulsePosPlus();
  }
}

void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void Controler(void){
  CRL_x = MePS2.MeAnalog(2);
  CRL_y = MePS2.MeAnalog(4);
  CRR_x = MePS2.MeAnalog(6);
  CRR_y = MePS2.MeAnalog(8);
  
  if(CRR_x>0){
    /*Right*/
    move(4,abs(CRR_x) / 100.0 * 255);
  }
  else if(CRR_x<0){
    /*Left*/
    move(3,abs(CRR_x) / 100.0 * 255);
  }
  else if(CRL_y>0){
    /*Up*/
    move(2,CRL_y / 100.0 * 255);
  }
  else if(CRL_y<0){
    /*down*/
    move(1,abs(CRL_y) / 100.0 * 255);
  }
}

void setup() {
  MePS2.begin(115200);
  Serial.begin(115200);
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  attachInterrupt(Encoder_3.getIntNum(), isr_process_encoder3, RISING);
  attachInterrupt(Encoder_4.getIntNum(), isr_process_encoder4, RISING);
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
  speed = 0;
}

void _loop() {
  MePS2.loop();
  Encoder_1.loop();
  Encoder_2.loop();
}

void loop() {
  Contro();
  Controler();  
  _loop();
} 
