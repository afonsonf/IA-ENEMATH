#include "minimax.h"

long long expandidos2; //number of nodes expanded
long long int podas;//number of prunes

Pos Minimax::minimax(Board *a, int depthx, bool player)
{

    //Check if there is a winning play
    Pos lp = a->last_play;
    Pos px;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            px.i = i, px.j = j;
            int erro_play = a->play(px);
            if (!erro_play)
            {
                int win = a->final_board();
                a->rmplay(lp);
                if (win)
                    return px;
            }
           
        }
    }
    

    expandidos2 = 0;
    podas = 0;
    int alfa = INT_MIN;
	int beta = INT_MAX;
    
    min_value(a,alfa,beta,depthx);

    printf("Numero de podas: %lld\n",podas);
    printf("Nos expandidos: %lld\n", expandidos2);
    return a->best_play;
}

int Minimax::max_value(Board *a, int alfa, int beta, int depth_max)
{
    int opt = 0;
    if (a->depth == 0)
        opt = 1;
    if (a->depth == 1)
        opt = 2;
    opt = 0;
    bool k = a->final_board();
    if (k || a->depth >= depth_max)
    {
        if(k) return -3000;
        else  return -a->eval_board();
        
    }
    int val = INT_MIN, x, kk;
    int podar = 0;
    Pos lp = a->last_play, px;

    for (int i = 0; i < 3 && !podar; i++)
    {
        for (int j = 0; j < 4 && !podar; j++)
        {
            px.i = i, px.j = j;
            kk = a->play(px);

            if (!kk)
            {
                expandidos2++;
                a->depth++;
                x = min_value(a,alfa, beta,depth_max);

                
                //for printing value of childs of first 2 levels
                if (opt == 1)
                {
                    printf("\t(%d,%d) = %d (0)\n", a->last_play.i, a->last_play.j, x);
                }
                if (opt == 2)
                {
                    printf("\t\t(%d,%d) = %d (1)\n", a->last_play.i, a->last_play.j, x);
                }
                
               
                if (val < x)
                {
                    if (a->depth == 1)
                        a->best_play = a->last_play;
                    val = x;
                }
                if (val>=beta){
                    podas++;
                    podar=1;
                }
                alfa = std::max (alfa,val);
                a->depth--;
                a->rmplay(lp);
            }
        }
    }
    return val;
}

int Minimax::min_value(Board *a, int alfa, int beta, int depth_max)
{    
    int opt = 0;
    if (a->depth == 0)
        opt = 1;
    if (a->depth == 1)
        opt = 2;
    opt = 0;
    bool k = a->final_board();
    if (k || a->depth >= depth_max)
    {
        if(k) return 3000;
        else  return a->eval_board();
        
    }
    int val = INT_MAX, x, kk;
    int podar = 0;

    Pos lp = a->last_play, px;
    for (int i = 0; i < 3 && !podar; i++)
    {
        for (int j = 0; j < 4 && !podar; j++)
        {
            px.i = i, px.j = j;
            kk = a->play(px);

            if (!kk)
            {
                expandidos2++;
                a->depth++;
                x = max_value(a, alfa, beta, depth_max);

                
                //for printing value of childs of first 2 levels
                if (opt == 1)
                {
                    printf("\t(%d,%d) = %d (0)\n", a->last_play.i, a->last_play.j, x);
                }
                if (opt == 2)
                {
                    printf("\t\t(%d,%d) = %d (1)\n", a->last_play.i, a->last_play.j, x);
                }
                

                if (val > x)
                {
                    if (a->depth == 1)
                        a->best_play = a->last_play;
                    val = x;
                }
                if (val<=alfa){
                    podas++;
                    podar=1;
                }
                beta = std::min (beta,val);
                a->depth--;
                a->rmplay(lp);
            }
        }
    }
    return val;
}