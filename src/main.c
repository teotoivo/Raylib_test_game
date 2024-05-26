#include "raylib.h"


// C standard library
#include <stdio.h>

#include "player.h"
#include "globals.h"


int main(void)
{
    //initalization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first game");

    //load player
    Player player = initPlayer(200, 400);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.position.x + player.width / 2, SCREEN_HEIGHT / 2.0f };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    //main game loop
    while (!WindowShouldClose())
    {
        // Update variables
        
        updatePlayer(&player);
        camera.target = (Vector2){ player.position.x + player.width / 2, SCREEN_HEIGHT / 2.0f };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

       

        DrawFPS(10, 10);

        //draw player cooridnates
        DrawText(TextFormat("Player x: %.1f y: %.1f", player.position.x, player.position.y)  , 10, 40, 20, RED);
        DrawText(TextFormat("Player direction: %d", player.direction)  , 10, 70, 20, RED);
        DrawText(TextFormat("Player vertical velocity: %d", player.verticalVelocity)  , 10, 100, 20, RED);
        
        

        BeginMode2D(camera);
            DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, RED);
            DrawRectangle(0, SCREEN_HEIGHT / 2 - 100, 100, 100, BLUE);

            Rectangle playerHitbox = { player.position.x, player.position.y, player.width, player.height };
            DrawRectangleRec(playerHitbox, RED);
            drawPlayer(&player);
        EndMode2D();

        EndDrawing();
    }

    // Unload everything
    CloseWindow();
}