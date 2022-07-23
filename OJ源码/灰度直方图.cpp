#include<iostream>
using namespace std;
 
int main(){
	int n,m,L;
	cin>>n>>m>>L;
	int value,count[300]={0};
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>value;
			count[value]++;
		}
	}
	for(int i=0;i<L;i++){
		cout<<count[i]<<" ";
	}
	return 0; 
} 
