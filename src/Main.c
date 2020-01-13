#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_timer.h>
#include </Users/lmuehrke/Documents/GitHub/PAC-entity/sdl2/2.0.10/include/SDL2/SDL_image.h>

#include "Pac-entity.h"
//#include "assets.h"

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

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = NULL;

    // SDL_Surface * window_surface = NULL;
    SDL_Surface * image_surface = NULL;

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }

    SDL_Surface* surface = IMG_Load("assets/PAC-entity_frameless.png");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // clear the window
    SDL_RenderClear(renderer);
    
    // draw the image to the window
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

    // wait a few seconds
    SDL_Delay(5000);

    SDL_Event event;
    int quit = 0;
    if(SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
    {
        quit = 0;
    }

    //window_surface = SDL_GetWindowSurface(window);

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
