#include <iostream>
#include <math.h>
using namespace std; 
int main(int argc, char** argv) {
	int n;
	cout<<"�����������������n��";
	cin>>n;
	double **set=new double*[n];
	int i,j;
	cout<<"��ֱ�����ÿ�е�Ԫ�أ���һ��1������n��n����\n";
	for(i=0;i<n;i++){
		set[i]=new double[n];  //����һ����ά�����ж�̬�滮 
		for(j=0;j<=i;j++){		 
			cin>>set[i][j];
		}
	} 
	for(i=1;i<n;i++){
		for(j=0;j<=i;j++){
			if(j==0) {
				set[i][j]+=set[i-1][j];
			}
			else if(j==i){
				set[i][j]+=set[i-1][j-1];
			}
			else{
				double maxformer=set[i-1][j-1]>set[i-1][j]?set[i-1][j-1]:set[i-1][j];
				set[i][j]+=maxformer;
			}
		}
	}
	double maxvalue=0;
	for(i=0;i<n;i++){
		if(set[n-1][i]>maxvalue)
			maxvalue=set[n-1][i];
	}
	cout<<"���·��Ϊ��"<<maxvalue;
	for(i=0;i<n;i++)
		delete [] set[i];
	delete [] set;
	return 0;
}
