#include "raylib.h"

#include "globals.h"
#include "level_start.h"
#include "button.h"

#include <stdbool.h>

void buttonCallBack();

int level_start() {

	while (currentLevel == LEVEL_START)
	{

		if (WindowShouldClose()) {
			return LEVEL_END;
		}

		BeginDrawing();
      ClearBackground(RAYWHITE);
			DrawFPS(10, 10);

			Vector2 buttonLocation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

			Button(buttonLocation, "Level 1", buttonCallBack, BUTTON_MIDDLE);

		EndDrawing();
		
	}
	return LEVEL_NOT_END;
}

void buttonCallBack() {
	currentLevel = LEVEL_LEVEL_1;
}