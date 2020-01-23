#ifndef _flomove_h_
#define _flomove_h_

#include <SDL.h>

bool canimove(int arx, int ary, int pox, int poy, int pox1, int poy1, int* munzenzahler, int *apfel);
void postion(SDL_Event event, SDL_Rect *immagepostion, int *rotation, int *munzenzahler, int *apfel);
bool canimoveV2(int *was, int speed, int arx, int ary, int pox, int poy, int pox1, int poy1, int *munzenzahler, int *apfel);
void postionV2(SDL_Event event, SDL_Rect* immageposition, int speed, int *rotation, int *munzenzahler, int *apfel);

#endif