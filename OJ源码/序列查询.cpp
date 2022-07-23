#include<stdio.h>
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int a[n];
    int i,sum=0;
    for(i=0; i<n; i++)
    {
        scanf("%d",&a[i]);
    }
    if(m>=a[n-1])
    {
        for(i=1; i<n; i++)
            sum+=(a[i]-a[i-1])*i;
        sum+=(m-a[n-1])*n;
    }
    else
    {
        for(i=1; a[i]<=m; i++)
            sum+=(a[i]-a[i-1])*i;
        sum+=(m-a[i])*i;
    }
 
    printf("%d",sum);
    return 0;
}
