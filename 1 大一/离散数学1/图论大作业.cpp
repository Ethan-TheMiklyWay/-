#include <iostream>
#include<fstream> 
using namespace std;

int main(int argc, char** argv) {
	ofstream aa;	
	ifstream kk;
	char c,s;
	char m[20];
	int x,y;
	
	int number1=0,number2=0,times;
	int data[30000];
	aa.open("f1",ios::out) ;          //д���ļ� 
	kk.open("ka.tsv",ios::binary);    //�����ļ� 
	for(int k=0;k<25;k++) {kk.get(c);cout<<c;}                                 
	for(x=0;x<20;x++) m[x]='\0';
	for(x=0;x<30000;x++) data[x]=0;
	
    while(!kk.eof() )               //һֱ�����ļ����� 
{

    for(x=0;x<20;x++)     //xΪһ��ĳ��� 
    {
    	kk.get(m[x]);
    	if(m[x]=='\n') break;
	} 
	for(y=0;y<20;y++)    //������һ������ 
	{
		if(m[y]>='0'&&m[y]<='9') number1=number1*10+m[y]-48;
		else break;
	}
	for(y++;y<x;y++)    //�����ڶ������� 
	{
		if(m[y]>='0'&&m[y]<='9') number2=number2*10+m[y]-48;
      	else break;
	}
 
	for(y++;y<x;y++)    //������������ 
	{
		if(m[y]>='0'&&m[y]<='9') times=times*10+m[y]-48;
		else break;
	}
    data[number1]=times+data[number1];
	data[number2]=times+data[number2]; 
    for(x=0;x<20;x++) m[x]='\0';
    number1=0;number2=0;times=0;
 
    
}
    int tt;              //���������� 
    for(x=0;x<29999;x++)
    for(y=0;y<29999;y++)
    if(data[y]<data[y+1]) {tt=data[y];data[y]=data[y+1];data[y+1]=tt;	} 
    
    int degree[30000],size[30000],ma=0,na;    
    for(x=0;x<30000;x++) {degree[x]=0;size[x]=0;}
    
    for(x=0,y=-1;x<30000;x++)    //����ÿ��������degree���ж��ٸ���㣨size��  
    {
    	if(ma!=data[x]) 
    	{
    		y++;
    		ma=data[x];
    		size[y]++;
			degree[y]=ma; 
		}
		else if(ma==data[x])
		{
			size[y]++;
		}
	}                         //y���ܵ�����
	
	for(x=0;x<y;x++) 
	{
		aa<<degree[x]<<"  "<<size[x]<<endl;    //д���ļ� 
	}
	aa.close() ; 
	kk.close() ;
	return 0;
}
