/*#include <stdio.h>
#include "SDL.h"

#include "window.h"

int mainn(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    if(createWindow()) {
        return 1;
    }

    createRender();

    
    

    SDL_Delay(5000);

    
    destroyWindow();
    
    return 0;
}*/