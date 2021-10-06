#include <MePS2.h>
#include <arduino.h>
#include <MeMegaPi.h>
#include <MeBluetooth.h>
#include <Math.h>
#include <SPI.h>
MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeMegaPiDCMotor motor3(PORT3B);
MeMegaPiDCMotor motor4(PORT4B);

char dir = '0';
int Speed = 255, value=0;
float  DCmotor1 = 0,DCmotor2 = 0, DCmotor3 = 0,DCmotor4 = 0;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial.println("Serial input is OK");
}

void loop()
{
  if (Serial3.available()){
        value = Serial3.read();
        Serial.print(value);
        if (value>100){
          Speed = (value-100)*2.55;
        }
        else{
          dir = char(value);
          Serial.println(dir);
        }
     }
  
  switch(dir){
    case 'W':
      DCmotor1 = Speed;
      DCmotor2 = Speed;
      DCmotor3 = -Speed;
      DCmotor4 = -Speed;
      break;
  
    case 'A':
      DCmotor1 = -Speed;
      DCmotor2 = -Speed;
      DCmotor3 = -Speed;
      DCmotor4 = -Speed;
      break;
  
    case 'S':
      DCmotor1 = -Speed;
      DCmotor2 = -Speed;
      DCmotor3 = Speed;
      DCmotor4 = Speed;
      break;
  
    case 'D':
      DCmotor1 = Speed;
      DCmotor2 = Speed;
      DCmotor3 = Speed;
      DCmotor4 = Speed;
      break;

    case 'E':
      DCmotor1 = -Speed;
      DCmotor2 = Speed;
      DCmotor3 = Speed;
      DCmotor4 = -Speed;
      break;
  
    case 'Q':
      DCmotor1 = Speed;
      DCmotor2 = -Speed;
      DCmotor3 = -Speed;
      DCmotor4 = Speed;
      break;
  
    default:
      DCmotor1 = 0;
      DCmotor2 = 0;
      DCmotor3 = 0;
      DCmotor4 = 0;
      break;
  }
  motor1.run(DCmotor1);
  motor2.run(DCmotor2);
  motor3.run(DCmotor3);
  motor4.run(DCmotor4);
}
