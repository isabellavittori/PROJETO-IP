#include "raylib.h"

double max(double a, double b) {
  if(a>b) return a;
  return b;
}

double min(double a, double b) {
  if(a>b) return b;
  return a;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "barradehp");

    float resource1 = 1000; // RECURSO DO PLAYER 1
    float resource2 = 1000; // RECURSO DO PLAYER 2
    float resourcemax1 = 1000; // MAXIMO DE RECURSO DO PLAYER 1
    float resourcemax2 = 1000; // MAXIMO DE RECURSO DO PLAYER 2
    float hpfac1 = 0;
    float hpfac2 = 0;
    int grayThick = 3; // GROSSURA DA BORDA
    int distToCorner = 10 + grayThick; // DISTANCIA EM PIXELS A BORDA
    int barLength = 432; // COMPRIMENTO DA BARRA. preferencia ~40% do comp da tela
    int barHeight = 36; // ALTURA DA BARRA. preferencia ~5% da altura da tela
    char *nome1 = "NOME1";
    char *nome2 = "NOME2";
    float timer = 90;
    char* stimer = (char *) malloc(ceil(log10(timer)+1)*sizeof(char));
    int tamanhofonte = barHeight/2;
    

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_R)) resource1 -= 1;
        //if(IsKeyDown(KEY_E)) resource2 -= 1;
        //resource1 -= 1; // UPDATE NO HP
        //resource2 -= 1; // UPDATE NO HP
        timer = max(timer-GetFrameTime(), 0);
        sprintf(stimer, "%d", (int)ceil(timer));
        hpfac1 = min(1, max(0, resource1/resourcemax1));
        hpfac2 = min(1, max(0, resource2/resourcemax2));
      
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangle(distToCorner, distToCorner, barLength, barHeight, GOLD);
            DrawRectangle(screenWidth - barLength - distToCorner, distToCorner, barLength, barHeight, GOLD);
            DrawRectangle(distToCorner + grayThick, distToCorner + grayThick, barLength - 2*grayThick, barHeight - 2*grayThick, DARKGRAY);
            DrawRectangle(screenWidth - barLength - distToCorner + grayThick, distToCorner + grayThick, barLength - 2*grayThick, barHeight - 2*grayThick, DARKGRAY);
            DrawRectangle(distToCorner + grayThick + floor((1-hpfac1)*(barLength - 2*grayThick)), distToCorner + grayThick, ceil(hpfac1*(barLength - 2*grayThick)), barHeight - 2*grayThick, RED);
            DrawRectangle(screenWidth - barLength - distToCorner + grayThick, distToCorner + grayThick, floor(hpfac2*(barLength - 2*grayThick)), barHeight - 2*grayThick, RED);
            DrawText(nome2, screenWidth - MeasureText(nome2, tamanhofonte) - distToCorner - grayThick, distToCorner + grayThick + barHeight, tamanhofonte, BLACK);
            DrawText(nome1, distToCorner + grayThick, distToCorner + grayThick + barHeight, tamanhofonte, BLACK);
            DrawText(stimer, screenWidth/2 - MeasureText(stimer, tamanhofonte)/2, distToCorner + grayThick, tamanhofonte, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free(stimer);
    return 0;
}
