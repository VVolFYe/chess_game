#ifndef CLASSIC_H
#define CLASSIC_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init_classic();
void close_classic();
void classic_game();
void display_chess_piece(const char, SDL_Renderer*, int, int, int , int);  //AM MODIFICAT AICI
void display_board(SDL_Renderer*);
void move_piece(int, int, int, int);
bool check_same_color(char, char); // verificam daca piesele sunt de aceeasi culoare

#endif