#ifndef GAME_FUNCTIONS
#define GAME_FUNCTIONS

#include "sprite.h"


void update_collisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PLayerBullets, Sprite* p_EnemyBullets, float tally, GAME_STATE* p_GAME);
void draw_sprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader);

#endif