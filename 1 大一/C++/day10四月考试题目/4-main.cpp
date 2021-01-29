#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
class VectorDouble
{
	private:
		unsigned int xx,yy;//����̬����������������̬������ʵ�ʴ洢Ԫ�صĸ�����
		double *zz;
	public:
		VectorDouble(){	xx=0;yy=0;		}
		VectorDouble(double *a,double *b)
		{
			xx=b-a;
			yy=xx;
			double *p=a;
			zz=new double[xx];
			for(int d=0;d<xx;d++) {zz[d]=*p;p++;			} 
		}
		VectorDouble(const VectorDouble &z)
		{
			xx=z.xx;
			yy=z.yy;
			zz=new double[xx];
			for(int t=0;t<xx;t++) zz[t]=z.zz[t];
		}
		VectorDouble(int a,double b=0)
		{
			xx=a;yy=a;
			zz=new double[a];
			for(int t=0;t<a;t++) zz[t]=b;
		}
		double&  operator[](int t)
		{
			if(t<xx)
			return this->zz[t];
			else 
			{
				cout<<"Out of Range!";exit(1);
			}
		}

		int  capacity()const{return xx;		} 
		int size()const {return yy;		}
        const double& operator[](unsigned int i)   const
        {
        	return this->zz[i];
		} 
		VectorDouble operator=(const VectorDouble &z)
		{
			VectorDouble t;
			cout <<"operator = called" <<endl; 
			xx=z.xx;
			yy=z.yy;
			zz=new double[xx];
			for(int d=0;d<xx;d++) zz[d]=z.zz[d];
			return t;
		}
		friend ostream& operator<<(ostream &t,const VectorDouble &z)
		{
			for (int i=0; i<z.capacity(); i++)
            {
                cout << setw(10)<<z[i] << " ";
                if ((i+1)%5 == 0) {t<<endl;}
            }
            cout<<endl;
            return t;
		}
		double *begin(){return zz;		}
		double *end()
		{
			double  *p=zz;
			for(int d=0;d<xx;d++) p++;
			return p;
		}
		VectorDouble operator+=(double t)
		{
			double  *p=zz;
			for(int d=0;d<xx;d++) 
			{ 
			    *(zz+d)	=*(zz+d)+t;	 
			}
		}
};


//StudybarCommentBegin
int main()
{
    double numbers[10] = {0};
    
    for (int i = 0; i < 10 ; i++) {
        numbers[i] += i*1.1;
    }
   
    VectorDouble v1(numbers+1, numbers+7); //������numbers[1]��ʼ��������numbers[6],����numbers[7]
   
    cout << v1;
     
    double *iter1, *iter2;
    iter1 = v1.begin();
    iter2 = v1.end() - 1;
 
    cout << "first element: " << *iter1 << endl;
    cout << "last element: " << *iter2 << endl;
 
    VectorDouble v2(v1.begin()+2,v1.end()); //��v1�еĵ�����Ԫ�أ������һ��Ԫ�أ�Ϊv2��ʼ����
    cout << v2;
    
    double value;
    cin >> value;
    
    v2 += value; //v2��ÿ��Ԫ�ض���valueֵ���
    
    cout << v2; 
    
    return 0;
}

//StudybarCommentEnd
