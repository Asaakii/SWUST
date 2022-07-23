#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1010;
struct snake
{
	double x,y,r;
}s[MAXN];
 
struct node 
{
	double up,down;
	int index;
}l[MAXN],r[MAXN];
 
int n;
bool map[MAXN][MAXN];
int fa[MAXN];
int lcnt=0,rcnt=0;
double lans=-1,rans=-1;
double lup=1000,ldown=0,rup=1000,rdown=0;
//lup表示左边界可用区间的最高点，ldown左边界可用区间的最低点
 
int find(int x)
{
	if(x==fa[x])	return fa[x];
	return fa[x]=find(fa[x]);
}
 
bool check(node t[],double x,int n)
{
	for(int i=0;i<n;i++)
		if(t[i].up>x && t[i].down<x)	return false;
	return true;
}
 
void readdate()
{
	cin>>n;
	memset(map,0,sizeof(map));
	for(int i=0;i<MAXN;i++)	fa[i]=i;
	
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&s[i].x,&s[i].y,&s[i].r);
		
		if(s[i].y+s[i].r>1000)	map[0][i]=map[i][0]=true;
		
		if(s[i].y-s[i].r<0)		map[n+1][i]=map[i][n+1]=true;
				
		//与左边界的关系
		if(s[i].x-s[i].r<0)
		{
			l[lcnt].up=s[i].y+sqrt(s[i].r*s[i].r-s[i].x*s[i].x);
			l[lcnt].down=s[i].y-sqrt(s[i].r*s[i].r-s[i].x*s[i].x);
			l[lcnt++].index=i;
		}
		
		//与右边界的关系
		if(s[i].x+s[i].r>1000)
		{
			r[rcnt].up=s[i].y+sqrt(s[i].r*s[i].r-(1000-s[i].x)*(1000-s[i].x));
			r[rcnt].down=s[i].y-sqrt(s[i].r*s[i].r-(1000-s[i].x)*(1000-s[i].x));
			r[rcnt++].index=i;
		}
	}
	
	return;
}
void work()
{
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(s[i].r+s[j].r > sqrt((s[i].x-s[j].x)*(s[i].x-s[j].x)+(s[i].y-s[j].y)*(s[i].y-s[j].y)))
				map[i][j]=map[j][i]=true;
		}
		
	for(int i=0;i<=n;i++)
		for(int j=i+1;j<=n+1;j++)
		{
			if(map[i][j])
			{
				int x=find(i);
				int y=find(j);
				if(x!=y)	fa[y]=x;
			}
		}
	return;
}
 
void solve_l()
{
	//找出可用区间(ldown,lup),因为如果find(a)==find(0)
	
	//圆a又与左边界相交，相交部分到最高点1000,都是不可用的
	
	for(int i=0;i<lcnt;i++)
	{
		if(find(l[i].index)==find(0) && l[i].down<lup)
			lup=l[i].down;
			
		if(find(l[i].index)==find(n+1) && l[i].up>ldown)
			ldown=l[i].up;
	}
	
	//判断最高点1000是否可用，如果在圆和左边界相交区域则不可用
	
	if(check(l,1000,lcnt) && lup==1000)	lans=1000;
	
	//最高点一定坐落在左边界的最高点或与圆的交点
	
	//所以判断交点是否在可用区间，判断交点是否可用，判断lans是否值得替换
	
	for(int i=0;i<lcnt;i++)
	{
		if(l[i].up<=lup && l[i].up>=ldown && check(l,l[i].up,lcnt) && lans<l[i].up)
		{
			lans=l[i].up;
		}
		if(l[i].down<=lup && l[i].down>=ldown && check(l,l[i].down,lcnt) && lans<l[i].down)
		{
			lans=l[i].down;
		}
	}
	return;
}
 
void solve_r()
{
	//找出可用区间(rdown,rup),因为如果find(a)==find(0)
	
	//圆a又与右边界相交，相交部分到最高点1000,都是不可用的
	
	for(int i=0;i<rcnt;i++)
	{
		if(find(r[i].index)==find(0) && r[i].down<rup)
			rup=r[i].down;
			
		if(find(r[i].index)==find(n+1) && r[i].up>rdown)
			rdown=l[i].up;
	}
	
	//判断最高点1000是否可用，如果在圆和右边界相交区域则不可用
	
	if(check(r,1000,rcnt) && rup==1000)	rans=1000;
	
	//最高点一定坐落在右边界的最高点或与圆的交点
	
	//所以判断交点是否在可用区间，判断交点是否可用，判断rans是否值得替换
	for(int i=0;i<rcnt;i++)
	{
		if(r[i].up<=rup && r[i].up>=rdown && check(r,r[i].up,rcnt) && rans<r[i].up)
			rans=r[i].up;
		if(r[i].down<=rup && r[i].down>=rdown && check(r,r[i].down,rcnt) && rans<r[i].down)
			rans=r[i].down;
	}
	return;
}
 
int main()
{
	readdate();
	work();
	if(find(n+1)==find(0))	printf("Bill will be bitten.\n");
	else
	{
		
		solve_l();
		
		solve_r();
		
		if(lcnt==0)	lans=1000;
		
		if(rcnt==0)	rans=1000;
		
		if(rans<0||lans<0)
			printf("Bill will be bitten.\n");
		else
			printf("Bill enters at (0.00, %.2lf) and leaves at (1000.00, %.2lf).\n",lans,rans);
				//	Bill enters at (0.00, 1000.00) and leaves at (1000.00, 800.00).
	}
	return 0;
}
