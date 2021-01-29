
#include "pl0.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char base_path[15] = "base.data";
char save_path[15] = "save.s";

void write_mips_inst(FILE *save_file,int *jump_record){
	
	int i; 
	for(i=0;i<cx-1;i++)
   	{
   		char buffer[50] = {0};
		char temp_buf[25] = {0};
		
		//���������к�
		char line_num[10] = {'#'};
		char tempt[10] = {0}; 
		itoa(i, tempt, 10);
		strcat(line_num, tempt);
		strcat(line_num, "\n");
		fputs(line_num, save_file);
		
		//�ж��Ƿ���Ҫ��ת
		if(jump_record[i]!=-1){
			char tempt2[20] = "user_location_";
			char tempt22[10];
			itoa(i, tempt22, 10);
			strcat(tempt2, tempt22);
			strcat(tempt2, ":\n");
			fputs(tempt2, save_file);
		} 
		
   		switch(code[i].f)
		{
			case lit:
				strcat(buffer, "        ori $t4, $zero, ");
				itoa(code[i].a, temp_buf, 10);
				strcat(buffer, temp_buf);
				strcat(buffer, "\n        jal _lit\n");  
				break;
			case opr:        
				strcat(buffer, "        jal _opr_");
				itoa(code[i].a, temp_buf, 10);
				strcat(buffer, temp_buf);
				strcat(buffer, "\n");
				break;
			case lod:       
				strcat(buffer, "        ori $t4, $zero, ");
				itoa(code[i].a * 4, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t4, $zero, number
				strcat(buffer, "\n        ori $t5, $zero, "); 
				itoa(code[i].l, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t5, $zero, number
				strcat(buffer, "\n        jal _lod\n");  
				break;
			case sto:       
				strcat(buffer, "        ori $t4, $zero, ");
				itoa(code[i].a * 4, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t4, $zero, number
				strcat(buffer, "\n        ori $t5, $zero, "); 
				itoa(code[i].l, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t5, $zero, number
				strcat(buffer, "\n        jal _sto\n");  
				break;		
			case cal:       //calָ���д�����   
			    strcat(buffer, "        jal _cal\n        sw $ra, ($t9)\n        addi $t9, 4\n        j user_location_");
				itoa(code[i].a, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t4, $zero, number
				strcat(buffer, "\n");   
				break;		
			case inte:      
				strcat(buffer, "        ori $t4, $zero, ");
				itoa(code[i].a * 4, temp_buf, 10);
				strcat(buffer, temp_buf);  //ori $t4, $zero, number
				strcat(buffer, "\n        jal _inte\n");
				break;			
			case jmp: 
				strcat(buffer, "        j user_location_");
				itoa(code[i].a, temp_buf, 10);
				strcat(buffer, temp_buf);
				strcat(buffer, "\n");
				break;
			case jpc:
				strcat(buffer, "        jal _jpc\n        beq $t6, $zero, user_location_");
				itoa(code[i].a, temp_buf, 10);
				strcat(buffer, temp_buf);
				strcat(buffer, "\n");
	    		break;
	    		
		}
		fputs(buffer, save_file);
   	}
   	char tempt2[20] = "user_location_";
	char tempt22[10];
	itoa(i, tempt22, 10);
	strcat(tempt2, tempt22);
	strcat(tempt2, ":\n        j _end\n");
	fputs(tempt2, save_file);
} 

void interpret_to_mips(){
	FILE *base_file = fopen(base_path,"r");  //�򿪻��������ļ� 
	FILE *save_file = fopen(save_path,"w");   //�򿪴�д���ļ� 
	
	int *jump_record = new int[cx];           //��һ�飬��ȡ������תλ�ã��������
	for(int i=0;i<cx;i++)  jump_record[i] = -1;
	for(int i=0;i<cx;i++){
   		if(code[i].f == jmp || code[i].f == jpc || code[i].f == cal){
   			int target = code[i].a;
   			jump_record[target] = i;
		}
   	}
   	
   	//�����������ļ�д��save�ļ�
	char buffer[200];
	fgets(buffer,100,base_file);
	while(!feof(base_file)){
	    fputs(buffer,save_file);
	    fgets(buffer,100,base_file);
	}
	
	//д�����ָ�� 
	write_mips_inst(save_file,jump_record);
	//�ͷſռ�
	delete jump_record;
   	//�ر��ļ� 
	fclose(base_file);
	fclose(save_file);
}


