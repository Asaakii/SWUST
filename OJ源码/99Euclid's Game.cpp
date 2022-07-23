#include<stdio.h>
#include<iostream>

using namespace std;
//简单书写几组数据
//18和45—游戏结束之后时写过的数字是：18、45、27、9、36，共5个
//7和3—游戏结束之后写过的数字是：7、6、5、4、3、2、1，共7个
//8和2—游戏结束之后写过的数字是：8、6、4、2共4个；
//……
//从几组数据观察，可以发现数字的个数和两个数的公因子有关，具体下来就是总共的数字个数是两者中较大数与最大公倍数的商


//求最大公约数
//对2求余，奇数个第一个人胜，反之第二个人胜
int main()
{
	int m,n,a,b;
	cin>>a>>b;
	m=a>b?a:b;
	n=a>b?b:a;
	while(n!=0)
	{
		int tem = m%n;
		m=n;
		n=tem;
	}
	int num = a/m;
	if(num%2==0)
	{
		cout<<"B"<<endl;
	}
	else 
	{
		cout<<"A"<<endl;
	}
	return 0;
}
