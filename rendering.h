#ifndef RENDERING_H_
#define RENDERING_H_
#define WIDTH 11
#define HEIGHT 20

//int renderBlock(uint8_t block, uint8_t direction, uint8_t x, uint8_t y);
//int checkBlock(uint8_t block, uint8_t direction, uint8_t x, uint8_t y);
//uint8_t flip(int number, uint8_t bits);

int renderBlock(uint8_t block, uint8_t direction, uint8_t x, uint8_t y)
{

  bool overlap;
  extern char screen[HEIGHT][WIDTH+1];
  uint8_t i;

  // Default
    if (direction == 0)
    {
       // Render
       for (i = 0; i < 4; i++) {
          if (1 & (block >> i))
            screen[y][x + i] = '0';
          if (1 & (block >> (i + 4)))
            screen[y+1][x + i] = '0';
       }
       return 1;
    }

    // Rotated Right
    if (direction == 1)
    {
        // Render
        for (uint8_t i = 0; i < 4; i++) {
            if (1 & (block >> (4 + i)))
                screen[y + i -1][x] = '0';

            if (1 & (block >> i))
                screen[y + i -1][x+1] = '0';
        };

        return 1;
    }

  // Rotated Down
  if (direction == 2)
  {
    for (uint8_t i = 0; i < 4; i++) {
      if (1 & (block >> (4 + i)))
        screen[y][x + 3 - i] = '0';
      if (1 & (block >> i))
        screen[y+1][x + 3 - i] = '0';
    }
  }

  // Rotated Left
  if (direction == 3)
  {
    for (uint8_t i = 0; i < 4; i++) {
      if (1 & (block >> (4 + i)))
       screen[y + 2 - i][x+2] = '0';

      if (1 & (block >> i))
        screen[y + 2 - i][x+1] = '0';
    };
  }
}

int checkBlock(uint8_t block, uint8_t direction, uint8_t x, uint8_t y)
{
  bool overlap;
  extern char screen[HEIGHT][WIDTH+1];
  uint8_t i;

  // Default
    if (direction == 0)
    {
       for (i = 0; i < 4; i++) {
           if ((1 & (block >> i)) && screen[y][x+i] != ' ' && screen[y][x+i] != '0'  ) {
               return 0;
           }
          if ((1 & (block >> (i + 4))) && screen[y+1][x+i] != ' ' && screen[y+1][x+i] != '0') {
              return 0;
          }
       }
       return 1;
    }

    // Rotated Right
    if (direction == 1)
    {
        for (i = 0; i < 4; i++) {
            if (1 & (block >> (4 + i)) && screen[y+i-1][x] != ' ' && screen[y+i-1][x] != '0')
              return 0;

            if (1 & (block >> i) && screen[y+i-1][x+1] != ' ' && screen[y+i-1][x+1] != '0')
                return 0;
        };
        return 1;
    }

    // Rotated Down
    if (direction == 2)
    {
        for (uint8_t i = 0; i < 4; i++) {
            if (1 & (block >> (4 + i)) && screen[y][x+3-i] != ' ' && screen[y][x+3-i] != '0')
                return 0;
            if (1 & (block >> i) && screen[y+1][x + 3 - i] != ' ' && screen[y+1][x + 3 - i] != '0')
                return 0;
        }
    }

    // Rotated Left
    if (direction == 3)
    {
        for (uint8_t i = 0; i < 4; i++) {
            if (1 & (block >> (4 + i)) && screen[y + 2 - i][x+2] != ' ' && screen[y + 2 - i][x+2] != '0')
              return 0;

            if (1 & (block >> i) && screen[y + 2 - i][x+1] != ' ' && screen[y + 2 - i][x+1] != '0')
              return 0;
        };
    }


}
void repChar(char c, char r)
{
    extern char screen[HEIGHT][WIDTH+1];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH+1; x++) {
                screen[y][x] = (screen[y][x] == c) ? r : screen[y][x];
        }
    }
}
#endif // RENDERING_H_
