#include "game.h"

/*

    This files contains 1 function that checks for collisions and another than simply
    draws all the sprites to the screen. 

    Both of these have to be done on every frame (in the "render loop" in main.c).

    Rendering everything to the screen is farily straight forward - we select, or
    "bind" the VBO and VAO that we want to use, the shader program that goes with those
    objects ( you can, and we have, multiple shader programs that do different things), 
    and then tell openGL to draw the sprite. 


*/

void update_collisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, float tally, GAME_PROPS* p_GAME, float deltaTime) 
{
    // Keeping track of a tally variable that's modified depending on how many enemy sprites
    // are the screen. 
    // At the moment, I'm not entirely happy with how I'm doing this at the moment, but more information
    // on that can be found in the README file.
    tally = 0;
    // Similarly, we create a timer that ticks every frame while the player is destroyed
    static int respawn_timer = 0;

    if(p_Player->isDestroyed) {
        respawn_timer += 1;

        // If the remainder of x / 500 is 0 then x is a multiple of 500, which creates
        // a nice 5 second (roughly) timeout before the isDestroyed is set back to false.
        if(respawn_timer % 500 == 0) {
            p_Player->isDestroyed = false;
        }
    }


    for(int i = 0; i < 24; i++) 
    {
        tally += p_Enemy->instances[i].row4.x;
        // printf("\n\nx:%f, y: %f\n\n", p_Enemy->instances[i].row4.x, p_Enemy->instances[i].row4.y);

        for(int j = 0; j < p_Player->bulletsFired; j++) 
        {
            if
            (
                // Here we check the position of each enemy with the position of each bullet
                // The way this is done is by checking whether the x and y values of each bullet
                // are both within a certain range (which is the size of the enemy)
                p_Enemy->instances[i].row4.x + (ENEMY_BULLET_WIDTH / 2) >= p_PlayerBullets->instances[j].row4.x 
                && p_Enemy->instances[i].row4.x - (ENEMY_BULLET_WIDTH / 2) <= p_PlayerBullets->instances[j].row4.x
                && p_Enemy->instances[i].row4.y + (ENEMY_BULLET_HEIGHT / 2) >= p_PlayerBullets->instances[j].row4.y
                && p_Enemy->instances[i].row4.y - (ENEMY_BULLET_HEIGHT / 2) <= p_PlayerBullets->instances[j].row4.y
            )

            {
                // The results of a collision...
                // Reducing the hitpoints of the enemy, which in turn chanegs their colour
                p_Enemy->hitPoints[i] -= 1;
                p_Enemy->colors[i].x -= 0.2f;
                p_Enemy->colors[i].y += 0.2f;
                
                // Here we check if the hitpoints of each enemy are zero
                // if so, they've run out of lives and should be removed
                // Again, at this moment I'm just setting their position to outside of the screen
                // but I'm not happy with this and am looking into other solutions so that 
                // the game isn't checking them for collisions and such
                if(p_Enemy->hitPoints[i] <= 0)
                    p_Enemy->instances[i].row4.x = 3.0f;

                p_PlayerBullets->instances[j].row4.x = 4.0f;   
            }
            
        }

    }

    for(int j = 0; j < p_Enemy->bulletsFired; j++) 
    {
        if
        (
            p_Player->position.x + (PLAYER_WIDTH / 2) >= p_EnemyBullets->instances[j].row4.x 
            && p_Player->position.x - (PLAYER_WIDTH / 2) <= p_EnemyBullets->instances[j].row4.x
            && p_Player->position.y + (PLAYER_HEIGHT / 2) >= p_EnemyBullets->instances[j].row4.y
            && p_Player->position.y - (PLAYER_HEIGHT / 2) <= p_EnemyBullets->instances[j].row4.y
        )

        {
            // If the player gets hit, we reset the time value in main.c to zero
            // If you remember from the render loop, we call all our different game functions
            // based on the condition of the time value being higher than 5s returning true, so
            // we're essentially pasuing the game for 5s when the player gets hit
            p_EnemyBullets->instances[j].row4.x = -3.0f; 
            reset_player(p_Player, &respawn_timer);
            
        }
        
    }


    // Again... At the moment this resets the positions of the enemies back to their original
    // positions by checking if the tally/(number of enemies) is equal to 3.0f
    // The reason why this works is because when the enemies are hit, we change their x-coordinate
    // to 3.0, so if they're all at x: 3.0, then the tally/24 should return 3.0
    if(tally/24 == 3.0f) 
    {
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

        p_GAME->round += 1;

        for(int i = 0; i <= 24; i++) {

            p_Enemy->hitPoints[i] = 3;
            p_Enemy->colors[i] = vector4_create(1.0f, 0.0f, 0.0f, 1.0f);
            
        }
        
        // memset(&p_Enemy->hitPoints, 10, sizeof(int) * 24);
        // memset(p_Enemy->colors, vector4_create(1.0f, 0.0f, 0.0f, 1.0f), sizeof(float) * 4 * 24);

        
    }


    
}

void draw_sprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader) 
{           

        glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*24, &p_Enemy->instances[0], GL_STATIC_DRAW);
        glUseProgram(enemyShader);
        glBindVertexArray(p_Enemy->VAO);
        glBindTexture(GL_TEXTURE_2D, p_Enemy->texture_wrap.texture);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 24);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->instanceVBO);
        glUseProgram(playerBulletsShader);
        glBindVertexArray(p_PlayerBullets->VAO);
        glBindTexture(GL_TEXTURE_2D, p_PlayerBullets->texture_wrap.texture);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, p_Player->bulletsFired);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, p_EnemyBullets->instanceVBO);
        glUseProgram(playerBulletsShader);
        glBindVertexArray(p_EnemyBullets->VAO);
        glBindTexture(GL_TEXTURE_2D, p_EnemyBullets->texture_wrap.texture);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, p_Enemy->bulletsFired);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if(!p_Player->isDestroyed){

            glBindBuffer(GL_ARRAY_BUFFER, p_Player->VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_Player->EBO);
            glUseProgram(playerShader);
            glBindVertexArray(p_Player->VAO);
            glBindTexture(GL_TEXTURE_2D, p_Player->texture_wrap.texture);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    
}

void reset_player(Sprite* p_Player, int* respawn_timer) {

    p_Player->isDestroyed = true;
    p_Player->position = vector2_create(0.0f, -0.6f);

}

void update_enemies(Sprite* p_Enemy) {
    

}

void update_positions_sprites(Sprite* p_Player, Sprite* p_Enemy, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets) {

    //Player
    p_Player->position.x += p_Player->velocity.x;
    p_Player->position.y += p_Player->velocity.y;

    //Enemy
    p_Enemy->position.x += p_Enemy->velocity.x;
    p_Enemy->position.y += p_Enemy->velocity.y;



}