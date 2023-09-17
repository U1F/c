#ifndef SDLTEST_H
#define SDLTEST_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#endif // SDLTEST_H

typedef struct {
  int full_screen;
  int resolution_width;
  int resolution_height;
  int vsync;
  int anti_aliasing;
  char *texture_quality;
  char *shader_quality;
} ConfigGraphics;

typedef struct {
  int master_volume;
  int music_volume;
  int sfx_volume;
  int voice_volume;
  int ambience_volume;
  int mute_all;
  char *audio_output;
} ConfigAudio;

typedef struct {
  int grid_size;
  int show_grid;
  int auto_save_interval;
  int undo_stack_size;
  int default_layer;
  int snap_to_grid;
  char *tileset_path;
} ConfigEditorSettings;

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int width;
  int height;
} Dimensions;

typedef struct {
  Point position;
  Dimensions dimensions;
} Rect;

typedef struct {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
} Color;

/*
 * Parse settings file.
 *
 * Return value: 0 if the file was parsed successfully, 1 otherwise.
 */
int parse_settings_file();

/*
 * Handle events.
 *
 * e: event
 * renderer: renderer
 *
 * Return value: 0 if the program should not be terminated, 1 otherwise.
 */
int handle_event(SDL_Event, SDL_Renderer *);

/**
 * Free resources.
 *
 * renderer: renderer
 * window: window
 *
 * Return value: none
 */
void free_resources_renderer(SDL_Renderer *, SDL_Window *);

/**
 * Free resources.
 *
 * window: window
 *
 * Return value: none
 */
void free_resources_window(SDL_Window *);

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