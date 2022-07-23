#include <iostream>
#include <queue>

using namespace std;

int flag=0;
class treenode
{
	friend class tree;
public:
	treenode(char a) :data(a)
	{
		left=NULL;
		right=NULL;
	}
private:
	char data;
	treenode* left;
	treenode* right;
};
class tree
{
public:
	tree() :root(NULL){}
	void pre_create(treenode* &current,queue<char>&);
	bool check(treenode* root,queue<treenode*> &Q);
	treenode* root;
};

void tree::pre_create(treenode* &current,queue<char>& Q)
{
	if (Q.empty())
	{
		return;
	}
	if (Q.front()=='#')
	{
		Q.pop();
		current=NULL;
	}
	else
	{
		current=new treenode(Q.front());
		Q.pop();
		pre_create(current->left,Q);
		pre_create(current->right,Q);
	}
}

bool tree::check(treenode* current,queue<treenode*>& Q)
{
	if (current->left)
	{
		if (flag==1)
		{
			return false;
		}
		else
		{
			Q.push(current->left);
			
		}
	}
	else
	{
		flag=1;
	}
	if (current->right)
	{
		if (flag==1)
		{
			return false;
		}
		else
			Q.push(current->right);
	}
	else
	{
		flag=1;
	}
	Q.pop();
	if (Q.empty()&&flag==1)
	{
		return true;
	}
	if (!check(Q.front(),Q))
		return false;
	else
		return true;
}

int main()
{
	queue<char> Q1;
	queue<treenode*> Q2;
	char a[100];
	cin >> a;
	for (int i=0;a[i]!='\0';i++)
	{
		Q1.push(a[i]);
	}
	tree T;
	T.pre_create(T.root,Q1);
	Q2.push(T.root);
	if (T.check(T.root,Q2))
		cout << "Y";
	else
		cout << "N";
	return 0;
}
