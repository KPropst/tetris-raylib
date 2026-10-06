#include "headers.h"

void clearLines();
void blockUpdate(Texture2D red);
void scoreUpdate(int score, int x, int y, Texture2D one, Texture2D two, Texture2D three, Texture2D four, Texture2D five, Texture2D six, Texture2D seven, Texture2D eight, Texture2D nine, Texture2D zero);

char screen[HEIGHT][WIDTH+1] = {
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
  {'\n',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n'},
};

uint8_t blocks[] = {L_BLOCK, J_BLOCK, O_BLOCK, I_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};


Vector2 cubePos = {0,0};
Vector2 nextPos = {13,2};

int score = 0;
int main()
{
  int yPos = 2;
  int xPos = 4;
  int direction = 0;
  bool isFilled;
  uint8_t lineCount;

  uint8_t next = blocks[rand() % 7];
  uint8_t block = blocks[rand() % 7];
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 184*3;
  const int screenHeight = 141*3;

  Vector2 bgPos = {0,0};

  InitWindow(screenWidth, screenHeight, "tetris");

  Texture2D bg = LoadTexture("resources/BG.png");
  Texture2D red = LoadTexture("resources/red.png");

  Texture2D one = LoadTexture("resources/1.png");
  Texture2D two = LoadTexture("resources/2.png");
  Texture2D three = LoadTexture("resources/3.png");
  Texture2D four = LoadTexture("resources/4.png");
  Texture2D five = LoadTexture("resources/5.png");
  Texture2D six = LoadTexture("resources/6.png");
  Texture2D seven = LoadTexture("resources/7.png");
  Texture2D eight= LoadTexture("resources/8.png");
  Texture2D nine = LoadTexture("resources/9.png");
  Texture2D zero = LoadTexture("resources/0.png");
  int ticker = 0;
  //--------------------------------------------------------------------------------------

  // Game Loop
  //--------------------------------------------------------------------------------------
  while (!WindowShouldClose()) {

    /* Background */
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureEx(bg, bgPos, 0, 3, WHITE);
    blockUpdate(red);


    if (ticker >= 600) {
      yPos++;
      blockUpdate(red);

      /* Backend Code */
      if (checkBlock(block, direction, xPos, yPos)) {
        repChar('0', ' ');
        renderBlock(block, direction, xPos, yPos);
      }
      else { /* Block Placed */
        repChar('0', '1');
        yPos = 2;
        xPos = 4;
        direction = 0;
        block = next;
        next = blocks[rand() % 7];
        clearLines();
      }
      ticker = 0;
    }

    /* Controls */
    if (IsKeyPressed(KEY_RIGHT) && checkBlock(block, direction, xPos+1, yPos))
      xPos++;
    if (IsKeyPressed(KEY_LEFT) && checkBlock(block, direction, xPos-1, yPos))
      xPos--;
    if (IsKeyDown(KEY_DOWN) && checkBlock(block, direction, xPos, yPos+1) && (ticker % 60) == 0)
      yPos++;
    if (IsKeyPressed(KEY_SPACE) && checkBlock(block, (direction < 3) ? direction + 1 : 0, xPos, yPos))
      direction = (direction < 3) ? direction+1 : 0;

    Vector2 pos = {nextPos.x*21 + 111 , nextPos.y*21 + 4}; /* Preview */
    for (int i = 0; i < 4; i++) {
      pos.x += 21;
      if (1 & (next >> i)) {
        DrawTextureEx(red, pos, 0, 3, WHITE);
      }
      if (1 & (next >> (i + 4))) {
        pos.y += 21;
        DrawTextureEx(red, pos, 0, 3, WHITE);
        pos.y -= 21;
      }
    }

    scoreUpdate(score, 472, 104, one, two, three, four, five, six, seven, eight, nine, zero);

    /* Update */
    if (ticker % 30 == 0) {
      repChar('0', ' ');
      renderBlock(block, direction, xPos, yPos);
      blockUpdate(red);

    }

    ticker++;
    EndDrawing();
  }
  //--------------------------------------------------------------------------------------

}

void blockUpdate(Texture2D red)
{
    /* Update Blocks */
    for (int x = 1; x < WIDTH; x++ ) {
      for (int v = 0; v < HEIGHT; v++) {
        cubePos.x = (x*21)+111;
        cubePos.y = (v*21)+4;

        if (screen[v][x] == '0' || screen[v][x] == '1') {
          DrawTextureEx(red, cubePos, 0, 3, WHITE);
        }
      }
    }

}

void clearLines()
{
  bool isFilled;
        for (int y = 0; y < HEIGHT; y++) {
          isFilled = true;
          for (int x = 0; x < WIDTH; x++ ) {
            if (screen[y][x] == ' ') {
              isFilled = false;
              break;
            }
          }
          if (isFilled) {
            for (int x = 1; x < WIDTH; x++ ) {
              for (int v = 0; v < y; v++) {
                screen[y-v][x] = screen[y-v-1][x];
              }
            }
            score++;
          }
        }
}

void scoreUpdate(int score, int x, int y, Texture2D one, Texture2D two, Texture2D three, Texture2D four, Texture2D five, Texture2D six, Texture2D seven, Texture2D eight, Texture2D nine, Texture2D zero)
{
  Vector2 pos = {x, y};
  int scale = 22;
  int vscore = score;

  if (vscore == 0 ) {
    DrawTextureEx(zero, pos, 0, 3, WHITE);
    return;
  }
  for (int i = 1; vscore != 0; i++) {
    switch ((int)(vscore % (int)pow(10, i)) / (int)pow(10,(i-1))) {
      case 0:
        DrawTextureEx(zero, pos, 0, 3, WHITE);
        printf("HELP IM STOCCUK\n");
        break;
      case 1:
        DrawTextureEx(one, pos, 0, 3, WHITE);
        break;
      case 2:
        DrawTextureEx(two, pos, 0, 3, WHITE);
        break;
      case 3:
        DrawTextureEx(three, pos, 0, 3, WHITE);
        break;
      case 4:
        DrawTextureEx(four, pos, 0, 3, WHITE);
        break;
      case 5:
        DrawTextureEx(five, pos, 0, 3, WHITE);
        break;
      case 6:
        DrawTextureEx(six, pos, 0, 3, WHITE);
        break;
      case 7:
        DrawTextureEx(seven, pos, 0, 3, WHITE);
        break;
      case 8:
        DrawTextureEx(eight, pos, 0, 3, WHITE);
        break;
      case 9:
        DrawTextureEx(nine, pos, 0, 3, WHITE);
        break;
      default:
        break;
    }
    pos.x -= scale;
    vscore -= (vscore % (int)pow(10, i));
  }

}
