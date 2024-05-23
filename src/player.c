#include "raylib.h"

#include <stdio.h>

#include "player.h"
#include "globals.h"

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;

Player initPlayer(int x, int y)
{
	Player player;


	//! IMPORTANT when adding more animations remember to update the unload loops size and the size of the array in the header
	Texture2D idle = LoadTexture("resources/Main Characters/Virtual Guy/Idle (32x32).png");
  Texture2D walking = LoadTexture("resources/Main Characters/Virtual Guy/Run (32x32).png");

	player.animations[0] = idle;
	player.animations[1] = walking;

	player.height = PLAYER_HEIGHT;
	player.width = PLAYER_WIDTH;

	player.position.x = x;
	player.position.y = y;

	player.direction = 0;

	player.verticalVelocity = 0;

	player.frameRec.x = 0.0f;
	player.frameRec.y = 0.0f;
	player.frameRec.height = PLAYER_HEIGHT;
	player.frameRec.width = PLAYER_WIDTH;

	return player;
}

void unloadPlayer(Player* player)
{
    for (int i = 0; i < 2; i++) {
        if (player->animations[i].id != 0) {
            UnloadTexture(player->animations[i]);
        }
    }
}

void drawPlayer(Player* player)
{
	char animationClockStr[10];
	sprintf(animationClockStr, "%d", animationClock);
	TraceLog(LOG_INFO, animationClockStr);
	
	if (player->direction != 0) {
    DrawTextureRec(player->animations[ANIMATION_WALKING], player->frameRec, player->position, WHITE);
  } else {
     DrawTextureRec(player->animations[ANIMATION_IDLE], player->frameRec, player->position, WHITE);
  }
}