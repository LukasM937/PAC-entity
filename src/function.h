
typedef struct player
{
    int x;
    int y;
    int rotation;
    int speed;
    int targetX;
    int targetY;
    int ghostType;
    int collision;
} player;

bool canimoveV2(int *was, int speed, int pox, int poy, int pox1, int poy1, int *munzenzahler, int *apfel)
{
    int buf = *was;
    int pufferx, puffery, pufferx1, puffery1;
    for(int i = 1; i <= speed; i++)
    {
        if(buf == 1)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)(poy-i)/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)(poy1-i)/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf == 2)
        {
            pufferx = (int)((double)pox/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)(poy+i)/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)pox1/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)(poy1+i)/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf == 3)
        {
            pufferx = (int)((double)(pox+i)/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)(pox1+i)/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ARY));
        }
        else if(buf == 4)
        {
            pufferx = (int)((double)(pox-i)/(double)(SCREEN_WIDTH/ARX));
            puffery = (int)((double)poy/(double)(SCREEN_HEIGHT/ARY));

            pufferx1 = (int)((double)(pox1-i)/(double)(SCREEN_WIDTH/ARX));
            puffery1 = (int)((double)poy1/(double)(SCREEN_HEIGHT/ARY));
        }

        if((background[puffery][pufferx] == 0 || background[puffery][pufferx] == 1 || background[puffery][pufferx] == 22) && (background[puffery1] [pufferx1] == 0 || background[puffery1] [pufferx1] == 1 || background[puffery1][pufferx1] == 22))
        {
            *was = i;

            if(background[puffery][pufferx] == 22)
            {
                *apfel=*apfel+1;
                background[puffery][pufferx] = 0;
            }
            else if(background[puffery1][pufferx1] == 22)
            {
                *apfel=*apfel+1;
                background[puffery][pufferx] = 0;
            }
            if(background[puffery][pufferx] == 1)
            {
                *munzenzahler=*munzenzahler + 1;
                background[puffery][pufferx] = 0;
                backgroundCheck[puffery][pufferx] = 0;
            }
            else if(background[puffery1][pufferx1] == 1)
            {
                *munzenzahler =*munzenzahler + 1;
                background[puffery1][pufferx1] = 0;
                backgroundCheck[puffery][pufferx] = 0;
            }
        }
        else if (i == 1)
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

    if((background[puffery][pufferx] == 0 || background[puffery][pufferx] == 1 || background[puffery][pufferx] == 22) && (background[puffery1][pufferx1] == 0 || background[puffery1][pufferx1] == 1|| background[puffery][pufferx] == 22))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void setTarget(player *ghostStuff, player *pacStuff)
{
    switch (ghostStuff->ghostType)
    {
    case 1:
        ghostStuff->targetX = pacStuff->x;
        ghostStuff->targetY = pacStuff->y;
        break;
    case 2:
        switch (pacStuff->rotation)
        {
        case 0: //right
            ghostStuff->targetX = pacStuff->x + 100;
            ghostStuff->targetY = pacStuff->y;
            break;
        case 90: //down
            ghostStuff->targetX = pacStuff->x;
            ghostStuff->targetY = pacStuff->y + 100;
            break;
        case 180: //left
            ghostStuff->targetX = pacStuff->x - 100;
            ghostStuff->targetY = pacStuff->y;
            break;
        case 270: //up
            ghostStuff->targetX = pacStuff->x;
            ghostStuff->targetY = pacStuff->y - 100;
            break;
        
        default:
            break;
        }
        break;
    case 3:
        ghostStuff->targetX = abs(pacStuff->x - ghostStuff->targetX) + pacStuff->x; //gS->tx = red X , gS->x = cyan x
        ghostStuff->targetY = abs(pacStuff->y - ghostStuff->targetY) + pacStuff->y;
        break;
    case 4:
        ghostStuff->targetX = pacStuff->x;
        ghostStuff->targetY = pacStuff->y;
        break;
    
    default:
        break;
    }
}

void ghostMove (SDL_Rect *pac, SDL_Rect *ghost, player *ghostStuff, player *pacStuff)
{
    pacStuff->x = pac->x;
    pacStuff->y = pac->y;

    setTarget(ghostStuff, pacStuff);

    /*if (ghostStuff->collision > 0)
    {
        switch (ghostStuff->collision)
        {
        case 1:
            if (canimove(ghost->x, ghost->y - BUMPER, ghost->x + ghost->w, ghost->y - BUMPER) == false)
            {
                ghost->x += ghostStuff->speed;
            }
            else
            {
                ghost->y -= ghostStuff->speed;
                ghostStuff->collision = 0;
            }
            break;
        case 2:
            if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == false)
            {
                ghost->y += ghostStuff->speed;
            }
            else
            {
                ghost->x += ghostStuff->speed;
                ghostStuff->collision = 0;
            }
            break;
        case 3:
            if (canimove(ghost->x, ghost->y + ghost->h + BUMPER, ghost->x + ghost->w, ghost->y + ghost->h + BUMPER) == false)
            {

                ghost->x += ghostStuff->speed;
            }
            else
            {
                ghost->y += ghostStuff->speed;
                ghostStuff->collision = 0;
            }
            break;
        case 4:
            if (canimove(ghost->x, ghost->y + ghost->h + BUMPER, ghost->x + ghost->w, ghost->y + ghost->h + BUMPER) == false)
            {
                ghost->x -= ghostStuff->speed;
            }
            else
            {
                ghost->y += ghostStuff->speed;
                ghostStuff->collision = 0;
            }
            break;
        }

    }*/

    if (ghostStuff->targetY < ghost->y) 
    {
        if(canimove(ghost->x, ghost->y - BUMPER, ghost->x + ghost->w, ghost->y - BUMPER) == true)//moved nach oben
            {
                ghost->y -= ghostStuff->speed;
            }
        else
        {
            if (ghostStuff->targetX < ghost->x) 
            {
                if (canimove(ghost->x - BUMPER, ghost->y, ghost->x - BUMPER, ghost->y + ghost->h) == true) //moved nachlinks
                {
                    ghost->x -= ghostStuff->speed;
                }
                // else
                // {
                //     ghostStuff->collision = 1;
                // }
            }
            else 
            {
                if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true)
                {
                    ghost->x += ghostStuff->speed;
                }
                // else
                // {
                //     ghostStuff->collision = 2;
                // }
            }   
        }
    }
    if (ghostStuff->targetY == ghost->y) 
    {
        if (ghostStuff->targetX < ghost->x) 
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
    if (ghostStuff->targetY > ghost->y) 
    {
        if (canimove(ghost->x, ghost->y + ghost->h + BUMPER, ghost->x + ghost->w, ghost->y + ghost->h + BUMPER) == true) // moved nach unten
        {
            ghost->y += ghostStuff->speed;
        }
        else 
        {
            if (ghostStuff->targetX < ghost->x) 
            {
                if (canimove(ghost->x - BUMPER, ghost->y, ghost->x - BUMPER, ghost->y + ghost->h) == true) //moved nach links
                {
                    ghost->x -= ghostStuff->speed;
                }
                // else
                // {
                //     ghostStuff->collision = 3;
                // }
            }
            else 
            {
                if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true) 
                {
                    ghost->x += ghostStuff->speed;
                }
                // else
                // {
                //     ghostStuff->collision = 4;
                // }
            }
        }
    }
}

void randApple(int frame, int *ranX, int *ranY)
{
    srand(time(NULL));
    int X = rand() % 19;
    int Y = rand() % 22;

    if(frame % 1000 == 0)
    {
        
        for(int i = 0; i <= 1;)
        {
            // printf("%d, %d\n", X, Y);
            if(backgroundCheck[Y][X] == 1)
            {
                background[*ranY][*ranX] = 1;
                background[Y][X] = 22;
                *ranX = X;
                *ranY = Y;
                i++;
            }
            else if(backgroundCheck[Y][X] == 0)
            {
                background[*ranY][*ranX] = 0;
                background[Y][X] = 22;
                *ranX = X;
                *ranY = Y;
                i++;
            }
            else
            {
                X = rand() % 19;
                Y = rand() % 22;
            }
        }
    }
}

int collisions(SDL_Rect *pac, SDL_Rect *red, SDL_Rect *pink, SDL_Rect *cyan, SDL_Rect *brown, int *apfel)
{
    if(abs(pac->x - red->x) <= BUMPER)
    {
        if(abs(pac->y - red->y) <= BUMPER)
        {
            return 0;
        }
    }
    if(abs(pac->x - pink->x) <= BUMPER)
    {
        if(abs(pac->y - pink->y) <= BUMPER)
        {
            return 0;
        }
    }
    if(abs(pac->x - cyan->x) <= BUMPER)
    {
        if(abs(pac->y - cyan->y) <= BUMPER)
        {
            return 0;
        }
    }
    if(abs(pac->x - brown->x) <= BUMPER)
    {
        if(abs(pac->y - brown->y) <= BUMPER)
        {
            return 0;
        }
    }
    return 1;
}

int checkForZeros()
{
    int counter = 0;
    for(int i = 0; i < ARX; i++)
    {
        for(int j = 0; j < ARY; j++)
        {
            if(background[j][i] == 1)
            {
                counter++; 
            }
        }
    }
    if(counter == 0) return 0;
    else return 1;
}