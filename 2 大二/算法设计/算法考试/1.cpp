#include <iostream>
using namespace std; 
int main(int argc, char** argv) {
	int n;
	cout<<"�����뼯��Ԫ�صĸ�����";
	cin>>n;
	int *set=new int[n];
	int i,j;
	cout<<"��ֱ�������n������";
	for(i=0;i<n;i++)
		cin>>set[i];
	int maxtimes=0;
	int maxvalue=0;
	for(i=0;i<n;i++){
		int nowvalue=set[i];
		if(nowvalue==maxvalue) continue;
		int nowtimes=0;
		for(j=0;j<n;j++){
			if(set[j]==nowvalue){
				nowtimes++;
			}
		}
		if(nowtimes>maxtimes){
			maxtimes=nowtimes;
			maxvalue=nowvalue;
		}
		if(nowtimes==maxtimes){
			if(nowvalue<maxvalue)
				maxvalue=nowvalue;
		}
	}	
	cout<<"����Ϊ��"<<maxvalue;
	return 0;
}
