#include "raylib.h"

#include "background.h"

Background initBackground(Vector2 backgroundStartLeftTop, Vector2 backgroundEndRightBottom, char* texturePath) {
	Background background;

	
	//"resources/Background/Blue.png"
	Texture2D sky = LoadTexture(texturePath);

	background.backgroundEndRightBottom.x = backgroundEndRightBottom.x;
	background.backgroundEndRightBottom.y = backgroundEndRightBottom.y;

	background.backgroundStartLeftTop.x = backgroundStartLeftTop.x;
	background.backgroundStartLeftTop.y = backgroundStartLeftTop.y;

	background.backgroundTexture = sky;

	background.backgroundTileWidth = BACKGROUND_TILE_WIDTH;
	background.backgroundTileHeight = BACKGROUND_TILE_HEIGHT;

	return background;
}

void unloadBackground(Background* background) {
	UnloadTexture(background->backgroundTexture);
}

void drawBackground(Background* background) {
	for (int y = background->backgroundStartLeftTop.y; y + background->backgroundTileHeight < background->backgroundEndRightBottom.y; y += background->backgroundTileHeight) {
		for (int x = background->backgroundStartLeftTop.x; x + background->backgroundTileWidth < background->backgroundEndRightBottom.x; x += background->backgroundTileWidth) {
			DrawTexture(background->backgroundTexture, x, y, WHITE);
		}
	}
}