//vor eventschleife und while(1)
int apfel=1;

//unter eventschleife aber in while(1)
if((ghostposition.x==immageposition.x && ghostposition.y == immageposition.y)|| (ghostposition.x==immageposition.x+immageposition.w && ghostposition.y == immageposition.y+immageposition.h)){
                apfel--;
            }
if(apfel<=0) running=false;