#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

char Zhong[1000],Hou[1000];

void Ac(int Z,int H,int n)//Z:��ǰ������ͷλ�� H:��ǰ�ĺ���Ŀ�ͷλ�� n:���г��� 
{
	if (n<=0)
		return ;
	cout << Hou[H+n-1];//��������������һ��Ԫ���Ǹ��ڵ� ��������� 
	int i=Z;
	while (Zhong[i]!=Hou[H+n-1])
		i++;//�����������Ѱ�Ҹ��ڵ�
		//��������и��ڵ��ұ������������ұ������������ݹ鴦�� 
	Ac(Z,H,i-Z);//�ݹ鴦������� 
	Ac(i+1,H+i-Z,n+Z-i-1);//�ݹ鴦���Ҷ��� 
}

int main()
{
	while (~scanf("%s%S",Zhong,Hou))
		Ac(0,0,strlen(Zhong));
	return 0;
}
