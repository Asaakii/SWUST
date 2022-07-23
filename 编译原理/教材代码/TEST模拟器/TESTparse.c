//语法、语义分析及代码生成
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#define maxfhbp 500//定义符号表的容量
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
int name_def(char *name);
char token[20],token1[40];//token保存单词符号，token1保存单词值
extern char Scanout[300],Codeout[300]; //保存词法分析输出文件名
FILE *fp,*fout; //用于指向输入输出文件的指针
struct{//定义符号表结构
     char name[8];
     int address;
}fhb[maxfhbp];//改符号表最多容纳maxfhbp个记录
int fhbp=0,labelp=0,datap=0;
//插入符号表动作@name-def↓n, t的程序如下：
int name_def(char *name)
{    
	int i,es=0;
    if (fhbp>=maxfhbp) return(-1);
	for(i=fhbp-1;i==0;i--)//查符号表
	{ 
		if (strcmp(fhb[i].name,name)==0)
		{
			es=21;//21表示变量重复声明
			break;
		}
	}
	if (es==21)   return(es);
	strcpy(fhb[fhbp].name,name);
	fhb[fhbp].address=datap;
	datap++;//分配一个单元，数据区指针加1
	fhbp++;	
	return(es);
}
//查询符号表返回地址
int lookup(char *name,int *paddress)
{
	int i,es=0;
	for(i=0;i<fhbp;i++)
	{
		if (strcmp(fhb[i].name,name)==0)
		{
           *paddress=fhb[i].address;
		   return(es);
		}
	}
     es=23;//变量没有声明
	 return(es);
}
//语法、语义分析及代码生成程序
int TESTparse()
{
	int es=0;
	if((fp=fopen("bbb.t","r"))==NULL)
	{  
      printf("\n打开%s错误!\n",Scanout);
	  es=10;
	  return(es);
	}
	//printf("请输入目标文件名（包括路径）：");
    //scanf("%s",Codeout);
	if((fout=fopen("ccc.t","w"))==NULL)
	{  
      printf("\n创建%s错误!\n",Codeout);
	  es=10;
	  return(es);
	}
	if (es==0) es=program();
	printf("==语法、语义分析及代码生成程序结果==\n");
	switch(es)
	{
		case 0: printf("语法、语义分析成功并抽象机汇编生成代码!\n");break;	
		case 10: printf("打开文件 %s失败!\n",Scanout);break;
		case 1: printf("缺少{!\n");break;
		case 2: printf("缺少}!\n");break;
		case 3: printf("缺少标识符!\n");break;
		case 4: printf("少分号!\n");break;
		case 5: printf("缺少(!\n");break;
		case 6: printf("缺少)!\n");break;
		case 7: printf("缺少操作数!\n");break;
		case 21: printf("符号表溢出!\n");break;
		case 22: printf("变量重复定义!\n");break;
		case 23: printf("变量未声明!\n");break;
		
	}
	fclose(fp);
	fclose(fout);
	return(es);
}
//<程序>::={<声明序列><语句序列>}
//program::={<declaration_list><statement_list>}
int program()
{ 
   int es=0,i;
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
   printf("     符号表\n");
   printf("     名字       地址\n");
   for(i=0;i<fhbp;i++)
	   printf("      %s   %d\n",fhb[i].name,fhb[i].address);
   es=statement_list();
   if (es>0) return(es);
   if(strcmp(token,"}"))//判断是否'}'
   {
	   es=2;
	   return(es);
   }
   fprintf(fout,"        STOP\n");//产生停止指令
   return(es);
}
//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
//改成<declaration_list>::={<declaration_stat>}
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
//<declaration_stat>↓fhbp,datap,codep ->int ID↑n@name-def↓n,t;
int declaration_stat()
{
	int es=0;      
	fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n",token,token1);
	if (strcmp(token,"ID"))	return(es=3);  //不是标识符
	es=name_def(token1);//插入符号表
	if (es>0) return(es);
	fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n",token,token1);
	if (strcmp(token,";") )	return(es=4);		
	fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n",token,token1);
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
	if (es==0 && (strcmp(token,"ID")==0||strcmp(token,"NUM")==0)) es=expression_stat();//<表达式语句>
	return(es);
}
//<IF 语句>::= if (<表达式>) <语句 > [else <语句 >]
//<IF_stat>::= if (<expr>) <statement > [else < statement >]
/*
if (<表达式>)@BRF↑label1 <语句 > @BR↑label2 @SETlabel↓label1 
                   [ else <语句 >] @SETlabel↓label2
if (<expression>)@BRF↑label1 <statement > @BR↑label2 @SETlabel↓label1 
                  [ else < statement >] @SETlabel↓label2

其中动作符号的含义如下
  @BRF↑label1 ：输出 BRF label1, 
  @BR↑label2：输出 BR label2, 
  @SETlabel↓label1：设置标号label1 
  @SETlabel↓label2：设置标号label2
*/
int if_stat(){
	int es=0,label1,label2;  //if
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"(")) 	return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //少右括号
	label1=labelp++;//用label1记住条件为假时要转向的标号
	fprintf(fout,"        BRF LABEL%d\n",label1);//输出假转移指令
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement(); 
	if (es>0) return(es);
	label2=labelp++;//用label2记住要转向的标号
	fprintf(fout,"        BR LABEL%d\n",label2);//输出无条件转移指令
	fprintf(fout,"LABEL%d:\n",label1);//设置label1记住的标号
	if (strcmp(token,"else")==0)//else部分处理
	{  
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=statement(); 
	    if (es>0) return(es);
	}
	fprintf(fout,"LABEL%d:\n",label2);//设置label2记住的标号
	return(es);
}
//<while语句>::=while(<表达式>) <语句>
//<while_stat>::= while (<expr >) < statement >
/*<while语句>::=while @SETlabel↑label1(<表达式>) @BRF↑label2 
              <语句 >@BR↓label1 @SETlabel↓label2
<while_stat>::=while @SET↑labellabel1(<expression>) @BRF↑label2 
				<statement >@BR↓label1 @SETlabel↓label2
动作解释如下：
@SETlabel↑label1：设置标号label1
@BRF↑label2 ：输出 BRF label2,
@BR↓label1：输出 BR label1,
@SETlabel↓label2：设置标号label2
*/
int while_stat()
{
	int es=0,label1,label2;  
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);//设置label1标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"("))  return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,")"))  return(es=6); //少右括号
	label2=labelp++;
	fprintf(fout,"        BRF LABEL%d\n",label2);//输出假转移指令
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	if (es>0) return(es);
	fprintf(fout,"        BR LABEL%d\n",label1);//输出无条件转移指令
	fprintf(fout,"LABEL%d:\n",label2);//设置label2标号
	return(es);
}

//<for语句>::=for(<表达式>;<表达式>;<表达式>) <语句 >
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
/*
<for语句>::= for (<表达式>,<表达式>,<表达式>) <语句 >
<for_stat>::=for (<expression>;
             @SETlabel↑label1< expression >@BRF↑label2@BR↑label3;
             @SETlabel↑label4 < expression >@BR↓label1) 
             @SETlabel↓label3 <语句 >@BR↓label4@SETlabel↓label2 
动作解释：
1.	@SETlabel↓label1：设置标号label1
2.	@BRF↑label2 ：输出 BRF label2,
3.	@BR↑label3：输出 BR label3,
4.	@SETlabel↓label4：设置标号label4
5.	@BR↑label1：输出 BR label1,
6.	@SETlabel↓label3：设置标号label3
7.	@BR↑label4：输出 BR label4,
8.	@SETlabel↓label2：设置标号label2 
*/
int for_stat()
{
	int es=0,label1,label2,label3,label4;  
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"("))  return(es=5);  //少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	if (strcmp(token,";")) 	return(es=4);  //少分号
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);//设置label1标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	label2=labelp++;
	fprintf(fout,"        BRF LABEL%d\n",label2);//输出假条件转移指令
	label3=labelp++;
	fprintf(fout,"        BR LABEL%d\n",label3);//输出无条件转移指令
	if (strcmp(token,";"))  return(es=4);  //少分号
	label4=labelp++;
	fprintf(fout,"LABEL%d:\n",label4);//设置label4标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0) return(es);
	fprintf(fout,"        BR LABEL%d\n",label1);//输出无条件转移指令
	if (strcmp(token,")"))  return(es=6); //少右括号
	fprintf(fout,"LABEL%d:\n",label3);//设置label3标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	if (es>0) return(es);
	fprintf(fout,"        BR LABEL%d\n",label4);//输出无条件转移指令
	fprintf(fout,"LABEL%d:\n",label2);//设置label2标号
	return(es);
	
}
//<write_语句>::=write <表达式>;
//<write_stat>::=write <expression>;
//<write_语句>::=write <表达式>@OUT;
//<write_stat>::=write <expression>@OUT;
//动作解释：
//@ OUT：输出 OUT

int write_stat()
{
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if (es>0)return(es);
	if (strcmp(token,";"))  return(es=4);  //少分号
	fprintf(fout,"        OUT\n");//输出指令
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	return(es);
}
//<read_语句>::=read <变量>;
//<read_stat>::=read ID;
//<read_语句>::=read <变量>;
//<read_stat>::=read ID↑n LOOK↓n↑d @IN@STI↓d;
//动作解释：
//@LOOK↓n↑d:查符号表n，给出变量地址d; 没有，变量没定义
//@IN：输出IN
//@STI↓d：输出指令代码STI  d


int read_stat()
{
	int es=0,address;
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	if (strcmp(token,"ID"))  return(es=3);  //少标识符
	es=lookup(token1,&address);
	if (es>0) return(es);
	fprintf(fout,"        IN   %d\n",address);//输入指令
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
	if (strcmp(token,";")==0) 
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
//<表达式>::=<标识符>=↑n@LOOK↓n↑d<布尔表达式>@STO↓d|<布尔表达式>
//<expr>::=ID=↑n@LOOK↓n↑d<bool_expr>@STO↓d|<bool_expr>

int expression()
{
	int es=0,fileadd;
	char token2[20],token3[40];
	if (strcmp(token,"ID")==0)
	{   
		fileadd=ftell(fp);   //记住当前文件位置
		fscanf(fp,"%s %s\n", &token2,&token3);
		printf("%s %s\n",token2,token3);
		if (strcmp(token2,"=")==0)  //'='
		{
			int address;
			es=lookup(token1,&address);
			if (es>0) return(es);
			fscanf(fp,"%s %s\n",&token,&token1);
			printf("%s %s\n",token,token1);
			es=bool_expr();
			if (es>0) return(es);
			fprintf(fout,"        STO %d\n",address);

		} else 
		{
			fseek(fp,fileadd,0); //若非'='则文件指针回到'='前的标识符
			printf("%s %s\n",token,token1);
			es=bool_expr();
			if (es>0) return(es);
		}
	}
	
	return(es);
}

//<布尔表达式>::=<算术表达式>|<算术表达式>(>|<|>=|<=|==|!=)<算术表达式>
//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
/*<布尔表达式>::=<算术表达式>
|<算术表达式>><算术表达式>@GT
|<算术表达式><<算术表达式>@LES
|<算术表达式>>=<算术表达式>@GE
|<算术表达式><=<算术表达式>@LE
|<算术表达式>==<算术表达式>@EQ
|<算术表达式>!=<算术表达式>@NOTEQ
<bool_expr>::=<additive_expr>
|< additive_expr >><additive_expr>@GT
|< additive_expr ><<additive_expr>@LES
|< additive_expr >>=<additive_expr >@GE
|< additive_expr ><=< additive_expr >@LE
|< additive_expr >==< additive_expr >@EQ
|< additive_expr >!=< additive_expr >@NOTEQ
*/
int bool_expr()
{
	int es=0;
	es=additive_expr();
	if(es>0) return(es);
	if ( strcmp(token,">")==0 || strcmp(token,">=")==0
	   ||strcmp(token,"<")==0 || strcmp(token,"<=")==0
	   ||strcmp(token,"==")==0|| strcmp(token,"!=")==0)
	{
		char token2[20];
		strcpy(token2,token);//保存运算符
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=additive_expr();
		if(es>0) return(es);
		if ( strcmp(token2,">")==0 ) fprintf(fout,"        GT\n");
		if ( strcmp(token2,">=")==0 ) fprintf(fout,"        GE\n");
		if ( strcmp(token2,"<")==0 ) fprintf(fout,"        LES\n");
		if ( strcmp(token2,"<=")==0 ) fprintf(fout,"        LE\n");
		if ( strcmp(token2,"==")==0 ) fprintf(fout,"        EQ\n");
		if ( strcmp(token2,"!=")==0 ) fprintf(fout,"        NOTEQ\n");
	}
	return(es);
}
//<算术表达式>::=<项>{(+|-)<项>}
//<additive_expr>::=<term>{(+|-)< term >} 
//<算术表达式>::=<项>{(+<项>@ADD|-<项>@SUB)} 
//< additive_expr>::=<term>{(+< term >@ADD |-<项>@SUB)}

int additive_expr()
{
	int es=0;
	es=term();
	if(es>0) return(es);
	while (strcmp(token,"+")==0 || strcmp(token,"-")==0)
	{
		char token2[20];
		strcpy(token2,token);
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=term();
		if(es>0) return(es);
		if ( strcmp(token2,"+")==0 ) fprintf(fout,"        ADD\n");
		if ( strcmp(token2,"-")==0 ) fprintf(fout,"        SUB\n");
	}
	return(es);
}
//<项>::=<因子>{(*|/)<因子>}
//< term >::=<factor>{(*| /)< factor >} 
//<项>::=<因子>{(*<因子>@MULT|/<因子>@DIV)}
//< term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)} 

int term()
{
	int es=0;
	es=factor();
	if(es>0) return(es);
	while (strcmp(token,"*")==0 || strcmp(token,"/")==0)
	{
		char token2[20];
		strcpy(token2,token);
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=factor();
		if(es>0) return(es);
		if ( strcmp(token2,"*")==0 ) fprintf(fout,"        MULT\n");
		if ( strcmp(token2,"/")==0 ) fprintf(fout,"        DIV\n");
	}
	return(es);
}
//<因子>::=(<算术表达式>)|<标识符>|<无符号整数>
//< factor >::=(<additive_expr>)| ID|NUM
//<因子>::=(<算术表达式>)|<标识符>↑n@LOOK↓n↑d@LOAD↓d 
//                       |<无符号整数>↑i@LOADI↓i
//< factor >::=(< expression >)| ID↑n@LOOK↓n↑d@LOAD↓d |NUM↑i@LOADI↓i

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
		
		if (strcmp(token,"ID")==0)
		{
			int address;
			es=lookup(token1,&address);//查符号表，获取变量地址
			if (es>0) return(es);//变量没声明
			fprintf(fout,"        LOAD %d\n",address);
			fscanf(fp,"%s %s\n",&token,&token1);
			printf("%s %s\n",token,token1);
			return(es);
		} 
		if (strcmp(token,"NUM")==0)
		{
			fprintf(fout,"        LOADI %s\n",token1);
			fscanf(fp,"%s %s\n",&token,&token1);
			printf("%s %s\n",token,token1);
			return(es);
		}else
		{
			es=7;//缺少操作数
			return(es);
		}
	}
	return(es);
}