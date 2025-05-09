#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "classic.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// PAGINA DE MENIU

//le declaram aici globale si le folosim cu extern in functions.c
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

SDL_Texture *background_texture = NULL;

int main(void)
{
    printf("Start.\n");
    if (!init()){
        fprintf(stderr,"Problema la initializare.\n");
        exit(-1);
    }

    SDL_Surface *background_surface = IMG_Load("main_background.jpg");  //cream surface
    if (!background_surface){
        fprintf(stderr,"Eroare imagine background main.\n");
        close_program();
        exit(-1);
    }

    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);   //din surface => textura
    SDL_FreeSurface(background_surface);
    if (!background_texture){
        fprintf(stderr,"Eroare textura main.\n");
        close_program();
        exit(-1);
    }

    Button classic_button = {{300, 150, 200, 50}, "Classic Chess"}; //buton sah clasic
    Button atomic_button = {{300, 250, 200, 50}, "Atomic Chess"}; //buton atomic chess (mod de joc)
    Button exit_button = {{300, 350, 200, 50}, "Exit"}; //buton exit

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { 
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY); //vedem coordonatele mouse-ului cand este apasat

                if (check_button(classic_button, mouseX, mouseY)) {
                    printf("sah-clasic-selectat.\n");
                    classic_game();
                } 
                else if (check_button(atomic_button, mouseX, mouseY)) {
                    printf("Atomic Chess selected!\n");
                }
                else if (check_button(exit_button, mouseX, mouseY)) {
                    quit = true; //iesim din program.
                }
            }
        }

        //background negru
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);

        // alb pentru butoane.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &classic_button.rect);
        SDL_RenderFillRect(renderer, &atomic_button.rect);
        SDL_RenderFillRect(renderer, &exit_button.rect);

        // text cu functia din functions.h
        renderText(classic_button.label, classic_button.rect.x + 23, classic_button.rect.y + 10, renderer, font);
        renderText(atomic_button.label, atomic_button.rect.x + 23, atomic_button.rect.y + 10, renderer, font);
        renderText(exit_button.label, exit_button.rect.x + 73, exit_button.rect.y + 10, renderer, font);

        SDL_RenderPresent(renderer); //update;
    }

    SDL_DestroyTexture(background_texture); //eliberam textura de la background;
    close_program();
    
    return 0;
}