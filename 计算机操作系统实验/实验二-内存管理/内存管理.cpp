#include<iostream>
#include<stdlib.h>

using namespace std;

#define Free 0//空闲状态
#define Busy 1//已用状态
#define Notfree 2
#define OK 1//完成
#define ERROR 0//出错
#define MAX_length 65536//最大内存空间为64M

typedef int Status;
int flag;

typedef struct freearea//定义一个空闲区说明表结构
{
    long size;//分区大小
    long address;//分区地址
    int state;//状态
}ElemType;

//线性表的双向链表存储结构
typedef struct DuLNode
{
    ElemType data;
    struct DuLNode*prior;//前趋指针
    struct DuLNode*next;//后继指针
}

DuLNode,*DuLinkList;
DuLinkList block_first;//头结点
DuLinkList block_last;//尾结点
Status alloc(int);//内存分配
Status free(int);//内存回收
Status FF(int);//首次适应算法
Status NF(int);//循环首次适应算法
Status BF(int);//最佳适应算法
void show();//查看分配

Status Initblock();//开创空间表
Status Initblock()//开创带头结点的内存空间链表
{
    block_first=(DuLinkList)malloc(sizeof(DuLNode));
    block_last=(DuLinkList)malloc(sizeof(DuLNode));
    block_first->prior=NULL;
    block_first->next=block_last;
    block_last->prior=block_first;
    block_last->next=NULL;
    block_last->data.address=0;
    block_last->data.size=MAX_length;
    block_last->data.state=Notfree;
    return OK;
}

Status NotFree(int i,int j)
{
    DuLinkList temp=(DuLinkList)malloc(sizeof(DuLNode));
    static DuLNode *p=block_first->next;
    temp->data.size=i;
    temp->data.state=Free;
    temp->prior=p->prior;
    temp->next=p;
    temp->data.address=j;
    p->prior->next=temp;
    p->prior=temp;
    p->data.address=temp->data.address+temp->data.size;
    p->data.size-=i;
    
    temp->next=block_last;
    block_last->prior=temp;
    return OK;
}

//分配主存
Status alloc(int ch)
{
    int request=0;
    cout<<"请输入需要分配的主存大小(单位:KB)：";
    cin>>request;
    if(request<0||request==0)
    {
        cout<<"分配大小不合适，请重试！"<<endl;
        return ERROR;
    }
    if(ch==2)//选择首次循环适应算法
    {
        if(NF(request)==OK)
            cout<<"分配成功！"<<endl;
        else
            cout<<"内存不足，分配失败！"<<endl;
        return OK;
    }
    if(ch==3)//选择最佳适应算法
    {
        if(BF(request)==OK)
            cout<<"分配成功！"<<endl;
        else
            cout<<"内存不足，分配失败！"<<endl;
        return OK;
    }
    else//默认首次适应算法
    {
        if(FF(request)==OK)
            cout<<"分配成功！"<<endl;
        else
            cout<<"内存不足，分配失败！"<<endl;
        return OK;
    }
}

//首次适应算法
Status FF(int request)
{   //为申请作业开辟新空间且初始化
    DuLinkList temp=(DuLinkList)malloc(sizeof(DuLNode));
    temp->data.size=request;
    temp->data.state=Busy;
    DuLNode *p=block_first->next;
    while(p)
    {
        if(p->data.state==Free&&p->data.size==request)
        {   //有大小恰好合适的空闲块
            p->data.state=Busy;
            return OK;
            break;
        }
        if(p->data.state==Free&&p->data.size>request)
        {   //有空闲块能满足需求且有剩余
            temp->prior=p->prior;
            temp->next=p;
            temp->data.address=p->data.address;
            p->prior->next=temp;
            p->prior=temp;
            p->data.address=temp->data.address+temp->data.size;
            p->data.size-=request;
            return OK;
            break;
        }
        p=p->next;
    }
    return ERROR;
}

//循环首次适应算法
Status NF(int request)
{   //为申请作业开辟新空间且初始化
    DuLinkList temp=(DuLinkList)malloc(sizeof(DuLNode));
    temp->data.size=request;
    temp->data.state=Busy;
    static DuLNode *p=block_first->next;//static其值在下次调用时仍维持上次的值
    if(p->data.size<request)
        p=block_first->next;
    while(p)
    {
        if(p->data.state==Free&&p->data.size==request)
        {//有大小恰好合适的空闲块
            p->data.state=Busy;
            return OK;
            break;
        }
        if(p->data.state==Free&&p->data.size>request)
        {//有空闲块能满足需求且有剩余
            temp->prior=p->prior;
            temp->next=p;
            temp->data.address=p->data.address;
            p->prior->next=temp;
            p->prior=temp;
            p->data.address=temp->data.address+temp->data.size;
            p->data.size-=request;
            return OK;
            break;
        }
        p=p->next;
    }
    return ERROR;
}

//最佳适应算法
Status BF(int request)
{
    int ch;//记录最小剩余空间
    DuLinkList temp=(DuLinkList)malloc(sizeof(DuLNode));
    temp->data.size=request;
    temp->data.state=Busy;
    DuLNode *p=block_first->next;
    DuLNode *q=NULL;//记录最佳插入位置
    while(p)//初始化最小空间和最佳位置
    {
        if(p->data.state==Free&&(p->data.size>=request)){
            if(q==NULL)
            {
                q=p;
                ch=p->data.size-request;
            }
            else if(q->data.size>p->data.size)
            {
                q=p;
                ch=p->data.size-request;
            }
        }
        p=p->next;
    }
    if(q==NULL)
        return ERROR;//没有找到空闲块
    else if(q->data.size==request)
    {
        q->data.state=Busy;
        return OK;
    }
    else
    {
        temp->prior=q->prior;
        temp->next=q;
        temp->data.address=q->data.address;
        q->prior->next=temp;
        q->prior=temp;
        q->data.address+=request;
        q->data.size=ch;
        return OK;
    }
    return OK;
}

//主存回收
Status free(int flag)
{
    DuLNode *p=block_first;
    for(int i=0;i<=flag;i++)
        if(p!=NULL)
            p=p->next;
        else
            return ERROR;
    p->data.state=Free;
    if(p->prior!=block_first&&p->prior->data.state==Free&&p->data.address==p->prior->data.address+p->prior->data.size)//与前面的空闲块相连
    {
        p->prior->data.size+=p->data.size;
        p->prior->next=p->next;
        p->next->prior=p->prior;
        p=p->prior;
    }
    if(p->next!=block_last&&p->next->data.state==Free&&p->next->data.address==p->data.address+p->data.size)//与后面的空闲块相连
    {
        p->data.size+=p->next->data.size;
        p->next->next->prior=p;
        p->next=p->next->next;
    }
    if(p->next==block_last&&p->next->data.state==Free)//与最后的空闲块相连
    {
        p->data.size+=p->next->data.size;
        p->next=NULL;
    }
    return OK;
}

//显示主存分配情况
void show()
{
    int flag=0;
    cout<<"\n主存分配情况:\n";
    cout<<"**********************************************\n\n";
    DuLNode *p=block_first->next;
    cout<<"分区号\t起始地址\t分区大小\t状态\n\n";
    while(p)
    {
        if(p->data.state==Notfree)
            p=p->next;
        else
        {   
            if(p->data.state==Busy)
                cout<<""<<flag++<<"\t";
            else
            {
                cout<<"\t";
                flag++;
            }
            cout<<""<<p->data.address<<"\t\t";
            cout<<""<<p->data.size<<"KB\t\t";
            if(p->data.state==Free)
                cout<<"空闲\n\n";
            else
                cout<<"已分配\n\n";
            p=p->next;
        }
    }
    cout<<"*********************************************\n\n";
}

//主函数
int main()
{
    int ch;//算法选择标记
    int i,j,n;
    Initblock();//开创空间表
    cout<<"请输入空闲区的个数:"<<endl;
    cin>>n;
    cout<<"请依次输入空闲区大小和始址（空格键分开）:"<<endl;
    for(int k=0;k<n;k++)
    {
        cin>>i>>j;//键盘输入i,j值
        NotFree(i,j);
    }
    cout<<"请选择内存分配算法：(选择1~3输入)\n";
    cout<<"1.首次适应算法\n2.循环首次适应算法\n3.最佳适应算法\n";
    cin>>ch;
    while(ch<1||ch>3)
    {
        cout<<"输入错误，请重新选择内存分配算法：\n";
        cin>>ch;
    }
    int choice;//操作选择标记
    while(1)
    {
        show();
        cout<<"请输入要进行的操作：(选择0~2输入)";
        cout<<"\n1:分配内存\n2:回收内存\n0:退出\n";
        cin>>choice;
        if(choice==1)
        {
            cout<<"请输入要分配的内存个数:"<<endl;
            cin>>n;
            cout<<"请依次输入其大小,"<<endl;
            for(int k=0;k<n;k++)
            {
                alloc(ch);//分配内存
            }
        }
        else if(choice==2)//内存回收
        {
            int flag;
            cout<<"请输入要回收的分区号：";
            cin>>flag;
            free(flag);
        }
        else if(choice==0)
            break;//退出
        else//输入操作有误
        {
            cout<<"输入有误，请重试！"<<endl;
            continue;
        }
    }
}
