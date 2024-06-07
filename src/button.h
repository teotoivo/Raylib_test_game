#include <stdio.h>

#include "raylib.h"

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 1
#define BUTTON_MIDDLE 2

typedef void (*CallbackFunction)();

void Button(Vector2 coordinates, const char* text, CallbackFunction callback, int buttonAlignment);