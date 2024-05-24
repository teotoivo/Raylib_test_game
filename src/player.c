#include "raylib.h"

#include <stdio.h>

#include "player.h"
#include "globals.h"

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;

float idleAnimationTimer = 0;
float walkingAnimationTimer = 0;

int currentAnimation(Player* player)
{
    if (player->direction != 0) {
        return ANIMATION_WALKING;
    } else {
        return ANIMATION_IDLE;
    }
}

Player initPlayer(int x, int y)
{
	Player player;


	//! IMPORTANT when adding more animations remember to update the unload loops size and the size of the array in the header
	Texture2D idle = LoadTexture("resources/Main Characters/Virtual Guy/Idle (32x32).png");
    Texture2D walking = LoadTexture("resources/Main Characters/Virtual Guy/Run (32x32).png");

	player.sprites[0] = idle;
	player.sprites[1] = walking;

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

    player.animationClocks.idle = 0;
    player.animationClocks.walking = 0;
	return player;
}

void unloadPlayer(Player* player)
{
    for (int i = 0; i < 2; i++) {
        if (player->sprites[i].id != 0) {
            UnloadTexture(player->sprites[i]);
        }
    }
}

void drawPlayer(Player* player)
{
    switch (currentAnimation(player))
    {
    case ANIMATION_IDLE:
        DrawTextureRec(player->sprites[ANIMATION_IDLE], player->frameRec, player->position, WHITE);
        break;
    
    case ANIMATION_WALKING:
        DrawTextureRec(player->sprites[ANIMATION_WALKING], player->frameRec, player->position, WHITE);
        break;
    }
}

void updatePlayer(Player* player)
{
	// Player movment
    player->direction = 0;
    if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= WALKING_SPEED * GetFrameTime();
        player->direction = -1;
        if (player->frameRec.width > 0) {
            player->frameRec.width = -player->frameRec.width;
        }
    }
    if (IsKeyDown(KEY_RIGHT)) {
        if (player->frameRec.width < 0) {
            player->frameRec.width = -player->frameRec.width;
        }
        player->position.x += WALKING_SPEED * GetFrameTime();
        player->direction = 1;
    }

    switch (currentAnimation(player))
    {
        case ANIMATION_IDLE:
            float idleAnimationSpeed = 0.15f;
            if ((idleAnimationTimer += GetFrameTime()) > idleAnimationSpeed) {
                idleAnimationTimer -= idleAnimationSpeed;
                player->animationClocks.idle++;
                if (player->animationClocks.idle > 10) player->animationClocks.idle = 0;
            }

            player->frameRec.x = (float) player->width * player->animationClocks.idle;
            break;

        case ANIMATION_WALKING:
            float walkingAnimationSpeed = 0.07f;
            if ((walkingAnimationTimer += GetFrameTime()) > walkingAnimationSpeed) {
                walkingAnimationTimer -= walkingAnimationSpeed;
                player->animationClocks.walking++;
                if (player->animationClocks.walking > 10) player->animationClocks.walking = 0;
            }

            player->frameRec.x = (float) player->width * player->animationClocks.walking;
            break;
    }
}