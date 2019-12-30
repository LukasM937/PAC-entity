#include <stdio.h>

#include <SDL2/SDL.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = NULL;

    SDL_Surface * window_surface = NULL;
    SDL_Surface * image_surface = NULL;

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);

    window_surface = SDL_GetWindowSurface(window);
    image_surface = SDL_LoadBMP("image.bmp");

    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);

    SDL_UpdateWindowSurface(window);

    SDL_Event quitEvent;
    int quit = 0;
    while (quit == 0)
    {
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
