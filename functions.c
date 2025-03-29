#include <stdio.h>
#include "functions.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *font;

// functia de initializare
bool init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Eroare initializare SDL, \n");
        return false;
    }

    if (TTF_Init() == -1){
        fprintf(stderr,"Eroare TTF.\n");
    }

    window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (window == NULL){
        fprintf(stderr, "Eroare cand se creeaza window-ul,\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        fprintf(stderr, "Eroare renderer.\n");
        return false;
    }

    font = TTF_OpenFont("INLOCUIESTE_CU_FONTUL.ttf",24);
    if (font == NULL){
        fprintf(stderr,"Eroare OpenFont.\n");
        return false;
    }

    return true; //daca totul este in regula => returnam true :)
}


// omoram programul.
void close_program(){
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void renderText(const char *text, int x, int y){
    SDL_Color color = {255,255,255}; //text alb (rgb);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    /*
    x = coordonata x
    y = coordonata y
    */
    if (!textSurface){
        fprintf(stderr,"eroare text surface");
        return;
    }   

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    if (!textTexture){
        fprintf(stderr,"Eroare text texture.\n");
        SDL_FreeSurface(textSurface); //eliberam surface-ul;
        return;
    }
   

    SDL_Rect textRect = {x,y, textSurface->w, textSurface->h}; //width si height
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    return;
}

bool checkButtonClick(Button button, int mouseX, int mouseY) {
        return (mouseX >= button.rect.x && mouseX <= button.rect.x + button.rect.w && mouseY >= button.rect.y && mouseY <= button.rect.y + button.rect.h);
    }

    

