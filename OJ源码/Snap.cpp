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
        a.push_back(s[i]);//�����Ƶ�����
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
        }//��Jane����Ϊ0��
       else if(b.size()==0)
        {
           printf("Jane wins.\n");
           goto out;
        }
        len=min(a.size(),b.size());//����������С��Ϊ׼���бȽ�
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
        if(a.front()==b.front())//�Ƚ���������һ��һ��
        {
            m=(rand()/141)%2;//������˭Snap
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
        a.erase(a.begin());//ɾ����һ��Ԫ�أ�ÿ�Ƚ�һ��ɾ��һ��
        b.erase(b.begin());
    }
    if(a.empty())
        a=c,c.clear();//������ƿ��ˣ��Ͱ����ϵ��Ƹ���
    if(b.empty())
        b=d,d.clear();
    }
    printf("Keeps going and going ...\n");
    out:;
    return 0;
}
