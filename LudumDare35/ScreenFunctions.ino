//Sets the RGB value of a specific pixel on the screen
// (0,0) is the top left hand corner of the screen

byte blendMode = 0;

void setPixel(byte x, byte y, Color c)
{
  int index;
  if(y%2 == 0)
  {
    index = (y*16*3) + x*3;
  }
  else
  {
    index = (y*48) + 45-(x*3);
  }

  if (blendMode)
  {
    //Right now, just assumes true to be additive
    RGB[index] += c.rgb.g;
    RGB[index+1] += c.rgb.r;
    RGB[index+2] += c.rgb.b;
  }
  else
  {   
    RGB[index] = c.rgb.g;
    RGB[index+1] = c.rgb.r;
    RGB[index+2] = c.rgb.b;
  }
}

byte setBlendMode(byte newBlendMode)
{
  blendMode = newBlendMode;
}

//Fills the screen in one color
void fillScreen(Color color)
{       
  int i,j;
  for(j = 0; j < 16; j++)
  {
    for(i = 0; i < 16; i++)
    {
      setPixel(i, j, color);
    }
  }
}

//Draws a rectangle in the specified color, from (x,y) to (x+w, y+w)
void drawRect(byte x, byte y, byte w, byte h, Color c)
{
  int i,j;
  for(j = y; j < y + h; j++)
  {
    for(i = x; i < x + w; i++)
    {
      setPixel(i,j,color);
    }
  }
}

//Draws a circle in the specified color, with top left corner at (x, y) and diameter of d
void drawCircle(byte x, byte y, byte d, Color c)
{
  byte i, j;
  byte r2 = (d / 2) * (d / 2);
  byte cx, cy;
  cx = x + d/2;
  cy = y + d/2;

  for (i = x; i <= x+d; i++)
  {
    for (j = y; j <= y+d; j++)
    {
      if ((i-cx)*(i-cx) + (j-cy)*(j-cy) <= r2)
      {
        setPixel(i,j,c);
      }
    }
  }
}

//Moves every byte one spot to the right IN THE ARRAY, this causes the screen to do the cool snake like pattern
// This is due to the fact that the rows alternate directions
void rotateRight()
{
  int i, r,g,b;
  g = RGB[((NUM_LEDS-1) * 3)];
  r = RGB[((NUM_LEDS-1) * 3) + 1];
  b = RGB[((NUM_LEDS-1) * 3) + 2];
  for(i = NUM_LEDS-1; i >= 0; i--)
  {
     RGB[(3*i)] = RGB[3*(i-1)];
     RGB[(3*i)+1] = RGB[3*(i-1)+1];
     RGB[(3*i)+2] = RGB[3*(i-1)+2];
  }
  RGB[0] = g;
  RGB[1] = r;
  RGB[2] = b;
}

//Shifts every column to the right one, wrap controls whether the right side of the screen wraps back to the left side
void shiftRight(char wrap)
{
  Color farRight[16];
  Color c;
  char i,j;
  if(wrap)
  {
    for(i = 0; i < 16; i++)
    {
      getPixel(15, i, &c);
      farRight[i] = c;
    }
  }
  for(i = 16-1; i > 0; i--)
  { 
    for(j = 0; j < 16; j++)
    {
      getPixel(i-1,j, &c);
      setPixel(i,j, c);
    }
  }
  if(wrap)
  {
    for(i = 0; i < 16; i++)
    {
      c = farRight[i];
      setPixel(0,i,c); 
    }
  }
  else
  {
    for(i = 0; i < 16; i++)
    {
      setColor(&c, 0,0,0);
      setPixel(0,i,c); 
    }
  }
}

//Sets the pointer to the color of a particular pixel
void getPixel(byte x, byte y, Color * cPtr)
{
  int index;
  if(y%2 == 0)
  {
    index = (y*16*3) + x*3;
  }
  else
  {
    index = (y*48) + 45-(x*3);
  }
  (*cPtr).rgb.g = RGB[index];
  (*cPtr).rgb.r = RGB[index + 1];
  (*cPtr).rgb.b = RGB[index + 2];
}

//Shorthand way to change the color of a Color variable
void setColor(Color * cPtr, byte r, byte g, byte b)
{
  (*cPtr).rgb.r = r;
  (*cPtr).rgb.g = g;
  (*cPtr).rgb.b = b;
}

void blit(byte * ar, byte x, byte y, byte w, byte h)
{
  byte i,j, count;
  Color c;
  count = 0;
  for(j = y; j < y + h; j++)
  {
    for(i = x; i < x + w; i++)
    {
        setColor(&c, ar[count+1], ar[count], ar[count+2]);
        setPixel(i, j, c);
        count+=3;
    }
  }
}


//WS2812 Driver Function 
//Code by Kevin Darrah -> http://kevindarrah.com/download/arduino_code/WS1812_V4_FOR_VIDEO.ino
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE) {
  // LED is the LED number starting with 0
  // RED, GREEN, BLUE is the brightness 0..255 setpoint for that LED
  byte ExistingPort, WS2812pinHIGH;//local variables here to speed up pinWrites
  
  if(LED>=0){//map the REG GREEN BLUE Values into the RGB[] array
  RGB[LED * 3] = GREEN;
  RGB[LED * 3 + 1] = RED;
  RGB[LED * 3 + 2] = BLUE;
  }
  
  noInterrupts();//kill the interrupts while we send the bit stream out...
  ExistingPort = PORTB; // save the status of the entire PORT B - let's us write to the entire port without messing up the other pins on that port
  WS2812pinHIGH = PORTB | 1; //this gives us a byte we can use to set the whole PORTB with the WS2812 pin HIGH
  int bitStream = NUM_LEDS * 3;//total bytes in the LED string

//This for loop runs through all of the bits (8 at a time) to set the WS2812 pin ON/OFF times
  for (int i = 0; i < bitStream; i++) {

    PORTB = WS2812pinHIGH;//bit 7  first, set the pin HIGH - it always goes high regardless of a 0/1 
    
    //here's the tricky part, check if the bit in the byte is high/low then right that status to the pin
    // (RGB[i] & B10000000) will strip away the other bits in RGB[i], so here we'll be left with B10000000 or B00000000
    // then it's easy to check if the bit is high or low by AND'ing that with the bit mask ""&& B10000000)"" this gives 1 or 0
    // if it's a 1, we'll OR that with the Existing port, thus keeping the pin HIGH, if 0 the pin is written LOW
    PORTB = ((RGB[i] & B10000000) && B10000000) | ExistingPort; 
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//these are NOPS - these let us delay clock cycles for more precise timing 
    PORTB = ExistingPort;//okay, here we know we have to be LOW regardless of the 0/1 bit state
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//minimum LOW time for pin regardless of 0/1 bit state

    // then do it again for the next bit and so on... see the last bit though for a slight change

    PORTB = WS2812pinHIGH;//bit 6
    PORTB = ((RGB[i] & B01000000) && B01000000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 5
    PORTB = ((RGB[i] & B00100000) && B00100000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 4
    PORTB = ((RGB[i] & B00010000) && B00010000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 3
    PORTB = ((RGB[i] & B00001000) && B00001000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 2
    PORTB = ((RGB[i] & B00000100) && B00000100) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 1
    PORTB = ((RGB[i] & B00000010) && B00000010) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 0
    __asm__("nop\n\t");//on this last bit, the check is much faster, so had to add a NOP here
    PORTB = ((RGB[i] & B00000001) && B00000001) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); 
    PORTB = ExistingPort;//note there are no NOPs after writing the pin LOW, this is because the FOR Loop uses clock cycles that we can use instead of the NOPS
  }//for loop

  
  interrupts();//enable the interrupts

// all done!
}//void RGB_update

