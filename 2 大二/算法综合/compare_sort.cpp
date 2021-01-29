#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include "sort.h"
using namespace std; 

void random_quque(int n,vote *result,int range=100000){
	//����һ�����������
	/*********
		n��ʾ�������еĴ�С
		result��ʾ���ص�����
		range��ʾȡֵ��Χ 
	*/ 
	srand((unsigned)time(NULL));
	int i;
	for(i=0;i<n;i++){
		result[i].number=i;
		result[i].point=rand()%range;
	}
}

typedef void(*queue_sort)(vote *result,int first,int end);
ofstream fon("compare_sort_result.txt");
 
double test_time(queue_sort method,bool complax=false,const char* name=""){	
	/***********
		queue_sort����ʾ��Ҫ���õĺ������ƣ���void(*queue_sort)(vote *result,int first,int end)
		 			���͵�ָ�� 
		complax���ǣ�������������ȡ��100�򣬷���ֻȡָ��10��
		name�������������Ƶļ�¼ 		
	*/ 
	time_t start,end;
	fon<<endl<<"name:"<<name<<endl;
	if(complax)	
		fon<<"num:"<<5<<endl;
	else
		fon<<"num:"<<4<<endl;
	int number_range[5]={100,1000,10000,100000,1000000};
	int i;
	for(i=0;i<5;i++){
		if(!complax&&i==4) break;
		int number_length=number_range[i];
		vote *number=new vote[number_length];
		random_quque(number_length,number);
		
		start=clock();
		(*method)(number,0,number_length-1);
		end=clock();
		
		cout<<setw(7)<<number_length<<"������������ʱ��"<<
				double(end-start)/1000<<"s"<<endl;
		fon<<"number:"<<number_length<<";time:"<<double(end-start)/1000<<endl;
	}
	return 0;
}

int main(){
	//��������������ò�ͬ�����㷨��ʱ�� 
	cout<<"���򷽷�1���鲢����(merge sort)��"<<endl;
	test_time(merge_sort,true,"merge_sort");
	cout<<endl<<"���򷽷�2����������(quick sort)��"<<endl;
	test_time(quickSort,true,"quick_sort");
	cout<<endl<<"���򷽷�3��ϣ������(shell sort)��"<<endl;
	test_time(shell_sort,true,"shell_sort");
	cout<<endl<<"���򷽷�4��������(heap sort)��"<<endl;
	test_time(heap_sort,true,"heap_sort");
	cout<<endl<<"���򷽷�5����������(counting sort)��"<<endl;
	test_time(counting_sort,true,"counting_sort");
	cout<<endl<<"���򷽷�6����������(base sort)��"<<endl;
	test_time(base_sort,true,"base_sort");
	cout<<endl<<"���򷽷�7����������(insert sort)��"<<endl;
	test_time(insert_sort,false,"insert_sort");
	cout<<endl<<"���򷽷�8��ѡ������(select sort)��"<<endl;
	test_time(select_sort,false,"select_sort");
	cout<<endl<<"���򷽷�9��ľͰ����(bucket sort)��"<<endl;
	test_time(bucket_sort,false,"bucket_sort");
	cout<<endl<<"���򷽷�10���Ż�ð������(bubble sort2)��"<<endl;
	test_time(bubble_sort2,false,"bubble_sort2");
	cout<<endl<<"���򷽷�11��ð������(bubble sort)��"<<endl;
	test_time(bubble_sort,false,"bubble_sort");
}
