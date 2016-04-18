#include "WS2812.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//Variables
//byte RGB[768];//take your number of LEDs and multiply by 3
byte RGB[768] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int count = 0;
int count2 = 0;
Color color;
Player player;
Player player2;
Bullet testBullet;
Enemy testEnemy;
Bullet tempBullet;

//Initialization
void setup() 
{  
  byte player1Mask[25] =  {0, 0, 1, 0, 0, 
                           0, 0, 1, 0, 0,
                           1, 1, 0, 1, 1,
                           0, 1, 1, 1, 0,
                           0, 1, 1, 1, 0};
  byte player2Mask[25] =  {0, 0, 1, 0, 0, 
                           0, 1, 1, 1, 0,
                           1, 1, 0, 1, 1,
                           0, 1, 1, 1, 0,
                           0, 0, 1, 0, 0};
  byte testEnemyMask[16] = {1, 1, 1, 0,
                            0, 1, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                           
  pinMode(WS2812_pin, OUTPUT);
  
  Serial.begin(9600);
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 261;//651;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  // enable global interrupts:
  sei();
  color.longColor = 0x00100000;
  player.x = 10;
  player.y = 7;
  player.subx = 0;
  player.suby = 0;
  player.dX = 127;
  player.dY = 127;
  player.color = color;
  player.coreColor.longColor = 0x10101010;
  player.bulletList = NULL;

  player2.x = 7;
  player2.y = 7;
  player2.subx = 0;
  player2.suby = 0;
  player2.dY = -127;
  player2.dX = -127;
  player2.coreColor.longColor = 0x10101010;
  player2.color.longColor = 0x10000000;
  player2.bulletList = NULL;

  testEnemy.x = 1;
  testEnemy.y = 0;
  testEnemy.color.longColor = 0x10000000;
  testEnemy.bulletList = NULL;
  
  memcpy(player.mask, player1Mask, 25);
  memcpy(player2.mask, player2Mask, 25);
  memcpy(testEnemy.mask, testEnemyMask, 16);
  
  for(int i = 0; i < 25; i++)
  {
    //Serial.println(player.mask[i]);
  }
  testBullet.x.subShort = 0x0500;
  testBullet.y.subShort = 0x0100;
  testBullet.dX = 127;
  testBullet.dY = 127;
  color.longColor = 0x00101000;
  testBullet.color = color;
  testBullet.isDead = 0;
}//setup


void loop() 
{
  
  count++;
  count2++;
  if (count == 10)
  {
    if (! testBullet.isDead)
    {
      updateBullet(&testBullet);
    }
    
    updatePlayer(&player);
    updatePlayer(&player2);
    checkHitPlayerBullet(&player, &testBullet);
    checkHitPlayerBullet(&player2, &testBullet);
    color.longColor = 0x02020002;
    fillScreen(color);
    drawPlayers(&player, &player2);
    if (! testBullet.isDead)
    {
      drawBullet(&testBullet);
    }
    drawEnemy(&testEnemy);
    color.longColor = 0x0f000000;
    RGB_update(-1,0,0,0);//LED#, RED, GREEN, BLUE
    
    
    count = 0;
  }
  if (count2 == 30)
  {
    playerShootBullet(&player);
    playerShootBullet(&player2);
    rotatePlayer(&player);
    testEnemy.x++;
    if(testEnemy.x >= 15)
    {
      testEnemy.x = 0;
    }
    count2 = 0;
  }
  delay(20);
}//loop

ISR(TIMER1_COMPA_vect)
{ 
}
