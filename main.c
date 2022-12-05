#include <stdio.h>
#include "container.h"
#include <string.h>
const int screenWidth = 3000;
const int screenHeight = 1800;

int main()
{
    InitWindow(screenWidth,screenHeight, "Reversi Game");
    Texture2D undo_button = LoadTexture("C:\\Users\\Valentin\\Documents\\GitHub\\reversi\\undo_button.png");
    Texture2D redo_botton = LoadTexture("C:\\Users\\Valentin\\Documents\\GitHub\\reversi\\redo_button.png");
    //float frameHeight = (float)undo_button.height/NUM_FRAMES;
    Rectangle sourceRec = {0,0,(float)undo_button.width,(float )undo_button.height};
    Rectangle btnBounds = {200,1250,(float)undo_button.width,(float )undo_button.height};
    Rectangle btnBounds2 = {2500,1250,(float)redo_botton.width,(float )redo_botton.height};
    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);
    init_game();
    while(!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTextureRec(undo_button,sourceRec,(Vector2){btnBounds.x,btnBounds.y},WHITE);
        DrawTextureRec(redo_botton,sourceRec,(Vector2){btnBounds2.x,btnBounds2.y},WHITE);

        render_board();
        render_pieces();
        mark_playable_positions();
        make_next_move();

        ////More Bullshit
        if (CheckCollisionPointRec(mousePoint,btnBounds))
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                DrawRectangleLines(btnBounds.x,btnBounds.y, undo_button.width, undo_button.height, BLACK);
                if (check_undo_game())
                    DrawText("Impossible movement",50,700,60,MAROON);
                else{
                    undo_game();
                }
            }

        if (CheckCollisionPointRec(mousePoint,btnBounds2))
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawRectangleLines(btnBounds2.x,btnBounds2.y, undo_button.width, undo_button.height, BLACK);

        //////La logica del fnal del programa esta haciendo algo raro con el score que lo desmadra
        /////Solo hay que mover el game ended
        /*if (game_ended()){
            pause = true;
            render_end_of_the_game();
            EndDrawing();
            while(pause){
                if (IsKeyPressed(KEY_SPACE)){
                    pause = false;
                    init_game();
                    return 0;
                }
                if (IsKeyPressed(KEY_ESCAPE))
                    CloseWindow();
            }
        }*/
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
