//
// Created by Valentin on 20/11/2022.
//

#include "container.h"
#define WHITE_PLAYER 10
#define BLACK_PLAYER 11
#define EMPTY        2
#define PLAYABLE     3
#define FALSE        0
#define TRUE         1

char board[8][8];
int playable_direction [8][8][8];
int score [2];
int current_player = BLACK_PLAYER;
bool test = false;
int wrong_move = FALSE;
int has_valid_move = FALSE;


struct Position
{
    int x;
    int y;
}position;

//Inicializacio del tablero
void init_game()
{
    board[3][3] = BLACK_PLAYER;
    board[4][4] = BLACK_PLAYER;
    board[3][4] = WHITE_PLAYER;
    board[4][3] = WHITE_PLAYER;
    score[WHITE_PLAYER] = 2;
    score[BLACK_PLAYER] = 2;
                                  //Linea quitada de prueba
}

void render_board()
{
    int cellLength = 200;
    int x = 750;
    int y = 100;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                DrawRectangle(i * cellLength + x, j * cellLength + y, cellLength, cellLength, DARKGREEN);
            }
            else {
                DrawRectangle(i * cellLength + x, j * cellLength + y, cellLength, cellLength, GREEN);
            }
        }
    }
}

void render_pieces()
{
    int cellLength = 200;
    int x = 850;
    int y = 200;
    render_possible_moves();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board [i][j] == BLACK_PLAYER)
                DrawCircle(i*cellLength+x,j*cellLength+y,60,BLACK);
            if (board [i][j] == WHITE_PLAYER)
                DrawCircle(i*cellLength+x,j*cellLength+y,60,WHITE);
            if (board[i][j] == PLAYABLE)
                DrawCircleGradient(i*cellLength+x,j*cellLength+y, 60, GRAY, DARKGRAY);
        }
    }

}

void render_possible_moves()
{
    has_valid_move = FALSE;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board [i][j] == PLAYABLE)
                board [i][j] = EMPTY;
            if (is_playable(i,j)){
                board [i][j] = PLAYABLE;
                has_valid_move = TRUE;
            }
        }
    }
}

int is_playable( int i, int j )
{
    /*if ( !is_valid_position( i, j ) )
        return FALSE;
    if ( board[i][j] != EMPTY )
        return FALSE;*/

    int playable = FALSE;
    int opposing_player = (( current_player + 1 ) % 2)+10;

    // Test UL diagonal
    int i_it = i-1, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it -= 1;
        j_it -= 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][0] = 1;
        playable = TRUE;
    }

    // Test UP path
    i_it = i-1, j_it = j;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        i_it -= 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][1] = 1;
        playable = TRUE;
    }

    // Test UR diagonal
    i_it = i-1, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it -= 1;
        j_it += 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][2] = 1;
        playable = TRUE;
    }

    // Test LEFT path
    i_it = i, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        j_it -= 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][3] = 1;
        playable = TRUE;
    }

    // Test RIGHT path
    i_it = i, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        j_it += 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][4] = 1;
        playable = TRUE;
    }

    // Test DL diagonal
    i_it = i+1, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it += 1;
        j_it -= 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][5] = 1;
        playable = TRUE;
    }

    // Test DOWN path
    i_it = i+1, j_it = j;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        i_it += 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][6] = 1;
        playable = TRUE;
    }

    // Test DR diagonal
    i_it = i+1, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it += 1;
        j_it += 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
    {
        playable_direction[i][j][7] = 1;
        playable = TRUE;
    }
    return playable;
}

int is_valid_position( int i, int j )
{
    if ( i < 0 || i >= 8 || j < 0 || j >= 8 )
        return FALSE;
    return TRUE;
}

int distance( int i1, int j1, int i2, int j2 )
{
    int di = abs( i1 - i2 ), dj = abs( j1 - j2 );
    if ( di > 0 ) return di;
    return dj;
}

void make_next_move()
{
    get_mouse_position();
    if (is_valid_position(position.x,position.y) && board [position.x][position.y] == PLAYABLE){
        board [position.x][position.y] = current_player;
        score[current_player]++;
        if (test)
            change_current_player();
        test = false;
        position.x = -1;
        position.y = -1;
    }
}

char get_mouse_position ()
{
    int cellLength = 200;   //100
    int x = 750;    //750   //850
    int y = 100;    //100   //200
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = x; i < cellLength * 8 + x; i += cellLength) {
            if (GetMouseX() >= i  && GetMouseX() <= i + cellLength) {
                position.x = (i / cellLength) - 3;
                //position.x = GetMouseX() / i * cellLength + boardX;
                //position.x = 0;
                break;
            }
        }
        for (int i = y; i < cellLength * 8 + y; i += cellLength) {
            if (GetMouseY() >= i && GetMouseY() <= i + cellLength) {
                position.y = i / cellLength;
                //position.y = GetMouseY() / i * cellLength + boardY;
                //position.y = 0;
                break;
            }
        }
        test = true;
    }
    DrawText(TextFormat("Cordenada x: %i", position.x), 350, 100, 50, BLACK);
    DrawText(TextFormat("Cordenada y: %i", position.y), 350, 150, 50, BLACK);
}

void change_current_player( )
{
    current_player = (( current_player + 1 ) % 2)+10;
}

void mark_playable_positions( )
{
    has_valid_move = FALSE;
    for ( int i=0; i<8; ++i )
    {
        for ( int j=0; j<8; ++j )
        {
            if ( board[i][j] == PLAYABLE )
                board[i][j] = EMPTY;
            if ( is_playable( i, j ) )
            {
                board[i][j] = PLAYABLE;
                has_valid_move = TRUE;
            }
        }
    }
}