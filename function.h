#pragma once
typedef struct player
{
    int x;
    int y;
    int rotation;
    int speed;
} player;

int validPathX(int x)
{
    int a;
    a = x % 50;

    return a;
}
int validPathY(int y)
{
    int a;
    a = y % 50;

    return a;
}

bool canimoveV2(int* was, int speed, int pox, int poy, int pox1, int poy1, int* munzenzahler, int* apfel)
{
    int buf = *was;
    int pufferx, puffery, pufferx1, puffery1;
    for (int i = 1; i <= speed; i++)
    {
        if (buf == 0)
        {
            return false;
        }
        if (buf == 1)
        {
            pufferx = (int)((double)pox / (double)(SCREEN_WIDTH / ARX));
            puffery = (int)((double)(poy - i) / (double)(SCREEN_HEIGHT / ARY));

            pufferx1 = (int)((double)pox1 / (double)(SCREEN_WIDTH / ARX));
            puffery1 = (int)((double)(poy1 - i) / (double)(SCREEN_HEIGHT / ARY));
        }
        else if (buf == 2)
        {
            pufferx = (int)((double)pox / (double)(SCREEN_WIDTH / ARX));
            puffery = (int)((double)(poy + i) / (double)(SCREEN_HEIGHT / ARY));

            pufferx1 = (int)((double)pox1 / (double)(SCREEN_WIDTH / ARX));
            puffery1 = (int)((double)(poy1 + i) / (double)(SCREEN_HEIGHT / ARY));
        }
        else if (buf == 3)
        {
            pufferx = (int)((double)(pox + i) / (double)(SCREEN_WIDTH / ARX));
            puffery = (int)((double)poy / (double)(SCREEN_HEIGHT / ARY));

            pufferx1 = (int)((double)(pox1 + i) / (double)(SCREEN_WIDTH / ARX));
            puffery1 = (int)((double)poy1 / (double)(SCREEN_HEIGHT / ARY));
        }
        else if (buf == 4)
        {
            pufferx = (int)((double)(pox - i) / (double)(SCREEN_WIDTH / ARX));
            puffery = (int)((double)poy / (double)(SCREEN_HEIGHT / ARY));

            pufferx1 = (int)((double)(pox1 - i) / (double)(SCREEN_WIDTH / ARX));
            puffery1 = (int)((double)poy1 / (double)(SCREEN_HEIGHT / ARY));
        }

        if ((background[puffery][pufferx] == 0 || background[puffery][pufferx] == 1 || background[puffery][pufferx] == 22) && (background[puffery1][pufferx1] == 0 || background[puffery1][pufferx1] == 1 || background[puffery1][pufferx1] == 22))
        {
            *was = i;

            if (background[puffery][pufferx] == 22)
            {
                *apfel = *apfel + 1;
                background[puffery][pufferx] = 0;
            }
            else if (background[puffery1][pufferx1] == 22)
            {
                *apfel = *apfel + 1;
                background[puffery][pufferx] = 0;
            }
            if (background[puffery][pufferx] == 1)
            {
                *munzenzahler = *munzenzahler + 1;
                background[puffery][pufferx] = 0;
            }
            else if (background[puffery1][pufferx1] == 1)
            {
                *munzenzahler = *munzenzahler + 1;
                background[puffery1][pufferx1] = 0;
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

bool canimove(int pox, int poy, int pox1, int poy1)
{
    int pufferx = (int)((double)pox / (double)(SCREEN_WIDTH / ARX));
    int puffery = (int)((double)poy / (double)(SCREEN_HEIGHT / ARY));

    int pufferx1 = (int)((double)pox1 / (double)(SCREEN_WIDTH / ARX));
    int puffery1 = (int)((double)poy1 / (double)(SCREEN_HEIGHT / ARY));

    if ((background[puffery][pufferx] == 0 || background[puffery][pufferx] == 1 || background[puffery][pufferx] == 22) && (background[puffery1][pufferx1] == 0 || background[puffery1][pufferx1] == 1 || background[puffery][pufferx] == 22))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ghostMove(SDL_Rect* pac, SDL_Rect* ghost, player* ghostStuff)

{
    int collision = 0;
    if (collision > 0)
    {
        switch (collision)
        {
        case 1:
            if (canimove(, ghost->.x, ghost->y - BUMPER, ghost->x + ghost->w, ghost->y - BUMPER, background) == false)
            {
                ghost->x += ghostStuff->speed;
            }
            else
            {
                ghost->y -= ghostStuff->speed;
                collision = 0;
            }
            break;
        case 2:
            if (canimove(, ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h, background) == false)
            {
                ghost->y += ghostStuff->speed;
            }
            else
            {

                ghost->x += ghostStuff->speed;
                collision = 0;
            }
            break;
        case 3:
            if (canimove(, ghost->x, ghost->y + ghost->h + BUMPER, ghost->x + ghost->w, ghost->y + ghost->h + BUMPER, background) == false)
            {

                ghost->x += ghostStuff->speed;
            }
            else
            {
                ghost->y += ghostStuff->speed;
                collision = 0;

            }
            break;
        case 4:
            if (canimove(, ghost->x, ghost->y + ghost->.h + BUMPER, ghost->.x + ghost->.w, ghost->.y + ghost->.h + BUMPER, background) == false)
            {
                ghost->x -= ghostStuff->speed;
            }
            else
            {
                ghost->y += ghostStuff->speed;
                collision = 0;

            }
            break;
        }

    }
    else
    {
        if (pac->y < ghost->y)
        {
            if (canimove(ghost->x, ghost->y - BUMPER, ghost->x + ghost->w, ghost->y - BUMPER) == true)//moved nach oben
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
                    else
                    {
                        collision = 1;
                    }

                }
                else
                {
                    if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true)
                    {
                        ghost->x += ghostStuff->speed;
                    }
                    else
                    {
                        collision = 2,
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
                    else
                    {
                        collision = 3;
                    }


                }
                else
                {
                    if (canimove(ghost->x + ghost->w + BUMPER, ghost->y, ghost->x + ghost->w + BUMPER, ghost->y + ghost->h) == true)
                    {
                        ghost->x += ghostStuff->speed;
                    }
                    else
                    {
                        collision = 4;
                    }
                }
            }
        }
    }
}