#include <stdio.h>
int n;
float english[100],math[100],c[100],music[100],meishu[100];
struct student
{
	long ID;
	float Englishscore;
	float mathscore;
	float Cscore;
	float musicscore;
	float meishuscore;
	float ave;
};
void average1(student stu[])
{
	for (int i=0;i<n;i++)
		stu[i].ave=(stu[i].Cscore+stu[i].Englishscore+stu[i].mathscore+stu[i].meishuscore+stu[i].musicscore)/5;	
}
float average2(float *kemu)
{
	for (int i=0;i<n;i++)
	{
		kemu[0]+=english[i];
		kemu[1]+=math[i];
		kemu[2]+=c[i];
		kemu[3]+=music[i];
		kemu[4]+=meishu[i];
	}
	kemu[0]/=n;
	kemu[1]/=n;
	kemu[2]/=n;
	kemu[3]/=n;
	kemu[4]/=n;
}
int main()
{
	float average[5]={0};
	scanf ("%d",&n);
	student stu[100];
	for (int i=0;i<n;i++)
	{
		scanf ("%ld%f%f%f%f%f",&stu[i].ID,&stu[i].Englishscore,&stu[i].mathscore,&stu[i].Cscore,&stu[i].musicscore,&stu[i].meishuscore);
		english[i]=stu[i].Englishscore;
		math[i]=stu[i].mathscore;
		c[i]=stu[i].Cscore;
		music[i]=stu[i].musicscore;
		meishu[i]=stu[i].meishuscore;
	}
	average1(stu);
	average2(average);
	for (int i=0;i<n;i++)
		printf ("%ld %g %g %g %g %g %.1f\n",stu[i].ID,stu[i].Englishscore,stu[i].mathscore,stu[i].Cscore,stu[i].musicscore,stu[i].meishuscore,stu[i].ave);
	printf ("%.1f %.1f %.1f %.1f %.1f\n",average[0],average[1],average[2],average[3],average[4]);
	return 0;	
 } 
