#include<iostream>
using namespace std;
int main()
{
	int n,u,d;  //n��ʾҪ���ĸ߶�,u��ʾÿ�������ĸ߶�,d��ʾÿ����һ���Ӻ���Ϣ��һ�������»��ĸ߶�
	while(cin>>n>>u>>d)
	{
		if(n==0)   //n=0ʱ����
			break;
		int min;   //��¼������ʱ��
		int dis=0;  //��¼�����ĸ߶�
		for(min=1;;min++)
		{
			//����һ����,����Ϣһ����
			if(min%2==0)  
			{
				dis-=d;
			}
			else
			{
				dis+=u;
				if(dis>=n) //����ﵽ�˸߶�n,����
					break;
			}
		}
		cout<<min<<endl;
	}
	return 0;
}
