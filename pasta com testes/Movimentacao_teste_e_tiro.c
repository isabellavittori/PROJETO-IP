#include "raylib.h"
#include "raymath.h"

bool pulo;
int tempo_Pulo;
bool tiro;

typedef struct TiroDireita{
    Vector2 velocidadeDireita;
    bool ativoDireita;
    Vector2 posicaoDireita;
    int lifeSpawnDireita;
    float radiusDireita;
} TiroDireita;

typedef struct TiroEsquerda{
    Vector2 velocidadeEsquerda;
    bool ativoEsquerda;
    Vector2 posicaoEsquerda;
    int lifeSpawnEsquerda;
    float radiusEsquerda;
} TiroEsquerda;

static TiroDireita tiroDireita[3] = {0};
static TiroEsquerda tiroEsquerda[3] = {0};

bool direita;
bool esquerda;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1680;
    const int screenHeight = 980;
    const int personagemSpeed = 5;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    unsigned numFrames = 6;
    Texture2D personagem = LoadTexture("scarfy.png");
    int frameWidth = personagem.width / numFrames;
    Rectangle framePersonagem = { 0.0f , 0.0f , (float)personagem.width/numFrames, (float)personagem.height};
    Vector2 posicao_personagem = {screenWidth/2.0f , screenHeight/2.0f};
    Vector2 velocidade_personagem = {0.0f, 0.0f};
    Texture2D Textura_Bola_de_fogo = LoadTexture("Bola_de_fogo_atual.png");
    Rectangle Bola_de_fogo = { 0.0f , 0.0f , (float)Textura_Bola_de_fogo.width , (float)Textura_Bola_de_fogo.height};
    Vector2 posicao_Bola_de_fogo = {posicao_personagem.x , posicao_personagem.y}; 
    Vector2 velocidade_Bola_de_fogo = {15, 0.0f};
    
    unsigned frameIndex = 0;
    unsigned frameDelay = 5;
    unsigned frameDelayContador = 0;
    
    for(int i = 0; i < 3; i++){
        tiroDireita[i].posicaoDireita = (Vector2) {posicao_personagem.x + 30, posicao_personagem.y + 30 };
        tiroDireita[i].velocidadeDireita.x = 30;
        tiroDireita[i].radiusDireita = 10;
        tiroDireita[i].ativoDireita = false;
        tiroDireita[i].lifeSpawnDireita = 0;
    }
    
    for(int i = 0; i < 3; i++){
        tiroEsquerda[i].posicaoEsquerda = (Vector2) {posicao_personagem.x + 30, posicao_personagem.y + 30 };
        tiroEsquerda[i].velocidadeEsquerda.x = 30;
        tiroEsquerda[i].radiusEsquerda = 10;
        tiroEsquerda[i].ativoEsquerda = false;
        tiroEsquerda[i].lifeSpawnEsquerda = 0;
    }
    
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        if(IsKeyDown(KEY_RIGHT)){
            velocidade_personagem.x = personagemSpeed;
            direita = true;
            esquerda = false;
            if(framePersonagem.width < 0){
                framePersonagem.width = -framePersonagem.width;
            }
        }
        else if(IsKeyDown(KEY_LEFT)){
            velocidade_personagem.x = -personagemSpeed;
            esquerda = true;
            direita = false;
            if(framePersonagem.width > 0){
                framePersonagem.width = -framePersonagem.width;
            }
        }
        else{
            velocidade_personagem.x = 0;
        }    
        
        if(IsKeyDown(KEY_UP)){
            pulo = true;
        }
        if(pulo){
            tempo_Pulo += 1;
            if(tempo_Pulo <= 15){
                posicao_personagem.y -= 8;
            }
            else{
                posicao_personagem.y += 8;
            }
        }
        if(tempo_Pulo >= 30){
            tempo_Pulo = 0;
            pulo = false;
            velocidade_personagem.y = 0.0f;
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
         
         if(IsKeyPressed(KEY_SPACE) && direita){
             
            for(int i = 0; i < 3; i++){
                 
                 if(!tiroDireita[i].ativoDireita){
                     tiroDireita[i].posicaoDireita = (Vector2){posicao_personagem.x + 30, posicao_personagem.y + 30};
                     tiroDireita[i].ativoDireita = true;
                     break;
                 }
             }     
                
         }
         
        for(int i = 0; i < 3; i++){
             
            if(tiroDireita[i].ativoDireita){
                tiroDireita[i].posicaoDireita.x += 30;
                tiroDireita[i].lifeSpawnDireita++;
                 
                if(tiroDireita[i].posicaoDireita.x > 8000){
                     tiroDireita[i].ativoDireita = false;
                }
                if(tiroDireita[i].ativoDireita){
                    DrawTextureRec(Textura_Bola_de_fogo, Bola_de_fogo, tiroDireita[i].posicaoDireita, WHITE);
                }
                if(tiroDireita[i].lifeSpawnDireita >= 80){
                     tiroDireita[i].posicaoDireita = (Vector2) {posicao_personagem.x + 30, posicao_personagem.y + 30};
                     tiroDireita[i].velocidadeDireita = (Vector2) {0, 0};
                     tiroDireita[i].lifeSpawnDireita = 0;
                     tiroDireita[i].ativoDireita = false;
                }
            } 
             
        }
        
        if(IsKeyPressed(KEY_SPACE) && esquerda){
             
            for(int i = 0; i < 3; i++){
                 
                 if(!tiroEsquerda[i].ativoEsquerda){
                     tiroEsquerda[i].posicaoEsquerda = (Vector2){posicao_personagem.x - 20, posicao_personagem.y + 20};
                     tiroEsquerda[i].ativoEsquerda = true;
                     break;
                 }
             }     
                
         }
        
        
        for(int i = 0; i < 3; i++){
             
            if(tiroEsquerda[i].ativoEsquerda){
                tiroEsquerda[i].posicaoEsquerda.x -= 30;
                tiroEsquerda[i].lifeSpawnEsquerda++;
                 
                if(tiroEsquerda[i].posicaoEsquerda.x <= -8000){
                     tiroEsquerda[i].ativoEsquerda = false;
                }
                if(tiroEsquerda[i].ativoEsquerda){
                    DrawTextureRec(Textura_Bola_de_fogo, Bola_de_fogo, tiroEsquerda[i].posicaoEsquerda, WHITE);
                }
                if(tiroEsquerda[i].lifeSpawnEsquerda >= 80){
                     tiroEsquerda[i].posicaoEsquerda = (Vector2) {posicao_personagem.x - 20, posicao_personagem.y + 20};
                     tiroEsquerda[i].velocidadeEsquerda = (Vector2) {0, 0};
                     tiroEsquerda[i].lifeSpawnEsquerda = 0;
                     tiroEsquerda[i].ativoEsquerda = false;
                }
            } 
             
        }
        

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
