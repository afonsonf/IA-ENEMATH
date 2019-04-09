#ifndef MYBOOST_H
#define MYBOOST_H

#include <list>
#include <vector>

#include "common.h"

class MyBoost{
public:
	static bool loaded;
	
	static void load_boost();
	static int  eval(int x);
	static int  eval_aux(int n[]);
};

#endif // MYBOOST_H
