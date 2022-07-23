#include <iostream>

using namespace std;

int i=0;
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
	TreeNode();
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
	void preinsert(TreeNode* &current,char* arr);
	void inoder();
	void inoder(TreeNode * current);
	TreeNode * root=NULL;
};
void binarytree::inoder()
{
	inoder(root);
}

void binarytree::inoder(TreeNode* current)
{
	if (current)
	{
		inoder(current->leftnode);
		cout << current->data;
		inoder(current->rightnode);
	}
}
void binarytree::preinsert(TreeNode* &current,char* arr)
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
	Tree.inoder();
	return 0;
}
