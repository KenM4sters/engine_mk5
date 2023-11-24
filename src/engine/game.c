#include "game.h"

void updateCollisions(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, float tally) 
{
    tally = 0;

    for(int i = 0; i < 126; i++) 
    {
        tally += p_Enemy->instances[i].row4.x;
        // printf("\n\nx:%f, y: %f\n\n", p_Enemy->instances[i].row4.x, p_Enemy->instances[i].row4.y);

        for(int j = 0; j < p_Player->bulletsFired; j++) 
        {
            if
            (
                p_Enemy->instances[i].row4.x + 0.025 >= p_PlayerBullets->instances[j].row4.x 
                && p_Enemy->instances[i].row4.x - 0.025 <= p_PlayerBullets->instances[j].row4.x
                && p_Enemy->instances[i].row4.y + 0.025 >= p_PlayerBullets->instances[j].row4.y
                && p_Enemy->instances[i].row4.y - 0.025 <= p_PlayerBullets->instances[j].row4.y
            )

            {
                p_Enemy->instances[i].row4.x = 3.0f;
                p_PlayerBullets->instances[j].row4.x = 4.0f;   
            }
            
        }
    }

    if(tally/126 == 3.0f) 
    {
        int index = 0;
        float offset = 0.05f;
        for(int y = 3; y < 10; y += 1)
        {
            for(int x = -10; x < 10; x += 1)
            {
                matrix4 translation = matrix4_identity();
                translation.row4.x = (float)x / 10.0f + offset;
                translation.row4.y = (float)y / 10.0f + offset;
                p_Enemy->instances[index++] = translation;
                // vector2_log(translation);
            }
        }
    }


    
}

void drawSprites(Sprite* p_Enemy, Sprite* p_Player, Sprite* p_PlayerBullets, unsigned int playerShader, unsigned int enemyShader, unsigned int playerBulletsShader) 
{           

        glBindBuffer(GL_ARRAY_BUFFER, p_Enemy->instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(matrix4)*200, &p_Enemy->instances[0], GL_STATIC_DRAW);
        glUseProgram(enemyShader);
        glBindVertexArray(p_Enemy->VAO);   
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 126);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, p_PlayerBullets->instanceVBO);
        glUseProgram(playerBulletsShader);
        glBindVertexArray(p_PlayerBullets->VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, p_Player->bulletsFired);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, p_Player->VBO);
        // glBindTexture(GL_TEXTURE_2D, p_Player->texture.texture);
        glUseProgram(playerShader);
        glBindVertexArray(p_Player->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
