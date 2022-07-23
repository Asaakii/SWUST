#include <iostream>
#include <string.h>

using namespace std;

int minDistance(char word1[],char word2[])
{
	int n=strlen(word1);
	int m=strlen(word2);
	if (n*m==0)
		return n+m;
	int D[n+1][m+1];
	for (int i=0;i<n+1;i++)
	{
		D[i][0]=i;
	}
	for (int j=0;j<m+1;j++)
	{
		D[0][j]=j;
	}
	for (int i=1;i<n+1;i++)
	{
		for (int j=1;j<m+1;j++)
		{
			int left=D[i-1][j]+1;
			int down=D[i][j-1]+1;
			int left_down=D[i-1][j-1];
			if (word1[i-1]!=word2[j-1])
				left_down+=1;
			D[i][j]=min(left,min(down,left_down));
		}
	}
	return D[n][m];
}

int main()
{
	int ans=0;
	char str1[2000],str2[2000];
	scanf ("%s %s",&str1,&str2);
	ans=minDistance(str1,str2);
	cout<<ans<<endl;
	return 0;
}

/*
fxpimu
xwr
*/

/*
5
*/