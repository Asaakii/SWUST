#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#include<string.h>

int TESTparse();
int program();
int compound_stat();
int statement();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
char token[20],token1[40];//token保存单词符号，token1保存单词值
extern char Scanout[300]; //保存词法分析输出文件名
FILE *fp; //用于指向输入输出文件的指针
//语法分析程序
int TESTparse()
{
	int es=0;
	if((fp=fopen(Scanout,"r"))==NULL)
	{  
      printf("\n打开%s错误!\n",Scanout);
	  es=10;
	}
	
	if (es==0) es=program();
	printf("=====语法分析结果!======\n");
	switch(es)
	{
		case 0: printf("语法分析成功!\n");break;	
		case 10: printf("打开文件 %s失败!\n",Scanout);break;
		case 1: printf("缺少{!\n");break;
		case 2: printf("缺少}!\n");break;
		case 3: printf("缺少标识符!\n");break;
		case 4: printf("少分号!\n");break;
		case 5: printf("缺少(!\n");break;
		case 6: printf("缺少)!\n");break;
		case 7: printf("缺少操作数!\n");break;
		
	}
	fclose(fp);
	return(es);
}
//<程序>::={<声明序列><语句序列>}
//program::={<declaration_list><statement_list>}
int program()
{ 
   int es=0;
   fscanf(fp,"%s %s\n",token,token1);
   printf("%s %s\n",token,token1);
   if(strcmp(token,"{"))//判断是否'{'
   {
	   es=1;
	   return(es);
   }
   fscanf(fp,"%s %s\n",&token,&token1);
   printf("%s %s\n",token,token1);
   es=declaration_list();
   if (es>0) return(es);
   es=statement_list();
   if (es>0) return(es);
   if(strcmp(token,"}"))//判断是否'}'
   {
	   es=2;
	   return(es);
   }
   return(es);
}
//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//该成<declaration_list>::={<declaration_stat>}
int declaration_list()
{
	int es=0;
	while (strcmp(token,"int")==0)
	{
		es=declaration_stat();
		if (es>0) return(es);
	}
	return(es);
}
//<声明语句> ::=int <变量>；
//<declaration_stat>::=int ID;
int declaration_stat()
{
	int es=0;      
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"ID"))	return(es=3);  //不是标识符
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,";") )	return(es=4);		
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	return(es);
}
//<语句序列>::=<语句序列><语句>|<语句>
//<statement_list>::=<statement_list><statement>|<statement>
//改成<statement_list>::={<statement>}
int statement_list()
{
	int es=0;
	while (strcmp(token,"}"))
	{
		es=statement();
		if (es>0) return(es);
	}
	return(es);
}
//<语句>::=<if语句>|<while语句>|<for语句>|<read语句>
//         |<write语句>|<复合语句>|<表达式语句>
//<statement>::= <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>

int statement()
{
	int es=0;
	if (es==0 && strcmp(token,"if")==0) es=if_stat();//<IF语句>
	if (es==0 && strcmp(token,"while")==0) es=while_stat();//<while语句>
	if (es==0 && strcmp(token,"for")==0) es=for_stat();//<for语句>
	//可在此处添加do语句调用
	if (es==0 && strcmp(token,"read")==0) es=read_stat();//<read语句>
	if (es==0 && strcmp(token,"write")==0) es=write_stat();//<write语句>
	if (es==0 && strcmp(token,"{")==0) es=compound_stat();//<复合语句>
	if (es==0 && (strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0)) es=expression_stat();//<表达式语句>
	return(es);
}
//<IF 语句>::= if (<表达式>) <语句 > [else <语句 >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]

int if_stat(){
	int es=0;  //if
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"(")) 	return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //少右括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement(); 
	if (es>0) return(es);
	if (strcmp(token,"else")==0)//else部分处理
	{  
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=statement(); 
	    if (es>0) return(es);
	}
	return(es);
}
//<while语句>::=while(<表达式>) <语句>
//<while_stat>::= while (<expr >) < statement >
int while_stat()
{
	int es=0;  
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"("))  return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //少右括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	return(es);
}

//<for语句>::=for(<表达式>;<表达式>;<表达式>) <语句 >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
int for_stat()
{
	int es=0;  
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"("))  return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,";")) 	return(es=4);  //少分号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,";"))  return(es=4);  //少分号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //少右括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	return(es);
	
}
//<write_语句>::=write <表达式>;
//<write_stat>::=write <expression>;
int write_stat()
{
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,";"))  return(es=4);  //少分号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	return(es);
}
//<read_语句>::=read <变量>;
//<read_stat>::=read ID;
int read_stat()
{
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"ID"))  return(es=3);  //少标识符
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,";"))  return(es=4);  //少分号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	return(es);
}
//<复合语句>::={<语句序列>} 
//<compound_stat>::={<statement_list>} 
int compound_stat(){   //复合语句函数
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement_list();
	return(es);
}



//<表达式语句>::=<<表达式>;|;
//<expression_stat>::=<expression>;|;
int expression_stat()
{
	int es=0;
	if (strcmp(token,";")==0) 
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		return(es);
	}
	es=expression();
	if (es>0) return(es);
	if (es==0 && strcmp(token,";")==0) 
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		return(es);
	} else
	{
		es=4;
		return(es);//少分号
	}
}
//<表达式>::=<标识符>=<布尔表达式>|<布尔表达式>
//<expr>::=ID=<bool_expr>|<bool_expr>

int expression()
{
	int es=0,fileadd;
	char token2[20],token3[40];
	printf("aaaaaaaaaaa%s\n",token);
	if (strcmp(token,"ID")==0)
	{   
		fileadd=ftell(fp);   //记住当前文件位置
		fscanf(fp,"%s %s\n", &token2,&token3);
		printf("%s %s\n",token2,token3);
		
		if (es>0) return(es);
		if (strcmp(token2,"=")==0)  //'='
		{
			fscanf(fp,"%s %s\n",&token,&token1);
			printf("%s %s\n",token,token1);
			es=bool_expr();
		} else 
		{
			fseek(fp,fileadd,0); //若非'='则文件指针回到'='前的标识符
			printf("%s %s\n",token,token1);
			es=bool_expr();
			if (es>0) return(es);
		}
	}else es=bool_expr();
	
	return(es);
}

//<布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >

int bool_expr()
{
	int es=0;
	es=additive_expr();
	if(es>0) return(es);
	if (strcmp(token,">")==0 || strcmp(token,">=")==0
	   ||strcmp(token,"<")==0||strcmp(token,"<=")==0
	   ||strcmp(token,"==")==0||strcmp(token,"!=")==0)
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=additive_expr();
		if(es>0) return(es);
	}
	return(es);
}
//<算术表达式>::=<项>{(+|-)<项>}
//<additive_expr>::=<term>{(+|-)< term >} 
int additive_expr()
{
	int es=0;
	es=term();
	if(es>0) return(es);
	while (strcmp(token,"+")==0 || strcmp(token,"-")==0)
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=term();
		if(es>0) return(es);
	}
	return(es);
}
//<项>::=<因子>{(*|/)<因子>}
//< term >::=<factor>{(*| /)< factor >} 
int term()
{
	int es=0;
	es=factor();
	if(es>0) return(es);
	while (strcmp(token,"*")==0 || strcmp(token,"/")==0)
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=factor();
		if(es>0) return(es);
	}
	return(es);
}
//<因子>::=(<算术表达式>)|<标识符>|<无符号整数>
//< factor >::=(<additive_expr>)| ID|NUM

int factor()
{
	int es=0;
	
	if (strcmp(token,"(")==0)  
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=expression();
		if (es>0) return(es);
		if (strcmp(token,")"))  return(es=6); //少右括号
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
	} else
	{
		
		if (strcmp(token,"ID")==0||strcmp(token,"NUM")==0)
		{
			fscanf(fp,"%s %s\n",&token,&token1);
			printf("%s %s\n",token,token1);
			return(es);
		} else
		{
			es=7;//缺少操作数
			return(es);
		}
	}
	return(es);
}
