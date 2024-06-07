#include "raylib.h"


#include <stdio.h>

#include "player.h"
#include "globals.h"

//levels
#include "level_start.h"
#include "level1.h"

int main(void)
{
  //initalization
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first game");

    

  SetTargetFPS(60);

  bool shouldWindowClose = false;

  //main game loop
  while (!shouldWindowClose)
  {
	
		switch (currentLevel) {
			case LEVEL_START:
				if (level_start() == LEVEL_END) {
          shouldWindowClose = true;
        }

				break;
			case LEVEL_LEVEL_1:
				if (level1() == LEVEL_END) {
          shouldWindowClose = true;
        }
				
				break;
		}	
    
  }

  // Unload everything
  CloseWindow();
}