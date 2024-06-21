#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "SDL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "SNAKE"
#define SQUARE_AMOUNT 16

typedef enum {
    N, S, W, E
} DIRECTIONS;

typedef struct s_apple {
    int x, y;
} APPLE;

typedef struct s_snake {
    int x;
    int y;
    int dir;
    struct s_snake *next;
} SNAKE;

int SQUARE_DIM = WINDOW_WIDTH / SQUARE_AMOUNT;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
APPLE apple;

int createWindowAndRender(void);
void renderBoard(void);
void renderSnake(SNAKE* snake);
void renderApple(void);
void createApple(void);
void moveSnake(SNAKE* snake);
SNAKE* initSnake(void);
void createTale(SNAKE* snake);
void eatApple(SNAKE* snake);

int main(int argc, char** argv) {
    if(createWindowAndRender()) return 1;

    srand(time(NULL));

    bool quit = false;
    SNAKE* snake;

    snake = initSnake();
    createApple();
    createTale(snake);
    createTale(snake);
    createTale(snake);

    while (!quit) {
        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) quit = true;
            else if(event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_UP:
                    snake->dir = N;
                    break;
                case SDLK_DOWN:
                    snake->dir = S;
                    break;
                case SDLK_LEFT:
                    snake->dir = W;
                    break;
                case SDLK_RIGHT:
                    snake->dir = E;
                    break;
                default:
                    break;
                }
            }
        }

        moveSnake(snake);
        eatApple(snake);

        renderBoard();
        renderSnake(snake);
        renderApple();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);

        SDL_Delay(200);
    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    return 0;
}

int createWindowAndRender(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        WINDOW_NAME, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        // SDL_Quit();
        return 1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        fprintf(stderr, "unable to set renderer!\n");
    }

    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return 0;
}

void renderBoard(void) {
    SDL_Rect rect;
    
    rect.h = rect.w = SQUARE_DIM;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i = 0; i < SQUARE_AMOUNT; i++) {
        for(int j = 0; j < SQUARE_AMOUNT; j++) {
            rect.x = SQUARE_DIM * i;
            rect.y = SQUARE_DIM * j;
            SDL_RenderDrawRect(renderer, &rect);
        }
    }

    return;
}

void renderSnake(SNAKE* snake) {
    SNAKE* aux = snake;
    SDL_Rect rect;

    rect.h = rect.w = SQUARE_DIM;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    while(aux != NULL) {
        rect.x = aux->x * SQUARE_DIM;
        rect.y = aux->y * SQUARE_DIM;
        SDL_RenderFillRect(renderer, &rect);

        aux = aux->next;
    }

    return;
}

void renderApple(void) {
    SDL_Rect rect = {apple.x * SQUARE_DIM, apple.y * SQUARE_DIM, SQUARE_DIM, SQUARE_DIM};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    return;
}

void createApple(void) {
    apple.x = rand() % SQUARE_AMOUNT;
    apple.y = rand() % SQUARE_AMOUNT;

    return;
}

void moveSnake(SNAKE* snake) {
    SNAKE* aux = snake->next;
    int preX = snake->x, preY = snake->y;
    int auxX, auxY;

    switch (snake->dir)
    {
    case N:
        snake->y--;
        break;
    case S:
        snake->y++;
        break;
    case W:
        snake->x--;
        break;
    case E:
        snake->x++;
        break;
    }

    while(aux != NULL) {
        auxX = aux->x;
        auxY = aux->y;

        aux->x = preX;
        aux->y = preY;

        preX = auxX;
        preY = auxY;

        aux = aux->next;
    }

    return;
}

SNAKE* initSnake(void) {
    SNAKE* snake;

    snake = (SNAKE*)malloc(sizeof(SNAKE));
    snake->x = SQUARE_AMOUNT / 2;
    snake->y = SQUARE_AMOUNT / 2;
    snake ->dir = E;

    snake->next = NULL;

    return snake;
}

void createTale(SNAKE* snake) {
    SNAKE* new, *aux = snake;

    while(aux->next != NULL) aux = aux->next;

    new = (SNAKE*)malloc(sizeof(SNAKE));
    new->x = aux->x;
    new->y = aux->y;

    new->next = NULL;

    aux->next = new;

    return;
}

void eatApple(SNAKE* snake) {
    if(snake->x == apple.x && snake->y == apple.y) {
        createApple();
        createTale(snake);
    }

    return;
}

