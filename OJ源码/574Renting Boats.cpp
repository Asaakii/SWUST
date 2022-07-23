#include<stdio.h>

int f[201][201],n,i,j,k,p,tmp;

void solve() 
{
    for(k=2;k<n;k++)  
        for(i=0;i<n-k;i++) 
        {
            j=i+k; 
            for(p=i+1;p<j;p++) 
            {
                tmp=f[i][p]+f[p][j];  
                if(f[i][j]>tmp)     
                    f[i][j]=tmp;  
            }
        }
}
 
int main() 
{
    while(scanf("%d",&n)!=EOF) 
    {
        for(i=0;i<n;i++)   
        {
            for(j=i+1;j<n;j++)  
                scanf("%d",&f[i][j]); 
        }
        solve();
        printf("%d\n",f[0][n-1]); 
    }
    return 0;
}

/*
3
5 15
7
*/

/*
12
*/