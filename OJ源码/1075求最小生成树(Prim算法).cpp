#include<iostream>
#include<stdio.h>
using namespace std;
#define INF 0xfffffff
typedef struct
{
    int n;
    int e;
    char data[500];
    int edge[500][500];
} Graph;

typedef struct
{
    int index;
    int cost;
} mincost;

typedef struct
{
    int x;
    int y;
    int weight;
} EDGE;

typedef struct
{
    int index;
    int flag;
} F;

void create(Graph &G,int n,int e)
{
    int i,j,k,w;
    char a,b;
    for(i=0; i< n; i++)
        cin>>G.data[i];
    for(i=0; i< n; i++)
        for(j=0; j< n; j++)
        {
            if(i==j)
                G.edge[i][j]=0;
            else
                G.edge[i][j]=100;
        }
    for(k=0; k< e; k++)
	{
        cin>>a;
        cin>>b;
        cin>>w;
        for(i=0; i< n; i++)
            if(G.data[i]==a)
                break;
        for(j=0; j< n; j++)
            if(G.data[j]==b)
                break;
        G.edge[i][j]=w;
        G.edge[j][i]=w;
    }
    G.n=n;
    G.e=e;
}

void Prim(Graph &G,int v,int n)
{
    int lowcost[n],Min,closest[n],k;
    for(int i=0;i<G.n;i++)
	{
        lowcost[i]=G.edge[v][i];
        closest[i]=v;
    }

    for(int i=1;i<G.n;i++)
	{
        Min=INF;
        for(int j=0;j<G.n;j++)
            if(lowcost[j]&&lowcost[j]<Min)
			{
                Min=lowcost[j];
                k=j;
            }
        printf("(%c,%c)",G.data[closest[k]],G.data[k]);
        lowcost[k]=0;
        for(int j=0;j<G.n;j++)
        if(lowcost[j]&&G.edge[k][j]<lowcost[j])
		{
            lowcost[j]=G.edge[k][j];
            closest[j]=k;
        }
    }
}

int main()
{
    Graph my;
    int n,e;
    cin>>n>>e;
    create(my,n,e);
    Prim(my,0,n);
    return 0;
}
