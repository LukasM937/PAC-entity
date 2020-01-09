#include <stdio.h>

#include <SDL2/SDL.h>

#include "Pac-entity.h"

typedef struct player
{
    int posX;
    int posY;
} player;

// void move(void* arg, SDL_Point& points)
// {
//     player* one = (player*)arg;
//     one->posX = WINDOW_WIDTH/2;
//     one->posY = WINDOW_HEIGHT/2;

//     points = {{one->posX - 50, one->posY - 50},
//             {one->posX + 50, one->posY - 50},
//             {one->posX + 50, one->posY + 50},
//             {one->posX - 50, one->posY + 50}
//     };
// }

int main(void)
{
    player* one = malloc(sizeof(player));
    // SDL_Point* points[POINTS_COUNT];

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = NULL;

    SDL_Surface * window_surface = NULL;
    SDL_Surface * image_surface = NULL;

    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    int quit = 0;
    if(SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
    {
        quit = 0;
    }

    window_surface = SDL_GetWindowSurface(window);

    SDL_UpdateWindowSurface(window);

    
    while (quit == 0)
    {
        //move(one, points);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        {

            switch(event.type )
            {
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        one->posX -= 1;
                        break;
                    case SDLK_RIGHT:
                        one->posX  += 1;
                        break;
                    case SDLK_UP:
                        one->posY  -= 1;
                        break;
                    case SDLK_DOWN:
                        one->posY += 1;
                        break;
                    case SDLK_ESCAPE:
                        quit =1;
                        break;
                    default:
                        break;
                }
            }
        }
    }


    SDL_DestroyWindow(window);
    SDL_FreeSurface(image_surface);
    SDL_Quit();

    return 0;
}
