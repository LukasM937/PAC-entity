/*hier sind die Funktionen damit sich Pacman in dem Screen bewegen kann. Die eine Funktion ist der Standtart (postion()), 
bei der anderen kann man die Geschwindigkeit von Pacman einstellen (postionV2()).

Zu beachten:
    +)Die weite und höhe des Bildes müssen in der Main den selben Namen haben (SCREEN_WIDTH und SCREEN_HEIGHT)
    +)Das Array muss aus einer mitkompilierten .c Datei stammen. Das kann die Main sein beim mir liegt es in global.c
    +)In der Main müssen die übergabe Parameter: int speed=beliebig (wieviele Schritte pro Tastendruck), int munzenzahler=0 (zählt die Münzen), 
    apfel=1 (gibt einem Leben->noch nicht in Array inkludiert, bei apfel=0 -> Spielende), int rotation=0 und natürlich SDL_Rect & SDL_Event, definiert sein 

*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int background[22][19];


bool canimoveV2(int *was, int speed, int arx, int ary, int pox, int poy, int pox1, int poy1, int *munzenzahler, int *apfel){
        int buf= *was;
        int pufferx, puffery, pufferx1, puffery1;

        for(int i=1; i<=speed; i++){
            if(buf==1){
                pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
                puffery = (int)((double)(poy-i)/(double)(SCREEN_HEIGHT/ary));

                pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
                puffery1 = (int)((double)(poy1-i)/(double)(SCREEN_HEIGHT/ary));
            }
            else if(buf==2){
                pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
                puffery = (int)((double)(poy+i)/(double)(SCREEN_HEIGHT/ary));

                pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
                puffery1 = (int)((double)(poy1+i)/(double)(SCREEN_HEIGHT/ary));
            }
            else if(buf==3){
                pufferx = (int)((double)(pox+i)/(double)(SCREEN_WIDTH/arx));
                puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

                pufferx1 = (int)((double)(pox1+i)/(double)(SCREEN_WIDTH/arx));
                puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));
            }
            else if(buf==4){
                pufferx = (int)((double)(pox-i)/(double)(SCREEN_WIDTH/arx));
                puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

                pufferx1 = (int)((double)(pox1-i)/(double)(SCREEN_WIDTH/arx));
                puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));
            }

            if((background[puffery][pufferx]==0 || background[puffery][pufferx]==1 || background[puffery][pufferx]==22) && (background[puffery1] [pufferx1] == 0 || background[puffery1] [pufferx1] == 1 || background[puffery1][pufferx1]==22)){
                *was=i;

            if(background[puffery][pufferx]==22){
                *apfel=*apfel+1;
                background[puffery][pufferx]==0;
            }
            else if(background[puffery1][pufferx1]==22){
                *apfel=*apfel+1;
                background[puffery][pufferx]==0;
            }
            if(background[puffery][pufferx]==1){
                *munzenzahler=*munzenzahler+1;
                background[puffery][pufferx]=0;
            }
            else if(background[puffery1][pufferx1]==1){
                *munzenzahler=*munzenzahler+1;
                background[puffery1][pufferx1]=0;
            }
            }
            else if (i==1){
                return false;
            }
            else return true;
        }
    return true;

}

void postionV2(SDL_Event event, SDL_Rect* immageposition, int speed, int *rotation, int *munzenzahler, int *apfel){
int *was, o;
was=&o;
switch(event.key.keysym.sym){
                            case SDLK_UP: 
                                *was=1;
                                if(immageposition->y > 0 && canimoveV2(was, speed, 19, 22, immageposition->x, immageposition->y, immageposition->x+immageposition->w, immageposition->y, munzenzahler, apfel)==true) {
                                    immageposition->y = immageposition->y- *was; *rotation=270; }
                                break;
                            
                            case SDLK_DOWN: 
                                *was=2;
                                if(immageposition->y < SCREEN_HEIGHT && canimoveV2(was, speed, 19, 22, immageposition->x, immageposition->y+immageposition->h,immageposition->x+immageposition->w, immageposition->y+immageposition->h, munzenzahler, apfel)==true){
                                immageposition->y = immageposition->y+*was; *rotation=90;}
                                break;
                            
                            case SDLK_RIGHT: 
                                *was=3;
                                if(immageposition->x < SCREEN_WIDTH && canimoveV2(was, speed, 19, 22, immageposition->x+immageposition->w, immageposition->y, immageposition->x+immageposition->w , immageposition->y+immageposition->h, munzenzahler, apfel)==true){
                                immageposition->x = immageposition->x+ *was; *rotation=0;}
                                break;
                            
                            case SDLK_LEFT: 
                                *was=4;
                                if(immageposition->x > 0 && canimoveV2(was, speed, 19, 22, immageposition->x, immageposition->y, immageposition->x, immageposition->y+immageposition->h, munzenzahler, apfel)==true){
                                immageposition->x=immageposition->x-*was; *rotation=180;} 
                                break;  
                        }
}


bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1, int* munzenzahler, int *apfel){

        int pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/arx));
        int puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ary));

        int pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/arx));
        int puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ary));


        if((background[puffery][pufferx]==0 || background[puffery][pufferx]==1 || background[puffery][pufferx]==22) && (background[puffery1][pufferx1] == 0 || background[puffery1][pufferx1] == 1 || background[puffery1][pufferx1]==22)){
            if(background[puffery][pufferx]==22){
                *apfel=*apfel+1;
                background[puffery][pufferx]==0;
            }
            else if(background[puffery1][pufferx1]==22){
                *apfel=*apfel+1;
                background[puffery][pufferx]==0;
            }
            if(background[puffery][pufferx]==1){
                *munzenzahler=*munzenzahler+1;
                background[puffery][pufferx]=0;
            }
            else if(background[puffery1][pufferx1]==1){
                *munzenzahler=*munzenzahler+1;
                background[puffery1][pufferx1]=0;
            }
            return true;
        }
        else return false;
}

void postion(SDL_Event event, SDL_Rect* immageposition, int *rotation, int *munzenzahler, int *apfel){
    switch(event.key.keysym.sym){
                            case SDLK_UP: if(immageposition->y > 0 && canimove(19, 22, immageposition->x, immageposition->y-1, immageposition->x+immageposition->w, immageposition->y-1, munzenzahler, apfel)==true) {
                                immageposition->y --; *rotation=270; }  
                                //printf("%d", immageposition->x+immageposition->w);
                                //printf("%d")	
                                break;
                            
                            case SDLK_DOWN: if(immageposition->y < SCREEN_HEIGHT && canimove(19, 22, immageposition->x, immageposition->y+immageposition->h+1,immageposition->x+immageposition->w, immageposition->y+immageposition->h+1, munzenzahler, apfel)==true){
                                immageposition->y ++; *rotation=90;}
                                break;
                            
                            case SDLK_RIGHT: if(immageposition->x < SCREEN_WIDTH && canimove(19, 22,immageposition->x+immageposition->w+1, immageposition->y, immageposition->x +immageposition->w+1, immageposition->y+immageposition->h, munzenzahler, apfel)==true){
                                immageposition->x ++; *rotation=0;}
                                break;
                            
                            case SDLK_LEFT: if(immageposition->x > 0 && canimove(19, 22, immageposition->x-1, immageposition->y, immageposition->x-1, immageposition->y+immageposition->h, munzenzahler, apfel)==true){
                                immageposition->x --; *rotation=180;} 
                                break;
                            
                        }
}

