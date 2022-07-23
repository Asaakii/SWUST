#include <iostream>
#include <queue>

using namespace std;

class treenode
{
	friend class Tree;
public:
	treenode(char a):data(a),leftnode(NULL),rightnode(NULL){}
private:
	char data;
	treenode* leftnode;
	treenode* rightnode;
};
class Tree
{
public:
	Tree():root(NULL),i(0){}
	void precreate(treenode* &current,queue<char> &Q);
	void normal_tree(treenode* current,int count[100]);
	bool check();
public:
	int i;
	treenode* root;
};
bool Tree::check()
{
	if (root->rightnode!=NULL)
		return false;
	else
		return true;
}
void Tree::precreate(treenode* &current,queue<char> &Q)
{
	if (Q.empty())
		return ;
	if (Q.front()!='#')
	{
		treenode* temp=new treenode(Q.front());
		current=temp;
		Q.pop();
		precreate(current->leftnode,Q);
		precreate(current->rightnode,Q);
	}
	else
	{
		Q.pop();
	}
}
void Tree::normal_tree(treenode* current,int count[100])
{
	if (!check())
	return ;
	if (current==NULL)
	return ;
	if (current->rightnode)
	{
		count[i]++;
		normal_tree(current->rightnode,count);
	}
	if (current->leftnode)
	{
		i++;
		normal_tree(current->leftnode,count);
	}
}

int main()
{
	queue<char> Q;
	char a[1000];
	int count[100];
	cin >> a;
	for (int k=0;a[k]!='\0';k++)
	{
		Q.push(a[k]);
	}
	for (int n=0;n<100;n++)
	{
		count[n]=1;
	}
	Tree mytree;
	mytree.precreate(mytree.root,Q);
	mytree.normal_tree(mytree.root,count);
	int max=0;
	for (int j=mytree.i;j>=0;j--)
	{
		if (count[j]>max)
		max=count[j];
		
	}
	if (mytree.check())
	cout << max;
	else
	cout << "ERROR";
	return 0;
}
