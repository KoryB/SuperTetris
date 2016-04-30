#ifndef _PIECES_H_
#define _PIECES_H_

#define IWIDTH 4
#define IHEIGHT 4
#define PWIDTH 3
#define PHEIGHT 3
#define OWIDTH 3
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

class Piece
{
  public:
    Piece(char x, char y, char ox, char oy, pieceType ptype);
    ~Piece();

    void update();
    void draw(byte * pixels, Color color);
    byte rotateCW();
    byte rotateCCW();
    
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
};

Piece * makeRandomPiece(char x, char y, char ox, char oy);

#endif
