#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define NUM_BUTTONS 6

#define PRESS 0
#define DOWN 1
#define RELEASE 2
#define CODE 3

#define JUP 0
#define JRIGHT 1
#define JDOWN 2
#define JLEFT 3
#define BRED 4
#define BYELLOW 5
  
#define P1UP      42
#define P1RIGHT   41
#define P1DOWN    40
#define P1LEFT    43
#define P1RED     38
#define P1YELLOW  39

#define P2UP      51
#define P2RIGHT   50
#define P2DOWN    48
#define P2LEFT    47
#define P2RED     49
#define P2YELLOW  46

byte playerOneInputs[6][4] = 
{
  {0, 0, 0, P1UP},
  {0, 0, 0, P1RIGHT},
  {0, 0, 0, P1DOWN},
  {0, 0, 0, P1LEFT},
  {0, 0, 0, P1RED},
  {0, 0, 0, P1YELLOW},
};

byte playerTwoInputs[6][4] =
{
  {0, 0, 0, P2UP},
  {0, 0, 0, P2RIGHT},
  {0, 0, 0, P2DOWN},
  {0, 0, 0, P2LEFT},
  {0, 0, 0, P2RED},
  {0, 0, 0, P2YELLOW},
};

void setupInputs();
void handleInput();
void handlePlayerInput( byte (* input)[6][4], int index);
#endif
