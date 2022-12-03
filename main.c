#include <stdio.h>
#include "container.h"
#include <string.h>


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
        bool pause = true;
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        render_board();  //
        render_pieces();
        render_score();
        mark_playable_positions();
        make_next_move();
        if (game_ended()){
            //pause = true;
            while(pause){                                      ////Algo aqui esta mal, no se reinicia cuando deberia, pero si termina cuando no
                if (IsKeyPressed(KEY_SPACE)){
                    pause = false;
                    init_game();
                    return 0;
                }
                if (IsKeyPressed(KEY_ESCAPE))
                    CloseWindow();
                render_end_of_the_game();
                EndDrawing();
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
