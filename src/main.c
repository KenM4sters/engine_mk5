#include "../deps/include/glad/glad.h"
#include "../deps/include/GLFW/glfw3.h"
#include "./engine/shader.h"
#include "./engine/math/matrix4.h"
#include "./engine/math/vector4.h"
#include "./engine/math/vector2.h"
#include "./engine/sprite.h"
#include "./engine/game.h"
#include "./engine/stb_image.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window, Sprite* playerShip);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "game_engine", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to load window");        
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed");
        return -1;
    }

    //Loading Shaders
    unsigned int shipShader = load_shaders("./Shaders/ship.vs", "./Shaders/ship.fs");
    unsigned int shipsBulletsShader = load_shaders("./Shaders/ship_bullets.vs", "./Shaders/ship_bullets.fs");
    unsigned int enemiesShader = load_shaders("./Shaders/enemies.vs", "./Shaders/enemies.fs");
    unsigned int testShader = load_shaders("./Shaders/background.vs", "./Shaders/background.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // Initializing matrix to transform player position 
    matrix4 transformShipMatrix = matrix4_identity();
    float* pTransformShipMatrix = matrix4_value_ptr(transformShipMatrix);

    // Initialising sprites and pointers to sprites
    Sprite player = create_player();
    Sprite enemy = create_enemies();
    Sprite playerBullets = create_player_bullets();
    Sprite enemyBullets = create_enemy_bullets();

    Sprite* p_Player = &player;
    Sprite* p_Enemy = &enemy;
    Sprite* p_PlayerBullets = &playerBullets;
    Sprite* p_EnemyBullets = &enemyBullets;


    // Setting the position of the player at the beggining of the game
    p_Player->position.x = 0;
    p_Player->position.y = -0.6;
    // A variable to keep track of how many enemy sprites are on the screen
    // If it's zero, then the all the sprites return to their orginial positions,
    // as if to give the impression of a new round
    float tally = 0;
    // Time variables
    float deltaTime = 0.0f;
    float previousFrame = 0.0f;
    int timeCounter = 0;
    // Variable to keep track of the round number, which alters 
    // the difficulty of the game through enemy bullet velocity and frequency
    GAME_PROPS GAME;
    GAME.round = 1;
    
    GAME_STATE STATE = END;
    // Using the time libraray to generate a random number 
    // used to randomly select an enemy to fire a bullet
    srand(time(NULL));

    /*
    
        The following block is to render the background texture - will shortly be moved to its
        own function.
    
    */

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char *data = stbi_load(
            "assets/desert-background.png", 
            &width, 
            &height, 
            &nrChannels, 
            0
            );
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

        float vertices[] = {
            // positions      // colors         // texCoords
            1.0f,  1.0f,   0.2f, 0.2f, 0.2f,  1.0f, 1.0f, // top right
            1.0f, -1.0f,   0.2f, 0.2f, 0.2f,  1.0f, 0.0f, // bottom right
           -1.0f, -1.0f,   0.2f, 0.2f, 0.2f,  0.0f, 0.0f, // bottom left
           -1.0f,  1.0f,   0.2f, 0.2f, 0.2f,  0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);


    // Render loop
    // -----------

    while (!glfwWindowShouldClose(window)) 
    { 
        double currentFrame = glfwGetTime();
        // Getting the change in time between frames to use as a constant (roughly)
        // to modify game characteristics such as bullet speed
        // Without deltaTime, those characteristcs may vary from device to device with
        // a different FPS
        deltaTime = currentFrame - previousFrame;
        previousFrame = currentFrame;

        // input
        // -----
        process_input(window, p_Player);
        pTransformShipMatrix[3] = p_Player->position.x; 
        pTransformShipMatrix[7] = p_Player->position.y; 

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glUseProgram(testShader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Game
        // ------
        update_bullets(p_PlayerBullets, p_Player, p_EnemyBullets, p_Enemy, deltaTime, &timeCounter, window, &GAME);
        update_collisions(p_Enemy, p_Player, p_PlayerBullets, p_EnemyBullets, tally, &GAME, deltaTime);
        draw_sprites(p_Enemy, p_Player, p_PlayerBullets, p_EnemyBullets, shipShader, enemiesShader, shipsBulletsShader);
        set_mat4(shipShader, "uTransform", pTransformShipMatrix);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window, Sprite* player)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(!player->isDestroyed) 
    {
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && player->position.x < 0.9)
            player->position.x += 0.01f;

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && player->position.x > -0.9) 
            player->position.x -= 0.01f;
    }
        
    // if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    //     player->position.y += 0.01f;

    // if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
    //     player->position.y -= 0.01f;
    
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}