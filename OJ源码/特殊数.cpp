#include<stdio.h>
#include<string.h>
int vis[12];
int n,leap;
void DFS(int index,int num)//index用来记录现在的位数，num用来记录index-1位的值
{
    int i;
    if(leap)return;
    if(index==n+1)
    {
        printf("%d\n",num);
        leap=1;
        return;
    }
    for(i=1;i<=9;i++)
    {
        if(leap)
			break;
        if(vis[i]==0&&(10*num+i)%index==0)
        {
        	vis[i]=1;
        	DFS(index+1,10*num+i);
        	vis[i]=0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    leap=0;
    memset(vis,0,sizeof(vis));
    DFS(1,0);
    return 0;
}
