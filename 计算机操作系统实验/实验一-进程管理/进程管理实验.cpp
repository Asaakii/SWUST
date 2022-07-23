#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>

using namespace std;

struct Node
{
	char name;//������ 
	int Tarrive;//����ʱ�� 
	int Tservice;//����ʱ�� 
	int Tstart;//��ʼʱ�� 
	int Taccomplish;//���ʱ�� 
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

void fcfs()//FCFS�����㷨 
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
		cout<<"Ŀǰû�н��̣�"<<endl;
	else
	{
		cout << "������" << "\t" << "����ʱ��" << "\t" << "����ʱ��" << "\t" << "��ʼʱ��" << "\t" << "���ʱ��" <<endl; 
		for (int i = 0; i < num; i++){
		cout << job[i].name << "\t" << job[i].Tarrive << "\t\t" << job[i].Tservice << "\t\t"  << job[i].Tstart << "\t\t" << job[i].Taccomplish <<endl;
		}
	}
	cout<<endl;
}

void showdetail()
{
	if(num==0)
		cout<<"Ŀǰû�н��̣�"<<endl;
	else
	{
		cout << "������" << "\t" << "����ʱ��" << "\t" << "����ʱ��" <<endl; 
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
	cout << "������Ҫ�������̵����ƣ�";
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
		cout<<"���̲����ڣ�"<<endl;
	else
		cout<<"���̳����ɹ���"<<endl; 
	cout<<endl;
}

void createpc()
{
	char jname;
	int arrive;
	int service;
	int accomplish;
	cout << "�����������������ʱ�䡢����ʱ��" << endl;
	cin >> jname;
	job[num].name = jname;
	cin >> arrive;
	job[num].Tarrive = arrive;
	cin >> service;
	job[num].Tservice = service;
	num++;
	cout<<"�����Ѵ�����"<<endl;
	cout<<endl;
}

void display()
{
	int ch = 0;
	cout << "��������������������������������������������������" << endl;
	cout << "��������������������1���������� ������������������" << endl;
	cout << "��������������������2�����Ƚ��� ������������������" << endl;
	cout << "��������������������3����ʾ���� ������������������" << endl;
	cout << "��������������������4���������� ������������������" << endl;
	cout << "��������������������0���˳����� ������������������" << endl;
	cout << "��������������������������������������������������" << endl;
	do
	{
		cout << "��ѡ������Ҫ�Ĳ�����" << endl;
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
				cout << "����������������룡" << endl;
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

