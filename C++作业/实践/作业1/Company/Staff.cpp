#include<iostream>
#include<string>

#include "Staff.h"

using namespace std;

//输入员工信息
Staff::Staff()//构造
{
    cout << "请输入员工信息" << endl;

    cout << "员工姓名: " << endl;
    cin >> name;

    cout << "员工年龄: " << endl;
    cin >> age;

    cout << "员工性别:" << endl;
    cin >> sex;

    cout << "员工身份证号: " << endl;
    cin >> id;

    cout << "员工工号: " << endl;
    cin >> worknumber;

    cout << "员工工资: " << endl;
    cin >> salary;
}

void Staff::show_staff()//输出已建立的员工信息
{
    cout << "姓名: " << name << endl << "年龄: " << age << endl << "性别:" << sex << endl << "身份证号: " << id << endl << "工号: " << worknumber << endl << "工资: " << salary << '\b' << endl;
}

float Staff::get_salary()       //获取每个员工的工资
{
    return salary;
}

string Staff::get_name()        //获取每个员工的姓名
{
    return name;
}

int Staff::get_age()            //获取每个员工的年龄
{
    return age;
}

string Staff::get_sex()         //获取每个员工的性别
{
    return sex;
}

string Staff::get_id()          //获取每个员工的身份证号
{
    return id;
}

string Staff::get_worknumber()  //获取每个员工的工号
{
    return worknumber;
}