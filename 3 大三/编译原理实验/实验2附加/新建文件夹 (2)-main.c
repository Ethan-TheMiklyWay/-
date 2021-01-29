#include <stdio.h>
#include "pl0.h"
#include "string.h"
void startsplit();
//�ó���Ϊ�����Ĵʷ���������
//F:\������\����ԭ��ʵ��\Fibonacci_e02.txt
int main()
{
	bool nxtlev[symnum];
	//printf("Input a file:");
	//scanf("%s", fname);    
	fin = fopen("F:\\������\\����ԭ��ʵ��\\Fibonacci_e02.txt", "r");
	
	
	if(fin){
		ch=' ';
		init();     // ��ʼ�� 
		
		startsplit();
		fclose(fin);
	}
	else{
		printf("Can't open file!\n");
	}
	return 0;
} 

char name[10]="";
void startsplit(){
	printf("��ʼ������\n"); 
	int i;
	while(true){
		getsym();
		printf("(%s,%d)\n",name,sym);
		if(name[0]=='.')
			break;
	}
	printf("����������\n");
}

void init()
{
	int i;

	// ���õ��ַ����� 
	for (i=0; i<=255; i++)
	{
		ssym[i] = nul;
	}
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym['='] = eql;
	ssym[','] = comma;
	ssym['.'] = period;
	ssym['#'] = neq;
	ssym[';'] = semicolon;

	// ���ñ���������,������ĸ˳�򣬱����۰���� 
	strcpy(&(word[0][0]), "begin");
	strcpy(&(word[1][0]), "call");
	strcpy(&(word[2][0]), "const");
	strcpy(&(word[3][0]), "do");
	strcpy(&(word[4][0]), "end");
	strcpy(&(word[5][0]), "if");
	strcpy(&(word[6][0]), "odd");
	strcpy(&(word[7][0]), "procedure");
	strcpy(&(word[8][0]), "read");
	strcpy(&(word[9][0]), "then");
	strcpy(&(word[10][0]), "var");
	strcpy(&(word[11][0]), "while");
	strcpy(&(word[12][0]), "write");

	// ���ñ����ַ��� 
	wsym[0] = beginsym;
	wsym[1] = callsym;
	wsym[2] = constsym;
	wsym[3] = dosym;
	wsym[4] = endsym;
	wsym[5] = ifsym;
	wsym[6] = oddsym;
	wsym[7] = procsym;
	wsym[8] = readsym;
	wsym[9] = thensym;
	wsym[10] = varsym;
	wsym[11] = whilesym;
	wsym[12] = writesym;
	// ����ָ������ 
	strcpy(&(mnemonic[lit][0]), "lit");
	strcpy(&(mnemonic[opr][0]), "opr");
	strcpy(&(mnemonic[lod][0]), "lod");
	strcpy(&(mnemonic[sto][0]), "sto");
	strcpy(&(mnemonic[cal][0]), "cal");
	strcpy(&(mnemonic[inte][0]), "int");
	strcpy(&(mnemonic[jmp][0]), "jmp");
	strcpy(&(mnemonic[jpc][0]), "jpc");

	// ���÷��ż� 
	for (i=0; i<symnum; i++)
	{
		declbegsys[i] = false;
		statbegsys[i] = false;
		facbegsys[i] = false;
	}

	// ����������ʼ���ż� 
	declbegsys[constsym] = true;
	declbegsys[varsym] = true;
	declbegsys[procsym] = true;

	// ������俪ʼ���ż� 
	statbegsys[beginsym] = true;
	statbegsys[callsym] = true;
	statbegsys[ifsym] = true;
	statbegsys[whilesym] = true;
	statbegsys[readsym] = true;
	statbegsys[writesym] = true;

	//�������ӿ�ʼ���ż� 
	facbegsys[ident] = true;
	facbegsys[number] = true;
	facbegsys[lparen] = true;
}

void error(int n)
{
	char space[81];
	memset(space,32,81);

	space[cc-1]=0; //����ʱ��ǰ�����Ѿ����꣬����cc-1

	printf("****%s!%d\n", space, n);
	fprintf(fa1,"****%s!%d\n", space, n);

	err++;
}

int getch()
{
	if (cc == ll)  //cc��ll���ڼ�¼��ȡָ�롣ÿ�ε��õ�ʱ�����cc=ll˵��������ȡ���ˣ�Ҫ���¶�ȡ�ļ�
	{              //ÿ�ζ�ȡ�ļ���ll��¼һ�еĳ��ȣ�cc��¼��ǰλ�á�ÿ�ε��øú�������ch�б�����һ���ַ�
		if (feof(fin))
		{
			printf("program incomplete");
			return -1;
		}
		ll=0;
		cc=0;
		printf("��ǰ���ӣ�");
		fprintf(fa1,"%d ", cx);  //д��
		ch = ' ';
		while (ch != 10)     //һֱ�������з�Ϊֹ
		{
			//fscanf(fin,"%c", &ch)
			//richard
			if (EOF == fscanf(fin,"%c", &ch))   //��������˽�β���˳�
			{
				line[ll] = 0;
				break;
			}
			//end richard
			printf("%c", ch);
			fprintf(fa1, "%c", ch);
			line[ll] = ch;
			ll++;
		}
		printf("\n");
		fprintf(fa1, "\n");
	} 
	ch = line[cc];
	cc++;
	return 0;
}


int getsym()
{
	int i,j,k;
	
	// the original version lacks "\r", thanks to foolevery 
	while (ch==' ' || ch==10 || ch==13 || ch==9)  // ���Կո񡢻��С��س���TAB 
	{
		getchdo;
	}
	if (ch>='a' && ch<='z')
	{           // ���ֻ�������a..z��ͷ 
		k = 0;
		do {    //ȡ��һ����
			if(k<al)
			{
				a[k] = ch;
				k++;
			}
			getchdo;
		} while (ch>='a' && ch<='z' || ch>='0' && ch<='9');
		a[k] = 0;
		strcpy(id, a);
		strcpy(name, a);
		
		i = 0;
		j = norw-1;
		
		do {    //������ǰ�����Ƿ�Ϊ������    //�۰�����Ƿ�Ϊ������
			k = (i+j)/2;
			if (strcmp(id,word[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp(id,word[k]) >= 0)
			{   //����ifͬʱ���㣬�Ǳ����֣��� j��iС2
				i = k + 1;
			}
			
		} while (i <= j);
		
		if (i-1 > j)
		{
			sym = wsym[k];   //��ȡ��һ��������
			
		}
		else
		{
			sym = ident; // ����ʧ���������ֻ����� 
		}
	}
	else
	{
		if (ch>='0' && ch<='9')
		{           // ����Ƿ�Ϊ���֣���0..9��ͷ 
			k = 0;
			num = 0;
			sym = number;
			do {
				num = 10*num + ch - '0';
				name[k]=ch;
				k++;
				getchdo;
			} while (ch>='0' && ch<='9'); // ��ȡ���ֵ�ֵ 
			name[k]='\0'; 
			k--;
			if (k > nmax)
			{
				error(30);
			}
		}
		else
		{
			if (ch == ':')      // ��⸳ֵ���� 
			{
				name[0]=':';
				getchdo;
				if (ch == '=')
				{
					sym = becomes;
					name[1]='=';
					name[2]='\0';
					getchdo;
				}
				else
				{
					sym = nul;  // ����ʶ��ķ��� 
					name[0]='n';
					name[1]='i';
					name[2]='l';
					name[3]='\0';
				}
			}
			else
			{
				if (ch == '<')      // ���С�ڻ�С�ڵ��ڷ��� 
				{
					name[0]='<';
					getchdo;
					if (ch == '=')
					{
						name[1]='=';
						name[2]='\0';
						sym = leq;
						getchdo;
					}
					else
					{
						name[1]='\0';
						sym = lss;
					}
				}
				else
				{
					if (ch=='>')        // �����ڻ���ڵ��ڷ��� 
					{
						name[0]='>';
						getchdo;
						if (ch == '=')
						{
							name[1]='=';
							name[2]='\0';
							sym = geq;
							getchdo;
						}
						else
						{
							name[1]='\0';
							sym = gtr;
						}
					}
					else
					{
						sym = ssym[ch];     // �����Ų�������������ʱ��ȫ�����յ��ַ����Ŵ��� 
						//getchdo;
						//richard
						name[0]=ch;
						name[1]='\0';
						if (sym != period)
						{
							getchdo;
						}
						//end richard
					}
				}
			}
		}
	}
	return 0;
}



