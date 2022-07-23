#include<iostream>
#include<cstring>
using namespace std;

int form[26];//用来记录 str中的字母 最后一次出现的位置 

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
	int p = length_str - 1; //用来记录str最后一个字母 在text中 开始对比的位置
	while(p<length_text)
	{
		int j=0; 
		while(str[length_str-1-j] == text[p-j]&&j<length_str)//从右到左对比 
		{
			j++;
		}
		if(j==length_str)
		{
			return (p + 1 - length_str);
		}
		//p += form[text[p]-'A'];
		int shipei = length_str-j-1;  //坏字符在模式中失配的位置
		int last_show = form[text[p-j]-'A'];//坏字符在模式中最后一次出现的位置
		if(shipei>=last_show)  //可能会出现 last_show>shipei的情况 比如str:SIMPLE text:SPMPLESIMPLE ，导致str无法向右移动
			p += (shipei-last_show);//模式后移位数 = 坏字符在模式中失配的位置 - 坏字符在模式中最后一次出现的位置
		else 
			p++;
		//p += form[text[p]-'A'];
	} 
	return -1;
}

int main()
{
	memset(form, -1, sizeof(form));//置-1 
	string aim,text;
	cin >> aim >> text;
	cout <<match(aim,text)<<endl;
	return 0;
}

