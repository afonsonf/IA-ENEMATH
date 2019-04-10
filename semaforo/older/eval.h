#ifndef Eval_H
#define Eval_H

#include "common.h" 

class Eval{
public:
    static int eval4[4][4][4][4];
    static int eval3[4][4][4];

	static void init_eval();
	static int eval_aux(int x1, int x2, int x3);
};

#endif // Eval_H