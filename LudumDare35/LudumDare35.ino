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
Matrix * testMatrix;

int count = 0;

byte redPressed = 0, yellowPressed = 0, redDown = 0, yellowDown = 0, redReleased = 0, yellowReleased = 0;

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

  randomSeed(analogRead(A0));
  
  testMatrix = new Matrix(color);
  
}//setup


void loop() 
{
  currentTime = millis();
  elapsedTime = currentTime - lastTime;
  lastTime = currentTime;

  handleInput();

  testMatrix->update(elapsedTime);

  color.longColor = 0x000000FF;
  drawRect(0, 0, 16, 16, color);
  testMatrix->draw(RGB);
  RGB_update(-1,0,0,0);//LED#, RED, GREEN, BLUE
  lastDelay = (elapsedTime - lastDelay > DELAY) ? 0 : (DELAY - elapsedTime + lastDelay);
  delay(lastDelay);
}//loop 

void handleInput()
{
  //TODO: Add button class
  redPressed = yellowPressed = redReleased = yellowReleased = 0;

  if (digitalRead(49) == LOW)
  {
    if (!redDown)
    {
      redPressed = 1;
    }
    redDown = 1;
  }
  else
  {
    if (redDown)
    {
      redReleased = 1;
    }
    redDown = 0;
  }
  
  if (digitalRead(46) == LOW)
  {
    if (!yellowDown)
    {
      yellowPressed = 1;
    }
    yellowDown = 1;
  } 
  else
  {
    if (yellowDown)
    {
      yellowReleased = 1;
    }
    yellowDown = 0;
  }
}

