#include <iostream>
#include <string.h>
using namespace std;

void merge(int arr[], int low, int mid, int high){
    int i, k;
    int *tmp = new int[high-low+1];
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;

    for(k=0; left_low<=left_high && right_low<=right_high; k++){  // �Ƚ�����ָ����ָ���Ԫ��
        if(arr[left_low]<=arr[right_low]){
            tmp[k] = arr[left_low++];
        }else{
            tmp[k] = arr[right_low++];
        }
    }

    if(left_low <= left_high){  //����һ��������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
    //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
    for(i=left_low;i<=left_high;i++)
        tmp[k++] = arr[i];
    }
    
    if(right_low <= right_high){
    //���ڶ���������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
    //memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
        for(i=right_low; i<=right_high; i++)
            tmp[k++] = arr[i];
    }

    for(i=0; i<high-low+1; i++)
        arr[low+i] = tmp[i];
    delete[] tmp;
    return;
}

void merge_sort(int arr[], unsigned int first, unsigned int last){
    int mid = 0;
    if(first<last){
        mid = (first+last)/2; /* ע���ֹ��� */
        /*mid = first/2 + last/2;*/
        //mid = (first & last) + ((first ^ last) >> 1);
        merge_sort(arr, first, mid);
        merge_sort(arr, mid+1,last);
        merge(arr,first,mid,last);
    }
    return;
}

void change(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
int Partition(int r[ ], int first, int end){
    int i=first; 
	int j=end;         //��ʼ��
    while (i<j){  
        while (i<j && r[i]<=r[j]) j--;  //�Ҳ�ɨ��
        if(i<j) { 
            change(&r[i],&r[j]);           //����С��¼������ǰ��
            i++; 
        }
        while (i<j && r[i]<= r[j]) i++;  //���ɨ��
        if(i<j) {
            change(&r[i],&r[j]);            //���ϴ��¼����������
            j--; 
        }
    }
    return i;    // iΪ��ֵ��¼������λ��
}

void QuickSort(int r[ ], int first, int end){
     if (first<end) {      
        int pivot=Partition(r, first, end);  
          //����ֽ⣬pivot����ֵ�������е�λ��
        QuickSort(r, first, pivot-1); 
          //�ݹ�ض���������н��п�������
        QuickSort(r, pivot+1, end);
         //�ݹ�ض��Ҳ������н��п�������
     }
  }

int main(int argc, char** argv) 
{
	int n[100]={5,4,8,1,6,3,2,9,7,0};
	int m[100];
	merge_sort(n,0,9);
	for(int i=0;i<10;i++)
		cout<<n[i]<<" ";
	cout<<endl; 
	
	int n2[100]={5,4,8,1,6,3,2,9,7,0};
	QuickSort(n2,0,9);
	for(int i=0;i<10;i++)
		cout<<n2[i]<<" ";
	cout<<endl;
	
	return 0;
}
