#include <stdio.h>
#include <stdlib.h>

struct student
{
    long studentid;
    char classname[32];
    char name[32];
    float score[3];
    float aver;
};
void read(struct student stu[],int n)
{
    int i, j;
    for(i=0; i<n; i++)
    {
        scanf("%ld%s%s", &stu[i].studentid, stu[i].classname, stu[i].name);
        for(j=0; j<3; j++)
        {
            scanf("%f", &stu[i].score[j]);
        }
    }
}
void average(struct student stu[], int n)
{
    int i, j;
    int m;
    for(i=0; i<n; i++)
    {
        m=0;
        for(j=0; j<3; j++)
        {
            m += stu[i].score[j];
        }
        stu[i].aver = m*1.0/3;
    }
}
int paixu(struct student stu[], int n)
{
    int i, x;
    float temp = stu[0].aver;
    for(i=0; i<n; i++)
    {
        if(stu[i].aver > temp)
        {
            temp = stu[i].aver;
            x = i;
        }
    }
    return x;
}
int main()
{
    struct student stu[100];
    int n, i, l;
    scanf("%d", &n);
    read(stu, n);
    average(stu, n);
    for(i=0; i<n; i++)
    {
        printf("%s", stu[i].name);
        printf(" %.1f\n", stu[i].aver);
    }
    l = paixu(stu,n);
    printf("%ld %s %s %.1f %.1f %.1f %.1f", stu[l].studentid,stu[l].classname, stu[l].name, stu[l].score[0], stu[l].score[1], stu[l].score[2], stu[l].aver);
    printf("\n");
    return 0;
}
