#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include "sort.h"
using namespace std; 

int get_number(){
	/*****
		��ȡ���ķ�Χ 
	*/
	int maxx=0;
	ifstream fin("input.txt");
	string read_one_line;
	while(fin>>read_one_line){
		stringstream ss;
		ss<<read_one_line;
		int read_int;
		ss>>read_int;
		if(maxx<read_int)
			maxx=read_int;
	}
	fin.close();
	return maxx;
}
 
int main(int argc, char** argv) {	
	int number=38;   
	//numberΪ�ܵ�ѡ�ָ�������Ҫ���� 
	number=get_number();
	 
	vote *result=new vote[number];
	//voteΪ�ṹ�壬����numѡ�ֱ�ź�point��Ʊ��� 
	int i;
	for(i=0;i<number;i++){
		result[i].point=0;
		result[i].number=i;
	} 
	
	ifstream fin("input.txt");
	string read_one_line;
	while(fin>>read_one_line){
		stringstream ss;
		ss<<read_one_line;
		int read_int;
		ss>>read_int;
		result[read_int-1].point++;//ͳ�ƽ�� 
	}
	fin.close();
	
	ssort(result,0,number-1); 
	//���������㷨 
	ofstream fon("output.txt");
	for(i=0;i<number;i++){
		cout<<result[i].number+1<<": "<<result[i].point<<endl;
		fon<<result[i].number+1<<": "<<result[i].point<<endl;
		//�������ӡ������д�뵽txt�ļ����� 
	}
	fon.close();
	
	cout<<"��һ��Ϊ��"<<result[0].number+1<<"��ѡ�֣���"<<result[0].point<<"Ʊ"<<endl;
	cout<<"�ڶ���Ϊ��"<<result[1].number+1<<"��ѡ�֣���"<<result[1].point<<"Ʊ"<<endl;
	cout<<"������Ϊ��"<<result[2].number+1<<"��ѡ�֣���"<<result[2].point<<"Ʊ"<<endl;
	
	system("pause");
	return 0;
}
