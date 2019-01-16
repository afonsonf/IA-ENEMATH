#include "minimax.h"

long long expandidos2; //number of nodes expanded

Pos Minimax::minimax(Board *a, int depthx)
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

    min_value(a, depthx);

    printf("Nos expandidos: %lld\n", expandidos2);
    return a->best_play;
}

int Minimax::max_value(Board *a, int depth_max)
{
    int opt = 0;
    if (a->depth == 0)
        opt = 1;
    if (a->depth == 1)
        opt = 2;
    bool k = a->final_board();
    if (k || a->depth >= depth_max)
    {
        if(k) return 3000;
        else  return a->eval_board();
        
    }
    int val = INT_MIN, x, kk;
    Pos lp = a->last_play, px;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            px.i = i, px.j = j;
            kk = a->play(px);

            if (!kk)
            {
                expandidos2++;
                a->depth++;
                x = min_value(a, depth_max);

                /*
                //for printing value of childs of first 2 levels
                if (opt == 1)
                {
                    printf("\t(%d,%d) = %d (0)\n", a->last_play.i, a->last_play.j, x);
                }
                if (opt == 2)
                {
                    printf("\t\t(%d,%d) = %d (1)\n", a->last_play.i, a->last_play.j, x);
                }
                */
               
                if (val < x)
                {
                    if (a->depth == 1)
                        a->best_play = a->last_play;
                    val = x;
                }
                a->depth--;
                a->rmplay(lp);
            }
        }
    }
    return val;
}

int Minimax::min_value(Board *a, int depth_max)
{    
    int opt = 0;
    if (a->depth == 0)
        opt = 1;
    if (a->depth == 1)
        opt = 2;
    bool k = a->final_board();
    if (k || a->depth >= depth_max)
    {
        if(k) return 3000;
        else  return a->eval_board();
        
    }
    int val = INT_MAX, x, kk;
    Pos lp = a->last_play, px;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            px.i = i, px.j = j;
            kk = a->play(px);

            if (!kk)
            {
                expandidos2++;
                a->depth++;
                x = max_value(a, depth_max);

                /*
                //for printing value of childs of first 2 levels
                if (opt == 1)
                {
                    printf("\t(%d,%d) = %d (0)\n", a->last_play.i, a->last_play.j, x);
                }
                if (opt == 2)
                {
                    printf("\t\t(%d,%d) = %d (1)\n", a->last_play.i, a->last_play.j, x);
                }
                */

                if (val > x)
                {
                    if (a->depth == 1)
                        a->best_play = a->last_play;
                    val = x;
                }
                a->depth--;
                a->rmplay(lp);
            }
        }
    }
    return val;
}