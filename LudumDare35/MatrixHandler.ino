#include "Pieces.h"

#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH 12

typedef struct Matrix
{
  byte matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
  
  char x;
  char y;
} Matrix;

byte checkPieceAllowed(Matrix * matrix, Piece * piece); //Returns 1 if not blocked, assumes origin is this matrix's pos
byte clearRows(Piece * piece); //The piece last placed
void storePiece(Piece * piece);

byte checkPieceAllowed(Matrix * matrix, Piece * piece)
{
  char c, r, x, y;
  
  for (x = piece->x, c = 0; x < piece->x + piece->frameWidth; x++, c++)
  {
    for (y = piece->y, r = 0; y < piece->y + piece->frameHeight; y++, r++)
    {
      if (piece->frames[r*piece->frameWidth + c] )
      {
        setPixel(x, y, color);
      }
    }
  }

  return 1;
}

