#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 100010

using namespace std;

int n,k,f[N],s[N],p[N],t[N];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&p[i],&t[i]);
        s[p[i]]++;
    }   
    for(int i=n;i>=1;i--)
    {
        if(s[i]==0) f[i]=f[i+1]+1;
        else
        {
            for(int j=1;j<=k;j++)	
            {
                if(p[j]==i)
                    f[i]=max(f[i],f[i+t[j]]);
            }
        }
    }
    cout<<f[1]<<endl;
}

