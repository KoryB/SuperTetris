#include "Pieces.h"
#include "WS2812.h"
#include "Matrix.h"
#include "InputHandler.h"
#include <stdlib.h>

Matrix::Matrix(Color color, byte (* inputs)[6][4])
{
  char r, c;
  
  pieceColor = color;
  fastTime = DELAY;
  normalTime = DELAY * 20;
  currentMoveDelay = 0;

  dropTime = normalTime;

  for (c = 0; c < MATRIX_WIDTH; c++)
  {
    for (r = 0; r < MATRIX_HEIGHT; r++)
    {
      matrix[r][c] = 0;
    }
  }

  this->inputs = inputs;

  currentPiece = makeRandomPiece(MATRIX_WIDTH / 2, 0, MATRIX_X, MATRIX_Y);
  nextPiece = makeRandomPiece(MATRIX_WIDTH / 2, 0, MATRIX_X, MATRIX_Y);
}

byte Matrix::checkLanding(Piece * piece)
{
  char c, r, x, y;
  
  for (x = piece->x, c = 0; x < piece->x + piece->frameWidth; x++, c++)
  {
    r = 0;
    for (y = piece->y, r=0; y < piece->y + piece->frameHeight; y++, r++)
    {
      if (isLanding(x, y) && piece->frames[piece->index*piece->frameWidth*piece->frameHeight + r*piece->frameWidth + c])
      {
        return 1;
      }
    }
  }
  return 0;
}

byte Matrix::isLanding(char c, char r)
{
  if (r >= MATRIX_HEIGHT)
  {
    return 1;
  }

  return matrix[r][c];
}

byte Matrix::checkSideCollisions()
{
  char c, r, x, y;
  
  for (x = currentPiece->x, c = 0; x < currentPiece->x + currentPiece->frameWidth; x++, c++)
  {
    for (y = currentPiece->y, r=0; y < currentPiece->y + currentPiece->frameHeight; y++, r++)
    {
      if (isFilled(x, y) && currentPiece->frames[currentPiece->index*currentPiece->frameWidth*currentPiece->frameHeight + r*currentPiece->frameWidth + c])
      {
        return 1;
      }
    }
  }
  return 0;
}

byte Matrix::isFilled(char x, char y)
{
  if (x < 0 || x >= MATRIX_WIDTH || matrix[y][x])
  {
    return 1;
  }
  return 0;
}

byte Matrix::update(unsigned long elapsedTime)
{
  char r, c, x, y, dx=0, rotated=0, left, right;
  //Check inputs to move
  if ((*inputs)[BRED][PRESS])
  {
    currentPiece->rotateCCW();
    rotated=-1;
  }
  else if ((*inputs)[BYELLOW][PRESS])
  {
    currentPiece->rotateCW();
    rotated=1;
  }

  left = (*inputs)[JLEFT][DOWN];
  right = (*inputs)[JRIGHT][DOWN];

  if (left || right)
  {
    if (currentMoveDelay == 0 || (currentMoveDelay >= initialMoveDelay && currentMoveDelay >= moveDelay))
    {
      currentMoveDelay = initialMoveDelay * (currentMoveDelay != 0);
      
      if (left)
      {
        dx --;
      }
      else
      {
        dx ++;
      }
    }
    
    currentMoveDelay += elapsedTime;
  }
  else
  {
    currentMoveDelay = 0;
  }

  if ((*inputs)[JDOWN][DOWN])
  {
    dropTime = fastTime;
  }
  else
  {
    dropTime = normalTime;
  }

  currentPiece->x += dx;
  
  //Check side collisions for position first, then rotation.
  if(checkSideCollisions())
  {
    currentPiece->x -= dx;
  }

  if(checkSideCollisions() || checkLanding(currentPiece))
  {
    if (rotated == -1)
    {
      currentPiece->rotateCW();
    }
    else if (rotated == 1)
    {
      currentPiece->rotateCCW();
    }
  }
  
  currentTime += elapsedTime;

  if (currentTime >= dropTime)
  {
    currentTime = 0;
    
    currentPiece->y += 1;
    
    if (checkLanding(currentPiece))
    {
      currentPiece->y -= 1;
      storePiece();
      //Check clear lines
      clearLines();

      delete currentPiece;
      currentPiece = nextPiece;
      nextPiece = makeRandomPiece(MATRIX_WIDTH / 2, 0, MATRIX_X, MATRIX_Y);
      
      return 1;
    }
  }
  return 0;
}

byte Matrix::clearLines()
{
  char cleared = 0, clearedOther = 0, y, x;
  static char clearedArray[MATRIX_HEIGHT];
  static char clearedOtherArray[MATRIX_HEIGHT];

  for (y = 0; y < MATRIX_HEIGHT; ++y)
  {
    clearedArray[y] = checkLine(y);

    if (clearedArray[y])
    {
      clearedOtherArray[y] = checkLineOther(y);
    }
    else
    {
      clearedOtherArray[y] = 0;
    }
    
//    Serial.print(clearedOtherArray[y], DEC); Serial.print(", ");
  }

//    Serial.println();
//  Serial.println(clearedOtherArray, DEC);

  for (y = MATRIX_HEIGHT - 1; y >= 0; y--)
  {
    doClear(y, cleared);
    otherMatrix->doClear(y, clearedOther);

    cleared += clearedArray[y];
    clearedOther += clearedOtherArray[y];
  }
}

byte Matrix::doClear(char y, char cleared)
{
  char x;
  
  if (cleared)
  {
    for (x = 0; x < MATRIX_WIDTH; x++)
    {
      matrix[y + cleared][x] = matrix[y][x];
    }
  }
}

byte Matrix::checkLine(char y)
{
  char x;

  for (x = 0; x < MATRIX_WIDTH; x++)
  {
    if (! matrix[y][x])
    {
      return 0;
    }
  }

  return 1;
}

byte Matrix::checkLineOther(char y)
{
  char x, py, px; 

  static byte rowBuffer[MATRIX_WIDTH];

  py = y - currentPiece->y;

  //build buffer
  for (x = 0; x < MATRIX_WIDTH; ++x)
  {
    if (py >= 0 && py < currentPiece->frameHeight)
    {
      px = x - currentPiece->x;
  
      if (px < 0 || px >= currentPiece->frameWidth)
      {
        rowBuffer[x] = 0; 
      }
      else
      {
        rowBuffer[x] = currentPiece->frames[currentPiece->index*currentPiece->frameWidth*currentPiece->frameHeight + py*currentPiece->frameWidth + px];
      }
    }
    else
    {
      rowBuffer[x] = 0;
    }
  }

  for (x = 0; x < MATRIX_WIDTH; ++x)
  {
    if ( !( matrix[y][x] == (otherMatrix->matrix[y][x] | rowBuffer[x]) ) )
    {
      return 0;
    }
  }

  return 1;
}

void Matrix::storePiece()
{
  char c, r, x, y;
  
  for (x = currentPiece->x, c = 0; x < currentPiece->x + currentPiece->frameWidth; x++, c++)
  {
    for (y = currentPiece->y, r = 0; y < currentPiece->y + currentPiece->frameHeight; y++, r++)
    {
      if (currentPiece->frames[currentPiece->index*currentPiece->frameWidth*currentPiece->frameHeight + r*currentPiece->frameWidth + c])
      {
        matrix[y][x] = 1;
      }
    }
  }
}

void Matrix::draw(byte * pixels)
{
  char r, c;

//  drawRect(0, 0, 16, 16, color);

  for (c = 0; c < MATRIX_WIDTH; c++)
  {
    for (r = 0; r < MATRIX_HEIGHT; r++)
    {
      if (matrix[r][c])
      {
        setPixel(c + MATRIX_X, r + MATRIX_Y, pieceColor);
      }
    }
  }

  currentPiece->draw(pixels, pieceColor);
}











