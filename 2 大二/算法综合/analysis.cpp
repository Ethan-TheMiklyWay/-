#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>
#include "sort.h"

using namespace std;

void init(vote a[], int n)      //ʹ���������ʼ������������
{
    default_random_engine e;    //����c++11֧�ֵ��������������
    e.seed(time(0));
    uniform_int_distribution<unsigned> u(1, n); //��������ֲ�Ϊ���ȷֲ�
    for (int i = 0; i < n; i++)
    {
        a[i].point = u(e);
        a[i].number = i + 1;
    }
}

int main()
{
    ofstream out;
    out.open("data.txt");       //���ļ�����׼��������������ļ���

    clock_t start, end;
    vote *a = nullptr;

    for (int i = 10; i < 1000000; i+=100)   //ÿ����100�����ݣ���һ�����򲢼�¼����ʱ��
    {
        if (a)
            delete[] a;
        a = new vote[i];

        init(a, i);             //��ʼ������������

        Sort b;

        start = clock();

        //ѡ������������㷨

//        b.bubble_sort(a, 0, i-1);
//        b.select_sort(a, 0, i-1);
//        b.insert_sort(a, 0, i-1);
//        b.shell_sort(a, 0, i-1);
//        b.merge_sort()a, 0, i-1);
//        b.quickSort(a, 0, i-1);
//        b.base_sort(a, 0, i-1);
//        b.bucket_sort(a, 0, i-1);
//        b.counting_sort(a, 0, i-1);
        b.heap_sort(a, 0, i-1);

        end = clock();

        out << end - start << endl;         //�����������ļ�

        delete[] a;
        a = nullptr;
    }

    out.close();                //�ر��ļ���
    return 0;
}
