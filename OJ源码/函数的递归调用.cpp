#include <stdio.h>
#include <stdlib.h>
int main()
{
    int val;
    int i,mult=1;
    scanf("%d",&val);
    for(i=1;i<=val;++i)
	{
        mult = mult*i;
    }
    printf("%d\n",mult);
    return 0;
}
