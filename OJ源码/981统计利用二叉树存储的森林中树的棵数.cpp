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
	Tree():root(NULL),count(1){}
	void precreate(treenode*&,queue<char> &Q);
	int treenum(treenode* current);
	
treenode* root;
int count;
};
void Tree::precreate(treenode* & current,queue<char> &Q)
{
	if (Q.empty())
	return ;
	if (Q.front()!='#')
	{
		treenode* temp=new treenode(Q.front());
		Q.pop();
		current=temp;
		precreate(current->leftnode,Q);
		precreate(current->rightnode,Q);
	}
	else
	{
		Q.pop();
	}
}
int Tree::treenum(treenode* current)
{
	if (current->rightnode)
	{
		count++;
		treenum(current->rightnode);
	}
	return count;
}
int main()
{
	Tree mytree;
	queue<char> Q;
	char arr[1000];
	cin >> arr;
	for (int i=0;arr[i]!='\0';i++)
	{
		Q.push(arr[i]);
	}
	mytree.precreate(mytree.root,Q);
	cout << mytree.treenum(mytree.root);
	return 0;
}
