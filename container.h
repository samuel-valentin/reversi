//
// Created by Valentin on 20/11/2022.
//

#ifndef REVERSI_CONTAINER_H
#define REVERSI_CONTAINER_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_game();
void render_board();
void render_pieces();
void render_possible_moves();
int is_playable( int i, int j );
int is_valid_position( int i, int j );
int distance( int i1, int j1, int i2, int j2 );
void make_next_move();
char get_mouse_position ();
void change_current_player ();
void mark_playable_positions( );
void capture_pieces( int i, int j );
void render_score();
int game_ended();
int board_full();
void render_end_of_the_game();
#endif //REVERSI_CONTAINER_H
