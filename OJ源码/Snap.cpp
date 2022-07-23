#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;
vector<char> a,b,c,d;
int main()
{
    int i,n,m,len;
    char s[2017];
    a.clear();
    b.clear();
    c.clear();
    d.clear();
    scanf("%s",s);
    for(i=0;s[i]!='\0';i++)
        a.push_back(s[i]);//输入牌的种类
    scanf("%s",s);
    for(i=0;s[i]!='\0';i++)
        b.push_back(s[i]);
    vector<char>::iterator it;
    for(i=0;i<1000;i++)
    {
        if(a.size()==0)
        {
            printf("John wins.\n");
            goto out;
        }//当Jane手牌为0了
       else if(b.size()==0)
        {
           printf("Jane wins.\n");
           goto out;
        }
        len=min(a.size(),b.size());//手牌数量以小的为准进行比较
        while(len--)
        {
        if(a.size()==0)
        {
            printf("John wins.\n");
            goto out;
        }
       else if(b.size()==0)
        {
           printf("Jane wins.\n");
           goto out;
        }
        c.push_back(a.front());
        d.push_back(b.front());
        if(a.front()==b.front())//比较两个手牌一不一样
        {
            m=(rand()/141)%2;//决定是谁Snap
            if(m==0)
            {
                c.insert(c.end(),d.begin(),d.end());
                d.clear();
                n=0;
                for(it=c.begin();it!=c.end();it++)
                {
                    s[n++]=*it;
                }
                printf("Snap! for Jane: ");
                while(n--)
                    printf("%c",s[n]);
                printf("\n");
            }
            else
            {
                d.insert(d.end(),c.begin(),c.end());
                c.clear();
                n=0;
                for(it=d.begin();it!=d.end();it++)
                {
                    s[n++]=*it;
                }
                printf("Snap! for John: ");
                while(n--)
                    printf("%c",s[n]);
                printf("\n");
            }
        }
        a.erase(a.begin());//删除第一个元素，每比较一次删除一次
        b.erase(b.begin());
    }
    if(a.empty())
        a=c,c.clear();//如果手牌空了，就把桌上的牌给他
    if(b.empty())
        b=d,d.clear();
    }
    printf("Keeps going and going ...\n");
    out:;
    return 0;
}
