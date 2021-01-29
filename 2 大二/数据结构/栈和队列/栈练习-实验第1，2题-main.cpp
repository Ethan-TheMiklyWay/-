#include <iostream>
#define INIT_SIZE 100
#define INCREASE 50 
using namespace std;
template<typename T>
class stack{
	private:
		T *data;
		int top;
		int size;
		void increment();
	public:
		stack();
		~stack(); 
		void clear();
		void push_back(const T);
		void pop_back();
		T top_element();
};
template<typename T>
T stack<T>::top_element(){
	return data[top];
}
template<typename T>
void stack<T>::pop_back(){
	if(top<=-1) {
		printf("ERROR!");
	}
	top--;
}
template<typename T>
void stack<T>::push_back(const T value){
	if(top>=size-1) increment();
	top++;
	data[top]=value;	
}
template<typename T>
void stack<T>::increment(){
	T *newt=new T[size+INCREASE];
	if(!newt){
		printf("ERROR!");
		exit(1);
	}
	for(int i=0;i<=top;i++)
		newt[i]=data[i];
	delete[] data;
	data=newt;
	size=size+INCREASE;
}
template<typename T>
void stack<T>::clear(){
	top=-1;
}
template<typename T>
stack<T>::~stack(){
	delete[] data;
	top=-1;
	size=0;
}

template<typename T>
stack<T>::stack(){
	data=new T[INIT_SIZE];
	if(!data) {
		printf("ERROR!");
		exit(1);
	}
	top=-1;
	size=INIT_SIZE;
}

int main(int argc, char** argv) {
	cout<<"����Ϊջ(stack)�Ĳ��������"<<endl; 
	stack<int> st;
	for(int i=0;i<10;i++)
		st.push_back(i);
	for(int i=0;i<10;i++){
		cout<<st.top_element()<<" ";
		st.pop_back(); 
	}   
	cout<<endl<<"���������ϣ�ջ��������"<<endl<<endl;
	cout<<"������һ�����ݣ��ж������Ƿ���ģ�����end��ʾ�˳���"<<endl;
	stack<char> test;
	string s;
	while(true){
		cin>>s;
		bool flag=true;
		int is_odd=s.size()%2; 
		if(s=="end") break;
		for(int i=0;i<s.size()/2;i++)
			test.push_back(s[i]);	 
		for(int i=0;i<s.size()/2;i++){
			char c=test.top_element();		
			if(c!=s[s.size()/2+i+is_odd]){
				cout<<s<<"���ǻ�������"<<endl;
				test.clear();
				flag=false;
				break;
			}
			test.pop_back();	
		}
		if(flag)
			cout<<s<<"�ǻ�������"<<endl; 
	}
	return 0;
}
