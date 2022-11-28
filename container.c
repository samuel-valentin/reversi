//
// Created by Valentin on 20/11/2022.
//

#include "container.h"
#define WHITE_PLAYER 2
#define BLACK_PLAYER 1
char board [8][8];
int able_directions [8][8][8];
int score [2];
int current_player;

//Inicializacio del tablero
void init_game()
{
    board[3][3] = BLACK_PLAYER;
    board[4][4] = BLACK_PLAYER;
    board[3][4] = WHITE_PLAYER;
    board[4][3] = WHITE_PLAYER;
    score[WHITE_PLAYER] = 2;
    score[BLACK_PLAYER] = 2;
    current_player = BLACK_PLAYER;
}

void render_board()
{
    //int cellLength = 100;
    int x = 750;
    int y = 100;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                DrawRectangle(i * 200 + x, j * 200 + y, 200, 200, DARKGREEN);
            }
            else {
                DrawRectangle(i * 200 + x, j * 200 + y, 200, 200, GREEN);
            }
        }
    }
}

void render_pieces()
{
    //board [0][0] = BLACK_PLAYER;
    //board [7][7] = WHITE_PLAYER;
    //board [0][7] = WHITE_PLAYER;
    //board [7][0] = BLACK_PLAYER;
    int x = 850;
    int y = 200;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board [i][j] == BLACK_PLAYER)
                DrawCircle(i*200+x,j*200+y,60,BLACK);
            if (board [i][j] == WHITE_PLAYER)
                DrawCircle(i*200+x,j*200+y,60,WHITE);
        }
    }
}