#include <bits/stdc++.h>
#define F first
#define S second
#define mp make_pair
using namespace std;
typedef unsigned long long int ull;

typedef struct node{
  ull tab;
  int win;
  int tot;
  node *parent;
  node *child[10];
  node(ull t, node *p)
  {
    tab=t;
    win=0;
    tot=0;
    parent=p;
    for(int i=0;i<7;i++)
    child[i]=NULL;
  }
} node;

void clean(node *a,int b)
{
  if(a!=NULL)
  {
    for(int i=0;i<7;i++)
    if(i!=b)
    clean(a->child[i],7);
    delete a;
  }
  return;
}


char p1,p2;
ull tab;
char s[100];
node *T;
const double EXPLOR_PARAM = 1.3;
const bool DEBUG = true;
const int NGAMES = 250000; //aguenta 10M, 1M~40s

int cheat;
pair <int,int> cheats[120] = { mp(1,3), mp(10,3), mp(11,1), mp(12,5), mp(13,3), mp(14,1), mp(15,5), mp(16,3), mp(20,3), mp(21,2), mp(22,3), mp(23,3), mp(24,3), mp(25,4), mp(26,3), mp(100,3), mp(101,3), mp(102,3), mp(103,3), mp(104,3), mp(105,3), mp(106,3), mp(110,1), mp(111,3), mp(112,1), mp(113,3), mp(114,3), mp(115,3), mp(116,3), mp(120,6), mp(121,3), mp(122,6), mp(123,3), mp(124,4), mp(125,6), mp(126,5), mp(130,4), mp(131,3), mp(132,3), mp(133,3), mp(134,3), mp(135,3), mp(136,2), mp(140,1), mp(141,0), mp(142,2), mp(143,3), mp(144,0), mp(145,3), mp(146,0), mp(150,3), mp(151,3), mp(152,3), mp(153,3), mp(154,5), mp(155,3), mp(156,5), mp(160,3), mp(161,3), mp(162,3), mp(163,3), mp(164,3), mp(165,3), mp(166,3), mp(200,3), mp(201,3), mp(202,3), mp(203,3), mp(204,3), mp(205,3), mp(206,4), mp(210,2), mp(211,1), mp(212,2), mp(213,1), mp(214,2), mp(215,2), mp(216,2), mp(220,3), mp(221,3), mp(222,2), mp(223,3), mp(224,3), mp(225,3), mp(226,3), mp(230,3), mp(231,2), mp(232,4), mp(233,3), mp(234,2), mp(235,4), mp(236,3), mp(240,3), mp(241,3), mp(242,3), mp(243,3), mp(244,4), mp(245,3), mp(246,3), mp(250,4), mp(251,4), mp(252,4), mp(253,5), mp(254,4), mp(255,5), mp(256,4), mp(260,2), mp(261,3), mp(262,3), mp(263,3), mp(264,3), mp(265,3), mp(266,3) };

void S(ull tabi)
{
  s[0] = (tabi>>(52))%2 + '0';
  s[1] = ' ';
  s[2] = (tabi>>(51))%2 + '0';
  s[3] = (tabi>>(50))%2 + '0';
  s[4] = (tabi>>(49))%2 + '0';
  int i=5;
  for(int j=0;j<49;j++)
  {
    if(j%7==0)
    s[i++]=' ';
    s[i++] = (tabi>>(48-j))%2 + '0';
  }
  s[i]='\0';
  return;
}

void print_tab() //imprime tabela
{
  ull tabi=tab;
  char tabu[10][10];
  bool in;
  for(int j=0;j<7;j++)
  {
    in=false;
    for(int i=6;i>=0;i--)
    {
      if(in)
      tabu[i][j] = (tabi%2==1)?p1:p2;
      else
      tabu[i][j] = '.';
      if(tabi%2==1)
      in=true;
      tabi = tabi >> 1;
    }
  }
  for(int i=5;i>=0;i--)
  for(int j=0;j<7;j++)
  printf("%c%c",tabu[i][j],(j==6)?'\n':' ');
  printf("-------------\n");
  for(int i=0;i<7;i++)
  printf("%d%c",i,(i==6)?'\n':' ');
}

int term(ull tabi)
{
  if(DEBUG)
  {
    S(tabi);
    printf("term   %s\n",s);
  }
  int tabu[10][10];

  bool in;
  for(int j=0;j<7;j++)
  {
    in=false;
    for(int i=6;i>=0;i--)
    {
      if(in)
      tabu[i][j] = (tabi%2==1)?1:2;
      else
      tabu[i][j] = 0;
      if(tabi%2==1)
      in=true;
      tabi = tabi >> 1;
    }
  }

  int b=tabi%8,a=5;
  while(tabu[a][b]==0)
  a--;
  int c = tabu[a][b];
  if(b==7)
  return 0;

  int H,V,DC,DD;
  H=V=DC=DD=1;

  bool h1,h2,v1,v2,dc1,dc2,dd1,dd2;
  h1=h2=v1=v2=dc1=dc2=dd1=dd2=true;

  for(int i=1;i<4;i++)
  {
    if(!h1 || b+i>=7 || tabu[a][b+i]!=c)
    h1=false;
    else
    H++;
    if(!h2 || b-i<0 || tabu[a][b-i]!=c)
    h2=false;
    else
    H++;

    if(!v1 || a+i>=6 || tabu[a+i][b]!=c)
    v1=false;
    else
    V++;
    if(!v2 || a-i<0 || tabu[a-i][b]!=c)
    v2=false;
    else
    V++;

    if(!dc1 || a+i>=6 || b+i>=7 || tabu[a+i][b+i]!=c)
    dc1=false;
    else
    DC++;
    if(!dc2 || a-i<0 || b-i<0 || tabu[a-i][b-i]!=c)
    dc2=false;
    else
    DC++;

    if(!dd1 || a-i<0 || b+i>=7 || tabu[a-i][b+i]!=c)
    dd1=false;
    else
    DD++;
    if(!dd2 || a+i>=6 || b-i<0 || tabu[a+i][b-i]!=c)
    dd2=false;
    else
    DD++;
  }

  if(c==2)
  c=-1;

  if(H>=4 || V>=4 || DC>=4 || DD>=4)
  return c*512-1;

  for(int i=0;i<7;i++)
  if(tabu[5][i]==0)
  return 0;

  return -1;
}

ull place(ull tabi, ull c)
{
  ull b = ((ull)1)<<52;
  ull peca = (((tabi & b)>>52)+1)%2; //peca para jogar

  if(DEBUG)
  {
    S(tabi);
    printf("place  %s %llu %llu\n",s,c,peca);
  }

  ull col = 127;
  ull col2 = 127;
  for(int i=0;i<(int)c;i++)
  {
    col <<= 7;
    col2 <<= 7;
  }
  col &= tabi;
  tabi &= ~col2;
  int s=0;
  while(col%2==0)
  {
    col>>=1;
    s++;
  }
  col = ((((col>>1)<<1)+peca)<<1)+1;
  while(s>1)
  {
    col<<=1;
    s--;
  }
  tabi |= col;

  ull c2 = 7;
  c <<= 49;
  c2 <<= 49;
  tabi = (tabi & (~c2)) | c;

  tabi = (tabi & ~b)|(peca<<52);

  return tabi;
}

double eval(node *t,int tot)
{
  if(t==NULL)
  return 0.5 + EXPLOR_PARAM*sqrt(log(tot+1));

  double wr = t->win/((double)t->tot+1);
  if(!((t->tab)>>52))
  wr = 1.0 - wr;
  return wr + EXPLOR_PARAM*sqrt(log(tot+1)/((double)t->tot+1));
}

node* select(node *t)
{
  if(term(t->tab))
  return t;
  vector <int> best;
  int score = 0;
  int tryi;
  if(DEBUG)
  {
    printf("tot %d\n",t->tot);
  }
  for(int i=0;i<7;i++)
  {
    if(((t->tab)>>(7*i))%2==1)
    continue;

    tryi = (int)((eval(t->child[i],t->tot))*100000);
    if(DEBUG)
    {
      printf("tryi %d %d ",i,tryi);
      if(t->child[i] != NULL)
      printf("%d %d",t->child[i]->win,t->child[i]->tot);
      printf("\n");
    }
    if(tryi>score)
    {
      best.clear();
      best.push_back(i);
      score = tryi;
    }
    else if(tryi==score)
    best.push_back(i);
  }
  int pick = best[rand()%(int)best.size()];
  if(DEBUG)
  {
    printf("pick %d\n",pick);
  }
  if(t->child[pick]==NULL)
  {
    t->child[pick] = new node(place(t->tab,pick),t);
    return t->child[pick];
  }
  return select(t->child[pick]);
}

int simul(ull tabi)
{
  if(DEBUG)
  {
    S(tabi);
    printf("Simul  %s\n",s);
  }
  int a = term(tabi);
  if(DEBUG)
  {
    printf("simter %d\n",a);
  }
  if(a)
  return a;

  vector <int> poss;
  for(int i=0;i<7;i++)
  {
    if((tabi>>7*i)%2==0)
    poss.push_back(i);
  }
  int pick = poss[rand()%(int)poss.size()];
  return simul(place(tabi,(ull)pick));
}

void update(node *t, int a)
{
  if(t==NULL)
  return;
  if(DEBUG)
  {
    S(t->tab);
    printf("Update %s\n",s);
  }
  (t->win)+=a;
  (t->tot)++;
  return update(t->parent,a);
}

void MC(node *t)
{
  if(DEBUG)
  {
    S(t->tab);
    printf("MC     %s\n",s);
    /*int a;
    scanf("%d",&a);*/
  }
  node *next = select(t);
  if(DEBUG)
  {
    S(next->tab);
    printf("Sel    %s\n",s);
  }
  int res = simul(next->tab);
  if(DEBUG)
  {
    printf("res %d\n",res);
  }
  if(res==511)
  update(next,1);
  if(res==-513)
  update(next,0);
}

int bestChoice(node *t)
{
  int b;
  int score = 0;
  int tryi;
  for(int i=0;i<7;i++)
  {
    if(t->child[i]==NULL)
    continue;
    tryi = t->child[i]->tot;
    if(DEBUG)
    {
      printf("%d %.3lf %.3lf %d\n",i,tryi/(double)t->tot,t->child[i]->win/(double)tryi,tryi);
    }
    if(tryi > score)
    {
      b=i;
      score = tryi;
    }
  }
  return b;
}

void play(int player)
{
  int a = term(tab);

  if(a==511)
  {
    print_tab();
    printf("EhEh, I won!\n");
    return;
  }
  if(a==-513)
  {
    print_tab();
    printf("You were lucky.\n");
    return;
  }
  if(a==-1)
  {
    print_tab();
    printf("Meh, it was ok...\n");
    return;
  }

  if(player == 1)
  {
    int start = clock();
    int jog;
    if(cheat<1000)
    for(int i=0;i<113;i++)
    {
      if(cheats[i].F==cheat)
      jog = cheats[i].S;
    }
    else
    {
      if(T==NULL)
      T = new node(tab,NULL);
      ull nos = 0;
      while(nos<NGAMES)
      {
        MC(T);
        nos++;
      }
      jog = bestChoice(T);
      node *t=T;
      T = T->child[jog];
      T->parent=NULL;
      clean(t,jog);
    }
    tab = place(tab,jog);
    printf("%.3lf ms\n", (clock()-start)/(double)(CLOCKS_PER_SEC)*1000);

    play(2);
  }
  else
  {
    print_tab();
    printf("It's your turn, player\n");

    int jog;
    scanf("%d",&jog);
    while(jog>6 || jog<0 || ((tab>>(7*jog))%2)==1)
    {
      printf("Invalid move, try again\n");
      scanf("%d",&jog);
    }

    tab = place(tab,jog);
    if(T!=NULL)
    {
      node *t=T;
      T = T->child[jog];
      T->parent=NULL;
      clean(t,jog);
    }

    if(cheat<1000)
    cheat = cheat*10+jog;

    play(1);
  }
}


int main()
{
  T=NULL;
  srand(time(NULL));
  printf("Do you want to be x or o ?\n");
  scanf(" %c",&p2);
  p1 = (p2=='x')?'o':'x'; //p1 computador | p2 jogador

  printf("Do you want to go first? (y/n):\n");
  char c;
  scanf(" %c", &c);

  if(c == 'y')
  {
    cheat=2;
    tab = 8727940616429632;
    play(2);
  }
  else
  {
    cheat=1;
    tab = 4224340989059136;
    play(1);
  }

  return 0;
}
