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
#define BUFFER_LENGTH 10
#define BACKGROUND_H 22
#define BACKGROUND_W 19

typedef struct player
{
    int x;
    int y;
    int rotation;
    int speed;
} player;

int validPathX (int x)
{
    if (x % 50 == 5)
    {
        return 1;
    }
    return 0;
}
int validPathY (int y)
{
    if (y % 50 == 5)
    {
        return 1;
    }
    return 0;
}

bool canimove(int *was, int speed, int pox, int poy, int pox1, int poy1, int *munzenzahler, int *apfel)
{
    int arx = BACKGROUND_W;
    int ary = BACKGROUND_W;
    int buf= *was;
    int pufferx, puffery, pufferx1, puffery1;

    for(int i=1; i<=speed; i++)
    {
        if(buf==1)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
            puffery = (int)((double)(poy-i)/(double)(SCREEN_HEIGHT/ary));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
            puffery1 = (int)((double)(poy1-i)/(double)(SCREEN_HEIGHT/ary));
        }
        else if(buf==2)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
            puffery = (int)((double)(poy+i)/(double)(SCREEN_HEIGHT/ary));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
            puffery1 = (int)((double)(poy1+i)/(double)(SCREEN_HEIGHT/ary));
        }
        else if(buf==3)
        {
            pufferx = (int)((double)(pox+i)/(double)(SCREEN_WIDTH/arx));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

            pufferx1 = (int)((double)(pox1+i)/(double)(SCREEN_WIDTH/arx));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));
        }
        else if(buf==4)
        {
            pufferx = (int)((double)(pox-i)/(double)(SCREEN_WIDTH/arx));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

            pufferx1 = (int)((double)(pox1-i)/(double)(SCREEN_WIDTH/arx));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));
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

void postionV2(SDL_Event event, SDL_Rect* pacPosition, int *speed, int *rotation, int *munzenzahler, int *apfel){
    int *was, o;
    was=&o;
    switch(event.key.keysym.sym)
    {
        case SDLK_UP: 
            *was=1;
            if(pacPosition->y > 0 && canimove(was, *speed, pacPosition->x, pacPosition->y, pacPosition->x+pacPosition->w, pacPosition->y, munzenzahler, apfel)==true)
            {
                pacPosition->y = pacPosition->y- *was; *rotation=270;
                printf("%d \n", *rotation);
            }
            break;
        
        case SDLK_DOWN: 
            *was=2;
            if(pacPosition->y < SCREEN_HEIGHT && canimove(was, *speed, pacPosition->x, pacPosition->y+pacPosition->h,pacPosition->x+pacPosition->w, pacPosition->y+pacPosition->h, munzenzahler, apfel)==true)
            {
                pacPosition->y = pacPosition->y+*was; *rotation=90;
                printf("%d \n", *rotation);
            }
            break;
        
        case SDLK_RIGHT: 
            *was=3;
            if(pacPosition->x < SCREEN_WIDTH && canimove(was, *speed, pacPosition->x+pacPosition->w, pacPosition->y, pacPosition->x+pacPosition->w , pacPosition->y+pacPosition->h, munzenzahler, apfel)==true)
            {
                pacPosition->x = pacPosition->x+ *was; *rotation=0;
                printf("%d \n", *rotation);
            }
            break;
        
        case SDLK_LEFT: 
            *was=4;
            if(pacPosition->x > 0 && canimove(was, *speed, pacPosition->x, pacPosition->y, pacPosition->x, pacPosition->y+pacPosition->h, munzenzahler, apfel)==true)
            {
                pacPosition->x=pacPosition->x-*was; *rotation=180;
                printf("%d \n", *rotation);
            } 
            break;
        default:
            break;
    }
}

int main(void)
{
    time_t start_t, end_t;
    double diff_t;
    int fpsDiff;
    int a;
    int munzenzahler=0;
    int *apfel = NULL;
    int *was, o;
    was = &o;

    SDL_Keycode *buffer;

    buffer = malloc(BUFFER_LENGTH * sizeof(SDL_Keycode));
    for(int k = 0; k < BUFFER_LENGTH; k++)
    {
        buffer[k] = 0;
    }
    
    player pac;
    pac.speed = PAC_SPEED/FPS_Cap;
    pac.rotation = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Im Arsch: %s \n", SDL_GetError());
        return 1;
    }

    //TODO -- make the Window bigger and show a scoreboards.

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

    SDL_Surface * loadedSurface = IMG_Load("/assets/PAC-Ghost_cyan_frameless.png");
    if (!loadedSurface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* ghostTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (ghostTexture == NULL) {
        printf("Unable to create texture from Surface");

    }

    //erstellt das viereck in dem pacman dargestellt wird
    SDL_Rect pacPosition;
    pacPosition.x = PAC_START_X;
    pacPosition.y = PAC_START_Y;
    pacPosition.w = SHAPE_SIZE;
    pacPosition.h = SHAPE_SIZE;

    SDL_Rect ghostposition;
    ghostposition.x = 225;
    ghostposition.y = 175;
    ghostposition.w = SHAPE_SIZE;
    ghostposition.h = SHAPE_SIZE;

    float y_pos = pacPosition.y;
    float x_pos = pacPosition.x;
    
    SDL_RenderCopy(renderer, pacEntity, NULL, &pacPosition);
    SDL_RenderPresent(renderer);

    //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir
    bool running = true;

    SDL_Event event;

    SDL_UpdateWindowSurface(window);

    while (running)
    {
        time(&start_t);
        SDL_RenderClear(renderer);
        for(int i = BUFFER_LENGTH - 1; i >= 0; i--)
        {
            buffer[i+1] = buffer[i];
        }
        buffer[0] = 0;

        while (SDL_PollEvent(&event))
        {
            
            switch(event.type )
            {
                case SDL_QUIT:
                    running = false;
                    break;
                /* Look for a keypress */
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;

                        default:
                            postionV2(event, &pacPosition, &pac.speed, &pac.rotation, &munzenzahler, apfel);
                            break;
                    }

                /* Check the SDLKey values and move change the coords */
                /*
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        *was = 4;
                        if(pacPosition.x > 0 && canimove(was, pac.speed, pacPosition.x-BUMPER, pacPosition.y, pacPosition.x-BUMPER, pacPosition.y+pacPosition.h, &munzenzahler, apfel) == true)
                        {
                            // buffer[0] = SDLK_LEFT;
                            pac.rotation=180;
                            // printf("left\n");
                        }
                        break;
                    case SDLK_RIGHT:
                        *was = 3;
                        if(pacPosition.x < SCREEN_WIDTH && canimove(was, pac.speed, pacPosition.x+pacPosition.w+BUMPER, pacPosition.y, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h,  &munzenzahler, apfel) == true)
                        {
                            // buffer[0] = SDLK_RIGHT;
                            pac.rotation=0;
                            // printf("right\n");
                        }
                        break;
                    case SDLK_UP:
                        *was = 1;
                        if(pacPosition.y > 0 && canimove(was, pac.speed, pacPosition.x, pacPosition.y-BUMPER, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER, &munzenzahler, apfel) == true)
                        {
                            // buffer[0] = SDLK_UP;
                            pac.rotation=270; 
                            // printf("up\n",);
                        }
                        break;
                    case SDLK_DOWN:
                        *was = 2;
                        if(pacPosition.y < SCREEN_HEIGHT && canimove(was, pac.speed, pacPosition.x, pacPosition.y+pacPosition.h+BUMPER,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER, &munzenzahler, apfel) == true)
                        {
                            // buffer[0] = SDLK_DOWN;
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
                */
            }
        }
        // printf("a \n");
        /*
        if((validPathX(pacPosition.x) == 1 && (pac.rotation == 90 || pac.rotation == 270 )) || (validPathY(pacPosition.y) == 1 && (pac.rotation == 0 || pac.rotation == 180 )) || pac.speed == 0)
        {
            // printf("b \n");
            for(int l = 0; l < BUFFER_LENGTH; l++)
            {
                if(buffer[l] != 0)
                {
                    switch (buffer[l])
                    {
                    case SDLK_LEFT:
                        if(pacPosition.x > 0 && canimove(was, pac.speed, pacPosition.x-BUMPER, pacPosition.y, pacPosition.x-BUMPER, pacPosition.y+pacPosition.h, &munzenzahler, apfel) == true)
                        {
                            pac.rotation = 180;
                            for(int k = 0; k < BUFFER_LENGTH; k++)
                            {
                                buffer[k] = 0;
                            }
                        }
                        break;
                    case SDLK_RIGHT:
                        if(pacPosition.x < SCREEN_WIDTH && canimove(was, pac.speed, pacPosition.x+pacPosition.w+BUMPER, pacPosition.y, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h,  &munzenzahler, apfel) == true)
                        {
                            pac.rotation = 0;
                            for(int k = 0; k < BUFFER_LENGTH; k++)
                            {
                                buffer[k] = 0;
                            }
                        }
                        break;
                    case SDLK_UP:
                        if(pacPosition.y > 0 && canimove(was, pac.speed, pacPosition.x, pacPosition.y-BUMPER, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER, &munzenzahler, apfel) == true)
                        {
                            pac.rotation = 270;
                            for(int k = 0; k < BUFFER_LENGTH; k++)
                            {
                                buffer[k] = 0;
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        if(pacPosition.y < SCREEN_HEIGHT && canimove(was, pac.speed, pacPosition.x, pacPosition.y+pacPosition.h+BUMPER,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER, &munzenzahler, apfel) == true)
                        {
                            pac.rotation = 90;
                            for(int k = 0; k < BUFFER_LENGTH; k++)
                            {
                                buffer[k] = 0;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        */

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

        //GeisterBewegung

        if (pacPosition.y < ghostposition.y) 
        {
            if(canimove(was, pac.speed, ghostposition.x, ghostposition.y - 1, ghostposition.x + ghostposition.w, ghostposition.y - 1, &munzenzahler, apfel)== true)//moved nach oben
            {
                ghostposition.y--;
            }
            else
            {
                if (pacPosition.x < ghostposition.x) 
                {
                    if (canimove(was, pac.speed, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true) //moved nachlinks
                    {
                        ghostposition.x--;
                    }

                }
                else 
                {
                    if (canimove(was, pac.speed, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true) 
                    {
                        ghostposition.x++;
                    }
                }        
            }
        }
        if (pacPosition.y == ghostposition.y) 
        {
            if (pacPosition.x < ghostposition.x) 
            {
                if (canimove(was, pac.speed, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true) //moved nach links
                {    
                    ghostposition.x--;
                }
            }
            else 
            {
                if (canimove(was, pac.speed, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true)
                {
                    ghostposition.x++;
                }

            }
        }
        if (pacPosition.y > ghostposition.y) 
        {
            if (canimove(was, pac.speed, ghostposition.x, ghostposition.y + ghostposition.h + 1, ghostposition.x + ghostposition.w, ghostposition.y + ghostposition.h + 1, &munzenzahler, apfel) == true) // moved nach unten
            {    
                ghostposition.y++;
            }
            else 
            {
                if (pacPosition.x < ghostposition.x) 
                {
                    if (canimove(was, pac.speed, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true) //moved nach links
                    {
                        ghostposition.x--;
                    }  
                }
                else 
                {
                    if (canimove(was, pac.speed, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h, &munzenzahler, apfel) == true) 
                    {
                        ghostposition.x++;
                    }
                }
            }
        }

        SDL_RenderCopyEx(renderer, ghostTexture, NULL, &ghostposition, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, pacEntity, NULL, &pacPosition, pac.rotation, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        
        //pac Animation

        //TODO --  enter a comand buffer to change directions in faster game. 
        //     --  Only alow direction change on valid paths (x,y)%50 = (5,5).

        // a = validPathX(pacPosition.x);
        // printf("\r%d, ", a);
        // a = validPathY(pacPosition.y);
        // printf("%d \n\r", a);

        /*
        switch (pac.rotation)
        {
            case 0:                         //right (5)
                x_pos += (float) pac.speed;
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x+pacPosition.w+BUMPER, pacPosition.y, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h, &munzenzahler, apfel) == true)
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
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x, pacPosition.y+pacPosition.h+BUMPER,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER, &munzenzahler, apfel))
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
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x-BUMPER-5, pacPosition.y, pacPosition.x-BUMPER-5, pacPosition.y+pacPosition.h, &munzenzahler, apfel))
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
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x, pacPosition.y-BUMPER-5, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER-5, &munzenzahler, apfel))
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
        */

       switch (pac.rotation)
        {
            case 0:                         //right (3)
                x_pos += (float) pac.speed;
                *was = 3; 
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x+pacPosition.w+BUMPER, pacPosition.y, pacPosition.x +pacPosition.w +BUMPER, pacPosition.y+pacPosition.h, &munzenzahler, apfel) == true)
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 90:                        //down (2)
                y_pos += (float) pac.speed;
                *was = 2;
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x, pacPosition.y+pacPosition.h+BUMPER,pacPosition.x+pacPosition.w, pacPosition.y+pacPosition.h+BUMPER, &munzenzahler, apfel))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 180:                       //left (4)
                x_pos -= (float) pac.speed;
                *was = 4;
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x-BUMPER-5, pacPosition.y, pacPosition.x-BUMPER-5, pacPosition.y+pacPosition.h, &munzenzahler, apfel))
                {
                    pac.speed = PAC_SPEED/FPS_Cap;
                }
                else
                {
                    pac.speed = 0;
                }
                break;
            case 270:                       //up (1)
                y_pos -= (float) pac.speed;
                *was = 1;
                if(canimove(was, PAC_SPEED/FPS_Cap, pacPosition.x, pacPosition.y-BUMPER-5, pacPosition.x+pacPosition.w, pacPosition.y-BUMPER-5, &munzenzahler, apfel))
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
    SDL_FreeSurface(loadedSurface);

    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(pointTexture);
    SDL_DestroyTexture(pacEntity);
    SDL_DestroyTexture(ghostTexture);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
