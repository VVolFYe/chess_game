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
SDL_Texture *chessboard = NULL;

bool init_classic() {
    classic_window = SDL_CreateWindow("Classic Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!classic_window) {
        fprintf(stderr, "Failed to create Classic Chess window: %s\n", SDL_GetError());
        return false;
    }

    classic_renderer = SDL_CreateRenderer(classic_window, -1, SDL_RENDERER_ACCELERATED);
    if (!classic_renderer) {
        fprintf(stderr, "Failed to create Classic Chess renderer: %s\n", SDL_GetError());  //afisam eroarea cu geterror (sdl)
        SDL_DestroyWindow(classic_window);
        return false;
    }

    classic_font = TTF_OpenFont("arial.ttf", 24); // Load the font with size 24
        if (!classic_font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());  //afisam eroare cu geterror (ttf)
        return false;
    }

    SDL_Surface *background_surface = IMG_Load("chessboard.jpg");  // Replace with the path to your image
    if (!background_surface) {
        fprintf(stderr, "Failed to load chessboard: %s\n", SDL_GetError());
        return false;
    }

    chessboard = SDL_CreateTextureFromSurface(classic_renderer, background_surface);
    SDL_FreeSurface(background_surface);  // Free the surface after creating the texture

    if (!chessboard) {
        fprintf(stderr, "Failed to create background texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close_classic() {
    SDL_DestroyTexture(chessboard);
    SDL_DestroyRenderer(classic_renderer);
    SDL_DestroyWindow(classic_window);
}

//BAGA MAINE IN BIBLIOTECA FUNCTIILE TE ROG EU PE EU
// SDL_Texture *load_image(const char *path, SDL_Renderer *renderer){
//     SDL

// }

void display_chess_piece(SDL_Renderer *renderer, SDL_Texture *piece_texture, int x, int y, int width, int height) {
    // Define the destination rectangle where the piece will be placed on the screen
    SDL_Rect pieceDestRect = {x, y, width, height};  // (x, y, width, height)

    // Render the chess piece texture to the specified position
    SDL_RenderCopy(renderer, piece_texture, NULL, &pieceDestRect);
}


void classic_game()
{
    if (!init_classic()){
        fprintf(stderr,"Eroare classic_game() la initializare.\n");
        return;
    }

    Button back_classic = {{0, WINDOW_HEIGHT - 40, 100, 40}, "Back"}; //buton back
    SDL_Event e;
    bool quit = false;

    SDL_Rect chessboard_dest_rect = {50, 50, 480, 480};
    // int chessboard_x = chessboard_dest_rect.x; // le salvam aici ca variabile ca sa le folosim in functii
    // int chessboard_y = chessboard_dest_rect.y; // pentru a putea schimba mai apoi tabla sau ceva idk (nu ma risc)

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

        SDL_SetRenderDrawColor(classic_renderer, 32, 32, 32, 255);  // black background;
        SDL_RenderClear(classic_renderer); 

        SDL_Rect chessboard_source_rect = {0, 0, 480, 480};
        SDL_RenderCopy(classic_renderer, chessboard, &chessboard_source_rect, &chessboard_dest_rect);

        SDL_SetRenderDrawColor(classic_renderer, 255, 255, 255, 255); 
        SDL_RenderFillRect(classic_renderer, &back_classic.rect); // Draw the button.

        // int mouseX, mouseY;          //pentru a testa pozitia mouse-ului decomenteaza :/
        // SDL_GetMouseState(&mouseX, &mouseY);
        // printf("Mouse x = %d, y = %d\n", mouseX, mouseY);

        renderText(back_classic.label, back_classic.rect.x + 20, WINDOW_HEIGHT - 35, classic_renderer, classic_font);

        SDL_RenderPresent(classic_renderer); // Update la screen.
    }

    close_classic();
}