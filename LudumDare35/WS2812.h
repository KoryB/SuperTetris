//VARIABLES AND DEFINES HERE - NEEDED BY THE WS2812 DRIVER CODE
#define WS2812_pin 53 // only digital pin 8 works right now
#define NUM_LEDS (256)// total number of RGB LEDs
#define NO_BLEND 0
#define ADD_BLEND 1

//Unions and structs
typedef union Color 
{
  unsigned long longColor;
  struct{
    byte a,b,g,r;
  } rgb;
} Color;

typedef union SubPixel 
{
  struct
  {
    byte sub;
    byte pixel;
  };
  unsigned short subShort;
} SubPixel;

typedef struct Bullet
{
  SubPixel x;
  SubPixel y;
  float dX, dY;
  Color color;
  byte isDead;
  Bullet * nextBullet;
} Bullet;

typedef struct Player
{
  byte x, y;
  int subx, suby;
  int dX, dY;
  
  byte oldx, oldy;
  byte oldsubx, oldsuby;
  
  byte mask[25];
  Color color;
  Color coreColor;
  Bullet * bulletList;
} Player;

typedef struct Enemy
{
  byte x, y;
  byte mask[16];
  Color color;
  Bullet * bulletList;
} Enemy;

//Function Prototypes
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE);//function to drive LEDs
void rotateRight();
void shiftRight(char wrap);
void getPixel(byte x, byte y, Color * cPtr);
void setPixel(byte x, byte y, union Color c);
void setColor(union Color * color, byte r, byte g, byte b);
void drawRect(byte x, byte y, byte w, byte h, union Color c);
void drawCircle(byte x, byte y, byte d, union Color c);
void blit(byte * ar, byte x, byte y, byte w, byte h);

