#include <iostream>
#include <cstring>
#include <cstdio>

#define MX 55
#define oo 10020123
#define MD 100000007

using namespace std;

typedef long long ll;

ll qpw(ll x,ll t){ll ans=1;for(int i=1;i<=t;i++)ans=ans*x%MD;return ans;}

ll calc(char *str,int l,int r,ll a)
{
    int prio=0,mnpos=MX,mn=+oo,cnt=0,p[MX],num=0;
    memset(p,0x3f,sizeof(p));
    for(int i=r;i>=l;i--)
    {
        if(str[i]==')')prio+=100;
        if(str[i]=='(')prio-=100;
        if(str[i]=='^')p[i]=prio+3,cnt++;
        if(str[i]=='*')p[i]=prio+2,cnt++;
        if(str[i]=='+')p[i]=prio+1,cnt++;
        if(str[i]=='-')p[i]=prio+1,cnt++;
        if(mn>p[i])mn=p[i],mnpos=i;
    }
    if(cnt==0)
    {
        for(int i=l;i<=r;i++)if(str[i]=='a')return a;
        for(int i=l;i<=r;i++)if(isdigit(str[i]))num=num*10+str[i]-'0';
        return num;
    }
    else
    {
        if(str[mnpos]=='^')return qpw(calc(str,l,mnpos-1,a),calc(str,mnpos+1,r,a));
        if(str[mnpos]=='*')return (calc(str,l,mnpos-1,a)*calc(str,mnpos+1,r,a))%MD;
        if(str[mnpos]=='+')return (calc(str,l,mnpos-1,a)+calc(str,mnpos+1,r,a))%MD;
        if(str[mnpos]=='-')return (calc(str,l,mnpos-1,a)-calc(str,mnpos+1,r,a))%MD;
    }
    return 0;
}

int main()
{
    int len[27],n,ans[15];
    char str[27][MX];  
	cin.getline(str[0],MX);  
    len[0]=strlen(str[0]);
    scanf("%d",&n),getchar();
    for(int i=1;i<=n;i++)
    {
    	cin.getline(str[i],MX);
        len[i]=strlen(str[i]);
    }
    for(int i=0;i<=10;i++)ans[i]=calc(str[0],0,len[0]-1,i-5);
    for(int i=1;i<=n;i++)
    {
        int f=1;
        for(int j=0;j<=10;j++)
            if(ans[j]!=calc(str[i],0,len[i]-1,j-5))
                {f=0;break;}
        if(f)printf("%c",'A'+i-1);
    }
    return 0;
}
