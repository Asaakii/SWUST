#include <stdio.h>
#include <ctype.h>
#include <string.h>

//�����ֱ�
char* keyword[8] = {"if","else","for","while","do","int","read","write"};

//���ֽ��
char singleword[50] = "+-*(){};,:#&|";

//˫�ֽ��
char doubleword[10] = "><=!&";

//���ڽ�����������ļ���
char Scanin[300],Scanout[300];

//����ָ����������ļ���ָ��
FILE* fin,* fout;

//�ʷ���������
int TflagTscan()
{
	char ch,token[40];//CHΪÿ�ζ�����ַ���TOKEN���ڱ���ʶ����ĵ���
	int flag = 0,j,n;//flagΪ������룬0��ʾû�д���
	int line = 1;
	printf("������Դ�����ļ�����");
	scanf("%s",Scanin);
	printf("������ʷ���������ļ�����");
	scanf("%s",Scanout);
	if((fin = fopen(Scanin,"r")) == NULL)//�ж������ļ����Ƿ���ȷ
	{
		printf("\n�򿪴ʷ����������ļ�����\n");
		flag=1;//�������flag��Ϊ1
	}
	if((fout = fopen(Scanout,"w")) == NULL)//�ж�����ļ����Ƿ���ȷ
	{
		printf("\n�����ʷ���������ļ�����\n");
		flag=2;//�������flag��Ϊ2
	}
	ch = getc(fin);
	
	while(ch!=EOF)
	{
		while(ch==' '||ch=='\n'||ch=='\t')
		{
			if (ch=='\n') 
				line++;
			ch=getc(fin);
		}
		
		if(isalpha(ch))//�������ĸ ����б�ʶ������
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			
			while(isalnum(ch))//�������ĸ��������ϱ�ʶ��
			{
				token[j++] = ch;//��ϵı�ʶ������TOKEN��
				ch = getc(fin);
			}
			token[j] = '\0';//��ʶ����Ͻ���
			
			n = 0;
			while ((n < 8) && strcmp(token, keyword[n]))
				n++;
			if (n  >= 8)//������Ǳ����������ʶ��
			{
				fprintf(fout,"%s\t%s\n","ID",token);//�����ʶ������
			}
			else//�Ǳ����� ���������
			{
				fprintf(fout,"%s\t%s\n",token,token);//��������ַ���
			}
		}
		
		else if(isdigit(ch))//���ִ���
		{
			token[0] = ch;
			j = 1;
			if(token[0]=='0')
			{
				ch=getc(fin);
				if(ch=='\0')
				{
						fprintf(fout,"NUM_0");
				}
				else
				{ 
					fprintf(fout,"%s\t%s\n","ERROR",token);
					printf("Line %d\t%s\t%s\n",line,"��0��ͷ������",token);
				} 
			}
			else
			{
				ch = getc(fin);//����һ���ַ�
				while(isdigit(ch))//������������������ ���������������Ͻ���
				{
					token[j++] = ch;//�������������TOKEN ��
					ch = getc(fin);//����һ���ַ�
				}
				token[j] = '\0';//������Ͻ���
				fprintf(fout,"%s\t%s\n","NUM",token);//�����������
			}
		}
		
		else if(strchr(singleword,ch)>0)//���ֽ������
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);//����һ�������Ա�ʶ����һ������
			fprintf(fout,"%s\t%s\n",token,token);//������ֽ����
		}
		
		else if(strchr(doubleword,ch)>0)//˫�ֽ������
		{
			token[0] = ch;
			ch = getc(fin);//����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
			if(ch == '=')//�����= ���˫�ֽ��
			{
				token[1] = ch;
				token[2] = '\0';//���˫�ֽ������
				ch = getc(fin);//����һ�������Ա�ʶ����һ������
				fprintf(fout,"%s\t%s\n",token,token);//���˫�ֽ������
			}
			else if(ch == '&')//�����& ���˫�ֽ��
			{
				token[1] = ch;
				token[2] = '\0';//���˫�ֽ������
				ch = getc(fin);//����һ�������Ա�ʶ����һ������
				fprintf(fout,"%s\t%s\n",token,token);//���˫�ֽ������
			}
			else//����=��Ϊ���ֽ��
			{
				token[1] = '\0';
				if(token[0]=='!') 
				{
					printf("Line %d\t%s\t%s\n",line,"�Ƿ��ַ�",token);
					fprintf(fout,"%s\t%s\n","ERROR",token);
				}
				else
				{
					fprintf(fout,"%s\t%s\n",token,token);//���˫�ֽ������
				}
			}
		}
		
		else if(ch=='/')//ע�� 
		{
			ch = getc(fin);
			if(ch == '*')//�����* ��ʼ����ע��
			{
				char ch1;
				ch1 = getc(fin);//����һ���ַ�
				while (true)
				{
					if (ch1==EOF)
					{
						printf("Line %d\t%s\tû��ƥ�䣡\n", line,"�Ƿ����");
						break;
					}
					ch=ch1;
					ch1=getc(fin);
					if(ch=='*' && ch1=='/')
						break;
				}
				ch = getc(fin);//����*�����ֽ��
			}
			else
			{
				token[0] = '/';
				token[1] = '\0';
				fprintf(fout,"%s\t%s\n",token,token);//������ֽ��
			}
		}
		
		else//������   
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			//����һ�������Ա�ʶ��
			flag = 0;//���ô������
			fprintf(fout,"%s\t%s\n","ERROR",token);//���������� ����ʾERROR
			printf("Line %d\t%s\t%s\n",line,"�Ƿ��ַ�",token);
		}
	}
	fclose(fin);//�ر���������ļ�
	fclose(fout);
	return flag;
}

int main()
{
	int flag = 0;
	flag = TflagTscan();//���ôʷ���������
	if (flag > 0)
		printf("�ʷ�����ʧ��!\n");
	else
		printf("�ʷ������ɹ�!\n");
	return 0;
}
