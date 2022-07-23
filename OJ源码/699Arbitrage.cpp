#include<iostream>
#include<string>
#include<map>

using namespace std;

const int INF = 0.00001; //���������ֵ������Ӧ����INF����ʾ����С����

int main()
{
    int n,m,i,j,k,t=0;
    double d[50][50];
    string x[50],x1,x2;
 
    while(cin >> n, n)
    {
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                d[i][j] = INF;
        map<string,int> p;
        for(i=1; i<=n; i++)
        {
            cin >> x[i];
            p[x[i]] = i;
        }
        cin >> m;
        double c;
        for(i=1; i<=m; i++)
        {
            cin >> x1 >> c >> x2;
            d[p[x1]][p[x2]] = c;
        }
        for(k=1; k<=n; k++)
          for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
               if(d[i][k] * d[k][j] > d[i][j]) //�����������">".
                  d[i][j] = d[i][k] * d[k][j];
        cout << "Case " << ++t ;
        if(d[1][1] > 1) cout<<" Yes"<<endl; //���������Լ����Լ���ת����������d[1][1];
        else  cout<<" No"<<endl;           //���������㵽�յ�n��ת������Ӧ����d[1][n];
    }
    return 0;
}

/*
3
USDollar
BritishPound
FrenchFranc
3
USDollar 0.5 BritishPound
BritishPound 10.0 FrenchFranc
FrenchFranc 0.21 USDollar

3
USDollar
BritishPound
FrenchFranc
6
USDollar 0.5 BritishPound
USDollar 4.9 FrenchFranc
BritishPound 10.0 FrenchFranc
BritishPound 1.99 USDollar
FrenchFranc 0.09 BritishPound
FrenchFranc 0.19 USDollar
0
*/

/*
Case 1 Yes
Case 2 No
*/