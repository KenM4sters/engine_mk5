#include "sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sprite CreatePlayer() 
{
    unsigned int VBO_SHIP, VAO_SHIP;
    int width, height, nrChannels;
    unsigned int texture;
    unsigned char *data = stbi_load("assets/SpaceShooterAssetPack_Ships.png", &width, &height, &nrChannels, 0);

    float playerVertices[] = 
    {
         //ship.xyz       //ship.rgb        //ship_texture.xy        
        -0.05f,  -0.20f,  1.0f, 0.5f, 0.4,  0.5f, 0.5f,       
         0.05f,  -0.20f,  1.0f, 0.5f, 0.4,  0.0f, 0.0f,    
         0.0f,   -0.10f,  1.0f, 0.5f, 0.4,  1.0f, 0.0f,      
    }; 
    
    float* p_PlayerVertices = &playerVertices[0];



    Texture_Data player_texture = {
        texture, width, height, nrChannels, 
        data
    };


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

    player.texture = player_texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    if (data)   
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture");
    }
    stbi_image_free(data);


    Sprite* p_Player = &player;

    //Texture 
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)(5 * sizeof(float)));
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glBindVertexArray(0);

    return player;


}

Sprite CreateEnemies() 
{
    //ENEMIES

    unsigned int VBO_SHIP_ENEMIES, VAO_SHIP_ENEMIES, instanceVBO;

    float enemies_vertices[] = 
    {
        //enemies.xyz      //enemies.rgb
        -0.025f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.025f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.0f, 0.025f, 0.0f,    1.0f, 0.0f, 0.0f,
    };
    float* pEnemies_vertices = &enemies_vertices[0];

    matrix4 translations[200];

    Sprite enemy = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f), 
        0,
        10,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        pEnemies_vertices, 
        sizeof(enemies_vertices)/sizeof(float), 
        VBO_SHIP_ENEMIES, 
        VAO_SHIP_ENEMIES,
        *translations,
        instanceVBO

    }; 
    
    Sprite* p_Enemy = &enemy;

    int index = 0;
    float offset = 0.05f;
    for(int y = 3; y < 10; y += 1)
    {
        for(int x = -9; x < 9; x += 1)
        {
            matrix4 translation = matrix4_identity();
            translation.row1.w = (float)x / 10.0f + offset;
            translation.row2.w = (float)y / 10.0f + offset;
            matrix4 translation_column_major = matrix4_transpose(translation);
            p_Enemy->instances[index++] = translation_column_major;
            // matrix4_log(matrix4_value_ptr(translation_column_major));
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*200, &p_Enemy->instances[0], GL_STATIC_DRAW);

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

    return enemy;
}


Sprite CreatePlayerBullets() 
{
    unsigned int VBO_SHIP_BULLETS, VAO_SHIP_BULLETS, instanceVBO;

    float ship_bullets_vertices[] = 
    {   
            //bullets.xyz         //bullets.rgb
        -0.01f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.01f, -0.15f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.0f, -0.14f, 0.0f,      1.0f, 1.0f, 1.0f,  
    };

    float* pShip_bullets_vertices = &ship_bullets_vertices[0];


    matrix4 translations[1000];

    Sprite playerBullets = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        pShip_bullets_vertices,
        sizeof(ship_bullets_vertices)/sizeof(float),
        VBO_SHIP_BULLETS,
        VAO_SHIP_BULLETS,
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 1000, &p_PlayerBullets->instances[0], GL_STATIC_DRAW);

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

void updateBullets(Sprite* p_Bullets, Sprite* p_Ship, float time, GLFWwindow* window)
{
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
    {
        p_Bullets->instances[p_Ship->bulletsFired] = matrix4_identity();
        p_Bullets->instances[p_Ship->bulletsFired].row4.x = p_Ship->position.x;
        p_Bullets->instances[p_Ship->bulletsFired].row4.y = p_Ship->position.y;
        p_Ship->bulletsFired += 1;
        // printf("\n\nBullets fired: %d\n\n", p_Ship->bulletsFired);

    }

    for(int i = 0; i <= p_Ship->bulletsFired; i++) 
    {
        p_Bullets->instances[i].row4.y += time * 4; 
    }

    // printf("\n\nx: %f y: %f\n\n", p_Bullets->instances[p_Ship->bulletsFired].row4.x, p_Bullets->instances[p_Ship->bulletsFired].row4.y);

    glBindBuffer(GL_ARRAY_BUFFER, p_Bullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 1000, &p_Bullets->instances[0], GL_STATIC_DRAW);

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

}


