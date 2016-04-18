#include <stdlib.h>
#include "Pieces.h"

char iFrames[] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
  
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
  
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

char oFrames[] = 
{ 
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
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
  
    0, 1, 0,
    0, 1, 1,
    0, 0, 1,
  
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

Piece * makeI(char x, char y, Piece * piece)
{
  piece->ptype = I;
  piece->frames = iFrames;
  piece->frameWidth = IWIDTH;
  piece->frameHeight = IHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeO(char x, char y, Piece * piece)
{
  piece->ptype = O;
  piece->frames = oFrames;
  piece->frameWidth = OWIDTH;
  piece->frameHeight = OHEIGHT;
  piece->numFrames = OFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeJ(char x, char y, Piece * piece)
{
  piece->ptype = J;
  piece->frames = jFrames;
  piece->frameWidth = PWIDTH;
  piece->frameHeight = PHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeL(char x, char y, Piece * piece)
{
  piece->ptype = L;
  piece->frames = lFrames;
  piece->frameWidth = PWIDTH;
  piece->frameHeight = PHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeS(char x, char y, Piece * piece)
{
  piece->ptype = S;
  piece->frames = sFrames;
  piece->frameWidth = PWIDTH;
  piece->frameHeight = PHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeZ(char x, char y, Piece * piece)
{
  piece->ptype = Z;
  piece->frames = zFrames;
  piece->frameWidth = PWIDTH;
  piece->frameHeight = PHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeT(char x, char y, Piece * piece)
{
  piece->ptype = T;
  piece->frames = tFrames;
  piece->frameWidth = PWIDTH;
  piece->frameHeight = PHEIGHT;
  piece->numFrames = PFRAMES;
  piece->index = 0;
  piece->x = x;
  piece->y = y;

  return piece;
}

Piece * makeRandom(char x, char y, Piece * piece)
{
  int choose = random(NUM_PIECES);

  switch (choose)
  {
    case IINDEX:
      return makeI(x, y, piece);
      break;

    case OINDEX:
      return makeO(x, y, piece);
      break;

    case JINDEX:
      return makeJ(x, y, piece);
      break;

    case LINDEX:
      return makeL(x, y, piece);
      break;

    case SINDEX:
      return makeS(x, y, piece);
      break;

    case ZINDEX:
      return makeZ(x, y, piece);
      break;

    case TINDEX:
      return makeT(x, y, piece);
      break;

    default:
      return makeT(x, y, piece);
      break;    
  }
}

byte rotatePieceCW(Piece * piece)
{
  piece->index++;
  if (piece->index >= piece->numFrames)
  {
    piece->index = 0;
  }
}

byte rotatePieceCCW(Piece * piece)
{
  piece->index--;
  if (piece->index < 0)
  {
    piece->index = piece->numFrames - 1;
  }
}

void drawPiece(byte * pixels, Piece * piece)
{
  static char c, r, x, y;
  Color color;
  color.longColor = 0x202020FF;

  for (x = piece->ox + piece->x, c = 0; x < piece->ox + piece->x + piece->frameWidth; x++, c++)
  {
    for (y = piece->oy + piece->y, r = 0; y < piece->oy + piece->y + piece->frameHeight; y++, r++)
    {
      if (piece->frames[piece->index*piece->frameWidth*piece->frameHeight + r*piece->frameWidth + c])
      {
        setPixel(x, y, color);
      }
    }
  }
}

