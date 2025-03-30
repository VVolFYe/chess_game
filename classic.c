#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"
#include "classic.h"

SDL_Window *classic_window = NULL;
SDL_Renderer *classic_renderer = NULL;

bool init_classic() {
    classic_window = SDL_CreateWindow("Classic Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!classic_window) {
        fprintf(stderr, "Failed to create Classic Chess window: %s\n", SDL_GetError());
        return false;
    }

    classic_renderer = SDL_CreateRenderer(classic_window, -1, SDL_RENDERER_ACCELERATED);
    if (!classic_renderer) {
        fprintf(stderr, "Failed to create Classic Chess renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(classic_window);
        return false;
    }

    return true;
}

void close_classic() {
    SDL_DestroyRenderer(classic_renderer);
    SDL_DestroyWindow(classic_window);
}


void classic_game()
{
    if (!init_classic()){
        fprintf(stderr,"Eroare classic_game() la initializare.\n");
        return;
    }

    SDL_Event e;
    bool quit = false;

    while (!quit){
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;    
            }
        }

        SDL_SetRenderDrawColor(classic_renderer, 0, 0, 0, 255); //fundal negru;
        SDL_RenderClear(classic_renderer);
    
        renderText("Classic Chess Game", 300, 50);
        SDL_RenderPresent(classic_renderer);
    }

    close_classic();
}