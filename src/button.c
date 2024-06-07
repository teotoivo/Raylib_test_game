#include "raylib.h"

#include "button.h"

#define BUTTON_FONT_SIZE 20
#define BUTTON_PADDING 10

void Button(Vector2 coordinates, const char* text, CallbackFunction callback, int buttonAlignment) {
	int buttonWidth = MeasureText(text, BUTTON_FONT_SIZE) + 2 * BUTTON_PADDING;

	int x;
	int y = coordinates.y - (20 + BUTTON_PADDING * 2);
	switch (buttonAlignment)
	{
	case BUTTON_LEFT:
		x = coordinates.x;
		break;
	case BUTTON_MIDDLE:
		x = coordinates.x - (buttonWidth / 2);
		break;
	case BUTTON_RIGHT:
		x = coordinates.x - buttonWidth;
		break;
	}

	Rectangle buttonRect = { x, y, buttonWidth, BUTTON_FONT_SIZE + 2 * BUTTON_PADDING };
	bool isButtonPressed = false;
	
	if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			isButtonPressed = true;
		}
	}
	
	if (isButtonPressed)
	{
		DrawRectangleRec(buttonRect, GRAY);
		callback();
	}
	else
	{
		DrawRectangleRec(buttonRect, LIGHTGRAY);
	}
	
	DrawText(text, x + BUTTON_PADDING, y + BUTTON_PADDING, BUTTON_FONT_SIZE, DARKGRAY);
}