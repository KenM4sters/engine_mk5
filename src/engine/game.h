#ifndef GAME_FUNCTIONS
#define GAME_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"

typedef enum GAME_INPUT {MOVE_LEFT, MOVE_RIGHT, STILL, QUIT} GAME_INPUT;

void update_collisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PLayerBullets, Sprite* p_EnemyBullets, float tally, GAME_PROPS* p_GAME, float deltaTime);
void draw_sprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader);
void reset_player(Sprite* p_Player, int* respawn_timer);
void update_enemies(Sprite* p_Enemy);
void update_positions_sprites(Sprite* p_Player, Sprite* p_Enemy, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets);
#endif