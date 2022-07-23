#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

struct node
{
    int x,y;
}a[1000000];
bool cmp(node x,node y)
{
    return x.y>y.y;
}
int main()
{
    int num;
    scanf("%d",&num);
    int i;
    for(i=0;i<num;i++)
    {
        scanf("%d %d",&a[i].x,&a[i].y);
    }
    sort(a,a+num,cmp);
    if(num/2==0)
        printf("0\n");
    else 
    {
        int k=a[num/2].y;
        int sum=0;
        for(i=0;i<num;i++)
        {
            if(a[i].y-k>=0)
                sum+=a[i].y-k;
            else sum+=-(a[i].y-k);
        }
        printf("%d\n",sum);
    }
    return 0;
}

