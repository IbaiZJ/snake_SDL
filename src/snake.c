#include <stdio.h>
#include "SDL.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    
    
    
    return 0;
}