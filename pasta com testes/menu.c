#include <stdio.h>
# include "raylib.h"
typedef enum GameScreen { INITIAL = 0, HISTORY, TUTORIAL, GAME } GameScreen;



int main(void){
  int flag = 0;
  GameScreen telaInicial = INITIAL;
  int frameCounter = 0;
  Vector2 mousePoint = { 0.0f, 0.0f };

      // #### SCREEN DEFINITIONS ####
  const int screenWidth = 1920;
  const int screenHeight = 1080;
    
      // #### BUTTON DEFINITIONS ####
  const int buttonWidth = 400;
  const int buttonHeight = 150;
  const int buttonPositX = 755.0f;
  const int buttonPositY = 550.0f;
    
      // #### INITIALIZING WINDOW & AUDIO ####  
  InitWindow(screenWidth, screenHeight, "MenuInicializing");
  InitAudioDevice();
  
      // #### SETTING BACKGOUNG (BG) ####
  Rectangle BGrec = { 0, 0, screenWidth, screenHeight };
  Texture2D BGtexture = LoadTexture("Assets/Fundo.png");
  Texture2D BGhistory = LoadTexture("Assets/History.png");
  Texture2D BGtutorial = LoadTexture("Assets/Tutorial.png");
  
      // #### SETTING BUTTON (BTN) ####
  Rectangle BTNrec = {0, 0, buttonWidth, buttonHeight};
  Rectangle BTNbounds = {buttonPositX, buttonPositY, buttonWidth, buttonHeight};
  Texture2D BTNtexture = LoadTexture("Assets/Button.png");
  Texture2D BTNtexture2 = LoadTexture("Assets/Button2.png");
  
      // #### SETTING FPS ####
  SetTargetFPS(60);
  
      // #### WINDOW VISION ####
  while (!WindowShouldClose()){

    mousePoint = GetMousePosition();
  
    switch(telaInicial){
      
      case INITIAL:{
        if(CheckCollisionPointRec(mousePoint, BTNbounds)){
          flag++;
          if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) telaInicial = TUTORIAL;
        }
        if(flag != 0 && !CheckCollisionPointRec(mousePoint, BTNbounds)) flag = 0;
      }break;

      case TUTORIAL:{
        if(IsKeyPressed(KEY_ENTER)) telaInicial = HISTORY;
      }break;
      
      case HISTORY:{
        frameCounter++;
        if(frameCounter > 150) telaInicial = GAME;
      }break;
      default: break;

      case GAME:{
        
      }break;
      
    }
  
    
    BeginDrawing();
      ClearBackground(RAYWHITE);
      switch(telaInicial){
        
        case INITIAL:{
          DrawTextureRec(BGtexture, BGrec, (Vector2){0.0f, 0.0f}, RAYWHITE);
          if(flag == 0)
            DrawTextureRec(BTNtexture, BTNrec, (Vector2){buttonPositX, buttonPositY}, RAYWHITE);
          if(flag != 0)
            DrawTextureRec(BTNtexture2, BTNrec, (Vector2){buttonPositX, buttonPositY}, RAYWHITE);
        }break;

        case TUTORIAL:{
          DrawTextureRec(BGtutorial, BGrec, (Vector2){0.0f, 0.0f}, RAYWHITE);
          //DrawText("Pressione ENTER para fechar o tutorial", 10, 10, 50, DARKGRAY);
        }break;
        
        case HISTORY:{
          DrawTextureRec(BGhistory, BGrec, (Vector2){0.0f, 0.0f}, RAYWHITE);
        }break;

        case GAME:{
          DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        }break;
      }
    EndDrawing();
  
    
  }
      // #### CLOSING WINDOW ####
  CloseWindow();
    
  return 0;
}
