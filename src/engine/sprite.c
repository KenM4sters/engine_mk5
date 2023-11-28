#include "sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sprite create_player() 
{
    unsigned int VBO_SHIP, VAO_SHIP;

    float playerVertices[] = 
    {
         //ship.xyz       //ship.rgb        //ship_texture.xy        
        -0.04f,  -0.20f,  0.0f, 0.0f, 1.0f,  0.5f, 0.5f,       
         0.04f,  -0.20f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,    
         0.0f,   -0.10f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,      
    }; 
    
    float* p_PlayerVertices = &playerVertices[0];

    Sprite player = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        p_PlayerVertices,
        sizeof(playerVertices)/sizeof(float),
        VBO_SHIP,
        VAO_SHIP

    };


    Sprite* p_Player = &player;

    //Texture 
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*7, (void*)(5 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    

    //SHIP
    glGenBuffers(1, &p_Player->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Player->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p_Player->verticesCount, p_Player->vertices, GL_STATIC_DRAW);
    printf("\n\n%lu\n\n", (sizeof(float) * p_Player->verticesCount));
    printf("\n\n%f\n\n", p_Player->vertices[13]);
 
    glGenVertexArrays(1, &p_Player->VAO);
    glBindVertexArray(p_Player->VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glBindVertexArray(0);

    return player;


}

Sprite create_enemies() 
{
    //ENEMIES

    unsigned int VBO_SHIP_ENEMIES, VAO_SHIP_ENEMIES, instanceVBO;

    float enemies_vertices[] = 
    {
        //enemies.xyz      //enemies.rgb
        -0.04f, 0.0f, 0.0f,   0.5f, 0.0f, 0.0f,
         0.04f, 0.0f, 0.0f,   0.5f, 0.0f, 0.0f,
         0.0f, -0.04f, 0.0f,    0.5f, 0.0f, 0.0f,
    };
    float* pEnemies_vertices = &enemies_vertices[0];

    matrix4 translations[24];

    int enemyHitPoints[24];

    Sprite enemy = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f), 
        0,
        0,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        pEnemies_vertices, 
        sizeof(enemies_vertices)/sizeof(float), 
        VBO_SHIP_ENEMIES, 
        VAO_SHIP_ENEMIES,  
        *translations,
        instanceVBO

    }; 

    for(int i = 0; i <= 24; i++)
        enemy.hitPoints[i] = 10;
    
    for(int i = 0; i <= 24; i++)
        enemy.colors[i] = vector4_create(1.0f, 0.0f, 0.0f, 1.0f);
    
    
    Sprite* p_Enemy = &enemy;

    int index = 0;
    int moveRow = 0;
    float offset = 0.05f;
    for(int y = 5; y < 8; y += 1)
    {
        for(int x = -8; x < 8; x += 2)
        {
            matrix4 translation = matrix4_identity();
            translation.row1.w = (float)x / 10.0f + offset;
            translation.row2.w = (float)y / 10.0f + offset;
            matrix4 translation_column_major = matrix4_transpose(translation);
            p_Enemy->instances[index++] = translation_column_major;
            moveRow += 1;
        }
    }

    glGenBuffers(1, &p_Enemy->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*p_Enemy->verticesCount, p_Enemy->vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &p_Enemy->VAO);
    glBindVertexArray(p_Enemy->VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //ENEMIES INSTANCES
    glGenBuffers(1, &p_Enemy->instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*24, &p_Enemy->instances[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));


    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Colors
    glGenBuffers(1, &p_Enemy->colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector4) * 24, &p_Enemy->colors[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribDivisor(6, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    return enemy;
}


Sprite create_player_bullets() 
{
    unsigned int VBO_SHIp_ShipBullets, VAO_SHIp_ShipBullets, instanceVBO;

    float ship_ShipBullets_vertices[] = 
    {   
            //bullets.xyz         //bullets.rgb
        -0.005f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.005f, -0.15f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.0f, -0.145f, 0.0f,      1.0f, 1.0f, 1.0f,  
    };

    float* pShip_ShipBullets_vertices = &ship_ShipBullets_vertices[0];


    matrix4 translations[10000];

    Sprite playerBullets = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        pShip_ShipBullets_vertices,
        sizeof(ship_ShipBullets_vertices)/sizeof(float),
        VBO_SHIp_ShipBullets,
        VAO_SHIp_ShipBullets,
        *translations,
        instanceVBO
    };

 
    Sprite* p_PlayerBullets = &playerBullets;

    glGenBuffers(1, &p_PlayerBullets->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*p_PlayerBullets->verticesCount, p_PlayerBullets->vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &p_PlayerBullets->VAO);
    glBindVertexArray(p_PlayerBullets->VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

    //Instacing bullets
    glGenBuffers(1, &p_PlayerBullets->instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 10000, &p_PlayerBullets->instances[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return playerBullets;

}

Sprite create_enemy_bullets() 
{
    unsigned int VBO_ENEMY_BULLETS, VAO_ENEMY_BULLETS, instanceVBO;

    float enemy_bullets_vertices[] = 
    {   
            //bullets.xyz         //bullets.rgb
        -0.01f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.01f, -0.15f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.0f, -0.16f, 0.0f,      1.0f, 1.0f, 1.0f,  
    };

    float* pEnemy_bullets_vertices = &enemy_bullets_vertices[0];


    matrix4 translations[1000];

    Sprite enemyBullets = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        pEnemy_bullets_vertices,
        sizeof(enemy_bullets_vertices)/sizeof(float),
        VBO_ENEMY_BULLETS,
        VAO_ENEMY_BULLETS,
        *translations,
        instanceVBO
    };

 
    Sprite* p_EnemyBullets = &enemyBullets;

    glGenBuffers(1, &p_EnemyBullets->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_EnemyBullets->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*p_EnemyBullets->verticesCount, p_EnemyBullets->vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &p_EnemyBullets->VAO);
    glBindVertexArray(p_EnemyBullets->VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

    //Instacing bullets
    glGenBuffers(1, &p_EnemyBullets->instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_EnemyBullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 1000, &p_EnemyBullets->instances[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return enemyBullets;
}

void update_bullets(Sprite* p_ShipBullets, Sprite* p_Ship, Sprite* p_EnemyBullets, Sprite* p_Enemy, float deltaTime, int* timeCounter, GLFWwindow* window, GAME_STATE* p_GAME)
{

    *timeCounter += 1;
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
    {
        p_ShipBullets->instances[p_Ship->bulletsFired] = matrix4_identity();
        p_ShipBullets->instances[p_Ship->bulletsFired].row4.x = p_Ship->position.x;
        p_ShipBullets->instances[p_Ship->bulletsFired].row4.y = p_Ship->position.y;
        p_Ship->bulletsFired += 1;
        // printf("\n\nBullets fired: %d\n\n", p_Ship->bulletsFired);

    }

    for(int i = 0; i <= p_Ship->bulletsFired; i++) 
    {
        p_ShipBullets->instances[i].row4.y += deltaTime * 4; 
    }

    // printf("\n\nTime Counter: %d \n\n", *timeCounter);

    if((*timeCounter % 100) / p_GAME->round == 0 && *timeCounter > 500) 
    {   
        int r = rand() % 24;
        
        if(p_Enemy->instances[p_Enemy->bulletsFired].row4.x != 3.0f)
            p_EnemyBullets->instances[p_Enemy->bulletsFired] = p_Enemy->instances[r];
            p_Enemy->bulletsFired += 1;
    }

    for(int i = 0; i <= p_Enemy->bulletsFired; i++) 
    {
        p_EnemyBullets->instances[i].row4.y -= (deltaTime * 2) + p_GAME->round / 10;
    }


    glBindBuffer(GL_ARRAY_BUFFER, p_ShipBullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 10000, &p_ShipBullets->instances[0], GL_STATIC_DRAW);
    glBindVertexArray(p_ShipBullets->VAO);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, p_EnemyBullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 1000, &p_EnemyBullets->instances[0], GL_STATIC_DRAW);
    glBindVertexArray(p_EnemyBullets->VAO);

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector4) * 24, &p_Enemy->colors[0], GL_STATIC_DRAW);
    glBindVertexArray(p_Enemy->VAO);

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribDivisor(6, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


