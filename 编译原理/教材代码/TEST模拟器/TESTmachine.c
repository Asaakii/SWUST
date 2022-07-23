#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int TESTmachine();

int TESTmachine()
{
	int es=0,i,k=0,codecount,stack[1000],stacktop=0;
	char Codein[300],code[1000][20],data[1000]; //用于接收输入文件名
	int label[100];
	char lno[4];
	FILE *fin; //用于指向输入输出文件的指针
	printf("请输入目标文件名（包括路径）：");
    scanf("%s",Codein);
	if((fin=fopen("ccc.t","r"))==NULL)
	{  
      printf("\n打开%s错误!\n",code);
	  es=10;
	  return(es);
	}
	codecount=0;
	i=fscanf(fin,"%s",&code[codecount]);
	while (!feof(fin))
	{
		i=strlen(code[codecount])-1;
		if (code[codecount][i]==':')
		{
			
			i=i-5;
			strncpy(lno,&code[codecount][5],i);
			lno[i]='\0';
			label[atoi(lno)]=codecount;//用label数组记住每个标号的地址
			code[codecount][0]=':';
			code[codecount][1]='\0';
			strcat(code[codecount],lno);
			k++;
		}
		codecount++;
		i=fscanf(fin,"%s",&code[codecount]);
	}
	fclose(fin);
	
	for (i=0;i<codecount;i++)
	{
		int l;
		l=strlen(code[i]);
		printf("1111%d  %s  %d\n",i,code[i],l);
		if ((l>1) && (code[i][1]=='A'))
		{
			
			strncpy(lno,&code[i][5],l-5);
			lno[i]='\0';
			itoa(label[atoi(lno)],code[i],10);
		}
	}
	
	i=0;
	while (i<codecount)//执行每条指令
	{
		
		if (strcmp(code[i],"LOAD")==0)//LOAD D将D中的内容加载到操作数栈。
		{
			i++;
			stack[stacktop]=data[atoi(code[i])];
			stacktop++;
		}
		if (strcmp(code[i],"LOADI")==0)//LOADI a将常量a压入操作数栈
		{
			i++;
			stack[stacktop]=atoi(code[i]);
			stacktop++;
		}
		//STO D 将操作数栈栈顶单元内容存入D
		//且栈顶单元内容保持不变。
		if (strcmp(code[i],"STO")==0)
		{
			i++;
			data[atoi(code[i])]=stack[stacktop-1];
		}
		//STI D 将操作数栈栈顶单元内容存入D
		//且栈顶单元内容出栈。
		if (strcmp(code[i],"STI")==0)
		{
			i++;
			data[atoi(code[i])]=stack[stacktop-1];
			stacktop--;
		}
		//ADD将次栈顶单元与栈顶单元内容出栈并相加，和置于栈顶。
		if (strcmp(code[i],"ADD")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]+stack[stacktop-1];
			stacktop--;
		}
		//SUB    将次栈顶单元减去栈顶单元内容并出栈，差置于栈顶。
		if (strcmp(code[i],"SUB")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]-stack[stacktop-1];
			stacktop--;
		}
		//MULT   将次栈顶单元与栈顶单元内容出栈并相乘，积置于栈顶。
		if (strcmp(code[i],"MULT")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]*stack[stacktop-1];
			stacktop--;
		}
		//DIV    将次栈顶单元与栈顶单元内容出栈并相除，商置于栈顶。
		if (strcmp(code[i],"DIV")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]/stack[stacktop-1];
			stacktop--;
		}
		//BR    lab  无条件转移到lab
		if (strcmp(code[i],"BR")==0)
		{
			i++;
			i=atoi(code[i]);			
		}
		//BRF  lab  检查栈顶单元逻辑值，若为假（0）则转移到lab
		if (strcmp(code[i],"BRF")==0)
		{
			i++;
			if (stack[stacktop-1]==0) i=atoi(code[i]);	
			stacktop--;
		}
		//EQ  将栈顶两单元做等于比较，并将结果真或假（1或0）置于栈顶
		if (strcmp(code[i],"EQ")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]==stack[stacktop-1];
			stacktop--;
		}
		//NOTEQ 将栈顶两单元做不等于比较，并将结果真或假（1或0）置于栈顶
		if (strcmp(code[i],"NOTEQ")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]!=stack[stacktop-1];
			stacktop--;
		}
		//GT    次栈顶大于栈顶操作数，则栈顶置1，否则置0
		if (strcmp(code[i],"GT")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]>stack[stacktop-1];
			stacktop--;
		}
		//LES  次栈顶小于栈顶操作数，则栈顶置1，否则置0
		if (strcmp(code[i],"LES")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]<stack[stacktop-1];
			stacktop--;
		}
		//GE  次栈顶大于等于栈顶操作数，则栈顶置1，否则置0
		if (strcmp(code[i],"GE")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]>=stack[stacktop-1];
			stacktop--;
		}
		//LE  次栈顶小于等于栈顶操作数，则栈顶置1，否则置0
		if (strcmp(code[i],"LE")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]<=stack[stacktop-1];
			stacktop--;
		}
		//AND 将栈顶两单元做逻辑与运算，并将结果真或假（1或0）置于栈顶
		if (strcmp(code[i],"AND")==0)
		{
			stack[stacktop-2]=stack[stacktop-2] && stack[stacktop-1];
			stacktop--;
		}
		//OR  将栈顶两单元做逻辑或运算，并将结果真或假（1或0）置于栈顶
		if (strcmp(code[i],"OR")==0)
		{
			stack[stacktop-2]=stack[stacktop-2]||stack[stacktop-1];
			stacktop--;
		}
		//NOT  将栈顶的逻辑值取反
		if (strcmp(code[i],"NOT")==0)
		{
			stack[stacktop-1]=!stack[stacktop-1];
		}
		//IN 从标准输入设备（键盘）读入一个整型数据，并入栈。
		if (strcmp(code[i],"IN")==0)
		{
			i++;
			printf("请输入数据：");
			scanf("%d",&stack[stacktop]);
			stacktop++;
		}
		//OUT 将栈顶单元内容出栈，并输出到标准输出设备上（显示器）。
		if (strcmp(code[i],"OUT")==0)
		{
			printf("程序输出%d\n",stack[stacktop-1]);
			stacktop--;
		}
		//STOP 停止执行
		if (strcmp(code[i],"STOP")==0)
		{
			break;
		}
		i++;
	}
	return(es);
}






