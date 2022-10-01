#include "raylib.h"
#include "libs/raymath.h"


bool isPlayerOnGround(Texture2D *personagem, Vector2 *posicao_personagem, Vector2 *chao_pos) {
    if(posicao_personagem->y + personagem->height >= chao_pos->y) {
        return true;
    }
    else {
        return false;
    }
}








int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int personagemSpeed = 5;
    const int gravity = 1;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
   

    unsigned numFrames = 8;

    Texture2D chao_text = LoadTexture("/assets/background_chao.png");

	Texture2D box_text = LoadTexture("/assets/chao.png");

    
    Texture2D personagem = LoadTexture("/assets/Run.png");
    
    Texture2D idle = LoadTexture("/assets/Idle.png");

    Texture2D attack = LoadTexture("/assets/attack.png");

    Texture2D jump = LoadTexture("/assets/jump_and_fall.png");

    //Texture2D fall = LoadTexture("/assets/JumpAndFall2.png");

    int frameWidth = personagem.width / numFrames;
    int flag_attack = 0;
    int flag_idle = 0;
    

    Rectangle chao = {0.0f, 0.0f, GetScreenWidth(), chao_text.height};

	Rectangle box = {400, 400, 200, 200};

    Rectangle framePersonagem = { 0.0f , 0.0f , (float)personagem.width/numFrames, (float)personagem.height};
    Rectangle framePersonagem_idle = {0.0f, 0.0f, (float)idle.width, (float)idle.height};
    Rectangle framePersonagem_attack = {0.0f, 0.0f, (float)attack.width/10, (float)attack.height};
    Rectangle framePersonagem_jump = {0.0f, 0.0f, (float)jump.width/2, (float)jump.height};
   

    Vector2 chao_pos = {0, GetScreenHeight() - 115};

	Vector2 box_pos = {400, GetScreenHeight() - 250};

    Vector2 posicao_personagem = {screenWidth/2.0f , chao_pos.y - personagem.height};
    Vector2 velocidade_personagem = {0.0f, 0.0f};
    
    //Rectangle corpo = {posicao_personagem.x, posicao_personagem.y, 200, 200};

	Rectangle atk_rec = {posicao_personagem.x + 200 - 17, posicao_personagem.y + (200/4), 200, 20};

    unsigned frameIndex = 0;
    unsigned frameDelay = 5;
    unsigned frameDelayContador = 0;
    
    
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {

        if(isPlayerOnGround(&personagem, &posicao_personagem, &chao_pos)){
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
            else if(IsKeyDown(KEY_S)){
                flag_attack = 1;
                velocidade_personagem.x = 0.0f;
				
            }
            else if(IsKeyDown(KEY_SPACE)) {
                velocidade_personagem.y = -2 * (personagemSpeed + 3);
            }
            else {
                flag_idle = 1;
                velocidade_personagem.x = 0.0f;
            }   
        }

        
        
        bool movimentacaoPersonagem = velocidade_personagem.x != 0.0f || velocidade_personagem.y != 0.0f;
        //bool wasPlayerOnGround = isPlayerOnGround(&personagem, &posicao_personagem, &chao_pos);
        posicao_personagem = Vector2Add(posicao_personagem, velocidade_personagem);
        bool PlayerIsOnGround = isPlayerOnGround(&personagem, &posicao_personagem, &chao_pos);

        if(PlayerIsOnGround) {
            velocidade_personagem.y = 0;
            posicao_personagem.y = chao_pos.y - personagem.height;
        }
        else {
            velocidade_personagem.y += gravity;
        }

        if(posicao_personagem.x <= 0){
            posicao_personagem.x = 0;
        }
        if(posicao_personagem.x >= screenWidth + 1200){//acho que vai ter que mudar, talvez 1920...
            posicao_personagem.x = screenWidth + 1200;
        }
        

        ++frameDelayContador;
        if(frameDelayContador > frameDelay){
            frameDelayContador = 0;
        
            if(movimentacaoPersonagem){
                if(PlayerIsOnGround){
                    ++frameIndex;
                    frameIndex %= numFrames;
                    framePersonagem.x = (float) frameWidth * frameIndex;
                }

                else if(PlayerIsOnGround && flag_idle == 1){
                    ++frameIndex;
                    frameIndex %= 1;
                    framePersonagem_idle.x = (float) idle.width * frameIndex;
                }
                   
                else{
                    if(velocidade_personagem.y < 0){
                        frameIndex = 0;
                    }
                    else {
                        frameIndex = 1;   
                    }
                    framePersonagem_jump.x = (float)jump.width/2 * frameIndex;
                }
            }

				else if(PlayerIsOnGround && flag_attack == 1){
                	++frameIndex;
                    frameIndex %= 10;
                    framePersonagem_attack.x = (float)attack.width/10 * frameIndex;
                    if(framePersonagem_attack.x == 315){
                    	flag_attack = 0;
                    }
                }

        }

		/*   player->ataque = (Rectangle) {player->posicao.x + LARGURA_PERSONAGEM-17, player->posicao.y + (ALTURA_PERSONAGEM/4), ALCANCE_ATAQUE, 20};
        }
        else if(player->index == 2) {
            player->ataque = (Rectangle) {player->posicao.x - ALCANCE_ATAQUE + 75, player->posicao.y + (ALTURA_PERSONAGEM/4), ALCANCE_ATAQUE, 20};
        }
		*/

        

        BeginDrawing();


        ClearBackground(RAYWHITE);

        DrawTextureRec(chao_text, chao, chao_pos, WHITE);
		DrawTextureRec(box_text, box, box_pos, WHITE);


            if(movimentacaoPersonagem && PlayerIsOnGround){
                DrawTextureRec(personagem, framePersonagem, posicao_personagem, WHITE);
            }
            else if(PlayerIsOnGround && flag_attack == 1){
                DrawTextureRec(attack, framePersonagem_attack, posicao_personagem, WHITE);
				if(CheckCollisionRecs(atk_rec, box)){
					DrawTextureRec(box_text, box, box_pos, RED);
				}
            }
            else if(PlayerIsOnGround && flag_idle == 1){
				DrawTextureRec(idle, framePersonagem_idle, posicao_personagem, WHITE);
			}
            else {
                DrawTextureRec(jump, framePersonagem_jump, posicao_personagem, WHITE);
            }
			
           
                
            
       

        EndDrawing();
        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(personagem);
    UnloadTexture(jump);
    UnloadTexture(attack);
    UnloadTexture(idle);

    CloseWindow();        

    return 0;
}
