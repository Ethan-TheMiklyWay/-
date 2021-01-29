#include <iostream>
#include <string>
using namespace std; 
class String{
	private:
		char *c;
	public:
		String();
		String(const char *t);
		friend ostream& operator<<(ostream &out,String s);
		int length();
		String insert(int loc,String s2);
		void push_back(char t);
		char operator[](int loc);
		String erase(int start,int leng);
		String replace(int start,int leng,String t);
		String substring(int start,int leng);
		String operator +(String s);
};
String String::operator +(String s){
	String temp=*this;
	for(int i=1;i<s.length();i++){
		temp.push_back(s[i]);
	}
	return temp;
}
String String::substring(int start,int leng){
	if(start<=0||start+leng>c[0]){
		cout<<"Error";
		throw("Overflow");
	}
	String temp;
	for(int i=start;i<start+leng;i++){
		temp.push_back(c[i]);
	}
	return temp;
}
String String::replace(int start,int leng,String t){
	String temp;
	temp=erase(start,leng);
	temp=temp.insert(start,t);
	return temp;
}
String String::erase(int start,int leng){
	String t;
	if(start<=0 || start+leng>c[0]){
		cout<<"Error!";
		throw("Overflow!");
	}
	int i;
	for(i=1;i<start;i++)
		t.push_back(c[i]);
	for(;i<length()-leng;i++)
		t.push_back(c[i+leng]);
	return t;
}
char String::operator[](int loc){
	if(c[0]<loc){
		cout<<"Error!";
		throw("overflow!");
	}
	return c[loc];
}
void String::push_back(char t){
	if(c[0]>255) {
		cout<<"overflow!"; 
		return ;
	}
	++c[0];
	c[c[0]]=t;
}
String String::insert(int loc,String s2){
	String t;
	int i,j,len;
	for(i=1,len=0;i<=loc;i++,len++)
		t.push_back(c[i]);
	for(j=1;j<=s2.length();j++,len++){
		t.push_back(s2[j]);
	}
	for(;i<=length();i++){
		t.push_back(c[i]);
	}
	return t;
}
int String::length(){
	return c[0];
}
ostream& operator<<(ostream &out,String s){
	for(int i=0;i<s.c[0];i++){
		printf("%c",s.c[i+1]);
	}
	return out;
}
String::String(){
	c=new char[256];
	c[0]=0;
}
String::String(const char *t){
	int i=0;
	c=new char[256];
	while(t[i]!=0){
		c[i+1]=t[i];
		++i;
	}
	c[0]=i;
}
int main(int argc, char** argv) {
//(1)������s="abcdefghijklmn"��s1="xyz"
 	String s="abcdefghijklmn",s1="xyz";
//(2)�����s
	cout<<s<<endl;
//(3)�����s�ĳ���
	cout<<s.length()<<endl;
//(4)�ڴ�s�ĵ�9��λ�ò��봮s1��������s2
	String s2=s.insert(9,s1);
//(5)���s2
	cout<<s2<<endl;
//(6)ɾ����s��2���ַ���ʼ��5���ַ���������s2
	s2=s.erase(2,5); 
//(7)���s2
	cout<<s2<<endl;
//(8)����s��2���ַ���ʼ��5���ַ��滻�ɴ�s1��������s2
	s2=s.replace(2,5,s1);
//(9)���s2
	cout<<s2<<endl;
//(10)��ȡ��s�ĵ�2���ַ���ʼ��10���ַ���������s3
	String s3=s.substring(2,10);
//(11)���s3
	cout<<s3<<endl;
//(12)����s1��s2����������������s4
	String s4=s1+s2;
//(13)���s4
	cout<<s4;
	return 0;	
}
