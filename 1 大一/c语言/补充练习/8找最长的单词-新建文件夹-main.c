#include <stdio.h>
#include <string.h>
int word(char c)
{
if((c>='a'&&c<='z')||(c>='A'&&c<='Z')) return 1;
else return 0;
}

int longest(char str[]) 
{
int i,flag=1,len=0,point,max_len=0,max_point; 
for(i=0;i<=strlen(str);i++)
{
    if(word(str[i])) //�ж��Ƿ�ΪӢ��
    {
        if(flag==1) //���ʵ�һ���ҵ���ı��־
        {
          point=i; 
          flag=0;
        }
        else len++; //��ʼ��������ʳ��Ƚ����ۼ�
    }
    else //��Ӣ����ĸ
    {
        flag=1; 
        if(len>max_len)
        {
        max_len=len;
        max_point=point;
        }
    len=0;
    }
}
return (max_point);
}
int main()
{
int word(char c);
int longest(char str[]);
int i;
char str[80];
gets(str);
printf("word=");
for(i=longest(str);word(str[i]);i++)
printf("%c",str[i]);
printf("\n");
return 0;
}
