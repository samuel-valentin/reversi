//
// Created by Valentin on 20/11/2022.
//

#include "container.h"
#define WHITE_PLAYER 0
#define BLACK_PLAYER 1
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
int skipp_turn = FALSE;
int movements [2];


struct Position
{
    int x;
    int y;
}position;

struct node
{
    int value_of_board;
    struct node *next;
    struct node *after;
};

struct stack
{
    Node *head;
};

Stack *stack_new()
{
    Stack *new = malloc(sizeof(Stack));
    new->head = NULL;
    return new;
}

Node *new_node(int value)
{
    Node *new = malloc(sizeof(Node));
    new->value_of_board = value;
    new->next = NULL;
    return new;
}

void add_board(Stack *s, int value) //agrego int en la matriz el profe agrega char
{
    if(s->head == NULL){
        s->head = new_node(value);
        return;
    }
    Node *new_head = new_node(value);
    new_head->next = s->head;
    s->head = new_head;
}

//Inicializacio del tablero
void init_game()
{
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = EMPTY;
        }
    }
    board[3][3] = BLACK_PLAYER;
    board[4][4] = BLACK_PLAYER;
    board[3][4] = WHITE_PLAYER;
    board[4][3] = WHITE_PLAYER;
    score[WHITE_PLAYER] = 2;    //2
    score[BLACK_PLAYER] = 2;    //2
    movements[WHITE_PLAYER] = 0;
    movements[BLACK_PLAYER] = 0;
}

void render_board()
{
    int cellLength = 200;
    int x = 700; //750
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
    int x = 800;    //850
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
    render_score();
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
    if ( !is_valid_position( i, j ) )
        return FALSE;
    if ( board[i][j] != EMPTY )
        return FALSE;

    int playable = FALSE;
    int opposing_player = (current_player + 1 ) % 2;

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
    if ( di > 0 )
        return di;
    return dj;
}

void make_next_move()
{
    Stack *s = stack_new();
    get_mouse_position();
    if (is_valid_position(position.x,position.y) && board [position.x][position.y] == PLAYABLE){
        score[current_player]++;                                          ////Has quitado esta linea para el score
        board [position.x][position.y] = current_player;
        capture_pieces( position.x, position.y);
        render_score();
        if (test)
            change_current_player();
        test = false;
        position.x = -1;
        position.y = -1;
        movements [current_player]++;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j <8; ++j) {
            add_board(s, board[i][j]);
        }
    }
}

char get_mouse_position ()
{
    int cellLength = 200;   //100
    int x = 700;    //750   //850
    int y = 100;    //100   //200
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = x; i < cellLength * 8 + x; i += cellLength) {
            if (GetMouseX() >= i  && GetMouseX() <= i + cellLength) {
                position.x = (i / cellLength) - 3;
                break;
            }
        }
        for (int i = y; i < cellLength * 8 + y; i += cellLength) {
            if (GetMouseY() >= i && GetMouseY() <= i + cellLength) {
                position.y = i / cellLength;
                break;
            }
        }
        test = true;
    }
}

void change_current_player( )
{
    current_player = (current_player + 1 ) % 2;
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

void capture_pieces( int i, int j )
{
    int opposing_player = (current_player + 1) % 2;
    int i_it, j_it;

    // Capture UL diagonal
    if ( playable_direction[i][j][0] )
    {
        i_it = i-1, j_it = j-1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it -= 1;
            j_it -= 1;
        }
    }

    // Capture UP path
    if ( playable_direction[i][j][1] )
    {
        i_it = i-1, j_it = j;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it -= 1;
        }
    }

    // Capture UR diagonal
    if ( playable_direction[i][j][2] )
    {
        i_it = i-1, j_it = j+1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it -= 1;
            j_it += 1;
        }
    }

    // Capture LEFT path
    if ( playable_direction[i][j][3] )
    {
        i_it = i, j_it = j-1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            j_it -= 1;
        }
    }

    // Capture RIGHT path
    if ( playable_direction[i][j][4] )
    {
        i_it = i, j_it = j+1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            j_it += 1;
        }
    }

    // Capture DL diagonal
    if ( playable_direction[i][j][5] )
    {
        i_it = i+1, j_it = j-1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it += 1;
            j_it -= 1;
        }
    }

    // Capture DOWN path
    if ( playable_direction[i][j][6] )
    {
        i_it = i+1, j_it = j;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it += 1;
        }
    }

    // Capture DR diagonal
    if ( playable_direction[i][j][7] )
    {
        i_it = i+1, j_it = j+1;
        while ( board[i_it][j_it] == opposing_player )
        {
            board[i_it][j_it] = current_player;
            score[current_player]++;
            score[opposing_player]--;
            i_it += 1;
            j_it += 1;
        }
    }
    render_score();
}

void render_score()
{
    DrawText(TextFormat("BLACK PLAYER\nScore: %i", score[BLACK_PLAYER]), 50, 100, 60, BLACK);
    DrawText(TextFormat("WHITE PLAYER\nScore: %i", score[WHITE_PLAYER]), 2350, 100, 60, WHITE);
}

int game_ended()
{
    /*if (board_full())
        return TRUE;
    if (!has_valid_move)
        return TRUE;*/
    for (int i = 0; i <8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == PLAYABLE)
                return FALSE;
        }
    }
    return TRUE;
}

int board_full()
{
    if ((score[BLACK_PLAYER] + score[WHITE_PLAYER]) == 64)
        return TRUE;
    return FALSE;
}

void render_end_of_the_game()
{
    render_pieces();
    render_score();
    DrawText("Game Over",715,750,300,RED);
    DrawText("For New Game press Space Bar",1010,1550,60,MAROON);
    DrawText("For Exit to the Game press Esc",1010,1610,60,MAROON);
    if (score[BLACK_PLAYER] > score[WHITE_PLAYER])
        DrawText("Winner!\nCongrats!", 50, 400, 100, BLACK);
    else
    DrawText("Winner!\nCongrats!", 2350, 400, 100, WHITE);
}

int check_undo_game()
{
    if (movements[current_player] < 1)
        return TRUE;
    return FALSE;
}

void undo_game()
{
    Stack *s;
    while (s->head == NULL)
        printf("%c\n",pop_board(s));
}

int pop_board(Stack *s)
{
    int to_return = s->head->value_of_board;
    Node *to_free = s->head;
    s->head = s->head->next;
    free(to_free);
    return to_return;
}
