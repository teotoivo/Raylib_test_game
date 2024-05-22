#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define IDLE_ANIMATION 0
#define WALKING_ANIMATION 1

// defined in player.c
extern const float PLAYER_WIDTH;
extern const float PLAYER_HEIGHT;

typedef struct {
    Texture2D animations[2];
    Rectangle frameRec;
    Vector2 position;
    int verticalVelocity;
    int direction;
} Player;

Player initPlayer(int x, int y);

void unloadPlayer(Player* player);

// Function to initialize a player
void drawPlayer(Player* player);


#endif // PLAYER_H
