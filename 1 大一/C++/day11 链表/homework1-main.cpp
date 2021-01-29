//StudybarCommentBegin
#include <iostream>
using namespace std;

class List
{
private:
	int data;	// �洢Ԫ��
	List *link;	// ��һԪ�ؽṹ��ָ��
	List *head=NULL;   //��һ��Ԫ�� 
    List *now=NULL;
public:
	List();
	void append(int val);	// ��β����һ��Ԫ��
	void insertElement(int pos, int val);	// ��ָ��λ�����һ��Ԫ��
	void deleteElement(int val);	// ɾ��Ԫ��	
    void travalList()const;	// ��ͷ�ڵ�����������

};
//StudybarCommentEnd

List::List()
{
	link=NULL; 
} 
void List::append(int k)
{
	List *p;
	p=new List;
	p->data =k;
	p->link =NULL;
	if(head==NULL)
	{
		head=p;           //ȷ����һ��Ԫ�صĵ�ַ	 
		now=p;              //sҲ��ŵ�һ��Ԫ�ص�ַ 
	}
	else
	{ 
	    now->link =p;
        now=p;
	}  
}  
void List::travalList () const
{
	List *q=head;
	while(q->link!=NULL)
	{
		cout<<"->"<<q->data;
		q=q->link ;
	}
	cout<<"->"<<q->data<<endl ;	
}
void List::insertElement(int pos, int val)
{
	List *p=new List;
	p->data =val;
	List *st=head;
	for(int k=0;k<pos;k++) st=st->link ;
	p->link =st->link;
	st->link=p;
}
void List::deleteElement(int val)
{
	List *p=head,*before=head;
	while(p->link!=NULL)
	{
		if(p->data ==val) break;
		before=p;
		p=p->link;
	}
	if(p->link==NULL &&p->data !=val) cout<<endl<<"Element "<<val<<" not Found."<<endl;   //û�ҵ� 
	else if(before==p) //Ҫɾ�����ǵ�һ�� 
	{
	    head=p->link; 
		delete p;
	}
	       
	else if(p->data==val)                    //Ҫɾ���������һ�� 
	{
		before->link=NULL;
		delete p;
	}
	else
	{
		before->link =p->link; 
		delete p;
	}
}
//StudybarCommentBegin
int main(void)
{
	List list;
	list.append(10);
	list.append(8);
	list.append(12);
	list.append(100);
	list.travalList();
	list.insertElement(1, 20);
	list.travalList();
	list.deleteElement(2);
	list.deleteElement(10);
	list.travalList();
}
//StudybarCommentEnd

