//Da ist jetzt noch alles drinnen ich teile das später in 2 Dateien 
//Das mit dem Münzenzählen mache ich heute abend mal 

#include <SDL.h>
#undef main
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lukas.h"

#define SHAPE_SIZE 20

const int SCREEN_WIDTH = 475;
const int SCREEN_HEIGHT = 500;


bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1, int back[][ary]){
        int pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
        int puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

        int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
        int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));

        if(back[puffery][pufferx]==0 || back[puffery][pufferx]==1 && background [puffery1] [pufferx1] == 0 || background [puffery1] [pufferx1] == 1){
            return true;
        }
        else return false;
}

int main(int argc, char* argv[]) {
    
    SDL_Window* window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture *texi = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);

    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        printf("Im Arsch: %s \n", SDL_GetError());
    }
    else{
        //Window wird erstellt
        window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if( window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
        
    else{ 

        //Pacman reinladen im moment bmp aber bei Lukas mit SDL_Surface * image = IMG_Load("pac.png");
        SDL_Surface * image = SDL_LoadBMP("pac.bmp");
        render=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
        texi= SDL_CreateTextureFromSurface(render, image);
        SDL_FreeSurface(image);

        //erstellt das viereck in dem pacman dargestellt wird
        SDL_Rect immageposition;
        immageposition.x=100;
        immageposition.y=50;
        immageposition.w=SHAPE_SIZE;
        immageposition.h=SHAPE_SIZE;

        
        
        //Hintergrund wird rot -> wege auf denen pacman gehen darf
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
        SDL_RenderClear(render);

        //wege auf denen pacman nicht gehen darf werden grün -> da wird nachher hintergrund von lukas eingefügt
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        for(int i=0; i<SCREEN_HEIGHT; i++){
           for(int j=0; j<SCREEN_WIDTH; j++){
               int pufferx = j/(SCREEN_WIDTH/19);
                int puffery = i/(SCREEN_HEIGHT/22);
    	        if(background[puffery][pufferx]!=0 && background[puffery][pufferx]!=1){
                SDL_RenderDrawPoint(render, j, i);
                }
            }
        }

        //Presentiere den Hintergrund (Grünflächen und Wege)
        SDL_RenderPresent(render);

        //Pacman dreht seine Ausrichtung wenn er in eine andere richtung bewegt wir
        int rotation;
        
        bool running = true;
        SDL_Event event;

        //Eventschleife
        while(running) {
            while(SDL_PollEvent(&event)){
                switch(event.type) {
                    case SDL_QUIT: running = false; break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_UP: if(immageposition.y > 0 && canimove(19, 22, immageposition.x, immageposition.y-1, immageposition.x+immageposition.w, immageposition.y-1, background)==true) {
                                immageposition.y --; rotation=270; }
                                break;
                            
                            case SDLK_DOWN: if(immageposition.y < SCREEN_HEIGHT && canimove(19, 22, immageposition.x, immageposition.y+immageposition.h+1,immageposition.x+immageposition.w, immageposition.y+immageposition.h+1, background)==true){
                                immageposition.y ++; rotation=90;}
                                break;
                            
                            case SDLK_RIGHT: if(immageposition.x < SCREEN_WIDTH && canimove(19, 22,immageposition.x+immageposition.w+1, immageposition.y, immageposition.x +immageposition.w +1, immageposition.y+immageposition.h, background)==true){
                                immageposition.x ++; rotation=0;}
                                break;
                            
                            case SDLK_LEFT: if(immageposition.x > 0 && canimove(19, 22, immageposition.x-1, immageposition.y, immageposition.x-1, immageposition.y+immageposition.h, background)==true){
                                immageposition.x --; rotation=180;} 
                                break;
                            
                        } break;
                }
            } 
            
            //erstellt hintergrund neu
            SDL_RenderClear(render);
            SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
            SDL_RenderClear(render);
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
            for(int i=0; i<SCREEN_HEIGHT; i++){
                for(int j=0; j<SCREEN_WIDTH; j++){
                    int pufferx = j/(SCREEN_WIDTH/19);
                    int puffery = i/(SCREEN_HEIGHT/22);
    	            if(background[puffery][pufferx]!=0 && background[puffery][pufferx]!=1){
                        SDL_RenderDrawPoint(render, j, i);
                    }
                }
            }

            //läd pacman ins fenster und repräsentiert alles
            SDL_RenderCopyEx(render, texi, NULL, &immageposition, rotation, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(render);
        }

        //speicher wieder freigeben und aus sdl rausgehen
        SDL_DestroyTexture(texi);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        }
        return 0;
    }
}