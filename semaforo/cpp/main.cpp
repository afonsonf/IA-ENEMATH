#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "eval.h"
#include "minimax.h"

#include <time.h>

void play(Board *board, bool player);
void playbots(Board *board, bool player, int dif1, int dif2);
bool playbotM(Board *board, bool player, int dif1, int dif2);

int main()
{
    srand(time(NULL));
    Board *board = new Board();
    Eval::init_eval();

    //board->print_board();

    
    //playbots(board, 0, 3, 6);
    //play(board, 0);

    //return 0;

    int s=0, x;
    int dif1 =0;
    int dif2 =1;
    int n = 10000;
    int first = 1;
    for(int i=0;i<n;i++){
        board = new Board();
        if(playbotM(board, first, dif1, dif2)) s++;
        printf("%d %d\n",s,i-s);
    }

    printf("number of games: %d\n",n);
    if(first) printf("(1st, %d) %.2lf %d\n(2nd, %d) %.2lf %d\n",dif1,s*1.0/n,s,dif2,(n-s)*1.0/n,(n-s));
    else printf("(1st, %d) %.2lf %d\n(2nd, %d) %.2lf %d\n",dif2,(n-s)*1.0/n,(n-s),dif1,s*1.0/n,s);

    return 0;
}

void play(Board *board, bool player)
{
    if (board->final_board())
    {
        printf("%d %d\n", board->last_play.i, board->last_play.j);
        board->print_board();
        return;
    }

    if (player)
    {
        board->print_board();
        Pos p;

        printf("play:\n");
        scanf("%d %d", &p.i, &p.j);

        while (board->play(p))
        {
            printf("invalid move!\n");
            printf("play:\n");
            scanf("%d %d", &p.i, &p.j);
        }
        play(board, !player);
        return;
    }

    Pos p = Minimax::minimax(board, 2, player);
    board->play(p);
    printf("Bot played %d %d\n", p.i, p.j);
    printf("\n");
    play(board, !player);
    return;
}

void playbots(Board *board, bool player, int dif1, int dif2)
{
    if (board->final_board())
    {
        printf("%d %d\n", board->last_play.i, board->last_play.j);
        board->print_board();

        if (!player)
            printf("(true) bot with %d wins\n", dif1);
        else
            printf("(false) bot with %d wins\n", dif2);

        return;
    }

    if (player)
    {
        Pos p = Minimax::minimax(board, dif1, player);
        board->play(p);
        printf("Bot with dif: %d played %d %d\n", dif1, p.i, p.j);
        board->print_board();
        printf("\n");
        playbots(board, !player, dif1, dif2);
        return;
    }

    Pos p = Minimax::minimax(board, dif2, player);
    board->play(p);
    printf("Bot with dif: %d played %d %d\n", dif2, p.i, p.j);
    board->print_board();
    printf("\n");
    playbots(board, !player, dif1, dif2);
    return;
}

bool playbotM(Board *board, bool player, int dif1, int dif2)
{
    if (board->final_board())
        return !player;

    if (player)
    {
        Pos p = Minimax::minimax(board, dif1, player);
        board->play(p);
        //printf("Bot with dif: %d played %d %d\n", dif1, p.i, p.j);
        //board->print_board();
        //printf("\n");
        return playbotM(board, !player, dif1, dif2);
    }

    Pos p = Minimax::minimax(board, dif2, player);
    board->play(p);
    //printf("Bot with dif: %d played %d %d\n", dif1, p.i, p.j);
    //board->print_board();
    //printf("\n");
    return playbotM(board, !player, dif1, dif2);
}