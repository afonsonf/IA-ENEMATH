#include "myboost.h"

std::unordered_map<int,int> Global::m4;//combinations o length 4
std::unordered_map<int,int> Global::m5;//combinations o length 5
std::unordered_map<int,int> Global::m6;//combinations o length 6
std::unordered_map<int,int> Global::m7;//combinations o length 7
std::unordered_map<int,int> Global::m6c;//combinations o length 6 for column

bool MyBoost::loaded = false;
//vectors for eficiency of generation
std::vector<int> p4;
std::vector<int> p5;
std::vector<int> p6;

void MyBoost::load_boost(){
	if(loaded) return;
	loaded = true;
	std::list<int> temp;

	temp.push_back(0);
	int x;
	//diagonal size 4
	while(temp.size()>0){
		x = temp.front();
		temp.pop_front();
		if(x<100){
			temp.push_back(x*10+1);
			temp.push_back(x*10+2);
			temp.push_back(x*10+3);
		}
		else{
			p4.push_back(x*10+1);
			p4.push_back(x*10+2);
			p4.push_back(x*10+3);
		}
	}
	//diagonal size 5
	for(int i=0;i<(int)p4.size();i++){
		p5.push_back(p4[i]*10+1);
		p5.push_back(p4[i]*10+2);
		p5.push_back(p4[i]*10+3);
		Global::m4.insert(std::make_pair(p4[i],eval(p4[i])));
	}
	//diagonal size 5
	for(int i=0;i<(int)p5.size();i++){
		p6.push_back(p5[i]*10+1);
		p6.push_back(p5[i]*10+2);
		p6.push_back(p5[i]*10+3);

		Global::m5.insert(std::make_pair(p5[i],eval(p5[i])));
	}
	//line
	for(int i=0;i<(int)p6.size();i++){
		Global::m6.insert(std::make_pair(p6[i],eval(p6[i])));

		Global::m7.insert(std::make_pair(p6[i]*10+1,eval(p6[i]*10+1)));
		Global::m7.insert(std::make_pair(p6[i]*10+2,eval(p6[i]*10+2)));
		Global::m7.insert(std::make_pair(p6[i]*10+3,eval(p6[i]*10+3)));
	}

	//column
	temp.push_back(0);
	int k;
	while(temp.size()>0){
		x = temp.front();
		temp.pop_front();

		k=x*10+1;
		while(k<100000)k=k*10+3;
		Global::m6c.insert(std::make_pair(k,eval(k)));

		k=x*10+2;
		while(k<100000)k=k*10+3;
		Global::m6c.insert(std::make_pair(k,eval(k)));

		if(x<10000){
			temp.push_back(x*10+1);
			temp.push_back(x*10+2);
		}
	}

}

//evaluate segmente of n pieces
int MyBoost::eval(int x){
	int n[4],val;
	n[0]=x%10;x/=10;
	n[1]=x%10;x/=10;
	n[2]=x%10;x/=10;
	n[3]=x%10;x/=10;
	val = eval_aux(n);
	while(x>0){
		n[0]=n[1];
		n[1]=n[2];
		n[2]=n[3];
		n[3]=x%10;x/=10;
		val += eval_aux(n);
	}
	return val;
}

//evaluate 4 pieces
int MyBoost::eval_aux(int n[]){
	int s=0,x=-1,i;
	for(i=0;i<4;i++){
		if(x==-1 && n[i]!=3){
			x = n[i];
			s++;
		}
		else if(n[i] == x && n[i]!=3){
			s++;
		}
		else if(n[i] != x && n[i]!=3){
			break;
		}
	}
	int sign;
	if(i==4 && x!=-1){
		if(x==1)sign=-1;//sign
		else sign=1;

		switch(s){
			case 1: return sign*1;
			case 2: return sign*10;
			case 3: return sign*50;
			case 4: return sign*512;
		}
	}
	return 0;
}
