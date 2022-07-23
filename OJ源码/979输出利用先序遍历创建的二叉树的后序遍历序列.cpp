#include <iostream>
#include <queue>

using namespace std;

int i=0;
class binarytree;
class TreeNode
{
	friend class binarytree;
public:
	void getleft(TreeNode * p)
	{
		leftnode=p;
	}
	void getright(TreeNode *p)
	{
		rightnode=p;
	}
	TreeNode(char a) {data=a;leftnode=NULL;rightnode=NULL;};
	char data;
	TreeNode *leftnode;
	TreeNode *rightnode;
};
class binarytree
{
public:
	void getroot(TreeNode* p)
	{
		root=p;
	}
	
	void pastoder();                                    //������� 
	void pastoder(TreeNode* current);
	void preinsert(TreeNode* &current,char* arr);
	TreeNode * root;
};
void binarytree::pastoder()
{
	pastoder(root);
}
void binarytree::pastoder(TreeNode* current)
{
	if (current)
	{
		pastoder(current->leftnode);
		pastoder(current->rightnode);
		cout << current->data;
	}
}
void binarytree::preinsert(TreeNode* &current,char* arr)        //ע������������õ�ַ 
{
	if (arr[i]=='#')
	{
		current=NULL;
		i++;
	}
	else
	{
		current=new TreeNode(arr[i]);
		i++;
		preinsert(current->leftnode,arr);
		preinsert(current->rightnode,arr);
	}
}

int main()
{
	binarytree Tree;
	char arr[1000];
	cin >> arr;
	Tree.preinsert(Tree.root,arr);
	Tree.pastoder();
	return 0;
}
