#include <iostream>
#include <queue>

using namespace std;

class Tree;
class treenode
{
	friend class Tree;
public:
	treenode(char a):data(a),left(NULL),right(NULL){}
private:
	char data;
	treenode* left;
	treenode* right;
};
class Tree
{
public:
Tree():root(NULL){}
void precreate(treenode* &current,queue<char>&);
void levoder();
void levoder(treenode*,queue<treenode*>);
treenode* root;
};

void Tree::precreate(treenode* &current,queue<char>& Q)
{
	if (Q.empty())
		return ;
	if (Q.front()!='#')
	{
		treenode* node=new treenode(Q.front());
		Q.pop();
		current=node;
		precreate(current->left,Q);
		precreate(current->right,Q);
	}
	else
	{
		Q.pop();
	}
}
void Tree::levoder()
{
	queue<treenode*> Q;
	if (root)
	Q.push(root);
	else
	{
		cout<<"¿ÕÊ÷£¡"<<endl;
	}
	levoder(root,Q);
}
void Tree::levoder(treenode* current,queue<treenode*> Q)
{
	treenode* temp=Q.front();
	Q.pop();
	if (temp->left) Q.push(temp->left);
	if (temp->right) Q.push(temp->right);
	cout<<temp->data;
	if (!Q.empty()) levoder(Q.front(),Q);
}

int main(int argc,char* argv[])
{
	queue<char> Q;
	char a[1000];
	cin >> a;
	for (int i=0;a[i]!='\0';i++)
	{
		Q.push(a[i]);
	}
	Tree mytree;
	mytree.precreate(mytree.root,Q);
	mytree.levoder();
	return 0;
}
