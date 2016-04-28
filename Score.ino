#include <stdlib.h>
#include <stdbool.h>
void calcDisplayedScore(int score, int playerNum)
{
int tempScore = score;
bool _500kUnit = false;
int _100kUnits = 0;
int _10kUnits = 0;
bool _50kUnit = false;
int _1kUnits = 0;
bool _5kUnit = false;
int _100Units = 0;
bool _500Unit = false;
int _10Units = 0;
bool _50Unit = false;
int _1Units = 0;
bool _5Unit = false;

  if(tempScore%500000 == 1)
  {
    tempScore-=500000;
    _500kUnit = true;
  }
  while(tempScore%100000 == 1)
  {
    tempScore -=100000;
    _100kUnits++;
  }
  if(tempScore%50000 == 1)
  {
    tempScore-=50000;
    _50kUnit = true;
  }
  while(tempScore%10000 == 1)
  {
    tempScore -=10000;
    _10kUnits++;
  }
  if(tempScore%5000 == 1)
  {
    tempScore-=5000;
    _5kUnit = true;
  }
  while(tempScore%1000 == 1)
  {
    tempScore -=1000;
    _1kUnits++;
  }
  if(tempScore%500 == 1)
  {
    tempScore-=500;
    _500Unit = true;
  }
  while(tempScore%100 == 1)
  {
    tempScore -=100;
    _100Units++;
  }
  if(tempScore%50 == 1)
  {
    tempScore-=50;
    _50Unit = true;
  }
  while(tempScore%10 == 1)
  {
    tempScore -=10;
    _10Units++;
  }
  if(tempScore%5 == 1)
  {
    tempScore-=5;
    _5Unit = true;
  }
  while(tempScore%1 == 1)
  {
    tempScore -=1;
    _1Units++;
  }
  drawScore(playerNum, 3, _100kUnits, _500kUnit, selectColor(5));
  drawScore(playerNum, 5, _10kUnits, _50kUnit, selectColor(4));
  drawScore(playerNum, 7, _1kUnits, _5kUnit, selectColor(3));
  drawScore(playerNum, 9, _100Units, _500Unit, selectColor(2));
  drawScore(playerNum, 11, _10Units, _50Unit, selectColor(1));
  drawScore(playerNum, 13, _1Units, _5Unit, selectColor(0));
}

void drawScore(int playerNum, int y, int units, bool _5Unit, Color col)
{
  int i = 0;
  byte x = 0;
  Color mCol = col;

  if(playerNum == 2)
  {
     x=13;
  }

  for(i = 1; i<= 3; i++)
  {
    if(units >=i)
    {
      setPixel((x+2)-i,y+1,mCol);
    }
  }

  for(i=4; i <6; i++)
  {
    if(units>=i)
    {
      setPixel(x+(i-4),y,mCol);
    }
  }
  col.longColor<<1;
  if(_5Unit)
  {
    setPixel(x+2,y,col);
  }
}


Color selectColor(int UnitType)
{
  Color c;
  if(UnitType == 0)
  {
    c.longColor = 0x10000000;
  }
  else if(UnitType == 1)
  {
    c.longColor = 0x00010000;
  }
  else if(UnitType == 2)
  {
    c.longColor = 0x00001000;
  }
  else if(UnitType == 3)
  {
    c.longColor = 0x10100000;
  }
  else if(UnitType == 4)
  {
    c.longColor = 0x10001000;
  }
  else if(UnitType == 5)
  {
    c.longColor = 0x10101000;
  }
  return c;
}



