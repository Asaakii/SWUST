#include"Manager.h"

//���캯��
Manager::Manager(int id, string name, string sex, int age, string idcard, float salary, int number)
{
	//ְ������
	this->m_id = id;
	//ְ������
	this->m_name = name;
	//ְ���Ա�
	this->m_sex = sex;
	//ְ������
	this->m_age = age;
	//ְ�����֤��
	this->m_idcard = idcard;
	//ְ������
	this->m_salary = salary;
	//���ű��
	this->m_number = number;
}

//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\tְ���Ա�" << this->m_sex
		<< "\tְ�����䣺" << this->m_age
		<< "\tְ�����֤�ţ�" << this->m_idcard
		<< "\tְ�����ʣ�" << this->m_salary
		<< "\t���ţ�" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񣬲��·��������ͨԱ��" << endl;
}

//��ȡ��λ����
string Manager::getDeptName()
{
	return string("����");
}

//��������
Manager::~Manager()
{

}