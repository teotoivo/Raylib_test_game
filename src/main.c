#include "raylib.h"

// C standard library
#include <stdio.h>

#include "player.h"
#include "globals.h"

// Define constants
#define WALKING_SPEED 150

int animationClock = 0;

int getSpriteAnimationOffSet(int maxNum, float animationSpeedMultiplier) {
    // Map the number to the range 0 to maxNum - 1, adjusted by the animationSpeedMultiplier
    int result = (int)((animationClock * animationSpeedMultiplier) / 100.0 * maxNum);
    return result % maxNum; // Ensure the result stays within 0 to maxNum - 1
}

int main(void)
{
    //initalization
    const int screenWidth = 800;
    const int screenHeight= 450;
    
    InitWindow(screenWidth, screenHeight, "My first game");

    //load player
    Player player = initPlayer(200, 200);

    SetTargetFPS(60);

    
    float animationTimerS = 0;

    //main game loop
    while (!WindowShouldClose())
    {
        // Update variables
        float deltaTime = GetFrameTime();
        if ((animationTimerS += deltaTime) > 0.010f) {
            animationTimerS -= 0.010f;
            animationClock++;
            if (animationClock > 100) animationClock = 0;
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

        
        // player.frameRec.x = (float) player.width * animationClock;
        player.frameRec.x = (float) player.width * getSpriteAnimationOffSet(10, 2);
        


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawPlayer(&player);

        EndDrawing();
    }

    // Unload everything
    CloseWindow();
}