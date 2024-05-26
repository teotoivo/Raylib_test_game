#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define ANIMATION_IDLE 0
#define ANIMATION_WALKING 1
#define ANIMATION_JUMPING 2
#define ANIMATION_FALLING 3

#define WALKING_SPEED 150
#define PLAYER_JUMP_HEIGHT 350
#define MAX_FALL_SPEED 250

#define GRAVITY 1000


typedef struct {
    int idle;
    int walking;
    int jumping;
    int falling;
} PlayerAnimationClocks;

typedef struct {
    Texture2D sprites[15];
    Rectangle frameRec;
    Vector2 position;
    int verticalVelocity;
    int direction;
    int width;
    int height;

    PlayerAnimationClocks animationClocks;
} Player;

Player initPlayer(int x, int y);

void unloadPlayer(Player* player);

void updatePlayer(Player* player);
void drawPlayer(Player* player);


#endif // PLAYER_H
