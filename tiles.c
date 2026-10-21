#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(void) {
    int tiles[2][6];

    const int rows = 2;
    const int cols = 6;
    const int tileSize = 80;
    const int gap = 5;

    const int windowWidth = cols * (tileSize + gap) + gap;
    const int windowHeight = rows * (tileSize + gap) + gap;

    int playerRow = 1;
    int playerCol = 0;
    int playerRadius = 10;
    int gameWon = 0;

    int flashCount = 0;
    float flashTimer = 0.0f;
    int flashing = 0;
    int flashRed = 0;
    int resetPending = 0;
    int failedRow = 0;
    int failedCol = 0;

    srand((unsigned int)time(NULL));

    for (int col = 0; col < cols; col++) {
        tiles[0][col] = rand() % 2;
        tiles[1][col] = 1 - tiles[0][col];
    }

    // Ensure the starting tile is safe
    tiles[playerRow][playerCol] = 1;
    tiles[0][playerCol] = 0;

    //graphics
    InitWindow(windowWidth, windowHeight, "Bridge Cross");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Player movement
        if (!gameWon && !flashing) {
            int nextRow = playerRow;
            int nextCol = playerCol;
            int moveRequested = 0;

            if (IsKeyPressed(KEY_W)) {
                nextRow--;
                moveRequested = 1;
            }
            else if (IsKeyPressed(KEY_S)) {
                nextRow++;
                moveRequested = 1;
            }
            else if (IsKeyPressed(KEY_D)) {
                nextCol++;
                moveRequested = 1;
            }
            else if (IsKeyPressed(KEY_E)) {
                nextRow--;
                nextCol++;
                moveRequested = 1;
            }
            else if (IsKeyPressed(KEY_F)) {
                nextRow++;
                nextCol++;
                moveRequested = 1;
            }

            if (moveRequested) {
                if (nextRow < 0 || nextRow >= rows ||
                    nextCol < 0 || nextCol >= cols) {
                    // Ignore moves outside grid
                }
                else {
                    // is tile safe
                    if (tiles[nextRow][nextCol] == 1) {
                        playerRow = nextRow;
                        playerCol = nextCol;

                        if (playerCol == cols - 1) {
                            gameWon = 1;
                        }
                    }
                    else {
                        // Flash unsafe tile red 3 times
                        flashing = 1;
                        flashCount = 0;
                        flashTimer = 0.0f;
                        flashRed = 1;
                        resetPending = 1;
                        failedRow = nextRow;
                        failedCol = nextCol;
                    }
                }
            }
        }

        // Update flashing animation
        if (flashing) {
            flashTimer += GetFrameTime();

            if (flashTimer >= 0.2f) {
                flashTimer = 0.0f;
                flashRed = !flashRed;

                if (flashRed) {
                    flashCount++;

                    if (flashCount >= 3) {
                        flashing = 0;
                        flashRed = 0;

                        if (resetPending) {
                            playerRow = 1;
                            playerCol = 0;
                            resetPending = 0;
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int x = gap + col * (tileSize + gap);
                int y = gap + row * (tileSize + gap);

                Color colour = tiles[row][col] == 1
                                ? LIGHTGRAY : LIGHTGRAY;

                if (flashing && flashRed &&
                    row == failedRow && col == failedCol) {
                    colour = RED;
                }

                DrawRectangle(x, y, tileSize, tileSize, colour);
            }
        }

        int playerX = gap + playerCol * (tileSize + gap) + tileSize / 2;
        int playerY = gap + playerRow * (tileSize + gap) + tileSize / 2;

        DrawCircle(playerX, playerY, playerRadius, BLACK);

        if (gameWon) {
            DrawText("YOU WIN!", 175, 60, 30, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("[%d] ", tiles[row][col]);
        }
        printf("\n");
    }

    return 0;
}
