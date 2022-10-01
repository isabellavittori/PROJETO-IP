/*Quando a bola grande estiver perto suficiente da bola pequena e a tecla "b" for apertada, a bola pequena muda de cor,
com essa lógica registrar dano vai ser fácil*/

#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int flag=0;
    float d=0;
    float y1=screenHeight/2,y2=screenHeight/2,x1=(screenWidth-400)/2,x2=(screenWidth+400)/2;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Vector2 ballPosition = { (float)x1, (float)y1 };
    Vector2 ballPosition_1 = { (float)x2, (float)y2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        d=sqrt((ballPosition.x-x2)*(ballPosition.x-x2)+(ballPosition.y-y2)*(ballPosition.y-y2));
        if(d<100 && IsKeyDown(KEY_B)) flag=1;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
            if(flag==0)
            {
                DrawCircleV(ballPosition, 50, MAROON);
                DrawCircleV(ballPosition_1, 25, MAROON);
            }
            else
            {
                DrawCircleV(ballPosition, 50, MAROON);
                DrawCircleV(ballPosition_1, 25, GOLD);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
