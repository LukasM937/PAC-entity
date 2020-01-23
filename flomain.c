#include <SDL.h>
#undef main
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "flomove.h"

#define SHAPE_SIZE 20

extern int background[22][19];

const int SCREEN_WIDTH = 475;
const int SCREEN_HEIGHT = 500;



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
        
        //zählt die münzen hoch
        int munzenzahler=0;

        //schritte die Pacman auf einmal geht
        int speed=4;
        
        //Leben = Äpfel
        int apfel=1;

        bool running = true;
        SDL_Event event;

        //Eventschleife
        while(running) {
            while(SDL_PollEvent(&event)){
                switch(event.type) {
                    case SDL_QUIT: running = false; break;
                    case SDL_KEYDOWN: postionV2(event, &immageposition, speed, &rotation, &munzenzahler, &apfel);
                                    //postion( event, &immageposition, &rotation, &munzenzahler, &apfel);
                                     break;
                }
            } 
            
            if(apfel==0) running=false;

            //erstellt Hintergrund neu
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

        printf("Muenzen: %d", munzenzahler);
        //speicher wieder freigeben und aus sdl rausgehen
        SDL_DestroyTexture(texi);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        }
        return 0;
    }
}