#include<stdio.h>//排序,赋给数组,外带个计数器;printf
#include<algorithm>

using namespace std;

int a[10000000],b[10000000],c[10000000]={0};//a初始,排序;b去重;c计数
int main()
{
    int i,n,k=-1,max=0;
    a[0]=-2000001;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a,a+n+1);
    for(i=1;i<=n;i++)
    {
        if(a[i]!=a[i-1])
        {
            k++;
            b[k]=a[i];
            c[k]=1;
        }
        else c[k]++;
    }
    for(i=0;i<=k;i++)
    {
        max= (c[i]>c[max]) ? i:max; 
    }
    printf("%d\n",b[max]);
    return 0;
}