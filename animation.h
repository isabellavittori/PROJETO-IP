#ifndef animation
#define animation
#include "raylib.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "character.h"

void animacaoPersonagem(objPersonagem *player,int frameCounter);

void terminarAnimacao(objPersonagem *player);

#endif
