/*
 * If you use the serial monitor for debugging remember to ster the baud rate to 115200.
 * The modules are set to only one-way communication. That means that the controller can only transmit and the tank can only receive.
 * If you wish to change this for two-way communication there is plenty of documentation to do so on the internet and in examples.
 * 
 * This program receives the X and Y values and processes it into movement.
 */
#include <SPI.h>  
#include "RF24.h" 
#include <Servo.h>

Servo yaxis;
Servo xaxis;

RF24 myRadio (7, 8); 
struct package
{
  int X=512;
  int Y=512;
  int yarm = 512;
  int xarm = 512;
};

byte addresses[][6] = {"0"}; 
int OUT1 = 5;
int OUT2 = 6;
int OUT3 = 9;
int OUT4 = 10;

int yval = 90;
int xval = 90;

typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  
  yaxis.attach(3);
  xaxis.attach(4);

  
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  analogWrite(OUT1, 0);
  analogWrite(OUT2, 0);
  analogWrite(OUT3, 0);
  analogWrite(OUT4, 0);
}


void loop()  
{
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("X:");
    Serial.print(data.X);
    Serial.print("      Y");
    Serial.println(data.Y);
    int X = data.X;
    int Y = data.Y;
    

    int yarm = data.yarm;
    int xarm = data.xarm;

    
    int foward = map(X,524,1024,0,255);
    int backward = map(X,500,0,0,255);
    int right = map(Y,524,1024,0,255);
    int left = map(Y,500,0,0,255);
    
   
    if(X > 524 && Y < 524 && Y > 500){
      analogWrite(OUT3, foward);
      analogWrite(OUT4, 0);
      analogWrite(OUT1, foward);
      analogWrite(OUT2, 0);
    }else if(X < 500 && Y < 524 && Y > 500){
      analogWrite(OUT4, backward);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, backward);
      analogWrite(OUT1, 0);
    }else if(X < 524 && X > 500 && Y < 524 && Y > 500){
      analogWrite(OUT4, 0);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, 0);
    }else if(X < 524 && X > 500 && Y > 524){
      analogWrite(OUT4, 0);
      analogWrite(OUT3, right);
      analogWrite(OUT2, right);
      analogWrite(OUT1, 0);
    }else if(X < 524 && X > 500 && Y < 500){
      analogWrite(OUT4, left);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, left);
    }

    
      ///////////////////////////////////////////////////
    if (yarm > 600 && yval <180){
      yval = yval-5;
      yaxis.write(yval);
      delay(15); 
    }
    else if (yarm < 400 && yval > 0){
      yval = yval +5;
      yaxis.write(yval);
      delay(15); 
    }

    
    /////////////////////////////////////////////////
    if (xarm > 600 && xval <180){
      xval = xval+5;
      xaxis.write(xval);
      delay(15);    
    }
    else if (xarm < 400 && xval > 0){
      xval = xval -5;
      xaxis.write(xval);
      delay(15); 
    }
    
  }

}
