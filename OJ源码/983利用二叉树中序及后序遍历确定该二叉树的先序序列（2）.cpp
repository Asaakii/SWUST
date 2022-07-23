#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

char Zhong[1000],Hou[1000];

void Ac(int Z,int H,int n)//Z:当前的中序开头位置 H:当前的后序的开头位置 n:序列长度 
{
	if (n<=0)
		return ;
	cout << Hou[H+n-1];//后序遍历的最后哪一个元素是根节点 所以先输出 
	int i=Z;
	while (Zhong[i]!=Hou[H+n-1])
		i++;//在中序遍历中寻找根节点
		//中序遍历中根节点右边是左子树，右边是右子树，递归处理 
	Ac(Z,H,i-Z);//递归处理左儿子 
	Ac(i+1,H+i-Z,n+Z-i-1);//递归处理右儿子 
}

int main()
{
	while (~scanf("%s%S",Zhong,Hou))
		Ac(0,0,strlen(Zhong));
	return 0;
}
