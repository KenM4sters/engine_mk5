#ifndef GAME
#define GAME

#include "sprite.h"

void updateCollisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PLayerBullets, float tally);
void drawSprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader);

#endif