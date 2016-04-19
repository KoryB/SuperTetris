#ifndef _MATRIX_H_
#define _MATRIX_H_

#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH 10
#define MATRIX_X 3
#define MATRIX_Y 0

typedef struct Matrix
{
  byte matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
  Color bgColor;
  Color pieceColor;

  unsigned long currentTime;
  unsigned long fastTime;
  unsigned long normalTime;
  
} Matrix;

byte checkPieceAllowed(struct Matrix * matrix, Piece * piece); //Returns 1 if not blocked, assumes origin is this matrix's pos
byte isValidPosition(struct Matrix * matrix, char x, char y);
byte isLanding(struct Matrix * matrix, char x, char y);
byte clearRows(Piece * piece); //The piece last placed
void storePiece(Matrix * matrix, Piece * piece);
byte updateMatrix(Matrix * matrix, Piece * piece, unsigned long elapsedTime);
Matrix * makeMatrix(Color bgColor);
void drawMatrix(byte * pixels, Matrix * matrix);

#endif
