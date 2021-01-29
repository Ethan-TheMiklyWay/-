#include <iostream>
using namespace std;
 
void SelectSort(int r[ ], int n){   
    for(int i=0;i<n;i++){  
        int index=i;
        for(int j=i+1;j<n;j++)
        	if(r[j]<r[index])
				index=j;
        if(index!=i){
        	int temp=r[i];
        	r[i]=r[index];
        	r[index]=temp;
		}
    }
}
void BubbleSort(int r[ ], int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n-1; j++)
    		if(r[j]>r[j+1]){
    			int temp=r[j];
    			r[j]=r[j+1];
    			r[j+1]=temp;
			}
}
void BubbleSort2(int r[ ], int n){
    int exchange=n-1;          //��һ����������ķ�Χ��r[1]��r[n]
    while (exchange!=-1){      //������һ�������м�¼�����Ž��б�������
        int bound=exchange;
		exchange=-1;  
        for(int j=0;j<bound;j++)          //һ����������
            if(r[j]>r[j+1]){
                int temp=r[j];
    			r[j]=r[j+1];
    			r[j+1]=temp;
                exchange=j;         //��¼ÿһ�η�����¼������λ��
            }
    }
}

int main(int argc, char** argv) 
{
	int n[10]={5,4,8,1,6,3,2,9,7,0};
	SelectSort(n,10);
	for(int i=0;i<10;i++)
		cout<<n[i]<<" ";
	cout<<endl; 
	
	int n2[10]={5,4,8,1,6,3,2,9,7,0};
	BubbleSort2(n2,10);
	for(int i=0;i<10;i++)
		cout<<n2[i]<<" ";
	cout<<endl; 
	return 0;
}
