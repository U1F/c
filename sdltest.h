/**
 * @file sdltest.h
 * @author Ulf Dellbrügge (xintamosaik@gmail.com)
 * @brief A test of the SDL2 library.
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 * @details This is a test of the SDL2 library. It is a simple program that
 * displays a window and a rectangle in it. The rectangle can be moved with the
 * arrow keys (SOON).
 */

#ifndef SDLTEST_H
#define SDLTEST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

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


/**
 * @brief Concatenates two paths.
 *
 * @param file_name The name of the file.
 * @param name_len The length of the file name.
 * @param file_path The path to the file.
 * @param path_len The length of the path.
 * @return char* The concatenated path.
 */
char* concat_strings(const char *, size_t, const char *, size_t);

/**
 * @brief Loads a texture from a file.
 *
 * @param renderer The renderer to load the texture to.
 * @param file_relative The path to the file.
 * @return SDL_Texture* The loaded texture.
 */
SDL_Texture* load_texture(SDL_Renderer *, const char *);

#endif // SDLTEST_H
