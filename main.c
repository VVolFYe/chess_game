#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// PAGINA DE MENIU


//le declaram aici globale si le folosim cu extern in functions.c
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;


int main(void)
{
    printf("Start.\n");
    if (!init()){
        fprintf(stderr,"Problema la initializare.\n");
        exit(-1);
    }



    return 0;
}