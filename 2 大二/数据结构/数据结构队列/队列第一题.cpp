#include <iostream>
#define SIZE 1000

using namespace std;
template<typename T>
class deque{
	private:
		T *data;
		int size;
		int rear;
		int front;
	public:
		deque(int size=SIZE);
		~deque();
		bool is_full();
		bool is_empty();
		bool add_rear(const T value);
		bool add_front(const T value);
		T pop_rear();
		T pop_front();
		int getsize();
};
template<typename T>
int deque<T>::getsize(){
	return (rear-front+size)%size;
}
template<typename T>
T deque<T>::pop_front(){
	if(this->is_empty()) throw "Queue empty.";
	T temp=data[front];
	front=(front+1)%size;
	return temp;
}
template<typename T>
T deque<T>::pop_rear(){
	if(this->is_empty()) throw "Queue empty.";
	T temp=data[rear];
	rear=(rear-1+size)%size;
	return temp;
}
template<typename T>
bool deque<T>::add_front(const T value){
	if(this->is_full()) return false;
	data[front]=value;
	front=(front-1+size)%size;
	return true;
}
template<typename T>
bool deque<T>::add_rear(const T value){
	if(this->is_full()) return false;
	data[rear]=value;
	rear=(rear+1)%size;
	return true;
}
template<typename T>
bool deque<T>::is_empty(){
	if(rear==front)
		return true;
	return false;
}

template<typename T>
bool deque<T>::is_full(){
	if((rear+1)%size==front)
		return true;
	return false;
}

template<typename T>
deque<T>::deque(int sizet){
	size=sizet;
	data=new T[size];
	rear=0;
	front=0;
}
template<typename T>
deque<T>::~deque(){
	delete data;
}
int main(int argc, char** argv) {
	cout<<"�Զ��н��в�����������д�СΪ8\n";
	deque<int> queue(8);
	for(int i=0;i<10;i++){
		if(queue.add_rear(i))
			cout<<"�ɹ���ӣ����Ԫ��Ϊ"<<i<<"����ǰ����Ԫ������Ϊ"<<queue.getsize()<<"��"<<endl;
		else 
			cout<<"���ʧ�ܣ�����������"<<endl;
	}
	cout<<"�Զ��н���ȡ��Ԫ�ز���"<<endl;
	for(int i=0;i<10;i++){
		try{
			int temp=queue.pop_front();
			cout<<"�ɹ����ӣ�����Ԫ��Ϊ"<<temp<<"����ǰ����Ԫ������Ϊ"<<queue.getsize()<<"��"<<endl;
		}
		catch(char const *t){
			cout<<"����Ϊ�գ��޷����ӣ�������Ϣ��"<<t<<endl;
		}
	} 
	cout<<"\n\n\n������ԴӶ�ͷ��ӣ���β����\n"; 
	for(int i=0;i<10;i++){
		if(queue.add_front(i))
			cout<<"�ɹ���ӣ����Ԫ��Ϊ"<<i<<"����ǰ����Ԫ������Ϊ"<<queue.getsize()<<"��"<<endl;
		else 
			cout<<"���ʧ�ܣ�����������"<<endl;
	}
	cout<<"�Զ��н���ȡ��Ԫ�ز���"<<endl;
	for(int i=0;i<10;i++){
		try{
			int temp=queue.pop_rear();
			cout<<"�ɹ����ӣ�����Ԫ��Ϊ"<<temp<<"����ǰ����Ԫ������Ϊ"<<queue.getsize()<<"��"<<endl;
		}
		catch(char const *t){
			cout<<"����Ϊ�գ��޷����ӣ�������Ϣ��"<<t<<endl;
		}
	} 
	return 0;
}

