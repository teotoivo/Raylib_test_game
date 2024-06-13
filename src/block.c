

#include <stdbool.h>

#include "block.h"

Block initBlock(Rectangle rect, Color color, bool isSolid, char* texturePath) {
	Block block;

	block.color = color;
	block.isSolid = isSolid;
	block.rect = rect;
	
	Texture2D texture = LoadTexture(texturePath);
	block.texture = texture;
}


void unloadBlock(Block* block) {
	UnloadTexture(block->texture);
}