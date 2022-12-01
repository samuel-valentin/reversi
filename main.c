#include <stdio.h>
#include "container.h"
#include <string.h>

int game_ended = 0;


int main()
{
    const int screenWidth = 3000;
    const int screenHeight = 1800;

    //inicializacion del tablero

    InitWindow(screenWidth,screenHeight, "Reversi Game");
    //MaximizeWindow();
    init_game();
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        render_board();  //
        render_pieces();
        mark_playable_positions();
        make_next_move();
        render_score();
        EndDrawing();

        if (game_ended){
            DrawText("Game Over",900,500,100,RED);
        }


    }

    CloseWindow();

    return 0;
}
