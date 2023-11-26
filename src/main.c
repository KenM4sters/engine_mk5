#include "../deps/include/glad/glad.h"
#include "../deps/include/GLFW/glfw3.h"
#include "./engine/shader.h"
#include "./engine/math/matrix4.h"
#include "./engine/math/vector4.h"
#include "./engine/math/vector2.h"
#include "./engine/sprite.h"
#include "./engine/game.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window, Sprite* playerShip);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        printf("\n\nE was pressed\n\n");
}

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

    //Shaders
    unsigned int shipShader = load_shaders("./Shaders/ship.vs", "./Shaders/ship.fs");
    unsigned int shipsBulletsShader = load_shaders("./Shaders/ship_bullets.vs", "./Shaders/ship_bullets.fs");
    unsigned int enemiesShader= load_shaders("./Shaders/enemies.vs", "./Shaders/enemies.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // Matrix
    matrix4 transformShipMatrix = matrix4_identity();
    float* pTransformShipMatrix = matrix4_value_ptr(transformShipMatrix);
    matrix4 test = matrix4_create(
        vector4_create(1.0, 2.0, 3.0, 4.0),
        vector4_create(5.0, 6.0, 7.0, 8.0),
        vector4_create(9.0, 10.0, 11.0, 12.0),
        vector4_create(13.0, 14.0, 15.0, 16.0)
    );

    matrix4_log(matrix4_value_ptr(test));
    printf("\n\n");

    matrix4 test_reversed = matrix4_transpose(test);
    matrix4_log(matrix4_value_ptr(test_reversed));

    Sprite player = create_player();
    Sprite enemy = create_enemies();
    Sprite playerBullets = create_player_bullets();
    Sprite enemyBullets = create_enemy_bullets();

    Sprite* p_Player = &player;
    Sprite* p_Enemy = &enemy;
    Sprite* p_PlayerBullets = &playerBullets;
    Sprite* p_EnemyBullets = &enemyBullets;

    float tally = 0;

    // render loop
    // -----------

    float deltaTime = 0.0f;
    float previousFrame = 0.0f;
    int timeCounter = 0;

    typedef enum {GAME_PLAY, GAME_PAUSE, GAME_END} GAME_STATE;

    GAME_STATE GAME = GAME_PAUSE;

    srand(time(NULL));

    while (!glfwWindowShouldClose(window)) 
    { 
        double currentFrame = glfwGetTime();

        deltaTime = currentFrame - previousFrame;
        previousFrame = currentFrame;
        // input
        // -----
        glfwSetKeyCallback(window, key_callback);
        process_input(window, p_Player);
        pTransformShipMatrix[3] = p_Player->position.x; 
        pTransformShipMatrix[7] = p_Player->position.y; 
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Game
        // ------
        update_bullets(p_PlayerBullets, p_Player, p_EnemyBullets, p_Enemy, deltaTime, &timeCounter, window);
        update_collisions(p_Enemy, p_Player, p_PlayerBullets, p_EnemyBullets, tally);
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

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player->position.x += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        player->position.x -= 0.01f;
        
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        player->position.y += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        player->position.y -= 0.01f;
    
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}