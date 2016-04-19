#include "Pieces.h"
#include "Matrix.h"
#include <stdlib.h>

byte checkLanding(struct Matrix * matrix, Piece * piece)
{
  char c, r, x, y;
  

  Serial.println(piece->y, DEC);
  c = 0;
  for (x = piece->x; x < piece->x + piece->frameWidth; x++)
  {
    r = 0;
    for (y = piece->y; y < piece->y + piece->frameHeight; y++)
    {
      if (isLanding(matrix, x, y) && piece->frames[r*piece->frameWidth + c])
      {
        return 1;
      }
      r++;
    }
    c++;
  }
  return 0;
}

byte isLanding(struct Matrix * matrix, char c, char r)
{
  if (r >= MATRIX_HEIGHT)
  {
    Serial.println("Landing!");
    return 1;
  }

  return matrix->matrix[r][c];
}

byte isValidPosition(Matrix * matrix, char x, char y)
{
  if (x < MATRIX_X || x >= MATRIX_X + MATRIX_WIDTH)
  {
    return 0;
  }
  return 1;
}

byte updateMatrix(Matrix * matrix, Piece * piece, unsigned long elapsedTime)
{
  char r, c, x, y;
  //Check inputs to move
  //Check side collisions
  //Check drop
  matrix->currentTime += elapsedTime;

  if (matrix->currentTime >= matrix->normalTime)
  {
    matrix->currentTime = 0;
    
    piece->y += 1;
    
    if (checkLanding(matrix, piece))
    {
      Serial.println("Landed!");
      piece->y -= 1;
      storePiece(matrix, piece);
    }
  }
  //Check fall store
  //Check clear lines
}

void storePiece(Matrix * matrix, Piece * piece)
{
  char c, r, x, y;
  
  for (x = piece->x, c = 0; x < piece->x + piece->frameWidth; x++, c++)
  {
    for (y = piece->y, r = 0; y < piece->y + piece->frameHeight; y++, r++)
    {
      if (piece->frames[r*piece->frameWidth + c])
      {
        matrix->matrix[y][x] = 1;
      }
    }
  }
}

Matrix * makeMatrix(Color bgColor)
{
  Matrix * matrix = (Matrix * ) calloc(1, sizeof(Matrix));
  Color color;

  color.longColor = 0x202020FF;
  
  matrix->bgColor = bgColor;
  matrix->pieceColor = color;
  matrix->fastTime = 500;
  matrix->normalTime = 500;

  return matrix;
}

void drawMatrix(byte * pixels, Matrix * matrix)
{
  char x, y;

  Color color;
  color.longColor = 0x202020FF;

  drawRect(0, 0, 16, 16, color);

//  for (x = MATRIX_X; x < MATRIX_X + MATRIX_WIDTH; x++)
//  {
//    for (y = MATRIX_Y; y < MATRIX_Y + MATRIX_HEIGHT; y++)
//    {
//      if (matrix->matrix[y - MATRIX_Y][x - MATRIX_X])
//      {
//        setPixel(x, y, matrix->pieceColor);
//      }
//    }
//  }
}











