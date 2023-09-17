/**
 * @file sdltest.h
 * @author Ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief A test of the SDL2 library.
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SDLTEST_H
#define SDLTEST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Holds the configuration for the graphics.
 *
 */
typedef struct {
  int full_screen;
  int resolution_width;
  int resolution_height;
  int vsync;
  int anti_aliasing;
  char *texture_quality;
  char *shader_quality;
} ConfigGraphics;

/**
 * @brief Holds the configuration for the audio.
 *
 */
typedef struct {
  int master_volume;
  int music_volume;
  int sfx_volume;
  int voice_volume;
  int ambience_volume;
  int mute_all;
  char *audio_output;
} ConfigAudio;

/**
 * @brief Holds the configuration for the controls.
 *
 */
typedef struct {
  int grid_size;
  int show_grid;
  int auto_save_interval;
  int undo_stack_size;
  int default_layer;
  int snap_to_grid;
  char *tileset_path;
} ConfigEditorSettings;

/**
 * @brief Description of a point.
 *
 */
typedef struct {
  int x;
  int y;
} Point;

/**
 * @brief Description of dimensions. Width and height.
 *
 */
typedef struct {
  int width;
  int height;
} Dimensions;

/**
 * @brief Description of a rectangle. Position and dimensions.
 *
 */
typedef struct {
  Point position;
  Dimensions dimensions;
} Rect;

/**
 * @brief Description of a color. RGB.
 *
 */
typedef struct {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
} Color;

/**
 * @brief Parses the settings file and stores the values in the config structs.
 *
 * @return int 0 if successful, 1 if not.
 */
int parse_settings_file();

/**
 * @brief Handles events from the event queue.
 *
 * @return int 0 if the program should continue, 1 if it should quit.
 */
int handle_event(SDL_Event, SDL_Renderer *);

/**
 * @brief Frees all resources from the renderer "backwards".
 *
 * @param renderer The renderer to free.
 * @param window The window to free.
 */
void free_resources_renderer(SDL_Renderer *, SDL_Window *);

/**
 * @brief Frees all resources from the window "backwards".
 *
 * @param window The window to free.
 */
void free_resources_window(SDL_Window *);

#endif // SDLTEST_H
