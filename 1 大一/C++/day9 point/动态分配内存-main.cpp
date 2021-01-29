//StudybarCommentBegin/*

#include <iostream>
using namespace std;
class Point {
public:
	Point();
	Point(int x, int y);
	~Point();
	int getX() const; 
	int getY() const; 
	void move(int newX, int newY);
private:
	int x, y;
};
//StudybarCommentEnd
Point::	Point(int a, int b){x=a;y=b;cout<< "Constructor called."<<endl;}
Point::Point(){x=0;y=0;cout<<"Default Constructor called."<<endl;}
 int  Point::getX()const {return x;}
int Point::getY() const{return y;}
void Point::move(int newX, int newY) 
{
x = newX;
y = newY;	
}
Point::~Point(){ cout<<"Destructor called."<<endl; }

int main() {
cout << "Step one: " << endl;
Point *ptr1 = new Point; //����Ĭ�Ϲ��캯��
cout<<ptr1->getX()<<endl; //���GetX 
delete ptr1; //ɾ�������Զ�������������
cout << "Step two: " << endl;
ptr1 = new Point(1,2);
cout<<ptr1->getX()<<endl; //���GetX 
delete ptr1;
return 0;
}


