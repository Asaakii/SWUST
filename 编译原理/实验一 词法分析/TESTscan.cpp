#include <stdio.h>
#include <ctype.h>
#include <string.h>

//保留字表
char* keyword[8] = {"if","else","for","while","do","int","read","write"};

//单分界符
char singleword[50] = "+-*(){};,:#&|";

//双分界符
char doubleword[10] = "><=!&";

//用于接收输入输出文件名
char Scanin[300],Scanout[300];

//用于指向输入输出文件的指针
FILE* fin,* fout;

//词法分析函数
int TflagTscan()
{
	char ch,token[40];//CH为每次读入的字符，TOKEN用于保存识别出的单词
	int flag = 0,j,n;//flag为错误代码，0表示没有错误
	int line = 1;
	printf("请输入源程序文件名：");
	scanf("%s",Scanin);
	printf("请输入词法分析输出文件名：");
	scanf("%s",Scanout);
	if((fin = fopen(Scanin,"r")) == NULL)//判断输入文件名是否正确
	{
		printf("\n打开词法分析输入文件出错！\n");
		flag=1;//如果出错flag置为1
	}
	if((fout = fopen(Scanout,"w")) == NULL)//判断输出文件名是否正确
	{
		printf("\n创建词法分析输出文件出错！\n");
		flag=2;//如果出错flag置为2
	}
	ch = getc(fin);
	
	while(ch!=EOF)
	{
		while(ch==' '||ch=='\n'||ch=='\t')
		{
			if (ch=='\n') 
				line++;
			ch=getc(fin);
		}
		
		if(isalpha(ch))//如果是字母 则进行标识符处理
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			
			while(isalnum(ch))//如果是字母数字则组合标识符
			{
				token[j++] = ch;//组合的标识符存在TOKEN中
				ch = getc(fin);
			}
			token[j] = '\0';//标识符组合结束
			
			n = 0;
			while ((n < 8) && strcmp(token, keyword[n]))
				n++;
			if (n  >= 8)//如果不是保留字输出标识符
			{
				fprintf(fout,"%s\t%s\n","ID",token);//输出标识符符号
			}
			else//是保留字 输出保留字
			{
				fprintf(fout,"%s\t%s\n",token,token);//输出保留字符号
			}
		}
		
		else if(isdigit(ch))//数字处理
		{
			token[0] = ch;
			j = 1;
			if(token[0]=='0')
			{
				ch=getc(fin);
				if(ch=='\0')
				{
						fprintf(fout,"NUM_0");
				}
				else
				{ 
					fprintf(fout,"%s\t%s\n","ERROR",token);
					printf("Line %d\t%s\t%s\n",line,"以0开头的整数",token);
				} 
			}
			else
			{
				ch = getc(fin);//读下一个字符
				while(isdigit(ch))//如果是数字则组合整数 如果不是则整数组合结束
				{
					token[j++] = ch;//组合整数保存在TOKEN 中
					ch = getc(fin);//读下一个字符
				}
				token[j] = '\0';//整数组合结束
				fprintf(fout,"%s\t%s\n","NUM",token);//输出整数符号
			}
		}
		
		else if(strchr(singleword,ch)>0)//单分解符处理
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);//读下一个符号以便识别下一个单词
			fprintf(fout,"%s\t%s\n",token,token);//输出单分界符好
		}
		
		else if(strchr(doubleword,ch)>0)//双分界符处理
		{
			token[0] = ch;
			ch = getc(fin);//读下一个字符判断是否为双分界符
			if(ch == '=')//如果是= 组合双分界符
			{
				token[1] = ch;
				token[2] = '\0';//组合双分界符结束
				ch = getc(fin);//读下一个符号以便识别下一个单词
				fprintf(fout,"%s\t%s\n",token,token);//输出双分界符符号
			}
			else if(ch == '&')//如果是& 组合双分界符
			{
				token[1] = ch;
				token[2] = '\0';//组合双分界符结束
				ch = getc(fin);//读下一个符号以便识别下一个单词
				fprintf(fout,"%s\t%s\n",token,token);//输出双分界符符号
			}
			else//不是=则为但分界符
			{
				token[1] = '\0';
				if(token[0]=='!') 
				{
					printf("Line %d\t%s\t%s\n",line,"非法字符",token);
					fprintf(fout,"%s\t%s\n","ERROR",token);
				}
				else
				{
					fprintf(fout,"%s\t%s\n",token,token);//输出双分界符符号
				}
			}
		}
		
		else if(ch=='/')//注释 
		{
			ch = getc(fin);
			if(ch == '*')//如果是* 则开始处理注释
			{
				char ch1;
				ch1 = getc(fin);//读下一个字符
				while (true)
				{
					if (ch1==EOF)
					{
						printf("Line %d\t%s\t没有匹配！\n", line,"非法语句");
						break;
					}
					ch=ch1;
					ch1=getc(fin);
					if(ch=='*' && ch1=='/')
						break;
				}
				ch = getc(fin);//不是*则处理单分界符
			}
			else
			{
				token[0] = '/';
				token[1] = '\0';
				fprintf(fout,"%s\t%s\n",token,token);//输出单分界符
			}
		}
		
		else//错误处理   
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			//读下一个符号以便识别
			flag = 0;//设置错误代码
			fprintf(fout,"%s\t%s\n","ERROR",token);//输出错误符号 并提示ERROR
			printf("Line %d\t%s\t%s\n",line,"非法字符",token);
		}
	}
	fclose(fin);//关闭输入输出文件
	fclose(fout);
	return flag;
}

int main()
{
	int flag = 0;
	flag = TflagTscan();//调用词法分析程序
	if (flag > 0)
		printf("词法分析失败!\n");
	else
		printf("词法分析成功!\n");
	return 0;
}
