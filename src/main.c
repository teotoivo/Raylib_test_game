#include "raylib.h"

// C standard library
#include <stdio.h>

#include "player.h"

// Define constants
#define WALKING_SPEED 150

int animationClock = 0;

int main(void)
{
    //initalization
    const int screenWidth = 800;
    const int screenHeight= 450;
    
    InitWindow(screenWidth, screenHeight, "My first game");

    //load player
    Player player = initPlayer(200, 200);

    SetTargetFPS(60);

    int animationClock = 0;
    float animationTimerS = 0;

    //main game loop
    while (!WindowShouldClose())
    {
        // Update variables
        float deltaTime = GetFrameTime();
        if ((animationTimerS += deltaTime) > 0.100f) {
            animationTimerS -= 0.100f;
            animationClock++;
            if (animationClock > 10) animationClock = 0;
        }

        player.direction = 0;
        if (IsKeyDown(KEY_LEFT)) {
            player.position.x -= WALKING_SPEED * deltaTime;
            player.direction = -1;
            if (player.frameRec.width > 0) {
                player.frameRec.width = -player.frameRec.width;
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {
            if (player.frameRec.width < 0) {
                player.frameRec.width = -player.frameRec.width;
            }
            player.position.x += WALKING_SPEED * deltaTime;
            player.direction = 1;
        }

        
        player.frameRec.x = (float) PLAYER_WIDTH * animationClock;


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawPlayer(&player);

        EndDrawing();
    }

    // Unload everything
    CloseWindow();
}