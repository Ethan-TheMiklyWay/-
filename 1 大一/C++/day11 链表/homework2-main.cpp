#include <iostream>
using namespace std;

class List
{
private:
	int data;	// 存储元素
	List *link;	// 下一元素结构的指针
	List *head=NULL;   //第一个元素 
    List *now=NULL; 
public:
	List();
	List(List &);
	void append(int val);	// 链尾增加一个元素
	void insertElement(int pos, int val);	// 在指定位置添加一个元素
	void deleteElement(int val);	// 删除元素	
    void travalList()const;	// 从头节点遍历输出链表
    void getLength();
};

List::List(List &t)
{
	List *p=t.head ;	
	while(p->link !=NULL)
	{
		append(p->data);
		p=p->link ;
	}
	append(p->data );
}
List::List()
{
	link=NULL; 
} 
void List::append(int k)
{
	List *p;
	p=new List();
	p->data =k;
	p->link =NULL;
	if(head==NULL)
	{
		head=p;           //确定第一个元素的地址	 
		now=p;              //s也存放第一个元素地址 
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
	List *p=new List();
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
	if(p->link==NULL &&p->data !=val) cout<<endl<<"Element "<<val<<" not Found."<<endl;   //没找到 
	else if(before==p) //要删除的是第一个 
	{
	    head=p->link; 
		delete p;
	}
	       
	else if(p->data==val)                    //要删除的是最后一个 
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
void List::getLength() 
{
	List *p=head;
	int k=0;
	while(p->link !=NULL)
	{
		k++;
		p=p->link ;
	}
	cout<<endl<<"The length of this List is "<<++k<<"."<<endl;
}



//StudybarCommentBegin
int main(void)
{
	int n;
	List  listA;

	cin >> n;
	while (n != -1)
	{
		listA.append(n);
		cin >> n;
	}
	
	listA.travalList();
	List listB(listA);
        listA.append(250);
	listB.getLength();
	listB.travalList();
}
//StudybarCommentEnd

