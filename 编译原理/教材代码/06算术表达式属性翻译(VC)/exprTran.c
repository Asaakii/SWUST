//本程序将简单中缀算术表达式翻译成四元式，表达式中只有+和*运算符
#include "stdio.h"
#include "ctype.h"
char ch;
int T(int *p);
int F(int *p);
int E1(int p,int *t);
int T1(int p,int *t);
int NEWT()//返回一个临时变量，顺序产生A、B、...、Z，最多产生26个临时变量
{ static int i=64;//设置i为静态变量，确保下次调用时i为上次调用的结果
  i=i+1;
  return(i);
}
//产生式E↑t→T↑pE'↓p的翻译子程序，t为综合属性,形参用指针变量
int E(int *t)   
{  int es=0;
   int p;
   es=T(&p);//调分析T子程序
   es=E1(p,t);//调分析E1子程序  
   return(es);
}
//产生式E'↓p↑t→+T↑r @ADD↓p,r,t E'↓p↑t 和E'↓p↑t→ε翻译子程序
//p为继承属性,形参用整型变量,t为综合属性,形参用指针变量
int E1(int p,int *t)  
{	int r,es,t0;
	if (ch=='+')
	{  ch=getchar();
       es=T(&r);
       t0=NEWT();//产生一个临时变量
	   printf("      ADD %c,%c,%c\n",p,r,t0);
	   es=E1(t0,t);
	   return(es);
    }  else 
	{	*t=p;
		return(0);
	}
}
//产生式T↑p→F↑pT'↓p的翻译子程序，t为综合属性,形参用指针变量
int T(int *t)   
{  int es=0,p;
   es=F(&p);//调分析F子程序
   es=T1(p,t);//调分析T1子程序
   return(es);
}
//产生式T'↓p↑t→*F↑r @MULT↓p,r,t T' 和T'↓p↑t→ε翻译子程序
//p为继承属性,形参用整型变量,t为综合属性,形参用指针变量
int T1(int p,int *t)   
{
	int r,es,t0;
	if (ch=='*')
	{  ch=getchar();
       es=F(&r);
	   t0=NEWT();//产生一个临时变量
       printf("      MULT %c,%c,%c\n",p,r,t0);
	   es=T1(t0,t);
	   return(es);
    }  else 
	{	*t=p;
		return(0);
	}
}
//产生式F↑p ->(E↑p) |ID↑p的翻译子程序，p为综合属性,形参用指针变量
int F(int *p)//分析F子程序
{  int es=0;
   if (ch=='(')
   {
      ch=getchar();
      es=E(p);//调分析E子程序
      if (ch!=')') return(3);
      else {ch=getchar();return(es);}
   } else
   {
	if (isalpha(ch)) //判断是否为字母
	{   *p=ch;
	    ch=getchar();
		return(es);
	} else return(4);
   }
}
//主程序
main()
{
	int es=0,t;
    printf("请输入算术表达式(操作数只能是单个字母)：");
	ch=getchar();
	printf("输出四元式为：\n");
	es=E(&t);//调分析表达式E的翻译程序
	if (es==0) printf("\n翻译成功!\n");
	else printf("\n表达式有语法错误!\n");
}


