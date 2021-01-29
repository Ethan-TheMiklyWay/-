#include <iostream>
using namespace std;
template <typename T>
class DynamicArray {
private:
T* array; //pointer  ��һ��T���͵�ָ��
unsigned int mallocSize; //����ռ�Ĵ�С��

public:
//Constructors 
 DynamicArray(unsigned length, const T &content)  
{
    mallocSize=length;
    array=new T[length];
    for(int a=0;a<length;a++) array[a]=content;
    cout<<endl<< "new T["<<this->mallocSize<<"] malloc "<< this->mallocSize << "*"<<sizeof(T)<<"="<<this->mallocSize *sizeof(T)<<" bytes memory in heap";

 } 
//Copy Constructor 
DynamicArray(const DynamicArray<T> & anotherDA ) 
{
	mallocSize=anotherDA.mallocSize ;
	array=new T[mallocSize];
	for(int a=0;a<mallocSize;a++) array[a]=anotherDA.array[a] ;
	cout<<endl<< "Copy Constructor is called";
}
// Destructors
 ~DynamicArray()
{cout<<endl<< "delete[] array free "<< this->mallocSize << "*"<<sizeof(T)<<"="<<this->mallocSize *sizeof(T)<<" bytes memory in heap"; 

}
//return the this->mallocSize
//unsigned int capacity() const;

T& operator[](unsigned int i) 
{
	return this->array[i];
}

DynamicArray<T> & operator= (const DynamicArray<T> & anotherDA ) 
{
	cout<<endl<<"operator = is called";
	mallocSize=anotherDA.mallocSize ;
	array=new T[mallocSize];
	for(int a=0;a<mallocSize;a++) array[a]=anotherDA.array[a] ;
	return *this;
	
}

};



//StudybarCommentBegin


int main()
{
int length,i;
cin>> length;

DynamicArray<int> iarray(length,-1);

DynamicArray<int> iarray2(iarray),iarray3(iarray2);

cout<<endl;
for(i=0;i<length;i++) {
	cout << iarray3[i] <<" ";
	iarray[i] = i*1.1;	
}
iarray3=iarray2=iarray;
cout<<endl;
for(i=0;i<length;i++) {
	cout << iarray3[i] <<" ";	
}

return 0;
}
//StudybarCommentEnd
