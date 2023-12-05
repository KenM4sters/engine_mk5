#include "sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*

    In this file, we firstly create all the different functions for rendering the sprites
    on the screen. In summary, this involves the following procedure:

        1.  Allocating memory (an OpenGL "Vertex Buffer Object, or VBO") for an array that the 
            shader programs will use to render the vertices, colors, 
            textures etc of the ship.

            It's really up to you what you want to be in these buffer objects,
            and you'll see that throughout this program I captalise on their ability
            to change per vertex to create lots of different objects with different colours, 
            health, posiitons etc..
        
        2.  Allocating a vertex array object (VAO) which tells the shaders how to infer
            the data of the buffer object at question. 

            For example, in this application, I use a buffer object to store both the
            data for the vertices of my player ship and it's color. Without a VAO,
            my shaders wouldn't know which float corresponds to the vertex or the colour.

            The VAO explicitly tells my shader which floats should be used for the position 
            and which floats should be used for the colour. This is achieved quite simply
            by stating a starting position, how many floats are used, and after how many floats
            we return to the correct float (known as the Stride). 
            
            For example:

                "For the colour, start at the 4th element in the array, read the next 4 elements, 
                 and then come back here after you've read an aditional 10 elements"

        3.  Return the structure which contains the VBO and VAO, to be used
            in the rendering function to render the sprite to the screen.




*/

Sprite create_player() 
{
    unsigned int VBO_SHIP, EBO_SHIP, VAO_SHIP;

    float playerVertices[] = {
        // positions          // colors           // texture coords
         0.05f,  0.07f,   1.0f, 0.0f, 0.0f,   0.6f, 1.0f, // top right
         0.05f, -0.07f,   0.0f, 1.0f, 0.0f,   0.6f, 0.8f, // bottom right
        -0.05f, -0.07f,   0.0f, 0.0f, 1.0f,   0.4f, 0.8f, // bottom left
        -0.05f,  0.07f,   1.0f, 1.0f, 0.0f,   0.4f, 1.0f  // top left 
    };

    unsigned int playerIndices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Sprite player = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        &playerVertices[0],
        sizeof(playerVertices)/sizeof(float),
        &playerIndices[0],
        VBO_SHIP,
        EBO_SHIP,
        VAO_SHIP,

    };

    // TEXTURE
    // -----
    // stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(
        "assets/SpaceShooterAssetPack_Ships.png", 
        &player.texture_wrap.width, 
        &player.texture_wrap.height, 
        &player.texture_wrap.nrChannels, 
        0
        );

    glGenTextures(1, &player.texture_wrap.texture);
    glBindTexture(GL_TEXTURE_2D, player.texture_wrap.texture);

    if (data)
    {

        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            player.texture_wrap.width, 
            player.texture_wrap.height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data
            );

        glGenerateMipmap(GL_TEXTURE_2D);
        printf("width: %d", player.texture_wrap.height);
    }
    else
    {
        printf("\n\nFailed to load texture\n\n");
    }
    
    stbi_image_free(data);



    // Currently testing returning a pointer to the struct instead of the 
    // the struct itself
    Sprite* p_Player = &player;    

    // Player
    glGenVertexArrays(1, &p_Player->VAO);
    glGenBuffers(1, &p_Player->VBO);
    glGenBuffers(1, &p_Player->EBO);

    glBindVertexArray(p_Player->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, p_Player->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_Player->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerIndices), playerIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glBindVertexArray(0);

    return player;


}

Sprite create_enemies() 
{
    // Enemies
    unsigned int VBO_SHIP_ENEMIES, EBO_SHIP_ENEMIES, VAO_SHIP_ENEMIES, instanceVBO;

    float enemies_vertices[] = 
    {
        //enemies.xyz      //enemies.rgb       //Text Coords
        -0.04f, 0.0f,   0.5f, 0.0f, 0.0f,     0.4f, 0.4f,
         0.04f, 0.0f,   0.5f, 0.0f, 0.0f,     0.6f, 0.4f,
         0.0f, -0.08f,  0.5f, 0.0f, 0.0f,     0.5f, 0.2f
    };

    unsigned int enemy_indices[] = 
    {
        0, 1, 2,
        1, 2, 3,
    }; 

    
    // Initializing an an array of matrices (which in this program are an array of vectors, 
    // which are an array of floats), to be used to position the enemies
    matrix4 translations[24];

    // Similarly to the translations array, we initialze an array of hitpoints to 
    // keep track of how many times an enemy has been hit
    int enemyHitPoints[24];

    Sprite enemy = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f), 
        0,
        0,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        &enemies_vertices[0],
        sizeof(enemies_vertices)/sizeof(float), 
        &enemy_indices[0],
        VBO_SHIP_ENEMIES, 
        EBO_SHIP_ENEMIES,
        VAO_SHIP_ENEMIES,  
        *translations,
        instanceVBO

    }; 

    // Looping through the arrays to set their initial values
    for(int i = 0; i <= 24; i++)
        enemy.hitPoints[i] = 3;

    // memset(enemy.hitPoints, 1, sizeof(int) * 24);
    
    for(int i = 0; i <= 24; i++)
        enemy.colors[i] = vector4_create(1.0f, 0.0f, 0.0f, 1.0f);
    
    
    Sprite* p_Enemy = &enemy;


    // This snippet of code positions the enmies in rows and coloumns across the screen
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

            // Shader programs infer matrices as column major, meaning that
            // it essentially reads my row major matrices with their coloumn and
            // row values swapped. Obviously, this is a problem since I'll then be
            // changing the wrong values when it comes to modifying their positions
            // and such, so I created a function (matrix4_transpose) that returns the
            // passed through matrix but swaps the columns with the rows
            matrix4 translation_column_major = matrix4_transpose(translation);
            p_Enemy->instances[index++] = translation_column_major;
            moveRow += 1;
        }
    }

        // TEXTURE
    // -----
    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(
        "assets/SpaceShooterAssetPack_Ships.png", 
        &enemy.texture_wrap.width, 
        &enemy.texture_wrap.height, 
        &enemy.texture_wrap.nrChannels, 
        0
        );

    glGenTextures(1, &enemy.texture_wrap.texture);
    glBindTexture(GL_TEXTURE_2D, enemy.texture_wrap.texture);

    if (data)
    {

        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            enemy.texture_wrap.width, 
            enemy.texture_wrap.height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data
            );

        glGenerateMipmap(GL_TEXTURE_2D);
        printf("width: %d", enemy.texture_wrap.height);
    }
    else
    {
        printf("\n\nFailed to load texture\n\n");
    }
    
    stbi_image_free(data);

    glGenBuffers(1, &p_Enemy->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*p_Enemy->verticesCount, p_Enemy->vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &p_Enemy->VAO);
    glBindVertexArray(p_Enemy->VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

    // Enemy instances
    glGenBuffers(1, &p_Enemy->instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*24, &p_Enemy->instances[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Colors
    glGenBuffers(1, &p_Enemy->colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector4) * 24, &p_Enemy->colors[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribDivisor(7, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    return enemy;
}


Sprite create_player_bullets() 
{
    unsigned int VBO_SHIP_BULLETS, EBO_SHIP_BULLETS, VAO_SHIP_BULLETS, instanceVBO;

    float player_bullet_vertices[] = 
    {   
            //bullets.xyz         //bullets.rgb
        -0.005f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.005f, -0.15f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.0f, -0.145f, 0.0f,      1.0f, 1.0f, 1.0f,  
    };

    unsigned int player_bullet_indices[] = 
    {
        0, 1, 2,
        1, 2, 3,
    }; 


    // Same situation as the enemy translations array, but instead this is for the players bullets
    matrix4 translations[10000];

    Sprite playerBullets = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        &player_bullet_vertices[0],
        sizeof(player_bullet_vertices)/sizeof(float),
        &player_bullet_indices[0],
        VBO_SHIP_BULLETS,
        EBO_SHIP_BULLETS,
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
    unsigned int VBO_ENEMY_BULLETS, EBO_ENEMY_BULLETS, VAO_ENEMY_BULLETS, instanceVBO;

    float enemy_bullets_vertices[] = 
    {   
            //bullets.xyz         //bullets.rgb
        -0.01f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.01f, -0.15f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.0f, -0.16f, 0.0f,      1.0f, 1.0f, 1.0f,  
    };

    unsigned int enemy_bullet_indices[] = 
    {
        0, 1, 2,
        1, 2, 3,
    }; 

    // same situation as with the player bullets, but for the enemy bullets
    matrix4 translations[1000];

    Sprite enemyBullets = 
    {
        vector2_create(0.0f, 0.0f),
        vector2_create(0.0f, 0.0f),
        0,
        1,
        {vector2_create(0.0f, 0.0f), vector2_create(0.0f, 0.0f)},

        &enemy_bullets_vertices[0],
        sizeof(enemy_bullets_vertices)/sizeof(float),
        &enemy_bullet_indices[0],
        VBO_ENEMY_BULLETS,
        EBO_ENEMY_BULLETS,
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


/*

    The following function updates both the player and enemy bullets so that 
    they move down the screen over time. 

    This involves a lot more code than what you may think 
    (or at least what I thought at the beginning) since there's a few pieces of
    information that we need to gather first on every frame:

        1.  Firstly, we need the player position at the time of firing (pressing the spacebar)
            to know where to render the bullets, but we don't want this to change over time. 
            We only want to know where the ship was at the time of firing - we don't want
            the bullets to respond to any player movement after firing.
        
        2.  We need to give the bullets some vertical velocity (+ for the player, - for the enemies)
            to make the bullets move over time.
        
        3.  We need to create some kind of condition that modifies the value of the 
            enemy bullet's velocity and frequency based on the round number.

        5.  After we've done all of the above, we need to rerender the bullets to the screen
            on each frame.

*/

void update_bullets(Sprite* p_PlayerBullets, Sprite* p_Player, Sprite* p_EnemyBullets, Sprite* p_Enemy, float deltaTime, int* timeCounter, GLFWwindow* window, GAME_PROPS* p_GAME)
{
    // Dereferencing the timeCounter to add one to its value one each frame.
    // This is used to fire enemy bullets over time
    *timeCounter += 1;
    
    // Processing user input
    // -------
    // When the user presses the spacebar, we index into the VBO of player bullet's
    // translations array of matrices with the value of the number of bullets that have been
    // fired, and firstly enter a plain identity matrix which does nothing.
    // We need modify this matrix to set the position of the bullet based on the position of 
    // the ship at the time of pressing the spacebar
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetTime() > 0.1 && !p_Player->isDestroyed) 
    {
        p_PlayerBullets->instances[p_Player->bulletsFired] = matrix4_identity();
        p_PlayerBullets->instances[p_Player->bulletsFired].row4.x = p_Player->position.x;
        p_PlayerBullets->instances[p_Player->bulletsFired].row4.y = p_Player->position.y + PLAYER_HEIGHT;
        p_Player->bulletsFired += 1;
        glfwSetTime(0);
        // printf("\n\nBullets fired: %d\n\n", p_Player->bulletsFired);

    }

    // Translating the bullets up the screen over time
    for(int i = 0; i <= p_Player->bulletsFired; i++) 
    {
        p_PlayerBullets->instances[i].row4.y += 0.008 * 4; 
    }

    // Rendering enemy bullets over time, at the position of a random
    // enemy, based on the round number.
    // I also provide the condition that the time counter is over 500
    // to give the player some time to prepare at the beginning
    if((*timeCounter % 100) / p_GAME->round == 0 && *timeCounter > 500) 
    {   
        int r = rand() % 24;
        
        if(p_Enemy->instances[p_Enemy->bulletsFired].row4.x != 3.0f)
            p_EnemyBullets->instances[p_Enemy->bulletsFired] = p_Enemy->instances[r];
            p_Enemy->bulletsFired += 1;
    }


    // Translating the enemy bullets down the screen
    for(int i = 0; i <= p_Enemy->bulletsFired; i++) 
    {
        p_EnemyBullets->instances[i].row4.y -= (0.008 * 2) + p_GAME->round / 10;
    }


    // Re-rendering all the bullets to the screen
    glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4) * 10000, &p_PlayerBullets->instances[0], GL_STATIC_DRAW);
    glBindVertexArray(p_PlayerBullets->VAO);
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

    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribDivisor(7, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


