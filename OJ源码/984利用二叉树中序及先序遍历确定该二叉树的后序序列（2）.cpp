#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

char Zhong[1000],Xian[1000];

void Ac(int Z,int X,int n)//Z:��ǰ������ͷλ��  X:��ǰ������Ŀ�ͷλ�� n�����г��� 
{
	if (n<=0)
		return;
	int i=Z;
	while (Zhong[i]!=Xian[X])//������������ĵ�һ��Ԫ���Ǹ��ڵ� �����ҵ��������� 
		i++;//������и��ڵ���ұ��������� �ұ��������� �ݹ鴦�� 
	Ac(Z,X+1,i-Z);//�ݹ鴦������� 
	Ac(i+1,X+i-Z,n+Z-i-1);//�ݹ鴦���Ҷ��� 
	cout << Xian[X];//������ڵ� 
}

int main()
{
	while (~scanf("%s%s",Zhong,Xian))
		Ac(0,0,strlen(Zhong));
	return 0;
}
