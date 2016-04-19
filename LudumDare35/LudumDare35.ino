#include "WS2812.h"
#include "Pieces.h"
#include "Matrix.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define DELAY 32

//Variables
//byte RGB[768];//take your number of LEDs and multiply by 3
byte RGB[768] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Color color;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned long elapsedTime = 0;
unsigned long lastDelay = 0;
Piece * testPiece;
Matrix * testMatrix;

int count = 0;

//Initialization
void setup() 
{            
  char c, r, x, y;
                
  pinMode(WS2812_pin, OUTPUT);
  
  //player 1 (left player)

  //red
  pinMode(38,INPUT);
  //yellow
  pinMode(39,INPUT);

  //down
  pinMode(40,INPUT);
  //right
  pinMode(41,INPUT);
  //up
  pinMode(42,INPUT);
  //left
  pinMode(43,INPUT);
 

  
  // player 2 (right player)
  //yellow
  pinMode(46,INPUT);
  //left
  pinMode(47,INPUT);
  //down
  pinMode(48,INPUT);
  //red
  pinMode(49,INPUT);
  //right
  pinMode(50,INPUT);
  //up
  pinMode(51,INPUT);
  
  Serial.begin(9600);
  testPiece = makeT(5, 5, testPiece);
  testMatrix = makeMatrix(color);
  
}//setup


void loop() 
{
  currentTime = millis();
  elapsedTime = currentTime - lastTime;
  lastTime = currentTime;

  if (digitalRead(49) == LOW)
  {
    rotatePieceCCW(testPiece);
  }
  else if (digitalRead(46) == LOW)
  {
    rotatePieceCW(testPiece);
  } 

  if (digitalRead(47) == LOW)
  {
    testPiece->x --;
  }

  if (digitalRead(50) == LOW)
  {
    testPiece->x ++;
  }

  updateMatrix(testMatrix, testPiece, elapsedTime);

  color.longColor = 0x000000FF;
  drawRect(0, 0, 16, 16, color);
  drawMatrix(RGB, testMatrix);
  drawPiece(RGB, testPiece);
  RGB_update(-1,0,0,0);//LED#, RED, GREEN, BLUE
  lastDelay = (elapsedTime - lastDelay > DELAY) ? 0 : (DELAY - elapsedTime + lastDelay);
  delay(lastDelay);
}//loop 
