#ifndef _PIECES_H_
#define _PIECES_H_

#define IWIDTH 4
#define IHEIGHT 4
#define PWIDTH 3
#define PHEIGHT 3
#define OWIDTH 4
#define OHEIGHT 3

#define PFRAMES 4
#define OFRAMES 1

#define IINDEX 0
#define OINDEX 1
#define JINDEX 2
#define LINDEX 3
#define SINDEX 4
#define ZINDEX 5
#define TINDEX 6

#define NUM_PIECES 7

typedef enum {I, O, J, L, S, Z, T} pieceType;

typedef struct Piece
{
  pieceType ptype;
  char * frames;
  char frameWidth;
  char frameHeight;
  char numFrames;
  char index;

  char ox;
  char oy;

  char x;
  char y;
} Piece;

//Makes don't set the origin! Do eet yourself for now
Piece * makeI(char x, char y, Piece * piece);
Piece * makeO(char x, char y, Piece * piece);
Piece * makeJ(char x, char y, Piece * piece);
Piece * makeL(char x, char y, Piece * piece);
Piece * makeS(char x, char y, Piece * piece);
Piece * makeZ(char x, char y, Piece * piece);
Piece * makeT(char x, char y, Piece * piece);
Piece * makeRandom(char x, char y, Piece * piece);
void drawPiece(byte * pixels, Piece * piece);

#endif
