#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"
#include "classic.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window *classic_window = NULL;
SDL_Renderer *classic_renderer = NULL;
TTF_Font *classic_font = NULL;

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

    classic_font = TTF_OpenFont("arial.ttf", 24); // Load the font with size 24
        if (!classic_font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
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

Button back_classic = {{0, WINDOW_HEIGHT-50, 200, 50}, "Back"}; //buton back


    SDL_Event e;
    bool quit = false;

    while (!quit){
        while(SDL_PollEvent(&e) != 0){

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY); //vedem coordonatele mouse-ului cand este apasat
            
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (check_button(back_classic, mouseX, mouseY)) {
                    printf("Back to main menu.\n");
                    quit = true;
                }
            }

            if (e.type == SDL_QUIT){
                quit = true;    
            }
        }

        SDL_SetRenderDrawColor(classic_renderer, 0, 0, 0, 255);  // black background;
        SDL_RenderClear(classic_renderer); 

        SDL_SetRenderDrawColor(classic_renderer, 255, 255, 255, 255); 
        SDL_RenderFillRect(classic_renderer, &back_classic.rect); // Draw the button.

        // int x = back_classic.rect.x;
        // printf("x = %d\n", x);
        // int y = back_classic.rect.y;
        // printf("y = %d\n", y);

        // int mouseX, mouseY;
        // SDL_GetMouseState(&mouseX, &mouseY);
        // printf("Mouse x = %d, y = %d\n", mouseX, mouseY);

        renderText(back_classic.label, back_classic.rect.x + 50, WINDOW_HEIGHT + 15, classic_renderer, classic_font);

        SDL_RenderPresent(classic_renderer); // Update la screen.
    }

    close_classic();
}