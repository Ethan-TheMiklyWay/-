#include <iostream>
#include <string.h>
using namespace std;
 
void insert(char c1[],char c2[],char c,int i){
//��c ����c1 ����c1���Ƶ�c2
	int j;
	for(j=0;j<i;j++)
		c2[j]=c1[j];
	c2[i]=c;
	for(j=i+1;j<=strlen(c1)+1;j++)
		c2[j]=c1[j-1];
}
void perml(int n){
//Ϊ�������м���Ԫ�صĸ���
	int i,j,k,m=1;
	char **c[2];//���������ַ����д洢���ֱ�洢i-1��i��ȫ����
	
	c[1]=new char*[1];
	c[1][0]=new char[2];
	c[1][0][0]='1'; 
	c[1][0][1]=0;
	
	for(i=2;i<=n;i++){
		m=m*(i-1);
		c[i%2]=new char*[m*i];
		for(j=0;j<m;j++){
			for(k=0;k<i;k++){
				c[i%2][j*i+k]=new char[i+1];
				insert(c[(i+1)%2][j],c[i%2][j*i+k],char(i+'0'),k);
			}
			delete[] c[(i+1)%2][j];
		}
		delete[] c[(i+1)%2];
	}
	for (i=0;i<m*n;i++){
		cout<<"��"<<i+1<<"���У�"<<c[n%2][i]<<endl;
		delete[] c[n%2][i];
	}
}
/*
�����Ӽ�
    1����ʼ��һ������Ϊn�ı��ش�s=00��0������Ӧ���Ӽ������
    2��for (i=1; i<2n; i++)
          2.1  s++��
          2.2  ��s��Ӧ���Ӽ����
*/
int main(int argc, char** argv) 
{
	perml(5);

	return 0;
}
