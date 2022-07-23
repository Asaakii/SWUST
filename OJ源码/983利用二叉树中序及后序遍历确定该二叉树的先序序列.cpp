#include <iostream>

using namespace std;

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
	void create(treenode* & T,char *back,char *in,int n);
	void display(treenode* T);
	treenode* root;
};
void tree::create(treenode* & T,char *back,char *in,int n)
{
	if (n<=0)
	{
		T=NULL;
		return;
	}
	int k;
	char* p;
	T=new treenode(*(back+n-1));
	for (p=in;p<in+n;p++)
	{
		if (*p==*(back+n-1))
			break;
	}
	k=p-in;
	create(T->right,(back+n-1)-(n-1-k),in+k+1,n-k-1);
	create(T->left,back,in,k);
	return;
}

void tree::display(treenode* T)
{
	if (T)
	{
		cout << T->data;
		display(T->left);
		display(T->right);
	}
}

int main()
{
	int n=0;
	char ar_in[100];
	char ar_back[100];
	cin >> ar_in;
	cin >> ar_back;
	for (int i=0;ar_back[i];i++)
	{
		n++;
	}
	tree* T=new tree;
	T->create(T->root,ar_back,ar_in,n);
	T->display(T->root);
	return 0;
}
