//主程序
#include <stdio.h>
#include <ctype.h>
extern int TESTscan();
char Scanin[300],Scanout[300]; //用于接收输入输出文件名
FILE *fin,*fout; //用于指向输入输出文件的指针
void main(){
	int es=0;
	es=TESTscan();//调词法分析
    if (es>0) printf("词法分析有错,编译停止!");
	else printf("词法分析成功!\n");
}
