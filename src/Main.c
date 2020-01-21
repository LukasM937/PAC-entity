#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "background.h"

#define SCREEN_WIDTH 950
#define SCREEN_HEIGHT 1100
#define SHAPE_SIZE 40
#define FPS_Cap 60
#define PAC_SPEED 300
#define PAC_START_X 450
#define PAC_START_Y 805
#define BUMPER 10

typedef struct player
{
    int x;
    int y;
    int rotation;
    int speed;
} player;

int validPathX (int x)
{
    int a;
    a = x % 50;

    return a;
}
int validPathY (int y)
{
    int a;
    a = y % 50;

    return a;
}

bool canimove(int arx, int ary, int pox1, int poy1)
{
    int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
    int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));

    if(background [puffery1] [pufferx1] <= 1)
    {
        return true;
    }
    else return false;
}

int main(void)
{
    time_t start_t, end_t;
    double diff_t;
    int fpsDiff;
    int a;
    
    player pac;
    pac.speed = PAC_SPEED/FPS_Cap;

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
    
    SDL_Surface* backSurface = IMG_Load("/assets/Background_Map.bmp");
    if (!backSurface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* mapElements = IMG_Load("/assets/Map_elements.png");
    if (!mapElements)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    if (!backTexture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // clear the window
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);

    // Points
    SDL_Texture* pointTexture = SDL_CreateTextureFromSurface(renderer, mapElements);
    if (!pointTexture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect targetRect;
    SDL_Rect sourceRect;
    targetRect.w = blockSize;
    targetRect.h = blockSize;

    sourceRect.w = blockSize;
    sourceRect.h = blockSize;

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
    
    //erstellt das viereck in dem pacman dargestellt wird
    SDL_Rect pacPosition;
    pacPosition.x = PAC_START_X;
    pacPosition.y = PAC_START_Y;
    pacPosition.w = SHAPE_SIZE;
    pacPosition.h = SHAPE_SIZE;

    float y_pos = pacPosition.y;
    float x_pos = pacPosition.x;
    
    SDL_RenderCopy(renderer, pacEntity, NULL, &pacPosition);
    SDL_RenderPresent(renderer);

    //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir
    int rotation;
    
    bool running = true;

    SDL_Event event;

    SDL_UpdateWindowSurface(window);

    while (running)
    {
        time(&start_t);
        SDL_RenderClear(renderer);

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
                        if(pacPosition.x > 0 && canimove(19, 22, pacPosition.x-BUMPER, pacPosition.y+pacPosition.h)==true && validPathY(pacPosition.y) <= 5)
                        {
                            pac.rotation=180;
                            // printf("left\n");
                        }
                        break;
                    case SDLK_RIGHT:
                        if(pacPosition.x < SCREEN_WIDTH && canimove(19, 22, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h)==true && validPathY(pacPosition.y) <= 5)
                        {
                            pac.rotation=0;
                            // printf("right\n");
                        }
                        break;
                    case SDLK_UP:
                        if(pacPosition.y > 0 && canimove(19, 22, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER)==true && validPathX(pacPosition.x) <= 5)
                        {
                            pac.rotation=270; 
                            // printf("up\n",);
                        }
                        break;
                    case SDLK_DOWN:
                        rotation = pac.rotation;
                        if(pacPosition.y < SCREEN_HEIGHT && canimove(19, 22, pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER)==true && validPathX(pacPosition.x) <= 5)
                        {
                            pac.rotation=90;
                            // printf("down\n");
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
        
        //läd pacman ins fenster und repräsentiert alles
        pacPosition.y = (int) y_pos;
        pacPosition.x = (int) x_pos;
        
        SDL_RenderCopy(renderer, backTexture, NULL, NULL);
        for(int i = 0; i < 22; i++)
        {
            for(int j = 0; j < 19; j++)
            {
                targetRect.x = blockSize * j;
                targetRect.y = blockSize * i;
        
                if(background[i][j] == 1)
                {
                    sourceRect.x = 0;
                    sourceRect.y = 200;
                    SDL_RenderCopy(renderer, pointTexture, &sourceRect, &targetRect);
                }   
            }
        }

        SDL_RenderCopyEx(renderer, pacEntity, NULL, &pacPosition, pac.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        //pac Animation
        switch (pac.rotation)
        {
            case 0:                         //right
                x_pos += (float) pac.speed;
                if(canimove(19, 22, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 90:                        //down
                y_pos += (float) pac.speed;
                if(canimove(19, 22, pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 180:                       //left
                x_pos -= (float) pac.speed;
                if(canimove(19, 22, pacPosition.x-BUMPER, pacPosition.y+pacPosition.h))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 270:                       //up
                y_pos -= (float) pac.speed;
                if(canimove(19, 22, pacPosition.x+pacPosition.w, pacPosition.y-(BUMPER)))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            
            default:
                break;
        }
        a = validPathX(pacPosition.x);
        //printf("%d, ", a);
        a = validPathY(pacPosition.y);
        //printf("%d \n", a);

        time(&end_t);
        diff_t = difftime(end_t, start_t);
        fpsDiff = 60 - diff_t;

        SDL_Delay(1000/fpsDiff);
    }
    
    SDL_FreeSurface(image);
    SDL_FreeSurface(backSurface);
    SDL_FreeSurface(mapElements);

    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(pointTexture);
    SDL_DestroyTexture(pacEntity);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
