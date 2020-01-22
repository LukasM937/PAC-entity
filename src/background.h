#define blockSize 50

/*char background[22][19]= {{Q,Z,Z,Z,Z,Z,Z,Z,Z,W,Z,Z,Z,Z,Z,Z,Z,Z,E},
                {I,1,1,1,1,1,1,1,1,I,1,1,1,1,1,1,1,1,I},
                {I,1,Q,E,1,Q,W,E,1,I,1,Q,W,E,1,Q,E,1,I},
                {I,1,Y,C,1,Y,W,C,1,K,1,Y,W,C,1,Y,C,1,I},
                {I,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,I},
                {I,1,L,J,1,H,1,L,Z,W,Z,J,1,H,1,L,J,1,I},
                {I,1,1,1,1,I,1,1,1,I,1,1,1,I,1,1,1,1,I},
                {Y,Z,Z,E,1,A,Z,J,1,K,1,L,Z,D,1,Q,Z,Z,C},
                {0,0,0,I,1,I,1,1,1,1,1,1,1,I,1,I,0,0,0},
                {Z,Z,Z,C,1,K,1,Q,G,G,G,E,1,K,1,Y,Z,Z,Z},
                {1,1,1,1,1,1,1,I,0,0,0,I,1,1,1,1,1,1,1},
                {Z,Z,Z,E,1,H,1,Y,Z,Z,Z,C,1,H,1,Q,Z,Z,Z},
                {0,0,0,I,1,I,1,1,1,1,1,1,1,I,1,I,0,0,0},
                {Q,Z,Z,C,1,K,1,L,Z,W,Z,J,1,K,1,Y,Z,Z,Z},
                {I,1,1,1,1,1,1,1,1,I,1,1,1,1,1,1,1,1,I},
                {I,1,L,E,1,L,Z,J,1,K,1,L,Z,J,1,Q,J,1,I},
                {I,1,1,I,1,1,1,1,1,1,1,1,1,1,1,I,1,1,I},
                {A,J,1,K,1,H,1,L,Z,W,Z,J,1,H,1,K,1,L,D},
                {I,1,1,1,1,I,1,1,1,I,1,1,1,I,1,1,1,1,I},
                {I,1,L,Z,Z,X,Z,J,1,K,1,L,Z,X,Z,Z,J,1,I},
                {I,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,I},
                {Y,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,I}
};*/

int background[22][19]= {{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                {2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2},
                {2,1,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,1,2},
                {2,1,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,1,2},
                {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                {2,1,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,1,2},
                {2,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,2},
                {2,2,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,2,2},
                {0,0,0,2,1,2,1,1,1,1,1,1,1,2,1,2,0,0,0},
                {2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2},
                {1,1,1,1,1,1,1,2,0,0,0,2,1,1,1,1,1,1,1},
                {2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2},
                {0,0,0,2,1,2,1,1,1,1,1,1,1,2,1,2,0,0,0},
                {2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2},
                {2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2},
                {2,1,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,1,2},
                {2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2},
                {2,2,1,2,1,2,1,2,2,2,2,2,1,2,1,2,1,2,2},
                {2,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,2},
                {2,1,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,1,2},
                {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

void toTextureDestination(int input, int *outX, int *outY)
{
    switch(input)
    {
        printf(" ");
        // case 2:             //Upper left Corner 2/q
        //     *outX = 0;
        //     *outY = 0;
        //     break;
        // case 3:             //Upper right Corner 3/e
        //     *outX = 50;
        //     *outY = 0;
        //     break;
        // case 4:             //Lower left Corner 4/c
        //     *outX = 50;
        //     *outY = 50;
        //     break;
        // case 5:             //Lower right Corner 5/y
        //     *outX = 0;
        //     *outY = 50;
        //     break;

        // case 6:             // T down 6/w
        //     *outX = 150;
        //     *outY = 50;
        //     break;
        // case 7:             // T left 7/d
        //     *outX = 150;
        //     *outY = 150;
        //     break;
        // case 8:             // T up 8/x
        //     *outX = 100;
        //     *outY = 200;
        //     break;
        // case 9:             // T right 9/a
        //     *outX = 0;
        //     *outY = 150;
        //     break;
        
        // case 10:             // upper End 10/h
        //     *outX = 100;
        //     *outY = 50;
        //     break;
        // case 11:             // right End 11/j
        //     *outX = 50;
        //     *outY = 100;
        //     break;
        // case 12:             // lower End 12/k
        //     *outX = 150;
        //     *outY = 100;
        //     break;
        // case 13:             // left End 13/l
        //     *outX = 0;
        //     *outY = 100;
        //     break;
        
        // case 14:             // standig Wall 14/i
        //     *outX = 100;
        //     *outY = 100;
        //     break;
        // case 15:             // laying Wall 15/z
        //     *outX = 50;
        //     *outY = 150;
        //     break;
        // case 16:             // Cross 16/s
        //     *outX = 100;
        //     *outY = 150;
        //     break;
        
        case 1:             // Point
            *outX = 0;
            *outY = 200;
            break;
        case 0:             // Empty
            *outX = 50;
            *outY = 200;
            break;
        default:        // Gates 17,18,19 (L, M, R)
            *outX = 50;
            *outY = 200;
            break;
    }
}

void texture(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* tex)
{
    SDL_Texture* mapTiles;
    SDL_Texture* mapTarget;
    mapTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, 950, 1100);
    SDL_SetRenderTarget(renderer, mapTarget);

    // Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    SDL_Surface* surface = IMG_Load("/assset/Map_elements.png");
    mapTiles = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect targetRect;
    SDL_Rect sourceRect;

    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 19; j++)
        {
            //SDL_RenderClear(renderer);
            targetRect.x = 100;
            targetRect.y = 100;
            targetRect.w = blockSize;
            targetRect.h = blockSize;

            sourceRect.w = blockSize;
            sourceRect.h = blockSize;

            toTextureDestination(background[i][j], &sourceRect.x, &sourceRect.y);
            /*
            switch(background[i][j])
            {
                printf(" ");
                case 2:             //Upper left Corner 2/q
                    sourceRect.x = 0;
                    sourceRect.y = 0;
                    break;
                case 3:             //Upper right Corner 3/e
                    sourceRect.x = 50;
                    sourceRect.y = 0;
                    break;
                case 4:             //Lower left Corner 4/c
                    sourceRect.x = 50;
                    sourceRect.y = 50;
                    break;
                case 5:             //Lower right Corner 5/y
                    sourceRect.x = 0;
                    sourceRect.y = 50;
                    break;

                case 6:             // T down 6/w
                    sourceRect.x = 150;
                    sourceRect.y = 50;
                    break;
                case 7:             // T left 7/d
                    sourceRect.x = 150;
                    sourceRect.y = 150;
                    break;
                case 8:             // T up 8/x
                    sourceRect.x = 100;
                    sourceRect.y = 200;
                    break;
                case 9:             // T right 9/a
                    sourceRect.x = 0;
                    sourceRect.y = 150;
                    break;
                
                case 10:             // upper End 10/h
                    sourceRect.x = 100;
                    sourceRect.y = 50;
                    break;
                case 11:             // right End 11/j
                    sourceRect.x = 50;
                    sourceRect.y = 100;
                    break;
                case 12:             // lower End 12/k
                    sourceRect.x = 150;
                    sourceRect.y = 100;
                    break;
                case 13:             // left End 13/l
                    sourceRect.x = 0;
                    sourceRect.y = 100;
                    break;
                
                case 14:             // standig Wall 14/i
                    sourceRect.x = 100;
                    sourceRect.y = 100;
                    break;
                case 15:             // laying Wall 15/z
                    sourceRect.x = 50;
                    sourceRect.y = 150;
                    break;
                case 16:             // Cross 16/s
                    sourceRect.x = 100;
                    sourceRect.y = 150;
                    break;
                
                case 1:             // Point
                    sourceRect.x = 0;
                    sourceRect.y = 200;
                    break;
                case 0:             // Empty
                    sourceRect.x = 50;
                    sourceRect.y = 200;
                    break;
                default:        // Gates 17,18,19 (L, M, R)
                    sourceRect.x = 0;
                    sourceRect.y = 200;
                    break;
            }
            */

            SDL_RenderCopy(renderer, tex, NULL, NULL);
            SDL_RenderCopy(renderer, mapTiles, &sourceRect, &targetRect);
            SDL_SetRenderTarget(renderer, NULL);
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mapTarget, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(mapTiles);
    SDL_DestroyRenderer(renderer);
}
