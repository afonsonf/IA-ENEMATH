#include "eval.h"
#include <math.h>

int Eval::eval4[4][4][4][4];
int Eval::eval3[4][4][4];

void Eval::init_eval(){
    for(int k1=0;k1<4;k1++){
        for(int k2=0;k2<4;k2++){
            for(int k3=0;k3<4;k3++){
                for(int k4=0;k4<4;k4++){
                    eval4[k1][k2][k3][k4] = eval_aux(k1,k2,k3) + eval_aux(k2,k3,k4);
                }
                eval3[k1][k2][k3] = eval_aux(k1,k2,k3);
            }
        }
    }
}

int Eval::eval_aux(int x1, int x2, int x3){
    if(x1 == x2 && x2==x3 && x1 == 0) return 0;
    if(x1 == x2 && x2==x3) return 1000000;
    //return 0;
    int k = x1;
    if(k<x2) k = x2; if(k<x3) k = x3;
    int s = 0;
    s = k-x1 + k-x2 + k-x3;

    if(s%2) return pow(30 - 5*s,2);
    return -pow(30 - 5*s,2);
    //if(s%2) return -300 + 50*s;
    //return 300 - 50*s;
}
