#include "Pieces.h"
#include "WS2812.h"
#include "Matrix.h"
#include <stdlib.h>

Matrix::Matrix(Color bgColor)
{
  char r, c;
  Color color;

  color.longColor = 0x202020FF;
  
  bgColor = bgColor;
  pieceColor = color;
  fastTime = DELAY;
  normalTime = DELAY * 6;
  currentMoveDelay = 0;

  dropTime = normalTime;

  for (c = 0; c < MATRIX_WIDTH; c++)
  {
    for (r = 0; r < MATRIX_HEIGHT; r++)
    {
      matrix[r][c] = 0;
    }
  }

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
    Serial.println("Landing!");
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
  char r, c, x, y, dx=0, rotated=0;
  //Check inputs to move
  if (redPressed)
  {
    currentPiece->rotateCCW();
    rotated=-1;
  }
  else if (yellowPressed)
  {
    currentPiece->rotateCW();
    rotated=1;
  }

  if (digitalRead(47) == LOW)
  {
    currentMoveDelay += elapsedTime;
    if (currentMoveDelay >= moveDelay)
    {
      currentMoveDelay = 0;
      dx --;
    }
  }

  if (digitalRead(50) == LOW)
  {
    currentMoveDelay += elapsedTime;
    if (currentMoveDelay >= moveDelay)
    {
      currentMoveDelay = 0;
      dx ++;
    }
  }

  if (digitalRead(48) == LOW)
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

  if(checkSideCollisions())
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
  char cleared = 0, y, x;

  for (y = MATRIX_HEIGHT - 1; y >= 0; y--)
  {
    if (cleared)
    {
      for (x = 0; x < MATRIX_WIDTH; x++)
      {
        matrix[y + cleared][x] = matrix[y][x];
      }
    }
    
    cleared += checkLine(y);
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

  Color color;
  color.longColor = 0x202020FF;

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

  currentPiece->draw(pixels);
}











