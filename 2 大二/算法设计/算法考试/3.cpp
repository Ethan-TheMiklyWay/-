#include <iostream>
#include <math.h>
using namespace std; 
int main(int argc, char** argv) {
	int n;
	double C;
	cout<<"�ó�����1��Ϊλ�õ���㣬����Ϊ������\n"; 
	cout<<"��ֱ���������Ԫ��n�ĸ����ʹ����ҵ�����C��";
	cin>>n>>C;
	double *set=new double[n];
	int i,j;
	cout<<"��ֱ�������n����(���򣺴�С����)��";
	for(i=0;i<n;i++)
		cin>>set[i];
		
	for(i=0;i<n;i++){
		if(C<=set[i]) break;
	}
	if(C==set[i]){
		//��ʱ�ҵ�CԪ����
		cout<<"Ԫ��C��λ���ǣ�"<<i+1; 
	}
	else if(i==0){
		cout<<"CС�����е�Ԫ�أ���˴���x����СԪ��λ��Ϊ"<<1;
	}
	else if(i==n){
		cout<<"C�������е�Ԫ�أ����С��x�����Ԫ��λ��Ϊ"<<n;
	}
	else{
		cout<<"C���ڵ�"<<i<<"�͵�"<<i+1<<"��Ԫ��֮��"; 
	}
	
	 
	return 0;
}
