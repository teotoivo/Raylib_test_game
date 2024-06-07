#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"

#define BACKGROUND_TILE_WIDTH 64
#define BACKGROUND_TILE_HEIGHT 64

typedef struct {
	Vector2 backgroundStartLeftTop;
	Vector2 backgroundEndRightBottom;

	int backgroundTileHeight;
	int backgroundTileWidth;

	Texture2D backgroundTexture;
} Background;

Background initBackground(Vector2 backgroundStartLeftTop, Vector2 backgroundEndRightBottom, char* texturePath);

void unloadBackground(Background* background);

void drawBackground(Background* background);

#endif // BACKGROUND_H