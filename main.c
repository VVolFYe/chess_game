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

    Button classic_button = {{300, 150, 200, 50}, "Classic Chess"}; //buton sah clasic
    Button atomic_button = {{300, 250, 200, 50}, "Atomic Chess"}; //buton atomic chess (mod de joc)
    Button exit_button = {{300, 300, 200, 50}, "Exit"}; //buton exit

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { 
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (check_button(classic_button, mouseX, mouseY)) {
                    printf("Classic Chess selected!\n");
                } else if (check_button(atomic_button, mouseX, mouseY)) {
                    printf("Atomic Chess selected!\n");
                } else if (check_button(exit_button, mouseX, mouseY)) {
                    quit = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &classic_button.rect);
        SDL_RenderFillRect(renderer, &atomic_button.rect);
        SDL_RenderFillRect(renderer, &exit_button.rect);

        renderText(classic_button.label, classic_button.rect.x + 50, classic_button.rect.y + 10);
        renderText(atomic_button.label, atomic_button.rect.x + 50, atomic_button.rect.y + 10);
        renderText(exit_button.label, exit_button.rect.x + 70, exit_button.rect.y + 10);

        SDL_RenderPresent(renderer);
    }

    close_program();

    return 0;
}