#pragma once
#ifndef INFORMATION_H
#define INFORMATION_H

#include <iostream>
using namespace std;

class Information
{
private:
	char* Users;//�û���
	char* Password;//����
	char* Password1;//�ڶ������������
	char* users;//��¼ʱ������û���
	char* password;//��¼ʱ���������
public:
	Information()
	{ //���캯��
		this->Users = Users, this->Password = Password;
	}

	~Information() {} //��������

	void deleteusers() {//�û����ظ�ʱɾ����ע��
		
	}

	int Login(char* users, char* password) {//��¼
		int b = 1;//���Ƶ�¼�ĳɹ���ʧ��
		for (int o = 0, p = 0; o < strlen(Users) && o < strlen(users) && p < strlen(Password) && p < strlen(password); o++, p++) {
			if ((*(Users + o) == *(users + o)) && (*(Password + p) == *(password + p)))   b = 0;//�ɹ�Ϊ�㣬ʧ��Ϊһ
			else { b = 1; break; }
		}
		return b;
	}

	int setinformation() {//ע��
		int judge1 = 0;
		cout << "�����������û�����";
		Users = (char*)malloc(20 * sizeof(char));
		cin >> Users;
		cout << "�������������룺";
		Password = (char*)malloc(20 * sizeof(char));
		cin >> Password;
		cout << "���ٴ����������õ����룺";
		Password1 = (char*)malloc(20 * sizeof(char));
		cin >> Password1;//�û�����������
		if (strlen(Password) == strlen(Password1))
		{
			int p;
			for (p = 0; p < strlen(Password); p++)
			{
				if (*(Password + p) == *(Password1 + p))  judge1 = judge1 + 1; //�ж���������������Ƿ����
			}
			if (judge1 == p) return 1;
			else return 0;
		}
		else return 0;
	}

	char* getUsers() { return Users; }//�����û������ж�ע����û����Ƿ��ظ�
};
#endif // !INFORMATION_H
