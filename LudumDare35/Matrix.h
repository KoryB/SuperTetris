#ifndef _MATRIX_H_
#define _MATRIX_H_

#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH 10
#define MATRIX_X 3
#define MATRIX_Y 0
#define DELAY 32

class Matrix
{
  public:
    Matrix(Color bgColor, byte (* inputs)[6][4]);

    byte checkPieceAllowed(Piece * piece);
    byte checkSideCollisions();
    byte isFilled(char x, char y);
    byte isLanding(char x, char y);
    byte checkLanding(Piece * piece);
    byte clearLines();
    byte checkLine(char y);
    byte checkLineOther(char y);
    byte doClear(char y, char cleared);
    void storePiece();
    byte update(unsigned long elapsedTime);
    void draw(byte * pixels);
  
    byte matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    Color bgColor;
    Color pieceColor;
  
    unsigned long currentTime;
    unsigned long fastTime;
    unsigned long normalTime;
    unsigned long dropTime;
    unsigned long const moveDelay = DELAY;
    unsigned long const initialMoveDelay = DELAY*3;
    unsigned long currentMoveDelay;

    byte (* inputs)[6][4];

    Piece * currentPiece;
    Piece * nextPiece;

    Matrix * otherMatrix;
  
};

#endif
