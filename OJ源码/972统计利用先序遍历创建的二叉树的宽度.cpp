#include <iostream>
#include <queue>

using namespace std;

int i=0;
int Count=0;
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
	
	int leveloder();                                                //后序遍历 
	int leveloder(TreeNode* current,queue<TreeNode*>);
	void preinsert(TreeNode* &current,char* arr);
	TreeNode * root;
};
int binarytree::leveloder()
{
	queue<TreeNode*> Q;
	Q.push(root);
	int ret=0;
	ret=leveloder(root,Q);
	if (ret==0&&root)
		ret=1;
	return ret;
}
int binarytree::leveloder(TreeNode* current,queue<TreeNode*>Q)
{
	TreeNode* temp=Q.front();
	Q.pop();
	if(temp->leftnode)Q.push(temp->leftnode);
	if(temp->rightnode)Q.push(temp->rightnode);
	
	if(temp->leftnode)leveloder(temp->leftnode,Q);
	if(temp->rightnode)leveloder(temp->rightnode,Q);
	Count=Q.size()>Count?Q.size():Count;
	return Count; 
}
void binarytree::preinsert(TreeNode* &current,char* arr)            //注意这里的是引用地址 
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
	cout<< Tree.leveloder();
	return 0;
}
