#include "raylib.h"


#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "globals.h"
#include "background.h"

int level1()
{
	//load player
    Player player = initPlayer(200, 400);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.position.x + player.width / 2, SCREEN_HEIGHT / 2.0f };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

		bool levelOver = false;

    Vector2 bgStart = {0, 0};
    Vector2 bgEnd = {SCREEN_WIDTH, SCREEN_HEIGHT};
    Background background = initBackground(bgStart, bgEnd, "resources/Background/Blue.png");

		while (!levelOver)
		{
      if (WindowShouldClose()) {
        unloadBackground(&background);
        return LEVEL_END;
      }
			 // Update variables
        
        updatePlayer(&player);
        camera.target = (Vector2){ player.position.x + player.width / 2, SCREEN_HEIGHT / 2.0f };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);


				BeginMode2D(camera);
            drawBackground(&background);

            //hitbox
            Rectangle playerHitbox = { player.position.x, player.position.y, player.width, player.height };
            DrawRectangleRec(playerHitbox, RED);
            
            drawPlayer(&player);
        EndMode2D();

        
				DrawFPS(10, 10);

				//draw player cooridnates
        DrawText(TextFormat("Player x: %.1f y: %.1f", player.position.x, player.position.y)  , 10, 40, 20, RED);
        DrawText(TextFormat("Player direction: %d", player.direction)  , 10, 70, 20, RED);
        DrawText(TextFormat("Player vertical velocity: %d", player.verticalVelocity)  , 10, 100, 20, RED);

        EndDrawing();
		}
    unloadBackground(&background);
		return LEVEL_NOT_END;
}