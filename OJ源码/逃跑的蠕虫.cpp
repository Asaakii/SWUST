#include<iostream>
using namespace std;
int main()
{
	int n,u,d;  //n表示要爬的高度,u表示每分钟爬的高度,d表示每爬完一分钟后休息的一分钟内下滑的高度
	while(cin>>n>>u>>d)
	{
		if(n==0)   //n=0时结束
			break;
		int min;   //记录所花的时间
		int dis=0;  //记录已爬的高度
		for(min=1;;min++)
		{
			//先爬一分钟,再休息一分钟
			if(min%2==0)  
			{
				dis-=d;
			}
			else
			{
				dis+=u;
				if(dis>=n) //如果达到了高度n,结束
					break;
			}
		}
		cout<<min<<endl;
	}
	return 0;
}
