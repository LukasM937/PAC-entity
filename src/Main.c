#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_timer.h>
#include <SDL2/SDL_image.h>

//#include "Pac-entity.h"
//#include "assets.h"
#include "background.h"

typedef struct player
{
    int posX;
    int posY;
} player;

int main(void)
{
    player* one = malloc(sizeof(player));

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello, Fenster!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       950, 1100, 0);
    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

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

    SDL_Surface* surface = IMG_Load("/assset/Background.png");
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

    texture(window, renderer, tex);
    /*
    SDL_Texture* mapTiles;

    //Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    surface = IMG_Load("/assset/Map_elements.png");
    mapTiles = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect targetRect;
    SDL_Rect sourceRect;

    for(int i = 0; i < 22; i++)
    {
        printf("%d\n", i);
        for(int j = 0; j < 19; j++)
        {
            printf("%d\n", j);
            targetRect.x = blockSize * j;
            targetRect.y = blockSize * i;
            targetRect.w = blockSize;
            targetRect.h = blockSize;

            sourceRect.w = blockSize;
            sourceRect.h = blockSize;

            toTextureDestination(background[i][j], &sourceRect.x, &sourceRect.y);
            SDL_RenderCopy(renderer, tex, NULL, NULL);
            SDL_RenderCopy(renderer, mapTiles, &sourceRect, &targetRect);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(mapTiles);
    SDL_DestroyRenderer(renderer);
    */


    SDL_Event event;
    int quit = 0;

    SDL_UpdateWindowSurface(window);

    while (quit == 0)
    {
        //move(one, points);
        /*SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
        SDL_RenderPresent(renderer);*/

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


    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
