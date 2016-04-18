#include <stdlib.h>

int sign(int x) {
    return (x > 0) - (x < 0);
}

void drawPlayer(Player * p, byte doClear)
{
  byte i, j;
  byte count = 0;
  static Color clearColor;
  
  for(i = p->x; i <= p->x + 4; i++)
  {
    for(j = p->y; j <= p->y + 4; j++)
    {
      //Serial.println(p->mask[i + j * 5]);
      if(p->mask[count])
      {
        if (doClear)
        {
          setPixel(i, j, clearColor);
        }
        else
        {
          setPixel(i, j, p->color);
        }
      }
      count++;
    }
  }
  if(p -> bulletList != NULL)
  {
    drawBullet(p -> bulletList);
  }
}

void drawPlayers(Player * p1, Player * p2)
{
  drawPlayer(p1, 1);
  drawPlayer(p2, 1);
  setBlendMode(ADD_BLEND);
  drawPlayer(p1, 0);
  drawPlayer(p2, 0);
  setBlendMode(NO_BLEND);
  setPixel(p1->x+2, p1->y+2, p1->coreColor);
  setPixel(p2->x+2, p2->y+2, p2->coreColor);
}

void drawBullet(Bullet * b)
{
  setPixel(b->x.pixel, b->y.pixel, b->color);
  if ( b -> nextBullet != NULL)
  {
    drawBullet(b -> nextBullet);
  }
}

void updateBullet(Bullet * b)
{
  b -> x.subShort += b -> dX;
  b -> y.subShort += b -> dY;
  if(b -> x.pixel >= 15 || b -> x.pixel <= 0 || b -> y.pixel >= 15 || b -> y.pixel <= 0)
  {
    b->isDead = 1;
  }
  if(b->nextBullet != NULL)
  {
    updateBullet(b->nextBullet);
  }
}

void updatePlayer(Player * p)
{
  p->oldx = p->x;
  p->oldy = p->y;
  p->oldsubx = p->subx;
  p->oldsuby = p->suby;
    
  p->subx += p->dX;
  p->suby += p->dY;

  if(abs(p->subx) > 255)
  {
    p->subx = 0;
    p->x += 1 * sign(p->dX);
  }

  if(abs(p->suby) > 255)
  {
    p->suby = 0;
    p->y += 1 * sign(p->dY);
  }

  if(255 - p->suby <= p->dY)
  {
    p->suby = 0;
    p->y++;
  }
  else
  {
  }

  if (p->x > 11)
  {
    p->x = p->oldx;
    p->subx = p->oldsubx;
  }

  if (p->y > 11)
  {
    p->y = p->oldy;
    p->suby = p->oldsuby;
  }
  
  if(p->bulletList)
  {
    if(!p->bulletList->isDead)
    {
      updateBullet(p->bulletList);
    }
    else
    {
      Bullet * tempPtr = p->bulletList->nextBullet;
      free(p->bulletList);
      p->bulletList = NULL;
      p->bulletList = tempPtr;
    }
  }
}

byte checkHitPlayerBullet(Player * p, Bullet * b)
{
  static byte r, c;
  if (b->isDead)
  {
    return 0;
  }
  if (b->x.pixel >= p->x && (r = b->x.pixel - p->x) <= 4)
  {
    if (b->y.pixel >= p->y && (c = b->y.pixel - p->y) <= 4)
    {
      if (p->mask[5*r + c])
      {
        p->mask[5*r + c] = 0;
        b->isDead = 1;
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }
}

void playerShootBullet(Player * p)
{
  Bullet * b = (Bullet *)malloc(sizeof(Bullet));
  if(b == 0)
  {
    Serial.println("Could not create room for new bullet!");
  }
  else
  {
    b->x.subShort = 0.0f;
    b->y.subShort = 0.0f;
    b->x.pixel = p->x + 2;
    b->y.pixel = p->y + 2;
    b->dX = 0;
    b->dY = -127;
    b->nextBullet = NULL;
    b->color = p->coreColor;
    b->isDead = 0;
    addBullet(&(p->bulletList), b);
  }
}

void addBullet(Bullet ** bList, Bullet * b)
{
  while(*bList != NULL)
  {
    bList = &((*bList) -> nextBullet);
  }
  (*bList) = b;
}

void rotatePlayer(Player * p)
{
  byte i, j;
  byte tempArray[25]; 
  for(i = 0; i < 5; i++)
  {
    for(j = 0; j < 5; j++)
    {
      tempArray[j + (-i + 4) * 5]  = p->mask[i + j * 5];
    }
  }
  memcpy(p->mask, tempArray, 25);
}

void drawEnemy(Enemy * e)
{
  byte i, j;
  byte count = 0;
  
  for(j = e->y; j <= e->y + 3; j++)
  {
    for(i = e->x; i <= e->x + 3; i++)
    {
      if(e->mask[count])
      {
        setPixel(i, j, e->color);
      }
      count++;
    }
  }
  if(e -> bulletList != NULL)
  {
    drawBullet(e -> bulletList);
  }
}

