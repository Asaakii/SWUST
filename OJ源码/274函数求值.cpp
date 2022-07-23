#include<iostream>

#define LL long long

using namespace std;

LL n,a;
LL fun(const LL x)
{
    if(x==0) return 0;
    if(x%2==1) return (x+1)*(x+1)/4+fun(x/2);
    else return x*x/4+fun(x/2);
}

int main()
{
    while(cin>>n)
    {
        cout<<fun(n)<<endl;
    }
    return 0;
}
