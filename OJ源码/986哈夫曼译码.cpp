const int maxvalue=100;
const int maxbit=100;
const int maxn=100;
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "string.h" 
using namespace std;
struct haffnode
{
    char ch;
    int weight;
    int flag;
    int parent;
    int leftchild;
    int rightchild;
};
struct code
{
    int bit[maxn];
    int start;
    int weight;
    char ch;
};
void haffman(int weight[],char text[],int n,haffnode hafftree[])
{
    int j,m1,m2,x1,x2,i;
    for(i=0; i< 2*n-1; i++)
    {
        if(i < n)
        {
            hafftree[i].weight=weight[i];
            hafftree[i].
            ch=text[i];
        }
        else
        {
            hafftree[i].weight=0;
            hafftree[i].ch='#';
        }
        hafftree[i].parent=0;
        hafftree[i].flag=0;
        hafftree[i].leftchild=-1;
        hafftree[i].rightchild=-1;
    }
    for(i=0; i< n-1; i++)
    {
        m1=m2=maxvalue;
        x1=x2=0;
        for(j=0; j< n+i; j++)
        {
            if(hafftree[j].weight< m1&&hafftree[j].flag==0)
            {
                m2=m1;
                x2=x1;
                m1=hafftree[j].weight;
                x1=j;
            }
            else if(hafftree[j].weight< m2&&hafftree[j].flag==0)
            {
                m2=hafftree[j].weight;
                x2=j;
            }
        }
        hafftree[x1].parent=n+i;
        hafftree[x2].parent=n+i;
        hafftree[x1].flag=1;
        hafftree[x2].flag=1;
        hafftree[n+i].weight=hafftree[x1].weight+hafftree[x2].weight;
        hafftree[n+i].leftchild=x1;
        hafftree[n+i].rightchild=x2;
    }
}
void haffmancode(haffnode hafftree[],int n,code haffcode[])
{
    code cd;
    int i,j;
    int child,parent;
    for( i=0; i< n; i++)
    {
        cd.start=n-1;
        cd.weight=hafftree[i].weight;
        cd.ch=hafftree[i].ch;
        child=i;
        parent=hafftree[child].parent;
        while(parent!=0)
        {
            if(hafftree[parent].leftchild==child)
                cd.bit[cd.start]=0;
            else
                cd.bit[cd.start]=1;
            cd.start--;
            child=parent;
            parent=hafftree[child].parent;
        }
        for(j=cd.start+1; j< n; j++)
            haffcode[i].bit[j]=cd.bit[j];
        haffcode[i].start=cd.start;
        haffcode[i].weight=cd.weight;
        haffcode[i].ch=cd.ch;
    }
}
void ccode(haffnode hafftree[],int n)
{
    int i,j=0,m=2*n-1;
    char b[maxn];
    memset(b,'\0',sizeof(b));
    i=m-1;                      
    scanf("%s",b);
    while(b[j]!='\0')
    {
        if(b[j]=='0')
            i=hafftree[i].leftchild;              
        else
            i=hafftree[i].rightchild;              
        if(hafftree[i].leftchild==-1)         
        {
            printf("%c",hafftree[i].ch);
            i=m-1;      
        }
        j++;
    }
}
int main( )
{
    int n=8;
    int weight[]= {5,29,7,8,14,23,3,11};
    char text[]= {'a','b','c','d','e','f','g','h'};
    haffnode myhafftree[maxvalue];
    code myhaffcode[maxvalue];
    haffman(weight,text,n,myhafftree);
    haffmancode(myhafftree,n,myhaffcode);
    ccode(myhafftree,n);
    return 0;
}
