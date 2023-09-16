#include "SDL_render.h"
#include "SDL_stdinc.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

const int QUARTER_WIDTH = 160;
const int QUARTER_HEIGHT = 120;
const int HALF_WIDTH = QUARTER_WIDTH * 2;
const int HALF_HEIGHT = QUARTER_HEIGHT * 2;
const int SCREEN_WIDTH = HALF_WIDTH * 2;
const int SCREEN_HEIGHT = HALF_HEIGHT * 2;

struct Color {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
};

struct Color white = {0xFF, 0xFF, 0xfF};
struct Color black = {0x00, 0x00, 0x00};
struct Color red = {0xFF, 0x00, 0x00};

struct Color green = {0x00, 0xFF, 0x00};
struct Color blue = {0x00, 0x00, 0xFF};

struct Color yellow = {0xFF, 0xFF, 0x00};
struct Color cyan = {0x00, 0xFF, 0xFF};
struct Color magenta = {0xFF, 0x00, 0xFF};

SDL_Texture* loadTexture(const char *path, SDL_Renderer *renderer);
/*
 * Main function.
 *
 * Arguments are not evaluated yet.
 *
 * argc: number of arguments
 * args: array of arguments
 *
 * Return value: 0 if the program was terminated successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  int initialization_failed = SDL_Init(SDL_INIT_VIDEO) < 0;
  if (initialization_failed) {
    printf("Error while initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  int img_initialization_failed =
      (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG;
  if (img_initialization_failed) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = NULL;
  window = SDL_CreateWindow("HELLO SDL", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Error while creating SDL_Window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error while creating SDL_Renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *your_image_texture = loadTexture("your_image.png", renderer);

  SDL_Event e;
  int quit = 0;
  while (quit == 0) {
    SDL_SetRenderDrawColor(renderer, magenta.red, magenta.green, magenta.blue,
                           0xFF);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e)) {

      if (e.type == SDL_QUIT) {

        printf("The app was terminated by the user.\n");
        quit = 1;
      } // End of: if (e.type == SDL_QUIT)

    } // End of: while (SDL_PollEvent(%e))

    // In your main loop, before calling SDL_RenderPresent
    SDL_SetRenderDrawColor(renderer, cyan.red, cyan.green, cyan.blue, 0xFF);
    SDL_Rect fillRect = {QUARTER_WIDTH, QUARTER_HEIGHT, HALF_WIDTH,
                         HALF_HEIGHT};
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderCopy(renderer, your_image_texture, NULL, NULL);
    // Update screen
    SDL_RenderPresent(renderer);
  } // End of: while (quit == 0)

  SDL_DestroyTexture(your_image_texture);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();

  return 0;
} // End of: main function


SDL_Texture* loadTexture(const char *path, SDL_Renderer *renderer) {
  SDL_Surface *loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    return NULL;
  }
  
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if (texture == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
  }

  SDL_FreeSurface(loadedSurface);
  return texture;
}


