#include "game.h"

typedef enum {PLAY, PAUSE, END} GAME_STATE;

void update_collisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, float tally) 
{
    tally = 0;

    for(int i = 0; i < 24; i++) 
    {
        tally += p_Enemy->instances[i].row4.x;
        // printf("\n\nx:%f, y: %f\n\n", p_Enemy->instances[i].row4.x, p_Enemy->instances[i].row4.y);

        for(int j = 0; j < p_Player->bulletsFired; j++) 
        {
            if
            (
                p_Enemy->instances[i].row4.x + 0.05 >= p_PlayerBullets->instances[j].row4.x 
                && p_Enemy->instances[i].row4.x - 0.05 <= p_PlayerBullets->instances[j].row4.x
                && p_Enemy->instances[i].row4.y + 0.05 >= p_PlayerBullets->instances[j].row4.y
                && p_Enemy->instances[i].row4.y - 0.05 <= p_PlayerBullets->instances[j].row4.y
            )

            {
                p_Enemy->instances[i].row4.x = 3.0f;
                p_PlayerBullets->instances[j].row4.x = 4.0f;   
            }
            
        }

        for(int j = 0; j < p_Player->bulletsFired; j++) 
        {
            if
            (
                p_EnemyBullets->instances[j].row4.x + 0.02 >= p_Player->position.x 
                && p_EnemyBullets->instances[j].row4.x - 0.02 <= p_Player->position.x
                && p_EnemyBullets->instances[j].row4.y + 0.02 >= p_Player->position.y
                && p_EnemyBullets->instances[j].row4.y - 0.02 <= p_Player->position.y
            )

            {
                p_EnemyBullets->instances[i].row4.x = -3.0f;
                p_Player->position.x = -4.0f;   
            }
            
        }
    }

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
    }


    
}

void draw_sprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, Sprite* p_EnemyBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader) 
{           

        glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*24, &p_Enemy->instances[0], GL_STATIC_DRAW);
        glUseProgram(enemyShader);
        glBindVertexArray(p_Enemy->VAO);   
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 24);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->instanceVBO);
        glUseProgram(playerBulletsShader);
        glBindVertexArray(p_PlayerBullets->VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, p_Player->bulletsFired);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, p_EnemyBullets->instanceVBO);
        glUseProgram(playerBulletsShader);
        glBindVertexArray(p_EnemyBullets->VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 24);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, p_Player->VBO);
        // glBindTexture(GL_TEXTURE_2D, p_Player->texture.texture);
        glUseProgram(playerShader);
        glBindVertexArray(p_Player->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
