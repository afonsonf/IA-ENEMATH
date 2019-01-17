#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "eval.h"
#include "minimax.h"

#include <time.h>

void play(Board *board, bool player);
void playbots(Board *board, bool player, int dif1, int dif2);

int main()
{
    srand(time(NULL));
    Board *board = new Board();
    Eval::init_eval();

    //board->print_board();

    
    playbots(board, 0, 0, 0);
    //play(board, 0);
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