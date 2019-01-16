#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "eval.h"
#include "minimax.h"

void play(Board *board, bool player);

int main(){
    Board *board = new Board();
    Eval::init_eval();
    
    //board->print_board();
    
    play(board, 1);
    return 0;
}

void play(Board *board, bool player){
    if(board->final_board()){
        printf("%d %d\n",board->last_play.i,board->last_play.j);
        board->print_board(); return;
    }

    if(player){
        board->print_board();
        Pos p;

        printf("play:\n");
        scanf("%d %d",&p.i, &p.j);

        while(board->play(p)){
            printf("invalid move!\n");
            printf("play:\n");
            scanf("%d %d",&p.i, &p.j);
        }
        play(board,!player);
        return;
    }

    Pos p = Minimax::minimax(board, 3);
    board->play(p);
    printf("Bot played %d %d\n",p.i, p.j);
    printf("\n");
    play(board, !player);
    return;
}