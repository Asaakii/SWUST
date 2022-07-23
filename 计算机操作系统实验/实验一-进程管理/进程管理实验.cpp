#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>

using namespace std;

struct Node
{
	char name;//进程名 
	int Tarrive;//到达时间 
	int Tservice;//服务时间 
	int Tstart;//开始时间 
	int Taccomplish;//完成时间 
}job[10];

int num=0;

void Arrive_sort()
{
	int temp1,temp2,temp3;
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (job[i].Tarrive > job[j].Tarrive)
			{
				temp1 = job[j].name;
				job[j].name = job[i].name;
				job[i].name = temp1;
				temp2 = job[j].Tarrive;
				job[j].Tarrive = job[i].Tarrive;
				job[i].Tarrive = temp2;
				temp3 = job[j].Tservice;
				job[j].Tservice = job[i].Tservice;
				job[i].Tservice = temp3;
			}
		}
	}
}

void fcfs()//FCFS调度算法 
{
	for (int i = 0; i < num; i++)
	{
		job[i].Tstart = job[i - 1].Taccomplish;
		if (job[i].Tstart < job[i].Tarrive)
		{
			job[i].Tstart = job[i].Tarrive;
		}
		else
		{
			job[i].Tstart = job[i - 1].Taccomplish;
		}
		job[i].Taccomplish = job[i].Tstart + job[i].Tservice;
	}
}

void print()
{
	if(num==0)
		cout<<"目前没有进程！"<<endl;
	else
	{
		cout << "进程名" << "\t" << "到达时间" << "\t" << "服务时间" << "\t" << "开始时间" << "\t" << "完成时间" <<endl; 
		for (int i = 0; i < num; i++){
		cout << job[i].name << "\t" << job[i].Tarrive << "\t\t" << job[i].Tservice << "\t\t"  << job[i].Tstart << "\t\t" << job[i].Taccomplish <<endl;
		}
	}
	cout<<endl;
}

void showdetail()
{
	if(num==0)
		cout<<"目前没有进程！"<<endl;
	else
	{
		cout << "进程名" << "\t" << "到达时间" << "\t" << "服务时间" <<endl; 
		for (int i = 0; i < num; i++)
		{
			cout << job[i].name << "\t" << job[i].Tarrive << "\t\t" << job[i].Tservice <<endl;
		}
	}
	cout<<endl;
}

void Delete()
{
	char name;
	int count=0;
	cout << "请输入要撤销进程的名称：";
	cin >> name;
	for(int i = 0; i < num; i++)
	{
		if(name==job[i].name)
		{
			for(int j=i;j<num;j++)
			{
				job[j]=job[j+1];
			}
			num--;
			count++;
		}
	}
	if(count==0)
		cout<<"进程不存在！"<<endl;
	else
		cout<<"进程撤销成功！"<<endl; 
	cout<<endl;
}

void createpc()
{
	char jname;
	int arrive;
	int service;
	int accomplish;
	cout << "请输入进程名、到达时间、服务时间" << endl;
	cin >> jname;
	job[num].name = jname;
	cin >> arrive;
	job[num].Tarrive = arrive;
	cin >> service;
	job[num].Tservice = service;
	num++;
	cout<<"进程已创建！"<<endl;
	cout<<endl;
}

void display()
{
	int ch = 0;
	cout << "—————————————————————————" << endl;
	cout << "——————————1、创建进程 —————————" << endl;
	cout << "——————————2、调度进程 —————————" << endl;
	cout << "——————————3、显示进程 —————————" << endl;
	cout << "——————————4、撤销进程 —————————" << endl;
	cout << "——————————0、退出进程 —————————" << endl;
	cout << "—————————————————————————" << endl;
	do
	{
		cout << "请选择你想要的操作：" << endl;
		cin >> ch;
		switch (ch)
		{
			case 1:
				createpc();
				break;
			case 2:
				Arrive_sort();
				fcfs();
				print();
				break;
			case 3:
				showdetail();
				break;
			case 4:
				Delete();
				break;
			case 0:
				exit(0);
			default:
				cout << "输入错误，请重新输入！" << endl;
				break;
		}
	}
	while (ch != 0);
}

int main()
{
	display();
	return 0;
}

