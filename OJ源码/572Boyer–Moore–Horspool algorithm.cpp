#include<iostream>
#include<cstring>
using namespace std;

int form[26];//������¼ str�е���ĸ ���һ�γ��ֵ�λ�� 

int match(string str,string text)
{
	int length_str,length_text;
	length_str = str.length();
	length_text = text.length();
	for(int i=0;i<length_str - 1;i++)
	{
		form[str[i]-'A'] = i;
		//form[str[i] - 'A'] = length_str - i - 1;
	} 
	int p = length_str - 1; //������¼str���һ����ĸ ��text�� ��ʼ�Աȵ�λ��
	while(p<length_text)
	{
		int j=0; 
		while(str[length_str-1-j] == text[p-j]&&j<length_str)//���ҵ���Ա� 
		{
			j++;
		}
		if(j==length_str)
		{
			return (p + 1 - length_str);
		}
		//p += form[text[p]-'A'];
		int shipei = length_str-j-1;  //���ַ���ģʽ��ʧ���λ��
		int last_show = form[text[p-j]-'A'];//���ַ���ģʽ�����һ�γ��ֵ�λ��
		if(shipei>=last_show)  //���ܻ���� last_show>shipei����� ����str:SIMPLE text:SPMPLESIMPLE ������str�޷������ƶ�
			p += (shipei-last_show);//ģʽ����λ�� = ���ַ���ģʽ��ʧ���λ�� - ���ַ���ģʽ�����һ�γ��ֵ�λ��
		else 
			p++;
		//p += form[text[p]-'A'];
	} 
	return -1;
}

int main()
{
	memset(form, -1, sizeof(form));//��-1 
	string aim,text;
	cin >> aim >> text;
	cout <<match(aim,text)<<endl;
	return 0;
}

