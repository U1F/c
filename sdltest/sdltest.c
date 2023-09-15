#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum boolean
{
    FALSE,
    TRUE
};

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
   
    SDL_Window *window = NULL;
    window = SDL_CreateWindow("HELLO SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
  
    SDL_Surface *screenSurface = NULL;
    screenSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window);

    // Hack to get window to stay up
    SDL_Event e;
    enum boolean quit = FALSE;
    while (quit == FALSE)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = TRUE;
        }
    }
  
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
