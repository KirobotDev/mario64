#include "raylib.h"
#include <stdio.h>

int main(void)
{
    const int screenWidth = 500;
    const int screenHeight = 380;
    int playerSize = 64;

    struct player {
        int playerX;
        int playerY;
    };

    struct player player;

    player.playerX = 0;
    player.playerY = 260;

    int a = 0;

    char playerplacement[32];

    InitWindow(screenWidth, screenHeight, "Mario 64");
    Image icon = LoadImage("./image/icon.png");
    Texture2D background = LoadTexture("./image/background.png");
    Texture2D playerTexture = LoadTexture("./image/player.png");
    Texture2D playerjump = LoadTexture("./image/jump.png");

    Texture2D lucky[4] = {
        LoadTexture("./image/lucky.png"),
        LoadTexture("./image/lucky.png"),
        LoadTexture("./image/lucky.png"),
        LoadTexture("./image/lucky.png")
    };

    Texture2D piece[3] = {
        LoadTexture("./image/piece.png"),
        LoadTexture("./image/piece.png"),
        LoadTexture("./image/piece.png")
    };

    Texture2D champignon = LoadTexture("./image/champignon.png");
    SetWindowIcon(icon);
    SetTargetFPS(30);    

    while (!WindowShouldClose())    
    {
        BeginDrawing();

        int currentGround = (a == 1) ? 235 : 260;

        Rectangle playerRect = {
            player.playerX,
            player.playerY,
            playerSize,
            playerSize
        };

        Rectangle blockRect = {
            200,
            170,
            32,
            32
        };

        Rectangle champignonRect = {
            200,
            170,
            32,
            32
        };

            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);
            snprintf(playerplacement, sizeof(playerplacement), "%d", player.playerX);
            DrawText("Position Player : ", 0, 0, 20, WHITE);
            DrawText(playerplacement, 180, 0, 20, WHITE);

            if (IsKeyDown(KEY_D)) {
                player.playerX += 10;
            }

            if (IsKeyDown(KEY_A)) {
                player.playerX -= 10;
            }

            if (player.playerY < currentGround) {
                player.playerY += 5;
                if (player.playerY > currentGround) player.playerY = currentGround;
            }

            if (player.playerY < currentGround) {

                if (IsKeyDown(KEY_A)) {
                    DrawTexturePro(
                        playerjump,
                        (Rectangle){0, 0, -playerjump.width, playerjump.height},
                        (Rectangle){player.playerX, player.playerY, playerSize, playerSize},
                        (Vector2){0, 0},
                        0,
                        WHITE
                    );
                } else {
                    DrawTexturePro(
                        playerjump,
                        (Rectangle){0, 0, playerjump.width, playerjump.height},
                        (Rectangle){player.playerX, player.playerY, playerSize, playerSize},
                        (Vector2){0, 0},
                        0,
                        WHITE
                    );
                }

            } else {

                if (IsKeyDown(KEY_A)) {
                    DrawTexturePro(
                        playerTexture,
                        (Rectangle){0, 0, -playerTexture .width, playerTexture .height},
                        (Rectangle){player.playerX, player.playerY, playerSize, playerSize},
                        (Vector2){0, 0},
                        0,
                        WHITE
                    );
                } else {
                    DrawTexturePro(
                        playerTexture,
                        (Rectangle){0, 0, playerTexture .width, playerTexture .height},
                        (Rectangle){player.playerX, player.playerY, playerSize, playerSize},
                        (Vector2){0, 0},
                        0,
                        WHITE
                    );
                }
            }

            if (player.playerY == currentGround) {
                if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) {
                    player.playerY -= 80;
                }
            }

            if (a == 0) {
                DrawTexturePro(
                    lucky[0],
                    (Rectangle){0, 0, lucky[0].width, lucky[0].height},
                    (Rectangle){200, 170, 32, 32},
                    (Vector2){0, 0},
                    0,
                    WHITE
                );
            }


            if (CheckCollisionRecs(playerRect, blockRect) && a == 0) {
                DrawTexturePro(
                    champignon,
                    (Rectangle){0, 0, champignon.width, champignon.height},
                    (Rectangle){200, 170, 32, 32},
                    (Vector2){0, 0},
                    0,
                    WHITE
                );
                a = 1;
            } else if (CheckCollisionRecs(playerRect, champignonRect) && a == 1) {
                playerSize = 90;
                if (player.playerY == 260) {
                    player.playerY = 220;
                }
            }
            

        EndDrawing();
    }

    CloseWindow();        
    UnloadImage(icon);
    UnloadTexture(background);

    return 0;
}