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
	void getright(TreeNode * p)
	{
		rightnode=p;
	}
	TreeNode(char a){date=a;leftnode=NULL;rightnode=NULL;};
	char date;
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
	
	int preoder();
	int preoder(TreeNode* current,int h1,int h2);
	void preinsert(TreeNode* &current,char* arr);
	TreeNode* root;
};
int binarytree::preoder()
{
	int h1=1,h2=1;
	return preoder(root,h1,h2);
}
int h=0;
int binarytree::preoder(TreeNode* current,int h1,int h2)
{
	if (current)
	{
		if (h1>=h2&&h1>h)
			h=h1;
		else if (h2>=h1&&h2>h)
			h=h2;
		h1++;
		preoder(current->leftnode,h1,h2);
		h2++;
		preoder(current->rightnode,h2,h2);
	}
	return h;
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
	cout << Tree.preoder();
	return 0;
}
