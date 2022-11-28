#include <stdio.h>
#include "container.h"
#include <string.h>



int main()
{
    const int screenWidth = 3000;
    const int screenHeight = 1800;
    //inicializacion del tablero
    init_game();
    InitWindow(screenWidth,screenHeight, "Reversi Game");
    //MaximizeWindow();

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        render_board();
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                render_pieces();

            }
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
