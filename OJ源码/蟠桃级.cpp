#include<stdio.h>
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0||n>30)break;
        int s=1;
        for(n; n>1; n--)
        {
            s=(s+1)*2;
        }
        printf("%d\n",s);
    }
}
