#include <stdio.h>
#include "otherfunction.h"
#include "string.h"

int main()
{
	bool nxtlev[symnum];  
	fin = fopen("F:\\������\\����ԭ��ʵ��\\Fibonacci_e02.txt", "r");
	int trigernode=0;
	char c;
	printf("Open tree node[y/n]?");
	scanf("%c",&c);
	if(c=='y' || c=='Y')  trigernode=1;
	
	if(fin){
		ch=' ';
		init();     // ��ʼ�� 
		start_ofme(trigernode);
		fclose(fin);
	}
	else{
		printf("Can't open file!\n");
	}
	return 0;
} 

void start_ofme(int trigernode){
	trigernode_key=trigernode;
	printf("��ʼ���������\n"); 
	int i;
	getsymdo;
	program();
	levelup;
	getsymdo;
	printf("�������������\n");
}	

void program(){
	levelup;
	if (sym == constsym)    {
		// �յ������������ţ���ʼ���������� 
		getsymdo;
		constdeclaration_ofme();
	}
	if (sym == varsym){
		// �յ������������ţ���ʼ����������� 
		getsymdo;
		vardeclaration_ofme();
	}
	do{
		if (sym == procsym){
			getsymdo;
			procedure_ofme();
		}
	}while(sym==procsym);
	statement_ofme();
	leveldown;
}


void procedure_ofme(){
	levelup;
	if (sym == ident) {getsymdo;}
	else error(4);   // procedure��ӦΪ��ʶ��
	if (sym == semicolon) {getsymdo;}
	else error(5);   // ©���˷ֺ� 
	program();
	leveldown;
}

void constdeclaration_ofme(){
	levelup;
	if (sym == ident){
		getsymdo;
		if (sym==eql){
			getsymdo;
			if (sym == number){
				getsymdo;
			}
			else error(2);   // ����˵��=��Ӧ������ 
		}
		else error(3); //����˵����ʶ��Ӧ��=
	}
	else error(4);   //const��Ӧ�Ǳ�ʶ 
	while(sym==comma){
		getsymdo;
		if (sym == ident){
			getsymdo;
			if (sym==eql){
				getsymdo;
				if(sym == number){
					getsymdo;
				}
				else error(2);   // ����˵��=��Ӧ������ 
			}
			else error(3); //����˵����ʶ��Ӧ��=
		}
		else error(4);   //const��Ӧ�Ǳ�ʶ 
	}
	if (sym == semicolon) {getsymdo;}
	else error(5);   //©���˶��Ż��߷ֺ�
	leveldown;
}


void vardeclaration_ofme(){
	levelup;
	if (sym == ident) {getsymdo;}
	else error(4);   // var��Ӧ�Ǳ�ʶ 
	while (sym == comma){
		getsymdo;
		if (sym == ident)  {getsymdo;}
		else error(4);   // var��Ӧ�Ǳ�ʶ 
	}
	if (sym == semicolon)  {getsymdo;}
	else error(5);   //©���˶��Ż��߷ֺ�
	leveldown;
}

void statement_ofme(){
	levelup;
	if (sym == ident) { // ׼�����ո�ֵ��䴦�� 
		getsymdo;
		allot_number();
	}
	else if (sym == readsym){ // ׼�����ո�ֵ��䴦�� 
		getsymdo;
		read_number();
	}
	else if(sym == writesym){    // ׼������write��䴦����read����
		getsymdo;
		write_number();
	}
	else if(sym == callsym){   //׼������call��䴦��
		getsymdo;
		call_ofme();
	}
	else if(sym == ifsym){    // ׼������if��䴦��
		getsymdo;
		if_ofme();
	}
	else if(sym == beginsym){   //׼�����ո�����䴦��
		getsymdo;
		complex_statement();
	}	
	else if(sym == whilesym){   //׼������whilesym��䴦��
		getsymdo;
		while_ofme();
	}
	else{
		error(100);  //û����Ե���� 
	}
	
	//�жϾ��ӽ���
	if (sym == semicolon || sym == endsym || sym == period){
		if (sym == semicolon || sym == semicolon) {getsymdo;}
	}
	else {
		error(5);   //©���˶��Ż��߷ֺ�
	}
	leveldown;
}

void while_ofme(){
	levelup;
	condition_ofme();
	if (sym == dosym)  {getsymdo;}
	else error(18);  // ȱ��do
	statement_ofme();
	leveldown;
} 

void complex_statement(){
	levelup;
	statement_ofme();
	while(sym != endsym){
		statement_ofme();
	}
	if (sym == endsym)  {getsymdo;}
	else error(18); 
	leveldown; 
}

void if_ofme(){
	levelup;
	condition_ofme();
	if (sym == thensym) {getsymdo;}
	else error(16);  // ȱ��then 
	statement_ofme();
	leveldown;
}


void call_ofme(){
	levelup;
	if (sym != ident) error(14);  // call��ӦΪ��ʶ�� 	
	getsymdo;
	leveldown;	
}


void write_number(){
	levelup;
	if (sym != lparen) error(34);  // ��ʽ����Ӧ�������� 
	do{
		getsymdo;
		expression_ofme();
	}while (sym == comma);
	if(sym == rparen) {getsymdo;}
	else error(33);
	leveldown;
}

void read_number(){
	levelup;
	if (sym != lparen) error(34);  // ��ʽ����Ӧ�������� 
	do{
		getsymdo;
		if (sym == ident) {getsymdo;}	
		else error(35);	
	}while (sym == comma);
	if(sym == rparen) {getsymdo;}
	else error(33);
	leveldown;
}


void allot_number(){
	levelup;
	if(sym == becomes) {getsymdo;}
	else error(13);  // û�м�⵽��ֵ���� 
	expression_ofme();
	leveldown;
}

void condition_ofme(){
	levelup;
	expression_ofme();
	if (sym!=eql && sym!=neq && sym!=lss && sym!=leq && sym!=gtr && sym!=geq)
		error(20);
	getsymdo;
	expression_ofme();
	leveldown;
}

void expression_ofme(){
	levelup;
	if(sym==plus || sym==minus) {
	// ��ͷ�������ţ���ʱ��ǰ���ʽ������һ�����Ļ򸺵��� 
		getsymdo;
		term_ofme();
	}
	else term_ofme();
	while (sym==plus || sym==minus){
		getsymdo;
		term_ofme();
	}
	leveldown;
}

void term_ofme(){
	levelup;
	factor_ofme(); 
	while(sym==times || sym==slash){
		getsymdo;
		factor_ofme();
	}
	leveldown;
}

void factor_ofme(){
	levelup;
	if(sym == ident){    // ����Ϊ��������� 
		getsymdo;
	}
	else if(sym == number){
		getsymdo;
	}
	else if (sym == lparen){
		getsymdo;
		expression_ofme();
		if (sym == rparen) {getsymdo;}
		else error(22);  // ȱ�������� 
	}
	leveldown;
}









