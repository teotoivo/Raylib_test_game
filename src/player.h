#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define ANIMATION_IDLE 0
#define ANIMATION_WALKING 1

#define WALKING_SPEED 150


typedef struct {
    int idle;
    int walking;
} PlayerAnimationClocks;

typedef struct {
    Texture2D sprites[2];
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
