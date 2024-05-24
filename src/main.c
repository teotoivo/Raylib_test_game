#include "raylib.h"

// C standard library
#include <stdio.h>

#include "player.h"
#include "globals.h"


int main(void)
{
    //initalization
    const int screenWidth = 800;
    const int screenHeight= 450;
    
    InitWindow(screenWidth, screenHeight, "My first game");

    //load player
    Player player = initPlayer(200, 200);

    SetTargetFPS(60);

    //main game loop
    while (!WindowShouldClose())
    {
        // Update variables
        
        updatePlayer(&player);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        drawPlayer(&player);

        EndDrawing();
    }

    // Unload everything
    CloseWindow();
}