#include <iostream>
#include <string>
#include <map>

using namespace std;

const int INF=0.00001;

int main()
{
	int n,m,i,j,k,t=0;
	double d[50][50];
	string x[50],x1,x2;
	while (cin>>n,n)
	{
		for (i=1;i<=n;i++)
		{
			for (j=1;j<=n;j++)
			{
				d[i][j]=INF;
			}
		}
		map<string,int> p;
		for (i=1;i<=n;i++)
		{
			cin>>x[i];
			p[x[i]]=i;
		}
		cin>>m;
		double c;
		for (i=1;i<=m;i++)
		{
			cin>>x1>>c>>x2;
			d[p[x1]][p[x2]]=c;
		}
		for (k=1;k<=n;k++)
			for (i=1;i<=n;i++)
				for (j=1;j<=n;j++)
					if (d[i][k]*d[k][j]>d[i][j])
						d[i][j]=d[i][k]*d[k][j];
		cout<<"Case "<<++t;
		if (d[1][1]>1)
			cout<<" Yes"<<endl;
		else
			cout<<" No"<<endl;
	}
	return 0;
}
