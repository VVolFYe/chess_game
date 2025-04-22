#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"
#include "classic.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BOARD_X 50
#define BOARD_Y 50
#define BOARD_WIDTH 480
#define BOARD_HEIGHT 480


SDL_Window *classic_window = NULL;
SDL_Renderer *classic_renderer = NULL;
TTF_Font *classic_font = NULL;
SDL_Texture *chessboard = NULL;

SDL_Texture *piece_textures[128]; // salvam texturile de dinainte;

/*
    Pentru tabla de sah folosim o matrice de 8x8
    Litere mari -> piese albe
    Litere mici -> piese negre
    Asta e pozitia initiala
*/
char board[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},  
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},  
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},  
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}   
};

void load_textures(SDL_Renderer *renderer) {
    char pieces_letters[20];
    strcpy(pieces_letters, "rnbqkpRNBQKP"); 
    for (int i = 1; i < 128; i++) {
        char path[100];
        if (strchr(pieces_letters, i) == NULL){
            continue;
        }
        sprintf(path, "/home/wolfye/chess_game/pieces/%c.png", i); // cream path-ul catre imaginea corespunzatoare pieesei selectate.
        SDL_Surface *surface = IMG_Load(path);
        if (surface == NULL) {
            fprintf(stderr, "Failed to load image: %s  --> %d\n", IMG_GetError(),i);
            continue;
        }
        piece_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        if (piece_textures[i] == NULL) {
            fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }
        SDL_FreeSurface(surface);
        fprintf(stderr, "Loaded texture for %c\n", i);
    }
}

void display_chess_piece(const char piece, SDL_Renderer *renderer, int x, int y, int width, int height) {
    int index = piece;
    SDL_Texture *texture = piece_textures[index];

    //printf("AM AJUNS AICI.\n");  ->merge<-

    if (texture == NULL) {
        fprintf(stderr, "Failed to create texture: %s --- ( display_chess_piece() function ))\n", SDL_GetError());
        return;
    }

    SDL_Rect display_rect = {x, y, width, height}; //parametrizam ca sa putem folosi
    SDL_RenderCopy(renderer, texture, NULL, &display_rect); //punem imaginea
    //SDL_DestroyTexture(texture); 
}

void display_board(SDL_Renderer *renderer){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            // int piece = board[i][j];

            char piece = board[i][j];

            int square_size = BOARD_HEIGHT / 8; // momentan e 60 dar in caz ca mai schimb
            int x = j * square_size + BOARD_X; 
            int y = i * square_size + BOARD_Y;

            if (piece != ' ') {


                display_chess_piece(board[i][j], renderer, x, y, square_size, square_size);

                // char path_image[100];
                // sprintf(path_image, "/home/wolfye/chess_game/pieces/%c.png", piece); // cream path-ul catre imaginea corespunzatoare pieesei selectate.
                // display_chess_piece(path_image, renderer, x, y, square_size, square_size);
            }
        }
    }
}

void move_piece(int from_row, int from_col, int to_row, int to_col) {
    //verificam daca exista piesa acolo. (nu este nevoie sa printam eroarea dar momentan ma ajuta)
    if (board[from_row][from_col] == ' ') {
        fprintf(stderr, "No piece at source position (%d, %d)\n", from_row, from_col);
        return;
    }

    // mutam piesa
    board[to_row][to_col] = board[from_row][from_col];
    board[from_row][from_col] = ' ';
}

bool init_classic(){
    classic_window = SDL_CreateWindow("Classic Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!classic_window) {
        fprintf(stderr, "Failed to create Classic Chess window: %s\n", SDL_GetError());
        return false;
    }

    classic_renderer = SDL_CreateRenderer(classic_window, -1, SDL_RENDERER_ACCELERATED);
    if (!classic_renderer){
        fprintf(stderr, "Failed to create Classic Chess renderer: %s\n", SDL_GetError());  //afisam eroarea cu geterror (sdl)
        SDL_DestroyWindow(classic_window);
        return false;
    }

    classic_font = TTF_OpenFont("arial.ttf", 24); // Load the font with size 24
        if (!classic_font){
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());  //afisam eroare cu geterror (ttf)
        return false;
    }

    SDL_Surface *background_surface = IMG_Load("chessboard_2.png");  // Replace with the path to your image
    if (!background_surface){
        fprintf(stderr, "Failed to load chessboard: %s\n", SDL_GetError());
        return false;
    }

    chessboard = SDL_CreateTextureFromSurface(classic_renderer, background_surface);
    SDL_FreeSurface(background_surface);  // Free the surface after creating the texture

    if (!chessboard){
        fprintf(stderr, "Failed to create background texture: %s\n", SDL_GetError());
        return false;
    }

    load_textures(classic_renderer); // incarca texturile pentru piese

    return true;
}

void close_classic(){
    SDL_DestroyTexture(chessboard);
    SDL_DestroyRenderer(classic_renderer);
    SDL_DestroyWindow(classic_window);
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
        display_board(classic_renderer);

        SDL_SetRenderDrawColor(classic_renderer, 255, 255, 255, 255); 
        SDL_RenderFillRect(classic_renderer, &back_classic.rect); // Draw the button.

        //test mouse-pos:
        int mouseX, mouseY;          //pentru a testa pozitia mouse-ului decomenteaza :/
        SDL_GetMouseState(&mouseX, &mouseY);
        printf("Mouse x = %d, y = %d\n", mouseX, mouseY);

        // move_piece(6,4,4,4);   // (pion e2-e4) --> TEST

        renderText(back_classic.label, back_classic.rect.x + 20, WINDOW_HEIGHT - 35, classic_renderer, classic_font);

        SDL_RenderPresent(classic_renderer); // Update la screen.
    }
    

    close_classic();
}