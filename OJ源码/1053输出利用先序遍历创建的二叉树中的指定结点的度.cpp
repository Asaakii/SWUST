#include <iostream>
#include <queue>

using namespace std;

int Count=0;
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
	void precreate(treenode* & current,queue<char> &Q);
	void find_left(treenode* current,char a);
	treenode* root;
};
void tree::precreate(treenode* & current,queue<char> &Q)
{
	if (Q.empty())
	{
		return;
	}
	if (Q.front()=='#')
	{
		current=NULL;
		Q.pop();
	}
	else
	{
		current=new treenode(Q.front());
		Q.pop();
		precreate(current->left,Q);
		precreate(current->right,Q);
	}
}

void tree::find_left(treenode* current,char a)
{
	if (current==NULL)
	{
		return;
	}
	if (current->data==a)
	{
		if (current->left)
			Count++;
		if (current->right)
			Count++;
		return;
	}
	else
	{
		if (current->left)
		{
			find_left(current->left,a);
		}
		if (current->right)
		{
			find_left(current->right,a);
		}
	}
}

int main()
{
	tree T;
	queue<char> Q;
	char arr[1000];
	cin >> arr;
	for (int i=0;arr[i]!='\0';i++)
	{
		Q.push(arr[i]);
	}
	T.precreate(T.root,Q);
	char x;
	cin >> x;
	T.find_left(T.root,x);
	cout << Count;
	return 0;
}
