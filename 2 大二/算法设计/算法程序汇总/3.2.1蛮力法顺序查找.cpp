#include <iostream>
using namespace std;
 
int SeqSearch2(int r[ ], int n, int k)  //����r[1] ~ r[n]��Ų��Ҽ���
{   
    r[0]=k; 
	int i=n;
    while (r[i]!=k)
		i--;
    return i;
}

int main(int argc, char** argv) 
{
	int i,a[10];
	for(i=0;i<10;i++)
		a[i]=i;
	cout<<SeqSearch2(a,9,5);
	
	return 0;
}
