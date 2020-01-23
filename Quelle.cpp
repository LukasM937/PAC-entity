#include <SDL.h>
#undef main
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<SDL_image.h>;
#include "background.h"

#define SHAPE_SIZE 20

const int SCREEN_WIDTH = 475;
const int SCREEN_HEIGHT = 500;


bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1, int back[22][19]) {
    int pufferx = (int)((double)pox / (double)(SCREEN_WIDTH / arx));
    int puffery = (int)((double)poy / (double)(SCREEN_HEIGHT / ary));

    int pufferx1 = (int)((double)pox1 / (double)(SCREEN_WIDTH / arx));
    int puffery1 = (int)((double)poy1 / (double)(SCREEN_HEIGHT / ary));

    if (back[puffery][pufferx] == 0 || back[puffery][pufferx] == 1 && background[puffery1][pufferx1] == 0 || background[puffery1][pufferx1] == 1) {
        return true;
    }
    else return false;
}
int moveghost(int pospacx, int pospacy, int posghox, int posghoy) {
    if (pospacx < posghox) {
        if (posghox > 0 && canimove(19, 22, posghox - 1, posghoy, posghox - 1 + SHAPE_SIZE, posghoy, background) == true) {
            return 0;
        }
        return 1337;
        
    }
    if (pospacx == posghox && pospacy > posghoy) {
        if (posghox > 0 && canimove(19, 22, posghox, posghoy, posghox - 1 + SHAPE_SIZE, posghoy, background) == true) {
            return 0;
        }
    }
}

int main(int argc, char* argv[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    SDL_Texture* texi = NULL;
    SDL_Texture* ghostTexture = NULL;
    SDL_Texture* ghost2Texture = NULL;
    SDL_Texture* ghost3Texture = NULL;
    SDL_Texture* ghost4Texture = NULL;
    

    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Im Arsch: %s \n", SDL_GetError());
    }
    else {
        //Window wird erstellt
        window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        else {

            //Pacman reinladen im moment bmp aber bei Lukas mit SDL_Surface * image = IMG_Load("pac.png");
            SDL_Surface* image = SDL_LoadBMP("pac.bmp");
            
            SDL_Surface* loadedSurface = SDL_LoadBMP("Ghost.bmp");
            SDL_Surface* loadedSurface1 = SDL_LoadBMP("Ghost2.bmp");
            SDL_Surface* loadedSurface2 = SDL_LoadBMP("Ghost3.bmp");
            SDL_Surface* loadedSurface3 = SDL_LoadBMP("Ghost4.bmp");
            
            

            render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            texi = SDL_CreateTextureFromSurface(render, image);
            SDL_FreeSurface(image);
            if (loadedSurface == NULL) {
                printf("Unable to load the image!");

            }
            else
            {
                ghostTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
                if (ghostTexture == NULL) {
                    printf("Unable to create texture from Surface");

                }
                SDL_FreeSurface(loadedSurface);
            }
            if (loadedSurface1 == NULL) {
                printf("Unable to load the image!");

            }
            else
            {
                ghost2Texture = SDL_CreateTextureFromSurface(render, loadedSurface1);
                if (ghost2Texture == NULL) {
                    printf("Unable to create texture from Surface");

                }
                SDL_FreeSurface(loadedSurface1);
            }
            if (loadedSurface2 == NULL) {
                printf("Unable to load the image!");

            }
            else
            {
                ghost3Texture = SDL_CreateTextureFromSurface(render, loadedSurface2);
                if (ghost3Texture == NULL) {
                    printf("Unable to create texture from Surface");

                }
                SDL_FreeSurface(loadedSurface2);
            }
            if (loadedSurface3 == NULL) {
                printf("Unable to load the image!");

            }
            else
            {
                ghost4Texture = SDL_CreateTextureFromSurface(render, loadedSurface3);
                if (ghost4Texture == NULL) {
                    printf("Unable to create texture from Surface");

                }
                SDL_FreeSurface(loadedSurface3);
            }

            //erstellt das viereck in dem pacman dargestellt wird
            SDL_Rect immageposition;
            immageposition.x = 100;
            immageposition.y = 50;
            immageposition.w = SHAPE_SIZE;
            immageposition.h = SHAPE_SIZE;

            SDL_Rect ghostposition;
            ghostposition.x = 225;
            ghostposition.y = 175;
            ghostposition.w = SHAPE_SIZE;
            ghostposition.h = SHAPE_SIZE;

            SDL_Rect ghost2position;
            ghost2position.x = 400;
            ghost2position.y = 300;
            ghost2position.w = SHAPE_SIZE;
            ghost2position.h = SHAPE_SIZE;
            
            SDL_Rect ghost3position;
            ghost3position.x = 10;
            ghost3position.y = 50;
            ghost3position.w = SHAPE_SIZE;
            ghost3position.h = SHAPE_SIZE;

            SDL_Rect ghost4position;
            ghost4position.x = 350;
            ghost4position.y = 200;
            ghost4position.w = SHAPE_SIZE;
            ghost4position.h = SHAPE_SIZE;



            //Hintergrund wird rot -> wege auf denen pacman gehen darf
            SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
            SDL_RenderClear(render);

            //wege auf denen pacman nicht gehen darf werden gr�n -> da wird nachher hintergrund von lukas eingef�gt
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
            for (int i = 0; i < SCREEN_HEIGHT; i++) {
                for (int j = 0; j < SCREEN_WIDTH; j++) {
                    int pufferx = j / (SCREEN_WIDTH / 19);
                    int puffery = i / (SCREEN_HEIGHT / 22);
                    if (background[puffery][pufferx] != 0 && background[puffery][pufferx] != 1) {
                        SDL_RenderDrawPoint(render, j, i);
                    }
                }
            }

            //Presentiere den Hintergrund (Gr�nfl�chen und Wege)
            SDL_RenderPresent(render);

            //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir
            int rotation = 0;

            bool running = true;
            SDL_Event event;

            //Eventschleife
            while (running) {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_QUIT: running = false; break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                        case SDLK_UP: if (immageposition.y > 0 && canimove(19, 22, immageposition.x, immageposition.y - 1, immageposition.x + immageposition.w, immageposition.y - 1, background) == true) {
                            immageposition.y--; rotation = 270;
                            
                          
                        }
                                   
                                    break;

                        case SDLK_DOWN: if (immageposition.y < SCREEN_HEIGHT && canimove(19, 22, immageposition.x, immageposition.y + immageposition.h + 1, immageposition.x + immageposition.w, immageposition.y + immageposition.h + 1, background) == true) {
                            immageposition.y++; rotation = 90;
                            
                        }
                                      break;

                        case SDLK_RIGHT: if (immageposition.x < SCREEN_WIDTH && canimove(19, 22, immageposition.x + immageposition.w + 1, immageposition.y, immageposition.x + immageposition.w + 1, immageposition.y + immageposition.h, background) == true) {
                            immageposition.x++; rotation = 0;
                            
                        }
                                       break;

                        case SDLK_LEFT: if (immageposition.x > 0 && canimove(19, 22, immageposition.x - 1, immageposition.y, immageposition.x - 1, immageposition.y + immageposition.h, background) == true) {
                            immageposition.x--; rotation = 180;
                           
                        }
                                      break;

                        } break;
                    }
                }

                //erstellt hintergrund neu
                SDL_RenderClear(render);
                SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
                SDL_RenderClear(render);
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
                for (int i = 0; i < SCREEN_HEIGHT; i++) {
                    for (int j = 0; j < SCREEN_WIDTH; j++) {
                        int pufferx = j / (SCREEN_WIDTH / 19);
                        int puffery = i / (SCREEN_HEIGHT / 22);
                        if (background[puffery][pufferx] != 0 && background[puffery][pufferx] != 1) {
                            SDL_RenderDrawPoint(render, j, i);
                        }
                    }
                }
                //Geistbewegung Geist 1
                if (immageposition.y < ghostposition.y) {
                    if(canimove(19,22, ghostposition.x, ghostposition.y - 1, ghostposition.x + ghostposition.w, ghostposition.y - 1, background)== true)//moved nach oben
                        ghostposition.y--;
                    else
                    {
                        if (immageposition.x < ghostposition.x) {
                            if (canimove(19, 22, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, background) == true) {//moved nachlinks
                                ghostposition.x--;
                            }

                        }
                        else {
                            if (canimove(19, 22, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h,background) == true) {
                                ghostposition.x++;
                            }
                        }
                            
       
                           
                    }
                }
                if (immageposition.y == ghostposition.y) {
                    if (immageposition.x < ghostposition.x) {
                        if (canimove(19, 22, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, background) == true) {//moved nach links
                            ghostposition.x--;
                        }
                    }
                    else {
                        if (canimove(19, 22, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h, background) == true) {
                            ghostposition.x++;
                        
                        }

                    }
                }
                if (immageposition.y > ghostposition.y) {
                    if (canimove(19, 22, ghostposition.x, ghostposition.y + ghostposition.h + 1, ghostposition.x + ghostposition.w, ghostposition.y + ghostposition.h + 1,background) == true) {// moved nach unten
                        ghostposition.y++;
                    }
                    else {
                        if (immageposition.x < ghostposition.x) {
                            if (canimove(19, 22, ghostposition.x - 1, ghostposition.y, ghostposition.x - 1, ghostposition.y + ghostposition.h, background) == true) {//moved nach links
                                ghostposition.x--;
                            }
                            
                            
                        }
                        else {
                            if (canimove(19, 22, ghostposition.x + ghostposition.w + 1, ghostposition.y, ghostposition.x + ghostposition.w + 1, ghostposition.y + ghostposition.h, background) == true) {
                                ghostposition.x++;
                            }
                        }
                    }
                }
                //Geistbewegung Geist 2
                if (immageposition.y < ghost2position.y) {
                    if (canimove(19, 22, ghost2position.x, ghost2position.y - 1, ghost2position.x + ghost2position.w, ghost2position.y - 1, background) == true)//moved nach oben
                        ghost2position.y--;
                    else
                    {
                        if (immageposition.x < ghost2position.x) {
                            if (canimove(19, 22, ghost2position.x - 1, ghost2position.y, ghost2position.x - 1, ghost2position.y + ghost2position.h, background) == true) {//moved nachlinks
                                ghost2position.x--;
                            }

                        }
                        else {
                            if (canimove(19, 22, ghost2position.x + ghost2position.w + 1, ghost2position.y, ghost2position.x + ghost2position.w + 1, ghost2position.y + ghost2position.h, background) == true) {
                                ghost2position.x++;
                            }
                        }



                    }
                }
                if (immageposition.y == ghost2position.y) {
                    if (immageposition.x < ghost2position.x) {
                        if (canimove(19, 22, ghost2position.x - 1, ghost2position.y, ghost2position.x - 1, ghost2position.y + ghost2position.h, background) == true) {//moved nach links
                            ghost2position.x--;
                        }
                    }
                    else {
                        if (canimove(19, 22, ghost2position.x + ghost2position.w + 1, ghost2position.y, ghost2position.x + ghost2position.w + 1, ghost2position.y + ghost2position.h, background) == true) {
                            ghost2position.x++;

                        }

                    }
                }
                if (immageposition.y > ghost2position.y) {
                    if (canimove(19, 22, ghost2position.x, ghost2position.y + ghost2position.h + 1, ghost2position.x + ghost2position.w, ghost2position.y + ghost2position.h + 1, background) == true) {// moved nach unten
                        ghost2position.y++;
                    }
                    else {
                        if (immageposition.x < ghost2position.x) {
                            if (canimove(19, 22, ghost2position.x - 1, ghost2position.y, ghost2position.x - 1, ghost2position.y + ghost2position.h, background) == true) {//moved nach links
                                ghost2position.x--;
                            }


                        }
                        else {
                            if (canimove(19, 22, ghost2position.x + ghost2position.w + 1, ghost2position.y, ghost2position.x + ghost2position.w + 1, ghost2position.y + ghost2position.h, background) == true) {
                                ghost2position.x++;
                            }
                        }
                    }
                }
                //Geistbewegung Geist 3
                if (immageposition.y < ghost3position.y) {
                    if (canimove(19, 22, ghost3position.x, ghost3position.y - 1, ghost3position.x + ghost3position.w, ghost3position.y - 1, background) == true)//moved nach oben
                        ghost3position.y--;
                    else
                    {
                        if (immageposition.x < ghost3position.x) {
                            if (canimove(19, 22, ghost3position.x - 1, ghost3position.y, ghost3position.x - 1, ghost3position.y + ghost3position.h, background) == true) {//moved nachlinks
                                ghost3position.x--;
                            }

                        }
                        else {
                            if (canimove(19, 22, ghost3position.x + ghost3position.w + 1, ghost3position.y, ghost3position.x + ghost3position.w + 1, ghost3position.y + ghost3position.h, background) == true) {
                                ghost3position.x++;
                            }
                        }



                    }
                }
                if (immageposition.y == ghost3position.y) {
                    if (immageposition.x < ghost3position.x) {
                        if (canimove(19, 22, ghost3position.x - 1, ghost3position.y, ghost3position.x - 1, ghost3position.y + ghost3position.h, background) == true) {//moved nach links
                            ghost3position.x--;
                        }
                    }
                    else {
                        if (canimove(19, 22, ghost3position.x + ghost3position.w + 1, ghost3position.y, ghost3position.x + ghost3position.w + 1, ghost3position.y + ghost3position.h, background) == true) {
                            ghost3position.x++;

                        }

                    }
                }
                if (immageposition.y > ghost3position.y) {
                    if (canimove(19, 22, ghost3position.x, ghost3position.y + ghost3position.h + 1, ghost3position.x + ghost3position.w, ghost3position.y + ghost3position.h + 1, background) == true) {// moved nach unten
                        ghost3position.y++;
                    }
                    else {
                        if (immageposition.x < ghost3position.x) {
                            if (canimove(19, 22, ghost3position.x - 1, ghost3position.y, ghost3position.x - 1, ghost3position.y + ghost3position.h, background) == true) {//moved nach links
                                ghost3position.x--;
                            }


                        }
                        else {
                            if (canimove(19, 22, ghost3position.x + ghost3position.w + 1, ghost3position.y, ghost3position.x + ghost3position.w + 1, ghost3position.y + ghost3position.h, background) == true) {
                                ghost3position.x++;
                            }
                        }
                    }
                }
                //Geistbewegung Geist 4
                if (immageposition.y < ghost4position.y) {
                    if (canimove(19, 22, ghost4position.x, ghost4position.y - 1, ghost4position.x + ghost4position.w, ghost4position.y - 1, background) == true)//moved nach oben
                        ghost4position.y--;
                    else
                    {
                        if (immageposition.x < ghost4position.x) {
                            if (canimove(19, 22, ghost4position.x - 1, ghost4position.y, ghost4position.x - 1, ghost4position.y + ghost4position.h, background) == true) {//moved nachlinks
                                ghost4position.x--;
                            }

                        }
                        else {
                            if (canimove(19, 22, ghost4position.x + ghost4position.w + 1, ghost4position.y, ghost4position.x + ghost4position.w + 1, ghost4position.y + ghost4position.h, background) == true) {
                                ghost4position.x++;
                            }
                        }



                    }
                }
                if (immageposition.y == ghost4position.y) {
                    if (immageposition.x < ghost4position.x) {
                        if (canimove(19, 22, ghost4position.x - 1, ghost4position.y, ghost4position.x - 1, ghost4position.y + ghost4position.h, background) == true) {//moved nach links
                            ghost4position.x--;
                        }
                    }
                    else {
                        if (canimove(19, 22, ghost4position.x + ghost4position.w + 1, ghost4position.y, ghost4position.x + ghost4position.w + 1, ghost4position.y + ghost4position.h, background) == true) {
                            ghost4position.x++;

                        }

                    }
                }
                if (immageposition.y > ghost4position.y) {
                    if (canimove(19, 22, ghost4position.x, ghost4position.y + ghost4position.h + 1, ghost4position.x + ghost4position.w, ghost4position.y + ghost4position.h + 1, background) == true) {// moved nach unten
                        ghost4position.y++;
                    }
                    else {
                        if (immageposition.x < ghost4position.x) {
                            if (canimove(19, 22, ghost4position.x - 1, ghost4position.y, ghost4position.x - 1, ghost4position.y + ghost4position.h, background) == true) {//moved nach links
                                ghost4position.x--;
                            }


                        }
                        else {
                            if (canimove(19, 22, ghost4position.x + ghost4position.w + 1, ghost4position.y, ghost4position.x + ghost4position.w + 1, ghost4position.y + ghost4position.h, background) == true) {
                                ghost4position.x++;
                            }
                        }
                    }
                }

                //l�d pacman ins fenster und repr�sentiert alles
                SDL_RenderCopyEx(render, texi, NULL, &immageposition, rotation, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(render, ghostTexture, NULL, &ghostposition, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(render, ghost2Texture, NULL, &ghost2position, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(render, ghost3Texture, NULL, &ghost3position, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(render, ghost4Texture, NULL, &ghost4position, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderPresent(render);

            }

            //speicher wieder freigeben und aus sdl rausgehen
            SDL_DestroyTexture(ghostTexture);
            SDL_DestroyTexture(texi);
            SDL_DestroyRenderer(render);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        return 0;
    }
}