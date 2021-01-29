#include <iostream>
using namespace std;
 
class CNode{
	public:
	char data;
	CNode *link; 
	CNode(){
		link=NULL;
	}
};

class sqList{
	private:
		CNode *head;
		int length;
	public:
		sqList();                   
		~sqList();                
		void push_back(const char) ;   
		friend ostream& operator<<(ostream&out,sqList&sq);
		int getLength();
		bool isempty();
		char operator[](int i);
		int find(char t); 
		void insert(int location,char t);
		void erase(int location);
};

ostream& operator<<(ostream&out,sqList&sq){
	CNode* q=sq.head;
	while(q->link){
		out<<q->data<<" ";
		q=q->link;
	}
	return out;
}
sqList::sqList(){
    head=new CNode();
    length=0;
}

sqList::~sqList(){
	CNode *q=head;
	CNode *p;
	cout<<"��ǰɾ��Ԫ��"; 
	while(q->link){
		p=q;
		cout<<p->data<<" " ;
		q=q->link;
		delete p;
	}
}
int sqList::getLength(){
	return length;
}
char sqList::operator[](int i){
	if(i>=length) 
		return 0; 
	CNode *q=head;
	while(i--){
		q=q->link;
	} 
	return q->data ;
}
bool sqList::isempty(){
	return length==0;
}
void sqList::push_back(const char value){
	CNode *q=head;
	while(q->link){
		q=q->link;
	}
	q->data=value;;
	q->link=new CNode(); 
    length++;
}
int sqList::find(char t){
	CNode *q=head;
	int lo=0;
	while(q->link){
		if(q->data==t) 
			return lo;
	    lo++;
	}
	return -1;
}
void sqList::insert(int location,char t){
	if(location>length && location<=0) return ;
	CNode *q=head;
	while(location-->1){
		q=q->link;
	}
	CNode *qt=new CNode;
	qt->data=t;
	qt->link=q->link;
	q->link=qt;	
}
void sqList::erase(int location){
	if(location>length && location<=0) return ;
	CNode *q=head,*before=head;
	while(location-->1){
		before=q;
		q=q->link;
	}
	if(before!=head){
		before->link=q->link;
		delete q;
		return;
	}
	else{
		head=head->link;
		delete before;
	}
}
int main(int argc, char** argv) {
	sqList list;          //��ʼ��������
	for(int i=0;i<5;i++){
		list.push_back(97+i);  //���β���a,b,c,d,eԪ��
	}
	cout<<"������Ԫ��:"<<list<<endl;
	cout<<"��������"<<list.getLength()<<endl;    //����������Ԫ�غͳ���
	if(list.isempty())
		cout<<"����Ϊ��"<<endl;
	else
		cout<<"����Ϊ��"<<endl;             //	 �жϵ������Ƿ�Ϊ�ա�
	cout<<"����ĵ�����Ԫ��Ϊ"<<list[2]<<endl;  //���������ĵ�3��Ԫ�ء�
	cout<<"����a��λ��"<<list.find('a')<<endl;        //���Ԫ��a��λ�á�
	list.insert(4,'f');             //�ڵ�4��Ԫ��λ���ϲ���fԪ�ء�
	list.erase(3);
	cout<<"������Ԫ��:"<<list<<endl;
    //���ڴ������Ƕ������Բ���Ҫdelete���Զ��ͷ� 
	return 0;
}
