#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define ANIMATION_IDLE 0
#define ANIMATION_WALKING 1

typedef struct {
    Texture2D animations[2];
    Rectangle frameRec;
    Vector2 position;
    int verticalVelocity;
    int direction;
    int width;
    int height;
} Player;

Player initPlayer(int x, int y);

void unloadPlayer(Player* player);

// Function to initialize a player
void drawPlayer(Player* player);


#endif // PLAYER_H
