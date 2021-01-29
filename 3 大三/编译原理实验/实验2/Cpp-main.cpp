//StudybarCommentBegin

#include<stdio.h>
#include<string.h>

#include<stdlib.h>
char prog[80];  //����������ַ� 
char token[8];   //����ȡ�����ַ� 
char ch;  //��ʱ���� 
int syn, p, m = 0, n, sum = 0; //p �ǻ����� prog ��ָ�룬m �� token ��ָ��
char rwtab[6][6] = { "begin","if","then","while","do","end" };
//ͬѧ����Ҫдһ��scaner()������Ȼ���ϴ������������£���Ҫ�Ѻ������еġ�������ա���������ϴ�������7���ִ�����Ҫ��䡣����ȥ�������ⲿ��/*   */ע�������.c��ʽ���ļ��ϴ���ϵͳ��ϲ�ǰ׺+�ϴ�����+��׺�����б��롣

//StudybarCommentEnd

void scaner()
{
	for (n = 0;n<8;n++)
		token[n] = '\0';
	ch = prog[p++];
	while (ch == ' ') //���ַ�
 		//�������1//���Կո�
 		ch = prog[p++];
 	
	if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))//��ʶ���ͱ�����
	{
		m = 0;
		while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9'))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		token[m++] = '\0';
		p--;
		syn = 10; //���õ����ֱ��� syn Ϊ 10����ʶ����
		for (n = 0;n<6;n++)
			if (!memcmp(token, rwtab[n], m - 1))
			{
				syn=n+1;
 				//�������2//���õ����ֱ��� syn�������֣�
				break;
			}
	}
	else
		if (ch >= '0'&&ch <= '9')//����
		{
			sum = 0;
			while (ch >= '0'&&ch <= '9') //�����ִ�ת��Ϊ��ֵ���� sum
			{
				sum=sum*10+ch-'0';
				ch = prog[p++];
 				//�������3
			}
			if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')) {
				while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))
				{
					ch = prog[p++];
				}
				p--;
				syn=-1; 	
				//�������4 //���õ����ֱ��� syn Ϊ-1������
			}
			else {
				p--;
 				syn=11;//���õ����ֱ��� syn
			}
		}
		else
			switch (ch)//�������ֺ���ĸ
			{
				case'>':
					m = 0;
					token[m++] = ch;
					ch = prog[p++];
					if (ch == '=')
					{
						syn = 24; //���õ����ֱ��� syn Ϊ 24��>=��
						token[m++] = ch;
					}
					else
					{
						syn = 23; //���õ����ֱ��� syn Ϊ 23��>��
						p--;
					}
					break;
				case'<':
				 	//�������5//���<��<=��<>�ţ����õ����ֱ���syn��ֵ
				 	m = 0;
					token[m++] = ch;
					ch = prog[p++];
					if (ch == '=')
					{
						syn = 22; 
						token[m++] = ch;
					}
					else if (ch == '>')
					{
						syn = 21; 
						token[m++] = ch;
					}
					else
					{
						syn = 20; 
						p--;
					}
                    break;
				case':':
					m = 0;
					token[m++] = ch;
					ch = prog[p++];
					if (ch == '=')
					{
						syn = 18; 
					 	//�������6//���õ����ֱ��� syn
						token[m++] = ch;
					}
					else
					{
						syn = 17; 
					 	//�������7//���õ����ֱ��� syn
						p--;
					}
					break;
				case'-':syn = 13;token[0] = ch;break;
				case'+':syn = 14;token[0] = ch;break;
				case'*':syn = 15;token[0] = ch;break;
				case'/':syn = 16;token[0] = ch;break;
				case';':syn = 26;token[0] = ch;break;
				case')':syn = 27;token[0] = ch;break;
				case'(':syn = 28;token[0] = ch;break;
				case'#':syn = 0;token[0] = ch;break;
				default:syn = -1;
			}
}



//StudybarCommentBegin
int main()
{
	char test1[80]="begin A1:=9; X1:=2*3; B:=A1+X1 end#";
	char test2[80]="while r<>0 do begin q:=m/n r:=m-q*n; m:=n; n:=r; end#";
	char test3[80]="begin if m<n then r:=m; m:=n; n:=r; end;#";
	char test4[80]="1a#";
	int i;
	scanf("%d",&i);
	{ 
		switch(i)
		{
			case 1:strcpy(prog,test1); break;
			case 2:strcpy(prog,test2);break;
			case 3:strcpy(prog,test3); break;
			case 4:strcpy(prog,test4);break;
		}
		p = 0;
		do
		{
			scaner();
			switch (syn)
			{
				case 11: printf("(11,%d)",sum ); break;
				case -1: printf("error!"); break;
				default: printf("(%d,%s)", syn, token );
			}
		} while (syn != 0);
		printf("\n");
	}
	return 0;
}
//StudybarCommentEnd
