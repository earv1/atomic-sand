// Copyright 2020-2030 Emmanuel Arvanitis

#include <SDL.h>
#include <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include "lib/wiring.h"
#include "game_loop/game_loop.h"





// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void INThandler(int);


//
// main is where all program execution starts
//
int main(int argc, char **argv) {
     signal(SIGINT, INThandler);

    // The window we'll be rendering to
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // The surface contained by the window
    // SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_CreateWindowAndRenderer(
      SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // DoStuffWithRendererAndMaybeDelete(gameObjectArray);
    // DoMoreStuffWithRendererAndMaybeDelete(gameObjectArray);

    // Manual garbage collection :-p
    // removeUnneededGameObjects(gameObjArray)

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Get window surface
    // screenSurface = SDL_GetWindowSurface( window );

    struct AtomicSandWiring wiring = { .renderer = renderer};
    game_loop(&wiring);

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait two seconds
    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    window = NULL;
    // TODO(mano) check this
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();

  return 0;
}

void  INThandler(int sig) {
    signal(sig, SIG_IGN);
    exit(0);
}
