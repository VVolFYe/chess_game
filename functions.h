#ifndef FUCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "classic.h"

typedef struct{
    SDL_Rect rect;      // forma
    const char *label;  // display-text
}Button;   //butoane

bool init();
void close_program();
void renderText(const char* text, int x, int y);
bool check_button(Button button, int mouse_x, int mouse_y);

#endif