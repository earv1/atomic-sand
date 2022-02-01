// Copyright 2020-2030 Emmanuel Arvanitis

#include <SDL.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <unistd.h>



#include "game_loop/game_loop.h"
#include "lib/wiring.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void Int_Handler(int);
void Seg_Handler(int);

#define WIN_WIDTH 160
#define WIN_HEIGHT 144

//
// main is where all program execution starts
//
int main(int argc, char **argv) {
  signal(SIGINT, Int_Handler);
  signal(SIGSEGV, Seg_Handler);   // install our handler
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  // The window we'll be rendering to
  // SDL_Window *window = NULL;
  // SDL_Renderer *renderer = NULL;
  // create SDL window
  SDL_Window *window = SDL_CreateWindow(
      "sdl2_pixelbuffer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WIN_WIDTH * 4, WIN_HEIGHT * 4, SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return 1;
  }

  // create renderer
  // SDL_Renderer *renderer = SDL_CreateRenderer(
  //     window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return 1;
  }
  SDL_RenderSetLogicalSize(renderer, WIN_WIDTH, WIN_HEIGHT);

  // Initialize SDL
  // DoStuffWithRendererAndMaybeDelete(gameObjectArray);
  // DoMoreStuffWithRendererAndMaybeDelete(gameObjectArray);

  // Manual garbage collection :-p
  // removeUnneededGameObjects(gameObjArray)

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT);
  // Get window surface
  // screenSurface = SDL_GetWindowSurface( window );

  struct AtomicSandWiring wiring = {.renderer = renderer, .texture = texture};
  game_loop(&wiring);

  // Update the surface
  SDL_UpdateWindowSurface(window);

  // Wait two seconds
  SDL_Delay(2000);

  SDL_DestroyWindow(window);
  window = NULL;
  // TODO(Emmanuel) check this
  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}

void Int_Handler(int sig) {
  signal(sig, SIG_IGN);
  exit(0);
}

void Seg_Handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  fprintf(stderr, "Error: signal %d:\n", sig);
  exit(1);
}
