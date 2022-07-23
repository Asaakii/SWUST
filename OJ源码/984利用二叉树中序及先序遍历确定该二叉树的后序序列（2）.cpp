#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

char Zhong[1000],Xian[1000];

void Ac(int Z,int X,int n)//Z:当前的中序开头位置  X:当前的先序的开头位置 n：序列长度 
{
	if (n<=0)
		return;
	int i=Z;
	while (Zhong[i]!=Xian[X])//树的先序遍历的第一个元素是根节点 所以找到后最后输出 
		i++;//序遍历中根节点的右边是左子树 右边是右子树 递归处理 
	Ac(Z,X+1,i-Z);//递归处理左儿子 
	Ac(i+1,X+i-Z,n+Z-i-1);//递归处理右儿子 
	cout << Xian[X];//输出根节点 
}

int main()
{
	while (~scanf("%s%s",Zhong,Xian))
		Ac(0,0,strlen(Zhong));
	return 0;
}
