#ifndef SPRITES
#define SPRITES
#include "../../deps/include/glad/glad.h"
#include "../../deps/include/GLFW/glfw3.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "math/matrix4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Weapon {

    vector2 position, velocity;

} Weapon;

typedef struct Texture_Data {
    int texture, width, height, nrChannels;
    unsigned char* data;

} Texture_Data;

typedef struct Sprite
{
    vector2 position, velocity;
    int bulletsFired;
    int hitPoints;
    Weapon bullets;

    float* vertices;
    unsigned int verticesCount;
    unsigned int VBO;
    unsigned int VAO;
    matrix4 instances[10000];
    unsigned int instanceVBO;

    Texture_Data texture;

} Sprite;



Sprite CreatePlayer();
Sprite CreatePlayerBullets();
Sprite CreateEnemies();
// void fireBullets(Sprite* p_Bullets, Sprite* p_Sprite);
void updateBullets(Sprite* p_Bullets, Sprite* p_Sprite, float time, GLFWwindow* window);


#endif