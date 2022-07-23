#include<iostream>
#include<queue>
#include<string.h>
#include<string>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;
const int N=1e3+5;
char mp[N][N];
int flag[N][N];
int n,m;

struct node
{
    int x,y,step;
};

int c[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

void bfs(int x,int y)
{
    queue<node>q;
    node t;
    t.x=x;t.y=y;t.step=0;
    q.push(t);
    while(q.empty()==0)
    {
        t=q.front();
        q.pop();
        if(mp[t.x][t.y]=='E')
        {
            cout<<t.step<<endl;
            return ;
        }
        for(int i=0;i<4;i++)
        {
            node h=t;
            h.x+=c[i][0];
            h.y+=c[i][1];
            h.step++;
            if(h.x>=1&&h.y>=1&&h.x<=n&&h.y<=m&&mp[h.x][h.y]!='#'&&flag[h.x][h.y]==0)
            {
                q.push(h);
                flag[h.x][h.y]=1;
            }
        }
    }
    cout<<"-1"<<endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        int posx,posy;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>mp[i][j];
                if(mp[i][j]=='S')
                {
                    posx=i;posy=j;
                }
            }
        }
        bfs(posx,posy);
    }
}
