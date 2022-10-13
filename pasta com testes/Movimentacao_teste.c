#include "raylib.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int personagemSpeed = 5;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    unsigned numFrames = 6;
    Texture2D personagem = LoadTexture("scarfy.png");
    int frameWidth = personagem.width / numFrames;
    Rectangle framePersonagem = { 0.0f , 0.0f , (float)personagem.width/numFrames, (float)personagem.height};
    Vector2 posicao_personagem = {screenWidth/2.0f , screenHeight/2.0f};
    Vector2 velocidade_personagem = {0.0f, 0.0f};
    
    unsigned frameIndex = 0;
    unsigned frameDelay = 5;
    unsigned frameDelayContador = 0;
    
    
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        if(IsKeyDown(KEY_RIGHT)){
            velocidade_personagem.x = personagemSpeed;
            if(framePersonagem.width < 0){
                framePersonagem.width = -framePersonagem.width;
            }
        }
        else if(IsKeyDown(KEY_LEFT)){
            velocidade_personagem.x = -personagemSpeed;
            if(framePersonagem.width > 0){
                framePersonagem.width = -framePersonagem.width;
            }
        }
        else{
            velocidade_personagem.x = 0;
        }    
        
        bool movimentacaoPersonagem = velocidade_personagem.x != 0.0f || velocidade_personagem.y != 0.0f;
        
        posicao_personagem = Vector2Add(posicao_personagem, velocidade_personagem);
        
        frameDelayContador++;
        if(frameDelayContador > frameDelay){
        frameDelayContador = 0;
        if(movimentacaoPersonagem){
            frameIndex++;
            frameIndex %= numFrames;
            framePersonagem.x = (float) frameWidth * frameIndex;
        } 
            
        }
        
        
        BeginDrawing();


        ClearBackground(RAYWHITE);

         DrawTextureRec(personagem, framePersonagem, posicao_personagem, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
