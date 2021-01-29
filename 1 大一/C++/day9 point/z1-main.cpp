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
 {mallocSize=length;
  array=new T[length];
  for(int a=0;a<length;a++) array[a]=content;
cout<<endl<< "new T["<<this->mallocSize<<"] malloc "<< this->mallocSize << "*"<<sizeof(T)<<"="<<this->mallocSize *sizeof(T)<<" bytes memory in heap";; // mallocSize=length; ����ÿ��Ԫ�صĳ�ʼ������ content��
 }
// Destructors
 
 ~DynamicArray()
 {cout<<endl<< "delete[] array free "<< this->mallocSize << "*"<<sizeof(T)<<"="<<this->mallocSize *sizeof(T)<<" bytes memory in heap"; 
 }

 //return the this->mallocSize
 unsigned int capacity() const
 {
 	return mallocSize;
 }

// for the array[i]=someT.
  T& operator[](unsigned int i) 
   {
   	    return this->array[i];
   }

};

//StudybarCommentBegin
int main()
{
int length,i;
cin>> length;

DynamicArray<int> iarray(length,-1);
DynamicArray<double> darray(length,-2.1);

cout<<endl<<"capacity:"<<iarray.capacity()<<endl;

for(i=0;i<length;i++) {
cout << iarray[i] <<" ";
iarray[i] = i*1.1;
}
cout<<endl;
for(i=0;i<length;i++) {
cout << darray[i] <<" ";
darray[i] = i*1.1;
}
cout<<endl;
for(i=0;i<length;i++) {
cout << iarray[i] <<" ";
iarray[i] = i*1.1;
}
cout<<endl;
for(i=0;i<length;i++) {
cout << darray[i] <<" ";
}
}

//StudybarCommentEnd


