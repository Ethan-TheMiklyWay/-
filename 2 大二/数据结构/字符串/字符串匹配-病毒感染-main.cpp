#include <iostream>
#include <stdlib.h>
#include <time.h>  
#include <fstream>  
#include <string>
using namespace std; 
void creat_DNA(char const *filename,int length,char const *name,string &se){
	fstream cfile;
	static bool flag=true;
	if(flag){
		srand((unsigned)time(NULL)); 
		rand();
		flag=false;
	}
    cfile.open(filename,ios::in);
    if(!cfile){
    	ofstream out(filename);
    	cout<<"���ڴ���"<<name<<"��DNA���С�"<<endl;
		for(int i=1;i<=length;i++){
			int t=rand()%4;
			char c;
			switch(t){
				case 0: c='A';break;
				case 1: c='T';break;
				case 2: c='C';break;
				case 3: c='G';break;
			}
			out<<c;
			if(i%100==0) out<<'\n';
		} 
	}
	else{
		cout<<"DNA�����Ѿ����ڡ�"<<endl;
	}
	ifstream in(filename);  
	string t;
	char buffer[1000];
	while (!in.eof())  
    {   
        in.getline(buffer,1000);  
        t+=buffer;
    }  
    se=t;
}
void creat_virul_DNA(int length,string &virul_DNA){
	creat_DNA("virul DNA sequence.txt",length,"����",virul_DNA);
}
void creat_host_DNA(int length,string &host_DNA){
	creat_DNA("host DNA sequence.txt",length,"����",host_DNA);
}
bool KMP(string main_sequence,string son_sequence){
	int length=son_sequence.length();
	int next[length];
	next[0]=0;
	int j=0,k=0,i=0;
	while(j<length){
		if(k==0||(son_sequence[j]==son_sequence[k-1])){
			++j;
			++k;
			next[j]=k;
		}
		else k=next[k-1];
	}
	i=0;j=0;
	while((i<=main_sequence.length()-length+1)&&(j<length)){
		if((j==-1)||(son_sequence[j]==main_sequence[i])){
			i++;
			j++;
		}
		else j=next[j]-1;
	}
	return j>=length;
	
}
int main(int argc, char** argv) {
	int host_DNA_length=100000;
	int virul_DNA_length=10;
	string host_DNA;
	string virul_DNA;
	creat_host_DNA(host_DNA_length,host_DNA);
	creat_virul_DNA(virul_DNA_length,virul_DNA);
	cout<<"������DNA����Ϊ��"<<host_DNA.substr(0,6)<<"..."
	<<host_DNA.substr(host_DNA_length-5,host_DNA_length)<<"����Ϊ��"<<host_DNA_length<<endl;
	cout<<"������DNA����Ϊ��"<<virul_DNA.substr(0,6)<<"..."
	<<virul_DNA.substr(virul_DNA_length-5,virul_DNA_length)<<"����Ϊ��"<<virul_DNA_length<<endl;
	int times=virul_DNA.length();
	string temp_virul=virul_DNA;
	int i;
	for(i=0;i<times;i++){
		temp_virul=temp_virul.substr(1,times)+temp_virul.substr(0,1);
		if(KMP(host_DNA,temp_virul)){
			cout<<"�����ѱ���Ⱦ����������Ϊ��"<<temp_virul<<endl;
			break;
		}
	}
	if(i==times)cout<<"����δ����Ⱦ"<<endl;
	
	return 0;
}
