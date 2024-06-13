#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
	Rectangle rect;
	Color color;
	bool isSolid;
	Texture2D texture;
} Block;

Block initBlock(Rectangle rect, Color color, bool isSolid, char* texturePath);
void unloadBlock(Block* block);

#endif // BLOCK_H