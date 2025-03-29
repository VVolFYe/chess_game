#ifndef FUCTIONS.H
#define FUNCTIONS.H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct{
    SDL_Rect rect;      // forma
    const char *label;  // display-text
}Button;   //butoane

bool init();
void close_program();
void renderText(const char* text, int x, int y);
bool checkButton(Button button, int mouse_x, int mouse_y);

#endif