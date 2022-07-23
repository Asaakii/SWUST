#include <bits/stdc++.h>

#define NewNode (node*)malloc(sizeof(node))

using namespace std;

int ans=0;

struct node
{
	char data;
	node *Lchild;
	node *Rchild;
};

node * Built()
{
	node *T;
	char ch=getchar();
	if (ch=='#')
		T=NULL;
	else
	{
		T=NewNode;
		T->data=ch;
		T->Lchild=Built();
		T->Rchild=Built();
	}
	return T;
}

//��������������ʱ��ÿ���ڵ����������ɱ�ʾ���ӣ����Ҷ����������ֵܽڵ�

int Count(node *&T)
{
	if (T==NULL)
		return 0;   //�������ڵ㲻���ڣ�����0 
	ans=max(ans,Count(T->Lchild));//���򣬲鿴���ӽڵ��ж������ģ��͵�ǰ��ans���Ƚ� 
	ans=max(ans,Count(T->Rchild)+1);//�鿴��ǰ�ڵ��м����ֵܣ���҅��+1���Լ������Ǹ��ڵ�Ķ�������ans���Ƚ� 
	return ans;
}

int main()
{
	node *root=Built();
	if (root->Rchild!=NULL)//������ڵ����ֵܣ���˵����ֹһ���� 
		cout << "ERROR";
	else
		cout << Count(root);
	return 0;
}
