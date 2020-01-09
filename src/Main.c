#include <stdio.h>

#include <SDL2/SDL.h>

#include "Pac-entity.h"

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = NULL;

    SDL_Surface * window_surface = NULL;
    SDL_Surface * image_surface = NULL;

    SDL_Renderer* renderer = NULL;
    SDL_Event quitEvent;
    int quit = 0;
    if(SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
    {
        quit = 0;
    }

    window_surface = SDL_GetWindowSurface(window);

    SDL_UpdateWindowSurface(window);

    
    while (quit == 0)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&quitEvent)){
            if (quitEvent.type == SDL_QUIT){
                quit = 1;
            }
            if (quitEvent.type == SDL_KEYDOWN){
                quit = 1;
            }
            if (quitEvent.type == SDL_MOUSEBUTTONDOWN){
                quit = 1;
            }
        }
    }


    SDL_DestroyWindow(window);
    SDL_FreeSurface(image_surface);
    SDL_Quit();

    return 0;
}
