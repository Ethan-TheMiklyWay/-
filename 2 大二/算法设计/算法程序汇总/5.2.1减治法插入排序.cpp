
#include<iostream>
using namespace std;
#include <algorithm>

void InsertSort(int r[],int n) { //���ü�����
	for(int i=2;i<=n;i++){
    //����n-1�β��룬���β���r[2],r[3],��,r[n]
    	r[0]=r[i];        //r[0]�Ǽ�����
    //˳��ȽϺ��ƶ�������r[i]�Ĳ���λ��
    	int j;
    	for(j=i-1;r[0]<r[j];j--) {   
      		r[j+1]=r[j]; //��¼���ƣ�������ǰ���� 
    	}
    	r[j+1]=r[0];   //����r[i]
  }
}


int main()
{
	int x[11]={0,5,6,2,1,8,9,3,4,7,0};
	InsertSort(x,10);
	for(int i=1;i<=10;i++)
		cout<<x[i]<<" ";
	
  
	return 0;
}
 
