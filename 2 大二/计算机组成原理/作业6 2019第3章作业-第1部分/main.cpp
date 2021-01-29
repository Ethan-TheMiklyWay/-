#include <iostream>
#include <windows.h>
using namespace std; 
void transfor(bool *re,int value){
	re[0]=(value>=0)?0:1;
	int i;
	for(i=31;i>0;i--){
		re[i]=value%2;
		value=value/2;
	} 
}
void transfor2(bool *re,int value){
	re[32]=(value>=0)?0:1;
	int i;
	for(i=0;i<32;i++)
		re[i]=0;
	for(i=63;i>32;i--){
		re[i]=value%2;
		value=value/2;
	} 
}
void show(bool *re){
	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++)
			if(re[i*8+j]==0) cout<<0;
			else cout<<1;
		cout<<" ";
	}
	cout<<endl;
}
void show2(bool *re){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
			if(re[i*8+j]==0) cout<<0;
			else cout<<1;
		cout<<" ";
	}
	cout<<endl;
}
void show3(bool *re){
	for(int i=4;i<8;i++){
		for(int j=0;j<8;j++)
			if(re[i*8+j]==0) cout<<0;
			else cout<<1;
		cout<<" ";
	}
	cout<<endl;
}
bool Add(bool *re1,bool *re2){
	int i;
	bool carry=0;
	for(i=0;i<32;i++){
		bool temp=re1[31-i]^re2[31-i]^carry;
		if((re1[31-i]&&re2[31-i]) || (re1[31-i]&&carry) ||
			(carry&&re2[31-i]))
			carry=1;
		else carry=0;
		re2[31-i]=temp;
	}
	return carry;
}
void translation(bool carry,bool *register2){
	int i;
	for(i=63;i>=1;i--){
		register2[i]=register2[i-1];
	} 
	register2[0]=carry;
}
int translate_to_dismal(bool *re){
	int result=0;
	int i;
	for(i=33;i<64;i++){
		int temp=(re[i]==0)?0:1;
		result=result*2+temp;
	}
	result=(re[32]==0)?result:-result;
	return result;
}
int main(int argc, char** argv) {
	int value1,value2;
	cout<<"Please input two multipliers"<<endl;
	cin>>value1>>value2; 
	bool register1[32];  //�Ĵ���1��ʾ������ 
	bool register2[64];  //�Ĵ���2�ĺ�32λ�ǳ˻��Ĵ���
	transfor(register1,value1);  //������ת��Ϊ2���Ʋ�����Ĵ����� 
	transfor2(register2,value2);
	cout<<"register1:";
	show(register1);	//չʾ�Ĵ����е����� 
	cout<<"register2:";
	show2(register2);
	int i;
	for(i=0;i<32;i++){
		cout<<"number"<<i+1<<":"<<endl; 
		Sleep(100);  //ģ��ʱ������ 
		bool enable=register2[63];  //ȡ���һλ���ж��Ƿ���Ҫ���
		bool carry=0;
		if(enable)		//�����Ҫ��ӣ��������� 
			carry=Add(register1,register2); //ģ�⴮�н�λ�ӷ��������ؽ�λ�ź� 
		cout<<"After add:";
		show2(register2);
		translation(carry,register2);	//ƽ�� 
		cout<<"After translation:";
		show2(register2);
		cout<<endl<<endl;
	} 
	if(value1*value2<0)  //�������λ 
		register2[32]=1;
	cout<<"Final result:";
	show3(register2);
	int finalresult=translate_to_dismal(register2);
	cout<<"To dismal:"<<finalresult;
	
	return 0;
}
