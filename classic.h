#ifndef CLASSIC_H
#define CLASSIC_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init_classic();
void close_classic();
void classic_game();
void display_chess_piece(const char*, SDL_Renderer*, int, int, int , int);
void display_board(SDL_Renderer*);


#endif