#include <iostream>
#include <math.h>
using namespace std; 
int main(int argc, char** argv) {
	int n,C;
	cout<<"��ֱ����뼯��Ԫ��n�ĸ�����C(ע�⣬ʱ�临�Ӷ�Ϊ2��n�η�*n������n���˹���)��";
	cin>>n>>C;
	int *set=new int[n];
	int i,j;
	cout<<"��ֱ�������n������";
	for(i=0;i<n;i++)
		cin>>set[i];
	
	bool exist=false;
	int times=pow(2,n);
	cout<<"��Ҫ����"<<times<<"��ѭ��"<<endl;
	for(i=0;i<times;i++){   //��������һ����00...00��11...11������ 
		int sum=0;
		int nowi=i;
		for(j=0;j<n;j++){
			if(nowi%2==1){				
				sum+=set[j];
			}
			nowi=nowi/2;
		}
		if(sum==C) {
			exist=true;
			break;
		}
	} 
	if(exist) cout<<"����";
	else cout<<"������"; 
	
	 
	return 0;
}
