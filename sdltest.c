/**
 * @file sdltest.c
 * @author ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief A simple SDL2 test program.
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "sdltest.h"
#include <stdio.h>

static ConfigGraphics config_graphics;
static ConfigAudio config_audio;
static ConfigEditorSettings config_editor_settings;

const int MIN_RESOLUTION_WIDTH = 800;
const int MIN_RESOLUTION_HEIGHT = 600;

const Point TOP_LEFT = {0, 0};

const Color WHITE = {0xFF, 0xFF, 0xfF};
const Color BLACK = {0x00, 0x00, 0x00};
const Color RED = {0xFF, 0x00, 0x00};
const Color GREEN = {0x00, 0xFF, 0x00};
const Color BLUE = {0x00, 0x00, 0xFF};
const Color YELLOW = {0xFF, 0xFF, 0x00};
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
int main(int argc, char *argv[]) {
  if (argc == 2) {
    printf("The program was called with the following argument: %s\n", argv[1]);
  }

  config_graphics.full_screen = 0;
  config_graphics.resolution_width = MIN_RESOLUTION_WIDTH;
  config_graphics.resolution_height = MIN_RESOLUTION_HEIGHT;
  
  int settings_file_parsing_failed = parse_settings_file();
  if (settings_file_parsing_failed) {
    return 1;
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
      config_graphics.resolution_width, config_graphics.resolution_height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    printf("Error while creating SDL_Window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error while creating SDL_Renderer: %s\n", SDL_GetError());
    free_resources_window(window);
    return 1;
  }

  char *file_name = "1_Generic_48x48.png";
  char *file_path = "assets/interiors/1_Interiors/48x48/Theme_Sorter_48x48/";
  // concatenate file_path and file_name
  char *file_relative = malloc(strlen(file_path) + strlen(file_name) + 1);
  strcpy(file_relative, file_path);
  strcat(file_relative, file_name);
  printf("file_relative: %s\n", file_relative);

  SDL_SetWindowMinimumSize(window, MIN_RESOLUTION_WIDTH, MIN_RESOLUTION_HEIGHT);
  SDL_Texture *your_image_texture = IMG_LoadTexture(renderer, file_relative);
  if (your_image_texture == NULL) {
    printf("Unable to create texture! SDL_image Error: %s\n", IMG_GetError());
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
 
    const SDL_Rect RECT_EDITOR = {TOP_LEFT.x, TOP_LEFT.y, output_screen.width / 2,
                                  output_screen.height};

    SDL_RenderFillRect(renderer, &RECT_EDITOR);
    SDL_RenderCopy(renderer, your_image_texture, NULL, &RECT_EDITOR);

    // Update screen
    SDL_RenderPresent(renderer);
  } // End of: while (quit == 0)

  SDL_DestroyTexture(your_image_texture);

  free_resources_renderer(renderer, window);

  return 0;
} // End of: main function

int parse_settings_file() {
  FILE *file = fopen("settings.ini", "r");
  if (file == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  char line[256];
  char *key, *value;
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '[' || line[0] == '\n') {
      continue; // Skip sections and empty lines
    }

    key = strtok(line, "=");
    value = strtok(NULL, "\n");

    if (key && value) {
      printf("Key: %s, Value: %s\n", key, value);
      if (strcmp(key, "FullScreen") == 0) {
        printf("FullScreen: %s\n", value);
        config_graphics.full_screen = strcmp(value, "true") == 0;
      } else if (strcmp(key, "ResolutionWidth") == 0) {
        config_graphics.resolution_width = atoi(value);
      } else if (strcmp(key, "ResolutionHeight") == 0) {
        config_graphics.resolution_height = atoi(value);
      } else if (strcmp(key, "VSync") == 0) {
        config_graphics.vsync = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AntiAliasing") == 0) {
        config_graphics.anti_aliasing = atoi(value);
      } else if (strcmp(key, "TextureQuality") == 0) {
        config_graphics.texture_quality = strdup(value);
      } else if (strcmp(key, "ShaderQuality") == 0) {
        config_graphics.shader_quality = strdup(value);
      } else if (strcmp(key, "MasterVolume") == 0) {
        config_audio.master_volume = atoi(value);
      } else if (strcmp(key, "MusicVolume") == 0) {
        config_audio.music_volume = atoi(value);
      } else if (strcmp(key, "SFXVolume") == 0) {
        config_audio.sfx_volume = atoi(value);
      } else if (strcmp(key, "VoiceVolume") == 0) {
        config_audio.voice_volume = atoi(value);
      } else if (strcmp(key, "AmbienceVolume") == 0) {
        config_audio.ambience_volume = atoi(value);
      } else if (strcmp(key, "MuteAll") == 0) {
        config_audio.mute_all = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AudioOutput") == 0) {
        config_audio.audio_output = strdup(value);
      } else if (strcmp(key, "GridSize") == 0) {
        config_editor_settings.grid_size = atoi(value);
      } else if (strcmp(key, "ShowGrid") == 0) {
        config_editor_settings.show_grid = strcmp(value, "true") == 0;
      } else if (strcmp(key, "AutoSaveInterval") == 0) {
        config_editor_settings.auto_save_interval = atoi(value);
      } else if (strcmp(key, "UndoStackSize") == 0) {
        config_editor_settings.undo_stack_size = atoi(value);
      } else if (strcmp(key, "DefaultLayer") == 0) {
        config_editor_settings.default_layer = atoi(value);
      } else if (strcmp(key, "SnapToGrid") == 0) {
        config_editor_settings.snap_to_grid = strcmp(value, "true") == 0;
      } else if (strcmp(key, "TilesetPath") == 0) {
        config_editor_settings.tileset_path = strdup(value);
      }
    }
  }

  fclose(file);
  return 0;
} // End of: parse_settings_file function

int handle_event(SDL_Event e, SDL_Renderer *renderer) {
  int should_quit = 0;
  switch (e.type) {
  case SDL_QUIT:
    printf("The app was terminated by the user.\n");
    should_quit = 1;
    break;
  case SDL_WINDOWEVENT:
    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
      
      if (e.window.data1 > 0 && e.window.data2 > 0) { // Only act on valid dimensions
        SDL_RenderSetLogicalSize(renderer, e.window.data1, e.window.data2);
        output_screen.width  = e.window.data1;
        output_screen.height = e.window.data2;
        printf("newWidth: %d, newHeight: %d\n", e.window.data1, e.window.data2);
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
