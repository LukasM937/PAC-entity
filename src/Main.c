#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_timer.h>
#include <SDL2/SDL_image.h>

//#include "Pac-entity.h"
//#include "assets.h"
#include "background.h"

#define SCREEN_WIDTH 950
#define SCREEN_HEIGHT 1100
#define SHAPE_SIZE 40

typedef struct player
{
    int posX;
    int posY;
} player;

bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1){
        //int pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
        //int puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

        int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
        int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));

        if(background [puffery1] [pufferx1] == 0 || background [puffery1] [pufferx1] == 1){
            return true;
        }
        else return false;
}
// bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1, int back[][ary]){
//         int pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
//         int puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

//         int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
//         int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));

//         if((back[puffery][pufferx]==0 || back[puffery][pufferx]==1 )&& (background [puffery1] [pufferx1] == 0 || background [puffery1] [pufferx1] == 1)){
//             return true;
//         }
//         else return false;
// }



int main(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Im Arsch: %s \n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pac-entity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    
    SDL_Surface* background = IMG_Load("/assets/Background_Map.bmp");
    if (!background)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, background);
    SDL_FreeSurface(background);
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

    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);

    //Pac-entity zeug
    
    SDL_Surface * image = IMG_Load("/assets/PAC-entity_frameless.png");
    if (!image)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* pacEntity = SDL_CreateTextureFromSurface(renderer, image);
    if (!pacEntity)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(image);
    
    //erstellt das viereck in dem pacman dargestellt wird
    SDL_Rect immageposition;
    immageposition.x = 100;
    immageposition.y = 50;
    immageposition.w = SHAPE_SIZE;
    immageposition.h = SHAPE_SIZE;
    
    SDL_RenderCopy(renderer, pacEntity, NULL, &immageposition);
    SDL_RenderPresent(renderer);

    //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir
    int rotation;
    
    bool running = true;

    SDL_Event event;

    SDL_UpdateWindowSurface(window);

    while (running)
    { 
        while (SDL_PollEvent(&event))
        {
            switch(event.type )
            {
                case SDL_QUIT:
                    running = false;
                    break;
                /* Look for a keypress */
                case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym )
                {
                    case SDLK_LEFT:
                        if(immageposition.x > 0 && canimove(19, 22, immageposition.x-1, immageposition.y, immageposition.x-1, immageposition.y+immageposition.h)==true)
                        {
                            immageposition.x --; rotation=180;
                            printf("left\n");
                        }
                        break;
                    case SDLK_RIGHT:
                        if(immageposition.x < SCREEN_WIDTH && canimove(19, 22,immageposition.x+immageposition.w+1, immageposition.y, immageposition.x +immageposition.w +1, immageposition.y+immageposition.h)==true)
                        {
                            immageposition.x ++; rotation=0;
                            printf("right\n");
                        }
                        break;
                    case SDLK_UP:
                        if(immageposition.y > 0 && canimove(19, 22, immageposition.x, immageposition.y-1, immageposition.x+immageposition.w, immageposition.y-1)==true)
                        {
                            immageposition.y --; rotation=270; 
                            printf("up\n");
                        }
                        break;
                    case SDLK_DOWN:
                        if(immageposition.y < SCREEN_HEIGHT && canimove(19, 22, immageposition.x, immageposition.y+immageposition.h+1,immageposition.x+immageposition.w, immageposition.y+immageposition.h+1)==true)
                        {
                            immageposition.y ++; rotation=90;
                            printf("down\n");
                        }
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(pacEntity);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
