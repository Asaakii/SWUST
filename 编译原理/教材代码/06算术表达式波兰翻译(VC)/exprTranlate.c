//本程序将简单中缀算术表达式翻译成波兰后缀表达式，表达式中只有+和*运算符
//文法为E->E+T@+，E->T，T->T*F@*，T->F，F->(E)，F->i@i
//其中i可为任意字母
//去掉左递归，修改后文法为：E->T{+T@+},T->F{*F@*},F->(E)|i@i
#include "stdio.h"
#include "ctype.h"
char ch;
int T();
int F();
int E()   //分析E子程序 E->T{+T@+}
{  int es=0;
   es=T();//调分析T子程序
   while (ch=='+')
   {  ch=getchar();
      es=T();//调分析T子程序
      printf("+");
      
   }
    return(es);
}
int T()    //调分析T子程序T->F{*F@*}
{  int es=0;
   es=F();//调分析F子程序
   while (ch=='*')
   {  ch=getchar();
      es=F();//调分析F子程序
      printf("*");
     
   }
    return(es);
}
int F()//分析F子程序
{  int es=0;
   if (ch=='(')
   {
      ch=getchar();
      es=E();//调分析E子程序
      if (ch!=')') return(3);
      else {ch=getchar();return(es);}
   } else
   {
	if (isalpha(ch)) //判断是否为字母
	{   printf("%C",ch);
		ch=getchar();
		return(es);
	} else return(4);
   }
}
main()
{
	int es=0;
    printf("请输入算术表达式（操作数只能是字母）：");
	ch=getchar();
	printf("波兰算术表达式：");
	es=E();//调分析表达式E的翻译程序
	if (es==0) printf("\n翻译成功!\n");
	else printf("\n表达式有语法错误!\n");
}
