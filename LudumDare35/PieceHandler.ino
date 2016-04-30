#include <stdlib.h>
#include "Pieces.h"

char iFrames[] =
{
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
  
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
  
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

char oFrames[] = 
{ 
    1, 1, 0,
    1, 1, 0,
    0, 0, 0
};

char jFrames[] = 
{
    1, 0, 0,
    1, 1, 1,
    0, 0, 0,
  
    0, 1, 1,
    0, 1, 0,
    0, 1, 0,
  
    0, 0, 0,
    1, 1, 1,
    0, 0, 1,
  
    0, 1, 0,
    0, 1, 0,
    1, 1, 0
};

char lFrames[] = 
{
    0, 0, 1,
    1, 1, 1,
    0, 0, 0,
  
    1, 0, 0,
    1, 0, 0,
    1, 1, 0,
  
    0, 0, 0,
    1, 1, 1,
    1, 0, 0,
  
    1, 1, 0,
    0, 1, 0,
    0, 1, 0
};

char sFrames[] = 
{
    0, 1, 1,
    1, 1, 0,
    0, 0, 0,
  
    0, 1, 0,
    0, 1, 1,
    0, 0, 1,
  
    0, 0, 0,
    0, 1, 1,
    1, 1, 0,
  
    1, 0, 0,
    1, 1, 0,
    0, 1, 0
  
};

char zFrames[] = 
{
    1, 1, 0,
    0, 1, 1,
    0, 0, 0,
  
    0, 0, 1,
    0, 1, 1,
    0, 1, 0,
  
    0, 0, 0,
    1, 1, 0,
    0, 1, 1,
  
    0, 1, 0,
    1, 1, 0,
    1, 0, 0
};

char tFrames[] = 
{
    0, 1, 0,
    1, 1, 1,
    0, 0, 0,
  
    0, 1, 0,
    0, 1, 1,
    0, 1, 0,
  
    0, 0, 0,
    1, 1, 1,
    0, 1, 0,
    
    0, 1, 0,
    1, 1, 0,
    0, 1, 0
};

Piece::Piece(char x, char y, char ox, char oy, pieceType ptype)
{
  this->ox = ox;
  this->oy = oy;
  this->x = x;
  this->y = y;
  this->ptype = ptype;
  index = 0;

  switch(this->ptype)
  {
    case I:
      frames = iFrames;
      frameWidth = IWIDTH;
      frameHeight = IHEIGHT;
      numFrames = PFRAMES;
      break;
    case O:
      frames = oFrames;
      frameWidth = OWIDTH;
      frameHeight = OHEIGHT;
      numFrames = OFRAMES;
      break;
    case J:
      frames = jFrames;
      frameWidth = PWIDTH;
      frameHeight = PHEIGHT;
      numFrames = PFRAMES;
      break;
    case L:
      frames = lFrames;
      frameWidth = PWIDTH;
      frameHeight = PHEIGHT;
      numFrames = PFRAMES;
      break;
    case S:
      frames = sFrames;
      frameWidth = PWIDTH;
      frameHeight = PHEIGHT;
      numFrames = PFRAMES;
    case Z:
      frames = zFrames;
      frameWidth = PWIDTH;
      frameHeight = PHEIGHT;
      numFrames = PFRAMES;
      break;
    case T:
    default:
      frames = tFrames;
      frameWidth = PWIDTH;
      frameHeight = PHEIGHT;
      numFrames = PFRAMES;
      break;
  }
}

Piece::~Piece()
{
//  delete frames;
}

byte Piece::rotateCW()
{
  index++;
  if (index >= numFrames)
  {
    index = 0;
  }

  return index;
}

byte Piece::rotateCCW()
{
  index--;
  if (index < 0)
  {
    index = numFrames - 1;
  }

  return index;
}

void Piece::draw(byte * pixels, Color color)
{
  static char c, r, tx, ty;

  for (tx = ox + x, c = 0; tx < ox + x + frameWidth; tx++, c++)
  {
    for (ty = oy + y, r = 0; ty < oy + y + frameHeight; ty++, r++)
    {
      if (frames[index*frameWidth*frameHeight + r*frameWidth + c])
      {
        setPixel(tx, ty, color);
      }
    }
  }
}

Piece * makeRandomPiece(char x, char y, char ox, char oy)
{
  int choose = random(NUM_PIECES);

  return new Piece(x, y, ox, oy, (pieceType) choose);

  /*switch (choose)
  {
    case IINDEX:
      return new makeI(x, y, piece);
      break;

    case OINDEX:
      return new makeO(x, y, piece);
      break;

    case JINDEX:
      return new makeJ(x, y, piece);
      break;

    case LINDEX:
      return new makeL(x, y, piece);
      break;

    case SINDEX:
      return new makeS(x, y, piece);
      break;

    case ZINDEX:
      return new makeZ(x, y, piece);
      break;

    case TINDEX:
      return new makeT(x, y, piece);
      break;

    default:
      return new makeT(x, y, piece);
      break;    
  }*/
}

