#include<iostream>
#include<cstdio>

using namespace std ;

int book[1500][1500];
 
int sum ;
void dfs(int x ,int y)
{
	if(book[x][y]==1)
	{
	
		book[x][y] =0 ;
			sum++; 
		dfs(x,y+1);
		dfs(x,y-1);
		dfs(x+1,y);
		dfs(x-1,y);
	}
	else if(book[x][y]==0)
	return ;
}

int main()
{
	int w ,h ;
	int i , j ,k ;
	
	char a[1000][100];
	int max ;
	char con;  
	sum = 0;
	cin>>w>>h;
	for(i=1;i<=h;i++)
	{
		for(j=1; j<=w ;j++)
		{
			cin>> a[i][j] ;  
			if(a[i][j]=='*')
			{
				book[i][j] = 1 ;
			}
			else
			book[i][j] = 0;	 
		}
	}
	max = 0 ; 
	for(i=1;i<=h;i++)
	{
		for(j=1; j<=w ;j++)
		{		
			if(a[i][i]=='*')
			{
				sum = 0;
				dfs(i,j);/*从二维数字第一个  '*'  开始深搜*/
				if(sum>=max)//更新最大值 
				max= sum ;
			}
			 
		}
	}
	cout<<max;
	return 0 ;
}
