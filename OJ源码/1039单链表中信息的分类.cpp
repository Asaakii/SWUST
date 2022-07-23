#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char str[100];
	char a[50],b[50],c[50];
	cin >> str;
	int i,len;
	len=strlen(str);
	int k1=0,k2=0,k3=0;
	for (i=0;i<len;i++)
	{
		if (str[i]>='0'&&str[i]<='9')
			a[k1++]=str[i];
		else if (str[i]>='a'&&str[i]<='z')
			b[k2++]=str[i];
		else
			c[k3++]=str[i];
	}
	for (i=0;i<k1;i++)
			cout << a[i];
		cout << endl;
	for (i=0;i<k2;i++)
			cout << b[i];
		cout << endl;
	for (i=0;i<k3;i++)
			cout << c[i];
		cout << endl;
		return 0;
}
