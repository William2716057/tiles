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

    srand((unsigned int)time(NULL));

    //srand(time(NULL));


    for (int col = 0; col < cols; col++) {
            tiles[0][col] = rand() % 2;
            tiles[1][col] = 1 - tiles[0][col];

    }

    //graphics
    InitWindow(windowWidth, windowHeight, "Bridge Cross");

    //InitWindow(cols * (tileSize + gap) + gap,
    //                rows * (tileSize + gap) + gap,
    //                "Bridge Cross");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mouse = GetMousePosition();

                    for (int row = 0; row < rows; row++) {
                            for (int col = 0; col < cols; col++) {
                                    int x = gap + col * (tileSize + gap);
                                    int y = gap + row * (tileSize + gap);

                                    Rectangle tile = {
                                            (float)x, (float)y,
                                            (float)tileSize, (float)tileSize
                                    };

                                    if (CheckCollisionPointRec(mouse, tile)) {
                                            tiles[row][col] = 1 - tiles[row][col];
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
                                            ? BLUE : LIGHTGRAY;

                            DrawRectangle(x, y, tileSize, tileSize, colour);

                            //DrawText(
                            //        tiles[row][col] == 1 ? "1" : "0",
                            //        x + 30, y + 25, 30, BLACK
                            //);

//                            const char *label = tiles[row][col] == 1 ? "1" : "0";
//                            const int fontSize = 30;
 //                           const int textWidth = MeasureText(label, fontSize);

//                            DrawText(
 //                                   label,
//                                    x + (tileSize - textWidth) / 2,
 //                                   y + (tileSize - fontSize) / 2,
  //                                  fontSize,
   //                                 BLACK
     //                       );
                    }
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
