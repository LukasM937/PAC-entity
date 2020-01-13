char [19][22] Z{{Q,Z,Z,Z,Z,Z,Z,Z,Z,W,Z,Z,Z,Z,Z,Z,Z,Z,E},
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
};


void toTextureDestination (char input, int *outX, int *outY)
{
    switch(intput)
    {
        case Q:             //Upper left Corner
            outX = 0;
            outY = 0;
            break;
        case E:             //Upper right Corner
            outX = 50;
            outY = 0;
            break;
        case C:             //Lower left Corner
            outX = 0;
            outY = 50;
            break;
        case Y:             //Lower right Corner
            outX = 50;
            outY = 50;
            break;

        case W:             // T down
            outX = 150;
            outY = 50;
            break;
        case D:             // T left
            outX = 150;
            outY = 150;
            break;
        case X:             // T up
            outX = 100;
            outY = 200;
            break;
        case A:             // T right
            outX = 0;
            outY = 150;
            break;
        
        case H:             // upper End
            outX = 100;
            outY = 50;
            break;
        case J:             // right End
            outX = 50;
            outY = 100;
            break;
        case K:             // lower End
            outX = 150;
            outY = 100;
            break;
        case L:             // left End
            outX = 0;
            outY = 100;
            break;
        
        case I:             // standig Wall
            outX = 100;
            outY = 100;
            break;
        case Z:             // laying Wall
            outX = 50;
            outY = 150;
            break;
        case S:             // Cross
            outX = 100;
            outY = 150;
            break;
        
        case 1:             // Point
            outX = 0;
            outY = 200;
            break;
        case 0:             // Empty
            outX = 50;
            outY = 200;
            break;
    }

}
