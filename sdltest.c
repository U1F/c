#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

const int EIGHTH_WIDTH = 160;
const int EIGHTH_HEIGHT = 90;
const int QUARTER_WIDTH = EIGHTH_WIDTH * 2;
const int QUARTER_HEIGHT = EIGHTH_HEIGHT * 2;
const int HALF_WIDTH = QUARTER_WIDTH * 2;
const int HALF_HEIGHT = QUARTER_HEIGHT * 2;
const int SCREEN_WIDTH = HALF_WIDTH * 2;
const int SCREEN_HEIGHT = HALF_HEIGHT * 2;

const int TOP_LEFT = 0;
const int ASSET_AREA_WIDTH = EIGHTH_WIDTH * 3;
const int EDITOR_AREA_WIDTH = EIGHTH_WIDTH * 5;

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

int handleEvent(SDL_Event, SDL_Renderer *);
void free_resources_renderer( SDL_Renderer *, SDL_Window * );
void free_resources_window( SDL_Window * );

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
  if (argc == 2) {
    printf("The program was called with the following argument: %s\n", argv[1]);
  }

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
  window = SDL_CreateWindow(
      "HELLO SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    printf("Error while creating SDL_Window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error while creating SDL_Renderer: %s\n", SDL_GetError());
    free_resources_window( window );
    return 1;
  }
  SDL_SetWindowMinimumSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Texture *your_image_texture = IMG_LoadTexture(renderer, "your_image.png");
  if (your_image_texture == NULL) {
    printf("Unable to create texture! SDL_image Error: %s\n", IMG_GetError());
    free_resources_renderer( renderer, window );
    return 1;
  }

  SDL_Event e;
  int quit = 0;
  while (quit == 0) {
    SDL_SetRenderDrawColor(renderer, magenta.red, magenta.green, magenta.blue,
                           0xFF);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e)) {
      quit = handleEvent(e, renderer);
    } // End of: while (SDL_PollEvent(%e))

    // In your main loop, before calling SDL_RenderPresent
    SDL_SetRenderDrawColor(renderer, cyan.red, cyan.green, cyan.blue, 0xFF);
    SDL_Rect fillRect = {TOP_LEFT, TOP_LEFT, EDITOR_AREA_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderCopy(renderer, your_image_texture, NULL, NULL);
    // Update screen
    SDL_RenderPresent(renderer);
  } // End of: while (quit == 0)

  SDL_DestroyTexture(your_image_texture);

  free_resources_renderer( renderer, window );

  return 0;
} // End of: main function

/*
 * Handle events.
 *
 * e: event
 * renderer: renderer
 *
 * Return value: 0 if the program should not be terminated, 1 otherwise.
 */
int handleEvent(SDL_Event e, SDL_Renderer *renderer) {
  int shouldQuit = 0;
  switch (e.type) {
  case SDL_QUIT:
    printf("The app was terminated by the user.\n");
    shouldQuit = 1;
    break;
  case SDL_WINDOWEVENT:
    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
      int newWidth = e.window.data1;
      int newHeight = e.window.data2;
      if (newWidth > 0 && newHeight > 0) { // Only act on valid dimensions
        SDL_RenderSetLogicalSize(renderer, newWidth, newHeight);
        printf("newWidth: %d, newHeight: %d\n", newWidth, newHeight);
      }
    }
    break;
  case SDL_KEYDOWN:
    printf("SDL_KEYDOWN\n");
    break;
  case SDL_KEYUP:
    printf("SDL_KEYUP\n");
    break;
  case SDL_MOUSEMOTION:
    printf("SDL_MOUSEMOTION\n");
    break;
  case SDL_MOUSEBUTTONDOWN:
    printf("SDL_MOUSEBUTTONDOWN\n");
    break;
  default:
    break;
  }
  return shouldQuit;
} // End of: handleEvent function

void free_resources_renderer( SDL_Renderer *renderer, SDL_Window *window ) {
  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
  }
  free_resources_window ( window );

} // End of: free_resources_renderer function

void free_resources_window( SDL_Window *window ) {
    if (window != NULL) {
    SDL_DestroyWindow(window);
  }
  if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
    IMG_Quit();
  }
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Quit();
  }
} // End of: free_resources_window function


