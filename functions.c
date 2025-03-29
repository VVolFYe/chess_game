#include <stdio.h>
#include "functions.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

// functia de initializare
bool init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Eroare initializare SDL, \n");
        return false;
    }

    window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (window == NULL){
        fprintf(stderr, "Eroare cand se creeaza window-ul,\n");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        fprintf(stderr, "Eroare renderer.\n");
    }

    return true; //daca totul este in regula => returnam true :)
}