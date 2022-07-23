#include"Employee.h"

//构造函数
Employee::Employee(int id, string name, string sex, int age, string idcard, float salary, int number)
{
	//职工工号
	this->m_id = id;
	//职工姓名
	this->m_name = name;
	//职工性别
	this->m_sex = sex;
	//职工年龄
	this->m_age = age;
	//职工身份证号
	this->m_idcard = idcard;
	//职工工资
	this->m_salary = salary;
	//部门编号
	this->m_number = number;
}

//显示个人信息
void Employee::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t职工性别：" << this->m_sex
		<< "\t职工年龄：" << this->m_age
		<< "\t职工身份证号：" << this->m_idcard
		<< "\t职工工资：" << this->m_salary
		<< "\t部门：" << this->getDeptName()
		<< "\t岗位职责：完成经理交待的任务" << endl;
}

//获取岗位名称
string Employee::getDeptName()
{
	return string("普通员工");
}

//析构函数
Employee::~Employee()
{

}
