/**
 * @file sdltest.c
 * @author ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief A simple SDL2 test program.
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 * @details This is a simple SDL2 test program. It displays a window and a
 * rectangle in it. The rectangle can be moved with the arrow keys (SOON).
 */

#include "sdltest.h"
#include "settings.h"

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MIN_RESOLUTION_WIDTH = 800;
const int MIN_RESOLUTION_HEIGHT = 600;

const Point TOP_LEFT = {0, 0};

// const Color WHITE = {0xFF, 0xFF, 0xfF};
// const Color BLACK = {0x00, 0x00, 0x00};
// const Color RED = {0xFF, 0x00, 0x00};
// const Color GREEN = {0x00, 0xFF, 0x00};
// const Color BLUE = {0x00, 0x00, 0xFF};
// const Color YELLOW = {0xFF, 0xFF, 0x00};
const Color CYAN = {0x00, 0xFF, 0xFF};
const Color MAGENTA = {0xFF, 0x00, 0xFF};

Dimensions output_screen;

/**
 * @brief Main function.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @return int The exit code of the program. 0 means success. Everything else
 * means failure.
 */
int main(int argc, const char *argv[]) {

  if (argc == 2) {
    cout << "The program was called with the following argument: " << argv[1]
         << endl;
  }

  config_graphics.full_screen = 0;
  config_graphics.resolution_width = MIN_RESOLUTION_WIDTH;
  config_graphics.resolution_height = MIN_RESOLUTION_HEIGHT;

  output_screen.width = config_graphics.resolution_width;
  output_screen.height = config_graphics.resolution_height;

  config_audio.master_volume = 100;

  config_editor_settings.grid_size = 32;

  int settings_file_parsing_failed = parse_settings_file();
  if (settings_file_parsing_failed) {
    return 1;
  }

  int initialization_failed = SDL_Init(SDL_INIT_VIDEO) < 0;
  if (initialization_failed) {
    cout << "Error while initializing SDL: " << SDL_GetError() << endl;
    return 1;
  }

  int img_initialization_failed =
      (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG;
  if (img_initialization_failed) {
    cout << "SDL_image could not initialize! SDL_image Error: "
         << IMG_GetError() << endl;
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = NULL;
  window = SDL_CreateWindow(
      "HELLO SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      config_graphics.resolution_width, config_graphics.resolution_height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    cout << "Error while creating SDL_Window: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    cout << "Error while creating SDL_Renderer: " << SDL_GetError() << endl;
    free_resources_window(window);
    return 1;
  }

  SDL_SetWindowMinimumSize(window, MIN_RESOLUTION_WIDTH, MIN_RESOLUTION_HEIGHT);

  string file_name = "1_Generic_48x48.png";
  string file_path = "assets/interiors/1_Interiors/48x48/Theme_Sorter_48x48/";
  string file_relative = file_path + file_name;

  SDL_Texture *your_image_texture =
      IMG_LoadTexture(renderer, file_relative.c_str());
  if (your_image_texture == NULL) {
    cout << "Error while creating SDL_Texture: " << SDL_GetError() << endl;
    free_resources_renderer(renderer, window);
    return 1;
  }

  SDL_Event e;
  int quit = 0;
  while (quit == 0) {
    SDL_SetRenderDrawColor(renderer, MAGENTA.red, MAGENTA.green, MAGENTA.blue,
                           0xFF);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e)) {
      quit = handle_event(e, renderer);
    } // End of: while (SDL_PollEvent(%e))

    SDL_SetRenderDrawColor(renderer, CYAN.red, CYAN.green, CYAN.blue, 0xFF);

    const SDL_Rect RECT_EDITOR = {
        TOP_LEFT.x, TOP_LEFT.y, output_screen.width / 2, output_screen.height};
    SDL_RenderFillRect(renderer, &RECT_EDITOR);
    SDL_RenderCopy(renderer, your_image_texture, NULL, &RECT_EDITOR);

    SDL_RenderPresent(renderer);
  } // End of: while (quit == 0)

  SDL_DestroyTexture(your_image_texture);

  free_resources_renderer(renderer, window);

  return 0;
} // End of: main function

bool handle_event(SDL_Event e, SDL_Renderer *renderer) {
  bool should_quit = false;
  switch (e.type) {
  case SDL_QUIT:
    cout << "The app was terminated by the user." << endl;
    should_quit = true;
    break;
  case SDL_WINDOWEVENT:
    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {

      if (e.window.data1 > 0 &&
          e.window.data2 > 0) { // Only act on valid dimensions
        SDL_RenderSetLogicalSize(renderer, e.window.data1, e.window.data2);
        output_screen.width = e.window.data1;
        output_screen.height = e.window.data2;
        cout << "newWidth: " << e.window.data1
             << ", newHeight: " << e.window.data2 << endl;
      }
    }
    break;
  case SDL_KEYDOWN:
    cout << "e.key.keysym.sym: " << e.key.keysym.sym << endl;
    break;
  case SDL_KEYUP:
    cout << "e.key.keysym.sym: " << e.key.keysym.sym << endl;
    break;
  case SDL_MOUSEMOTION:
    cout << "e.motion.x: " << e.motion.x << ", e.motion.y: " << e.motion.y
         << endl;
    break;
  case SDL_MOUSEBUTTONDOWN:
    cout << "e.button.x: " << e.button.x << ", e.button.y: " << e.button.y
         << endl;
    break;
  default:
    break;
  }
  return should_quit;
} // End of: handleEvent function

void free_resources_renderer(SDL_Renderer *renderer, SDL_Window *window) {
  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
  }
  free_resources_window(window);

} // End of: free_resources_renderer function

void free_resources_window(SDL_Window *window) {
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

SDL_Texture *load_texture(SDL_Renderer *renderer, const string &file_relative) {
  return IMG_LoadTexture(renderer, file_relative.c_str());
}
