#include "raylib.h"
#include "raymath.h"

#include <stdio.h>

#define G 600
#define PLAYER_JUMP_VELOCITY 400.0f
#define PLAYER_HORIZONTAL_SPEED 250.0f

#define PLAYER_HEIGHT 40
#define PLAYER_WIDTH 40

#define MAX_VERTICAL_VELOCITY 550.0f

typedef struct Player {
    Vector2 position;
    float verticalVelocity;
    float horizontalVelocity;
    bool canJump;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    Player player = { 0 };
    player.position = (Vector2){ 400, 280 };
    player.verticalVelocity = 0;
    player.canJump = false;
    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY },
        {{ 100, 400 - 50, 100, 50 }, 1, BLACK }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
        

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);


        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            player.position = (Vector2){ 400, 280 };
        }

        

        // Call update camera function by its pointer
        UpdateCameraCenterInsideMap(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            BeginMode2D(camera);

                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

                Rectangle playerRect = { player.position.x - PLAYER_WIDTH/2, player.position.y - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT };
                DrawRectangleRec(playerRect, RED);

            EndMode2D();

            DrawText("Controls:", 20, 20, 10, BLACK);
            DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
            DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
            DrawText("- R to reset", 40, 80, 10, DARKGRAY);
            DrawFPS(20, 100),
           

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HORIZONTAL_SPEED*delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HORIZONTAL_SPEED*delta;
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->verticalVelocity = -PLAYER_JUMP_VELOCITY;
        player->canJump = false;
    }

    int hitFloor = 0;

    float playerNextY = player->position.y += player->verticalVelocity*delta;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *enviromentItem = envItems + i;
        
        Vector2 *pPlayerPosition = &(player->position);
        if (enviromentItem->blocking &&
            enviromentItem->rect.x <= pPlayerPosition->x &&
            enviromentItem->rect.x + enviromentItem->rect.width >= pPlayerPosition->x &&
            enviromentItem->rect.y >= pPlayerPosition->y &&
            enviromentItem->rect.y <= pPlayerPosition->y + player->verticalVelocity*delta)
        {
            hitFloor = 1;
            player->verticalVelocity = 0.0f;
            pPlayerPosition->y = enviromentItem->rect.y;
        }
    }
    if (!hitFloor)
    {
        player->position.y += player->verticalVelocity*delta;
        player->verticalVelocity += G*delta;
        if (player->verticalVelocity > MAX_VERTICAL_VELOCITY)
        {
            player->verticalVelocity = MAX_VERTICAL_VELOCITY;
        }
        player->canJump = false;
    }
    else player->canJump = true;
}

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, *camera);
    Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = height - (max.y - height/2);
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y;
}
