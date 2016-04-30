#include "InputHandler.h"

void setupInputs()
{
  pinMode(P1UP,INPUT);
  pinMode(P1RIGHT,INPUT);
  pinMode(P1LEFT,INPUT);
  pinMode(P1DOWN,INPUT);
  pinMode(P1RED,INPUT);
  pinMode(P1YELLOW,INPUT);
  
  pinMode(P2UP,INPUT);
  pinMode(P2RIGHT,INPUT);
  pinMode(P2LEFT,INPUT);
  pinMode(P2DOWN,INPUT);
  pinMode(P2RED,INPUT);
  pinMode(P2YELLOW,INPUT);
}

void handleInput()
{
  int i;
  //TODO: Add button class
  for (i = 0; i < NUM_BUTTONS; ++i)
  {
    handlePlayerInput(&playerOneInputs, i);
    handlePlayerInput(&playerTwoInputs, i);
  }
}

void handlePlayerInput( byte (* input)[6][4], int index)
{
  (* input)[index][PRESS] = 0;
  (* input)[index][RELEASE] = 0;

  if (digitalRead((* input)[index][CODE]) == LOW)
  {
    if (!(* input)[index][DOWN])
    {
      (* input)[index][PRESS] = 1;
    }

    (* input)[index][DOWN] = 1;
  }
  else
  {
    if ((* input)[index][DOWN])
    {
      (* input)[index][RELEASE] = 1;
    }

    (* input)[index][DOWN] = 0;
  }
}

