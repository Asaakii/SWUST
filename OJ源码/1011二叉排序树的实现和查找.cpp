#include <iostream>

using namespace std;

int Count=1;
int flag=0;
class treenode
{
	friend class tree;
public:
	treenode(int a) :data(a)
	{
		left=NULL;
		right=NULL;
	}
private:
	int data;
	treenode* left;
	treenode* right;
};
class tree
{
public:
	tree() :root(NULL){}
	void insert(treenode* & T,treenode*&);
	int find(int x,treenode* current);
	treenode* root;
};

void tree::insert(treenode* & T,treenode* &current)
{
	if (current==NULL)
	{
		current=T;
	}
	if (current->data>T->data)
	{
		insert(T,current->left);
	}
	if (current->data<T->data)
	{
		insert(T,current->right);
	}
}

int tree::find(int x,treenode* current)
{
	if (current->data==x)
	{
		flag=1;
		return Count;
	}
	else
	{
		if (x>current->data)
		{
			if (current->right)
			{
				Count++;
				find(x,current->right);
			}
			else
			{
				return -1;
			}
		}
		if (x<current->data)
		{
			if (current->left)
			{
				Count++;
				find(x,current->left);
			}
			else
			{
				return -1;
			}
		}
	}
}

int main()
{
	tree T;
	int n;
	int x;
	cin >> n;
	for (int i=0;i<n;i++)
	{
		cin >> x;
		treenode* temp=new treenode(x);
		T.insert(temp,T.root);
	}
	int a;
	cin >> a;
	T.find(a,T.root);
	if (flag==0)
		cout<<-1;
	else
	cout << Count;
	return 0;
}
