#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_images.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// PAGINA DE MENIU

typedef struct{
    SDL_Rect rect;      // forma
    const char *label;  // display-text
}Button;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;



int main(void)
{
    printf("Start.\n");




    return 0;
}