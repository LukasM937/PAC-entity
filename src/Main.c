#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_timer.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 950
#define SCREEN_HEIGHT 1100
#define SHAPE_SIZE 40
#define FPS_Cap 60
#define PAC_SPEED 300
#define GHOST_SPEED 3
#define PAC_START_X 450
#define PAC_START_Y 805
#define BUMPER 10
#define ARX 19
#define ARY 22
#define BUFFER_LENGTH 10

#include "background.h"
#include "function.h"

/*
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

bool canimoveV2(int *was, int speed, int pox, int poy, int pox1, int poy1, int *munzenzahler, int *apfel)
{
    int buf = *was;
    int pufferx, puffery, pufferx1, puffery1;
    for(int i = 1; i <= speed; i++)
    {
        if(buf == 0)
        {
            return false;
        }
        if(buf==1)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)(poy-i)/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)(poy1-i)/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf==2)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)(poy+i)/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)(poy1+i)/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf==3)
        {
            pufferx = (int)((double)(pox+i)/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)(pox1+i)/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf==4)
        {
            pufferx = (int)((double)(pox-i)/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)(pox1-i)/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ARY));
        }

        if((background[puffery][pufferx]==0 || background[puffery][pufferx]==1 || background[puffery][pufferx]==22) && (background[puffery1] [pufferx1] == 0 || background[puffery1] [pufferx1] == 1 || background[puffery1][pufferx1]==22))
        {
            *was=i;

            if(background[puffery][pufferx]==22)
            {
                *apfel=*apfel+1;
                background[puffery][pufferx]=0;
            }
            else if(background[puffery1][pufferx1]==22)
            {
                *apfel=*apfel+1;
                background[puffery][pufferx]=0;
            }
            if(background[puffery][pufferx]==1)
            {
                *munzenzahler=*munzenzahler+1;
                background[puffery][pufferx]=0;
            }
            else if(background[puffery1][pufferx1]==1)
            {
                *munzenzahler=*munzenzahler+1;
                background[puffery1][pufferx1]=0;
            }
        }
        else if (i==1)
        {
            return false;
        }
        else return true;
    }
    return true;
}

bool canimove (int pox, int poy, int pox1, int poy1)
{
    int pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/ARX));
    int puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ARY));

    int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/ARX));
    int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ARY));

    if(background[puffery][pufferx]==0 || (background[puffery][pufferx]==1 && background[puffery1][pufferx1] == 0) || background[puffery1][pufferx1] == 1)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void ghostMove (SDL_Rect *pac, SDL_Rect *ghost, player *ghostStuff)
{
    if (pac->y < ghost->y) 
    {
        if(canimove(ghost->x, ghost->y - BUMPER, ghost->x + ghost->w, ghost->y - BUMPER) == true)//moved nach oben
            {
                ghost->y -= ghostStuff->speed;
            }
        else
        {
            if (pac->x < ghost->x) 
            {
                if (canimove(ghost->x - BUMPER, ghost->y, ghost->x - BUMPER, ghost->y + ghost->h) == true) //moved nachlinks
                {
                    ghost->x -= ghostStuff->speed;
                }

            }
            else 
            {
                if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true)
                {
                    ghost->x += ghostStuff->speed;
                }
            }   
        }
    }
    if (pac->y == ghost->y) 
    {
        if (pac->x < ghost->x) 
        {
            if (canimove(ghost->x - BUMPER, ghost->y, ghost->x - BUMPER, ghost->y + ghost->h) == true) //moved nach links
            {
                ghost->x -= ghostStuff->speed;
            }
        }
        else 
        {
            if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true) 
            {
                ghost->x += ghostStuff->speed;
            }
        }
    }
    if (pac->y > ghost->y) 
    {
        if (canimove(ghost->x, ghost->y + ghost->h + BUMPER, ghost->x + ghost->w, ghost->y + ghost->h + BUMPER) == true) // moved nach unten
        {
            ghost->y += ghostStuff->speed;
        }
        else 
        {
            if (pac->x < ghost->x) 
            {
                if (canimove(ghost->x - BUMPER, ghost->y, ghost->x - BUMPER, ghost->y + ghost->h) == true) //moved nach links
                {
                    ghost->x -= ghostStuff->speed;
                }
                
                
            }
            else 
            {
                if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true) 
                {
                    ghost->x += ghostStuff->speed;
                }
            }
        }
    }
}
*/

int main(void)
{
    time_t start_t, end_t;
    double diff_t;
    int fpsDiff;

    int *was, o;
    was=&o;

    //Leben = Äpfel
    int apfel=1;

    //zählt die münzen hoch
    int munzenzahler=0;

    //structs für Pac-Ding und geister. Geister sind unterschiedlich um unterschiedliche ziele leichter zu realisieren.
    player pac;
    player redG, pinkG, cyanG, brownG;
    pac.speed = PAC_SPEED/FPS_Cap;
    redG.speed = GHOST_SPEED;
    pinkG.speed = GHOST_SPEED;
    cyanG.speed = GHOST_SPEED;
    brownG.speed = GHOST_SPEED;

    redG.rotation = 0;
    pinkG.rotation = 0;
    cyanG.rotation = 0;
    brownG.rotation = 0;

    SDL_Texture* ghostRedTex = NULL;
    SDL_Texture* ghostPinkTex = NULL;
    SDL_Texture* ghostCyanTex = NULL;
    SDL_Texture* ghostBrownTex = NULL;

    SDL_Rect targetRect;
    SDL_Rect sourceRect;

    targetRect.w = blockSize;
    targetRect.h = blockSize;

    sourceRect.w = blockSize;
    sourceRect.h = blockSize;

    //Bewegungs Buffer
    SDL_Keycode *buffer;

    buffer = malloc(BUFFER_LENGTH * sizeof(SDL_Keycode));
    for(int k = 0; k < BUFFER_LENGTH; k++)
    {
        buffer[k] = 0;
    }

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

    SDL_Surface* ghostLoder = IMG_Load("/assets/PAC-Ghost_red_frameless.png");
    ghostRedTex = SDL_CreateTextureFromSurface(renderer, ghostLoder);
    SDL_FreeSurface(ghostLoder);

    ghostLoder = IMG_Load("/assets/PAC-Ghost_pink_frameless.png");
    ghostPinkTex = SDL_CreateTextureFromSurface(renderer, ghostLoder);
    SDL_FreeSurface(ghostLoder);

    ghostLoder = IMG_Load("/assets/PAC-Ghost_cyan_frameless.png");
    ghostCyanTex = SDL_CreateTextureFromSurface(renderer, ghostLoder);
    SDL_FreeSurface(ghostLoder);

    ghostLoder = IMG_Load("/assets/PAC-Ghost_brown_frameless.png");
    ghostBrownTex = SDL_CreateTextureFromSurface(renderer, ghostLoder);
    SDL_FreeSurface(ghostLoder);

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
    
    //erstellt das Viereck in dem pacman und Geister dargestellt werden
    SDL_Rect pacPosition;
    pacPosition.x = PAC_START_X;
    pacPosition.y = PAC_START_Y;
    pacPosition.w = SHAPE_SIZE;
    pacPosition.h = SHAPE_SIZE;

    SDL_Rect redPosition;
    redPosition.x = 225;
    redPosition.y = 175;
    redPosition.w = SHAPE_SIZE;
    redPosition.h = SHAPE_SIZE;

    SDL_Rect pinkPosition;
    pinkPosition.x = 400;
    pinkPosition.y = 300;
    pinkPosition.w = SHAPE_SIZE;
    pinkPosition.h = SHAPE_SIZE;
    
    SDL_Rect cyanPosition;
    cyanPosition.x = 10;
    cyanPosition.y = 50;
    cyanPosition.w = SHAPE_SIZE;
    cyanPosition.h = SHAPE_SIZE;

    SDL_Rect brownPosition;
    brownPosition.x = 350;
    brownPosition.y = 200;
    brownPosition.w = SHAPE_SIZE;
    brownPosition.h = SHAPE_SIZE;

    float y_pos = pacPosition.y;
    float x_pos = pacPosition.x;
    
    SDL_RenderCopy(renderer, pacEntity, NULL, &pacPosition);
    SDL_RenderPresent(renderer);

    //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir  
    bool running = true;

    SDL_Event event;

    SDL_UpdateWindowSurface(window);

    // @Draw everything on the Window 
    while (running)
    {
        time(&start_t);
        SDL_RenderClear(renderer);
        
        //Shift the Buffer
        for(int i = BUFFER_LENGTH - 1; i >= 0; i--)
        {
            buffer[i+1] = buffer[i];
        }
        buffer[0] = 0;

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                /* Look for a keypress */
                case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym )
                {   
                    case SDLK_UP:
                        *was=1;
                        if(pacPosition.y > 0 && canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y, pacPosition.x+pacPosition.w, pacPosition.y, &munzenzahler, &apfel)==true) 
                        {
                            pacPosition.y = pacPosition.y - *was;
                            pac.rotation = 270;
                            // buffer[0] = SDLK_UP;
                        }
                        break;
                    case SDLK_DOWN:
                        *was=2;
                        if(pacPosition.y < SCREEN_HEIGHT && canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y+pacPosition.h,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h, &munzenzahler, &apfel)==true)
                        {
                            pacPosition.y = pacPosition.y + *was;
                            pac.rotation = 90;
                            // buffer[0] = SDLK_DOWN;
                        }
                        break;
                    case SDLK_RIGHT:
                        *was=3;
                        if(pacPosition.x < SCREEN_WIDTH && canimoveV2(was, pac.speed, pacPosition.x+pacPosition.w, pacPosition.y, pacPosition.x+pacPosition.w , pacPosition.y+pacPosition.h, &munzenzahler, &apfel)==true)
                        {
                            pacPosition.x = pacPosition.x + *was;
                            pac.rotation = 0;
                            // buffer[0] = SDLK_RIGHT;
                        }
                        break;
                    case SDLK_LEFT:
                        *was=4;
                        if(pacPosition.x > 0 && canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y, pacPosition.x, pacPosition.y+pacPosition.h, &munzenzahler, &apfel)==true)
                        {
                            pacPosition.x = pacPosition.x - *was;
                            pac.rotation = 180;
                            // buffer[0] = SDLK_LEFT;
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
        //lÃ¤d pacman ins fenster und reprÃ¤sentiert alles
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

        //Geistbewegung Geist 1
        ghostMove(&pacPosition, &redPosition, &redG);
        //Geistbewegung Geist 2
        ghostMove(&pacPosition, &pinkPosition, &pinkG);
        //Geistbewegung Geist 3
        ghostMove(&pacPosition, &cyanPosition, &cyanG);
        //Geistbewegung Geist 4
        ghostMove(&pacPosition, &brownPosition, &cyanG);

        SDL_RenderCopyEx(renderer, pacEntity, NULL, &pacPosition, pac.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, ghostRedTex, NULL, &redPosition, redG.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, ghostPinkTex, NULL, &pinkPosition, pinkG.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, ghostCyanTex, NULL, &cyanPosition, cyanG.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, ghostBrownTex, NULL, &brownPosition, brownG.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        //pac Animation
        switch (pac.rotation)
        {
            case 0:                         //right (5)
                x_pos += (float) pac.speed;
                *was = 3;
                if(canimoveV2(was, pac.speed, pacPosition.x + pacPosition.w, pacPosition.y, pacPosition.x + pacPosition.w, pacPosition.y + pacPosition.h, &munzenzahler, &apfel) && canimove(pacPosition.x+pacPosition.w+BUMPER, pacPosition.y, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 90:                        //down (5)
                y_pos += (float) pac.speed;
                *was = 2;
                if(canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y + pacPosition.h, pacPosition.x + pacPosition.w, pacPosition.y + pacPosition.h, &munzenzahler, &apfel) && canimove(pacPosition.x, pacPosition.y+pacPosition.h+BUMPER,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 180:                       //left (5)
                x_pos -= (float) pac.speed;
                *was = 4;
                if(canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y, pacPosition.x, pacPosition.y + pacPosition.h, &munzenzahler, &apfel) && canimove(pacPosition.x-BUMPER-5, pacPosition.y, pacPosition.x-BUMPER-5, pacPosition.y+pacPosition.h))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 270:                       //up (5)
                y_pos -= (float) pac.speed;
                *was = 1;
                if(canimoveV2(was, pac.speed, pacPosition.x, pacPosition.y, pacPosition.x + pacPosition.w, pacPosition.y, &munzenzahler, &apfel) && canimove(pacPosition.x, pacPosition.y-BUMPER-5, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER-5))
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

        time(&end_t);
        diff_t = difftime(end_t, start_t);
        fpsDiff = 60 - diff_t;
        // printf("%d \n", fpsDiff);

        SDL_Delay(1000/fpsDiff);
    }
    
    free(buffer);
    SDL_FreeSurface(image);
    SDL_FreeSurface(backSurface);
    SDL_FreeSurface(mapElements);
    SDL_FreeSurface(ghostLoder);

    SDL_DestroyTexture(ghostRedTex);
    SDL_DestroyTexture(ghostPinkTex);
    SDL_DestroyTexture(ghostCyanTex);
    SDL_DestroyTexture(ghostBrownTex);

    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(pointTexture);
    SDL_DestroyTexture(pacEntity);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
