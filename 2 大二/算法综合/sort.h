#include<vector>
#include<algorithm>
#include<iostream>
#include <time.h>

#define SORT_SET 1
//�������ͷ�ļ��ı�ʶ 
using namespace std;
struct vote{
	int number;
	int point;
}; 

/*
����������ȥʵ�֣����Ǻ����������ʹ���࣬û���ú�������Ϊ�������д��ݲ���
���ԾͰ���ȡ���� ��������������Կ������Եĺ����� 

class Sort{
	private:
		void merge(vote *result, int low, int mid, int high);
		void exchange(vote *a,vote *b);
		int Partition(vote *r,int first,int end);
		int max_digit(vote *result,int first,int end);
		void rectify_max_heap(vote *result,int start,int end); 
	public:		
		void bubble_sort(vote *result,int begin,int end);
		void merge_sort(vote *result,int first,int last);
		void bubble_sort2(vote *result,int begin,int end);
		void quickSort(vote *result,int first,int end);
		void select_sort(vote *result,int first,int end);
		void bucket_sort(vote *result,int first,int end);
		void counting_sort(vote *result,int first,int end);
		void base_sort(vote *result,int first,int end);
		void insert_sort(vote *result,int first,int end);
		void shell_sort(vote *result,int first,int end);
		void heap_sort(vote *result,int len);
}; 

*/
inline void exchange(vote *a,vote *b){
	/**************
		�������������Ľ��� 
	*/
	int temp=a->number;
	a->number=b->number;
	b->number=temp;
	temp=a->point;
	a->point=b->point;
	b->point=temp;
}

void shell_sort(vote *result,int first,int end) {
	/***************************************************************
		ϣ�����򣺸Ľ���Ĳ�������ϣ���������ٽ����Ĵ����ͱ�
		�ϵĴ��������㷨Ϊ���ȶ��͵��㷨������һ���������У���
		װ����������н��в�������Ȼ���ٵ����������У��൱��
		��ԭ��ΪO(n2)���ӶȵĲ�������ֽ�Ϊ���ɸ���ÿ������O(m2)
		���Ӷȵ�С�͵Ĳ��������޷�����ʱ�临�Ӷȣ�����ʱ�临��
		��Ҫ����O(nlogn)��С��O(n2)��	 
	****************************************************************/
    int increment=end-first+1; 
    int temp_point;
    int temp_number; 
    int i,j;
    do{
        increment=increment/3+1;
        for(i=first+increment;i<=end;++i){    //��ÿ�����ֽ���ֱ�Ӳ�������
            if(result[i-increment].point>result[i].point){
                temp_point=result[i].point;
                temp_number=result[i].number;
                j=i-increment;
                do{  
                    result[j+increment].point=result[j].point;
                    result[j+increment].number=result[j].number;
                    j-=increment;
                }
				while(j>=first&&result[j].point>temp_point);
                result[j+increment].point=temp_point;  //����Ԫ��
                result[j+increment].number=temp_number;
            }
        }
    }while(increment>1);
   	for(i=first;i<first+(end-first)/2;i++)
		exchange(&result[i],&result[end+first-i]);
}
 

void insert_sort(vote *result,int first,int end){
	/*************************************************************
		�����������еĿ�ͷ��ʼ��������������λ��֮ǰ����Ϊ��
		�����У�֮��ÿѡ��һ�����֣��ͰѸ����ֲ�����֮ǰ�ĵ���
		�ֽ��н�����ֱ�����λ��֮ǰ�������ٴεı�Ϊ�������У�
		ʱ�临�Ӷ�ΪO(n2)	 
	*************************************************************/
	int i,j;
	for(int i=first+1;i<=end;i++){
		int temp_num=result[i].number;
		int temp_point=result[i].point;
		for(j=i-1;j>=first;j--){
			if(result[j].point<temp_point){
				result[j+1].point=result[j].point;
				result[j+1].number=result[j].number;
			}
			else break;
		}
		result[j+1].point=temp_point;
		result[j+1].number=temp_num;
	}

}

int max_digit(vote *result,int first,int end){
	//���ڻ�ȡ������ֵ����λ�� 
	int max_num=0;
	int i,j;
	for(i=first;i<=end;i++){
		int count=1;
		int tem=result[i].point;
		while(tem/10!=0){
			tem=tem/10;
			count++;
		}
		if(count>max_num)
			max_num=count;//�����λ����ֵmax
	}
	return max_num;
}
void base_sort(vote *result,int first,int end){
	/*************************************************************
		�����������������Ϊn����¼��d���ؼ��룬�ؼ����ȡֵ
		��ΧΪradix����ʱ�临�Ӷ�ΪO(d(n+radix))��ԭ��Ϊ��һ��
		�ؼ���Ϊ10������ʮ���Ƶ�����ÿ��ȡ��һλ�������е�����
		����һλ��������Ȼ��ϲ�Ϊһ�����С���ȡ��һ��λ����
		�����н������µ�����һ������d�Σ�dΪ�������������λ����
	*************************************************************/
	int maxx=max_digit(result,first,end); 
	int num=1;
	int i,j,k;
	for(i=0;i<maxx;i++){ 
		int count[10];
		int *temp_num[10];
		int *temp_point[10];
		for(j=0;j<10;j++){
			count[j]=0;
			temp_num[j]=new int[end-first+1];
			temp_point[j]=new int[end-first+1];
			for(k=0;k<end-first+1;k++){
				temp_num[j][k]=0;
				temp_point[j][k]=0;
			}
		}
		for(j=first;j<=end;j++){
			k=result[j].point/num;
			k=k%10;
			count[k]++;
			int te=count[k]-1;
			temp_point[k][te]=result[j].point;
			temp_num[k][te]=result[j].number;
		}
		int locate=0;
		for(j=0;j<10;j++){
			for(k=0;k<count[j];k++){ 
				result[locate].number=temp_num[j][k];
				result[locate].point=temp_point[j][k];
				locate++;
			}
		}
		num=num*10;
	}
	for(i=first;i<first+(end-first)/2;i++)
		exchange(&result[i],&result[end+first-i]);
	
}

 
void counting_sort(vote *result,int first,int end){
	/*************************************************************
		�������򣺼����������е����ֵ����Сֵ�ֱ���max��min��
		����һ����СΪmax-min������ռ䣬����һ����������У�
		��ÿ������Ӧ�±�λ�õ�����+1�����Ӵ�С����һ����
		���ٵ����飬�����Ӧλ�õ����ֳ��ִ����εı��+min��
		�ɡ�ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(max-min)��
	*************************************************************/
	int max_num=0;
	int min_num=100000;
	int i,j,k;
	for(i=first;i<=end;i++){
		if(max_num<result[i].point)
			max_num=result[i].point;
		if(min_num>result[i].point)
			min_num=result[i].point;
	}
	int *space=new int[max_num-min_num+1];
	vector<int> *num=new vector<int>[max_num-min_num+1];
	
	for(i=0;i<max_num-min_num+1;i++){
		space[i]=0;
	}
	for(i=first;i<=end;i++){
		space[result[i].point-min_num]++;
		num[result[i].point-min_num].push_back(result[i].number);
	}
	int locate=first;
	for(i=max_num-min_num+1-1;i>=0;i--){
		for(j=0;j<space[i];j++){
			result[locate].point=i+min_num;
			result[locate].number=num[i][j];
			locate++;
		}
	}
}
 
void bucket_sort(vote *result,int first,int end){
	/*************************************************************
		ľͰ���򣺽�n�������������С�ֳ�k���飬����ƽ��ÿ��m
		������ÿ�����ڽ������򣬸���ʱ�临�ӶȲ�ͬ����ΪO(m2)
		��O(mlogm)������մ�С˳����������
	*************************************************************/
	int max_num=0;
	int min_num=100000;
	int i,j,k;
	for(i=first;i<=end;i++){
		if(max_num<result[i].point)
			max_num=result[i].point;
		if(min_num>result[i].point)
			min_num=result[i].point;
	}
	int part=(max_num-min_num)/10+1;
	vector<vote> res[10];
	for(i=first;i<=end;i++){
		int index=result[i].point;
		index=(index-min_num)/part;
		res[index].push_back(result[i]);
	}
	for(i=0;i<10;i++){
		for(j=0;j<int(res[i].size())-1;j++){
			for(k=0;k<int(res[i].size())-1-j;k++){
				if(res[i][k].point<res[i][k+1].point){
					int temp=res[i][k].point;
					res[i][k].point=res[i][k+1].point;
					res[i][k+1].point=temp;
					temp=res[i][k].number;
					res[i][k].number=res[i][k+1].number;
					res[i][k+1].number=temp;
				}
			}	
		}
		
	}
	int locate=first;
	for(i=9;i>=0;i--){
		for(j=0;j<res[i].size();j++){
			result[locate]=res[i][j];
			locate++;
		}
	}
}
void select_sort(vote *result,int first,int end){
	/*************************************************************
		ѡ������ʱ�临�Ӷ�ΪO(n2)��ÿ�ν���ѡ��ʣ����������
		��ģ�������������һ�������н�����
	*************************************************************/
    int i;
    for(i=first;i<end;i++){
        int j=i;
        int min_index=i;
        for(j=i+1;j<=end;j++){
            if(result[j].point>result[min_index].point){
                min_index=j;
            }
        }
        if(min_index!=i){
            exchange(&result[i],&result[min_index]);  
        }
    }
}

int Partition(vote *result,int first,int end){
	//���ڿ�������ķָ� 
    int i=first; 
	int j=end;  
    while(i<j){  
        while (i<j&&result[i].point>=result[j].point)j--; 
        if(i<j){ 
            exchange(&result[i],&result[j]);           
            i++; 
        }
        while(i<j&&result[i].point>=result[j].point)i++;  
        if(i<j){
            exchange(&result[i],&result[j]);            
            j--; 
        }
    }
    return i;    
}

void quickSort(vote *result,int first,int end){
	/*************************************************************
		�����������������㷨֮һ�����ѡ��һ����־������
		������ֿ���ʹ�����������ұߣ�����С��������ߡ��ٵ�
		���������������顣ʱ�临�Ӷ�ΪO(nlogn)��
	*************************************************************/
     if(first<end){      
        int pivot=Partition(result,first,end);  
        quickSort(result,first,pivot-1); 
        quickSort(result,pivot+1,end);
     }
  }

void bubble_sort(vote *result,int begin,int end){
	/*************************************************************
		�������α�����ÿ�������ȽϽ��н�����ʱ�临�Ӷ�ΪO(n2)��
	*************************************************************/
	for(int i=begin;i<end;i++)
		for(int j=begin;j<end-i;j++){
			if(result[j].point<result[j+1].point){
				exchange(&result[j],&result[j+1]);
			}
		}
}
void bubble_sort2(vote *result,int begin,int end){
	/*************************************************************
		�Ż���ð��������ð������Ļ����ϣ����ñ�־λ��ÿ�α�
		��֮������жϣ��������Ҫ������ֱ�ӽ�����һ�ε�ѭ����
		����ʱ�临�Ӷ�С��O(n2)������ÿ��ѭ������һ���жϣ�Ч��
		����������ͨ��ð������
	*************************************************************/
    int exchange_=end;          //��һ����������ķ�Χ��r[1]��r[n]
    while (exchange_!=-1){      //������һ�������м�¼�����Ž��б�������
        int bound=exchange_;
		exchange_=-1;  
        for(int j=begin;j<bound;j++)          //һ����������
            if(result[j].point<result[j+1].point){
                exchange(&result[j],&result[j+1]);
                exchange_=j;         //��¼ÿһ�η�����¼������λ��
            }
    }
}

void merge(vote *result, int low, int mid, int high){
	//���ڹ鲢�����ĺϲ� 
    int i, k;
    vote *temp=new vote[high-low+1];
    int left_low=low;
    int left_high=mid;
    int right_low=mid+1;
    int right_high=high;

    for(k=0; left_low<=left_high && right_low<=right_high; k++){  
        if(result[left_low].point>=result[right_low].point){
        	temp[k].number=result[left_low].number ;
            temp[k].point=result[left_low].point ;
            left_low++;
        }
		else{
			temp[k].point=result[right_low].point;
            temp[k].number=result[right_low].number;
            right_low++;
        }
    }

    if(left_low<=left_high){  
	    for(i=left_low;i<=left_high;i++){
	    	temp[k].point=result[i].point;
            temp[k].number=result[i].number;
            k++;
		}
    }
    
    if(right_low <= right_high){
        for(i=right_low;i<=right_high;i++){
        	temp[k].point=result[i].point;
            temp[k].number=result[i].number;
            k++;
		}
    }

    for(i=0; i<high-low+1; i++){
    	result[low+i].point=temp[i].point;
    	result[low+i].number=temp[i].number;
	}
        
    delete[] temp;
    return;
}


void merge_sort(vote *result,int first,int last){
	/*************************************************************
	 	�鲢����:���÷��ε�˼�룬�����������鷴��һ��Ϊ����ֱ
		 �����ʣ����������ֱ�ӽ����õ��������κϲ��õ�������
		 ���顣ʱ�临�Ӷ�ΪO(nlogn)����ҪO(n)�Ŀռ俪����
	*************************************************************/
    int mid = 0;
    if(first<last){
        mid = (first+last)/2; 
        merge_sort(result, first, mid);
        merge_sort(result, mid+1,last);
        merge(result,first,mid,last);
    }
    return;
}

void rectify_max_heap(vote *result,int start,int end){  
	int dad = start;
	int son = 2*dad+1;
	//һֱɸѡ�����²� 
	while(son<=end){
		if(son+1<=end&&result[son].point<result[son+1].point){
			son++;
		}
		if(result[dad].point<result[son].point){
			swap(result[son],result[dad]);
			dad = son;
			son = 2*dad+1;
		}
		else{
			return ;
		}
	}
} 

void heap_sort(vote *result,int begin,int end){
	/*************************************************************
		��O(logn)��ʱ�临�ӶȽ��ѣ���O(logn)��ʱ�临�Ӷ�ά��һ
		�ζѣ���Ҫά��n�Σ���ʱ�临�Ӷ�ΪO(nlogn)����һЩά����
		�۽�С�ĳ���ʹ�ý϶ࡣ
	*************************************************************/
	//���� 
	int i;
	for(i=(end+1-begin)/2-1;i>-1;i--){
		rectify_max_heap(result,i,end-begin);
	}
	//ȡ�Ѷ��������ֵ���β������ά���� 
	for(i=(end-begin);i>0;i--){
		swap(result[0],result[i]);
		rectify_max_heap(result,0,i-1);
	}	
	for(i=begin;i<begin+(begin-end)/2;i++)
		exchange(&result[i],&result[end+begin-i]);
} 
 

void ssort(vote *result,int begin,int end){
	/**************
	�����㷨������stl�е������㷨�������жϣ�������ݵķ�ΧС����ü�������
	�������ȡһ�������㷨 
	*/
	int i;
	int minn=100000;
	int maxx=-100000;
	for(i=begin;i<=end;i++){
		if(result[i].point>maxx)
			maxx=result[i].point;
		if(result[i].point<minn)
			minn=result[i].point;
	}	
	if(maxx-minn<=200000)
		counting_sort(result,begin,end);
	else{
		srand((unsigned)time(NULL));
		int num=rand()%5;
		switch(num){
			case 0:
				merge_sort(result,begin,end);
				break;
			case 1:
				quickSort(result,begin,end);
				break;
			case 2:
				shell_sort(result,begin,end);
				break;
			case 3:
				heap_sort(result,begin,end);
				break;
			case 4:
				base_sort(result,begin,end);
				break;
		}
	}
}
 
