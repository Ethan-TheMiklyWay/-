/*
*��ϵͳ�ļ��裺
*����Ϊ40�����棬ÿ������4���ŵ���ÿ���ŵ�4�������¼��һ��40*4*4=640�����̿� 
*ÿ�����̿���1024���ֽڡ�
*���е�0�����̿�������Ŵ��̷����map��ǰ40�ֽڣ�ÿ���ֽ�ȡǰ16λ���ռ����� 
*���������320���ļ�����2kbһ���ļ�����һ����320��inode��㣬ÿ��inodeռ��100���ֽ�
*	��ÿ�����̿���Դ��10��inode��㣬��1����32����inode��� 
*i_blockһ��15�����ݣ�����ǰ13����ʾֱ��Ѱַ�����һ����ʾ1�����Ѱַ����󵥸��ļ���
*	�洢�ռ�Ϊ13+1024/4=269kb 
*ģ��Ĵ��̳�ʼ��Ϊ640*1024��int������ռ�ñ���ǰ33�鶼Ϊ1��ʾ�ѱ�ռ�� 
*/

#include <iostream>
#include <ctime> 
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
using namespace std;

struct mytime{
	int minute;  //�����ʱ��ֻ�з��Ӻ���
	int second;
};
struct ext2_inode{  //һ��inodeռ��25��int�Ĵ�С����100���ֽ� 
	int i_mode;     //�ļ�ģʽ��1��ʾ�ļ���2��ʾĿ¼��0Ϊ�� 
	int i_uid;       //�ļ�id 
	mytime i_ctime;  //����ʱ�� 
	char i_name[8];   //�ļ��� 
	int i_size;      //�ļ���С 
	int i_foruser;   //���� 
	
	int i_blocks; //���������
	int i_block[14];  //ָ��������ָ��
	int i_son;    //�����Ŀ¼�����ʾ��Ŀ¼���ļ���inodeλ�� 
	int i_brother;  //��ʾ���ڸ�Ŀ¼�µ��ֵܽ���inodeλ�� 
};

int **MyDisk;  //���� 
int pwd[20];   //����Ŀ¼��fcb��uid 
int current_depth=0;//��ǰ��� 

void trim(string &s) 
{
    if (s.empty()) 
    {
        return ;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
}
bool AddToOccupy(int ClusterNumber){ 
	//�˺������ڽ�һ��ָ���Ĵ��̿��Ϊռ��״̬ 
	int column=ClusterNumber/16;
	int inside=ClusterNumber%16;
	int bdata=MyDisk[0][column];
	int location=1;
	for(int i=0;i<inside;i++){
		location=location<<1;
	}
	int test=bdata&location;

	if(test!=0)  //��ʾ�Ѿ���ռ���� 
		return false;
	int ndata=bdata|location;
	MyDisk[0][column]=ndata;
	return true;
}
void DelFromOccupy(int ClusterNumber){
	//�Ӵ��̿��н�ָ���Ĵ��̿��Ϊδ��ռ�� 
	int column=ClusterNumber/16;
	int inside=ClusterNumber%16;
	int bdata=MyDisk[0][column];
	int location=1;
	for(int i=0;i<inside;i++){
		location=location<<1;
	}
	int ndata=(bdata)&(~location);
	MyDisk[0][column]=ndata;
}
bool* ReadMap(){
	//����һ��boolָ�룬����640����ʾ���̿��ռ����� 
	bool *omap=new bool[640];
	int location=0;
	for(int i=0;i<40;i++){
		int currentL=MyDisk[0][i];
		for(int j=0;j<16;j++){
			omap[location]=currentL%2;
			currentL/=2;
			location++;
		}
	}
	return omap;
}
bool ShowMap(bool* omap,int length=10){
	//��ʾһ��bool���飬��ʾ���̿��ռ����� 
	printf("��/λ��0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
	if(length>=40 || length<=0)
		return false;
	for(int i=0;i<length;i++){
		printf("%2d:    ",i);
		for(int j=0;j<16;j++){
			printf("%d  ",omap[i*16+j]);
		}
		printf("\n");
	}
	if(length!=40){
		printf("   ..    ..\n   ..    ..\n   ..    ..\n");
		printf("%2d:    ",39);
		for(int j=0;j<16;j++){
			printf("%d  ",omap[39*16+j]);
		}
		printf("\n");
	}
	return true;
}
ext2_inode* GetFCB(int *allPCB){
	//��ó������е�FCB
	int leftPCB;
	ext2_inode *inode=new ext2_inode[320];
	int location=0;
	for(int i=1;i<33;i++){
		for(int j=0;j<10;j++){
			if(MyDisk[i][j*25]==0){
				continue;
			}
			inode[location].i_mode=MyDisk[i][j*25];
			inode[location].i_uid=MyDisk[i][j*25+1];
			inode[location].i_ctime.minute=MyDisk[i][j*25+2];
			inode[location].i_ctime.second=MyDisk[i][j*25+3];
			char *c=(char*)(&MyDisk[i][j*25+4]);
			for(int k=0;k<8;k++){
				inode[location].i_name[k]=*c;
				c++;
			}			
			inode[location].i_size=MyDisk[i][j*25+6];
 			inode[location].i_foruser=MyDisk[i][j*25+7];
 			inode[location].i_blocks=MyDisk[i][j*25+8];
 			for(int k=0;k<14;k++){
 				inode[location].i_block[k]=MyDisk[i][j*25+9+k];
			}
			inode[location].i_son=MyDisk[i][j*25+23];
			inode[location].i_brother=MyDisk[i][j*25+24];
			location++;
		}
	}
	*allPCB=location;
	return inode;
}
void ShowFCB(ext2_inode* inode,int size){
	//����inode�������ͳ��ȣ���ʾ���е�FCB��� 
	printf("    name  mode  uid    size  creattime  blocks\n");
	for(int i=0;i<size;i++){
		printf("%7s   %2d   %3d  %6d      %d:%d      %2d\n",
			inode[i].i_name,
			inode[i].i_mode,inode[i].i_uid,inode[i].i_size,
			inode[i].i_ctime.minute,inode[i].i_ctime.second,
			inode[i].i_blocks);
	}   
	
}
int GetLastSonUid(bool *dirSon){
	//����uid 
	//�ҵ���ǰĿ¼�£������ֵܽ������һ����������ӽ���ʱ��ʹ��
	//dirSonΪtrue��ʾ��ǰĿ¼û�����ļ���Ӧ��ӵ����ӽ��
	//����Ӧ�ҵ���ǰ���ĺ��ӽ������һ���ֵܽ���uid 
	int nowUid=pwd[current_depth-1];
	*dirSon=true;
	int column=(nowUid%10)*25;
	int block=nowUid/10+1;
	if(MyDisk[block][column+23]!=0){
		*dirSon=false;
		nowUid=MyDisk[block][column+23];
		column=(nowUid%10)*25;
		block=nowUid/10+1;
		if(MyDisk[block][column+24]!=0){
		   	while(true){
		   		nowUid=MyDisk[block][column+24];
		   		column=(nowUid%10)*25;
				block=nowUid/10+1;
				if(MyDisk[block][column+24]==0){
					break;
				}
			}
		}
	}
	return nowUid;
}
int GetSonUidByName(string name){
	//�ڵ�ǰĿ¼�£����������ҵ�uid���Ҳ�������-1 
	int nowUid=pwd[current_depth-1];
	int column=(nowUid%10)*25;
	int block=nowUid/10+1;
	if(MyDisk[block][column+23]==0){
		return -1;
	}
	const char *name2=name.c_str();
	nowUid=MyDisk[block][column+23];
	while(true){
		int column=(nowUid%10)*25;
		int block=nowUid/10+1;
		char *n=(char*)(&MyDisk[block][column+4]);
		if(strcmp(n,name2)==0){
			return nowUid;
		}
		nowUid=MyDisk[block][column+24];
		if(nowUid==0)
			return -1;
	}
}
bool LinkToSystem(int LastUid,int NowUid,bool son){
	//���µĽ�����ӵ���ǰĿ¼�� 
	int column=(LastUid%10)*25;
	int block=LastUid/10+1;
	if(son){
		MyDisk[block][column+23]=NowUid;
	}
	else{
		MyDisk[block][column+24]=NowUid;
	}	
}
void Del(int uid){
	//ɾ��uid����Լ��ݹ����ɾ��uid����µ����Խ�� 
	int column=(uid%10)*25;
	int block=uid/10+1;
	int nowUid=MyDisk[block][column+23];
	if(nowUid!=0){
		Del(nowUid);
		while(true){
			column=(nowUid%10)*25;
			block=nowUid/10+1;
			nowUid=MyDisk[block][column+24];
			if(nowUid!=0){
				Del(nowUid);
			}
			else{
				break;
			}
		}
	}
	column=(uid%10)*25;
	block=uid/10+1;
	int blocks=MyDisk[block][column+8];
	int i;
	MyDisk[block][column]=0;
	for(i=0;i<blocks;i++){
		if(i==13) 
			break;
		DelFromOccupy(MyDisk[block][column+9+i]);
	}
	if(i==13 && MyDisk[block][column+22]!=0){
		int location=MyDisk[block][column+22];
		for(int j=0;j<256;j++){
			if(MyDisk[location][j]==0)
				break;
			DelFromOccupy(MyDisk[location][j]);
		}
		DelFromOccupy(MyDisk[block][column+22]);
	}

}
void DelByName(string name){	
	//�ҵ�Ŀ¼����Ӧ������ɾ������Ҫ�����ֵܽ����������� 
	int nowUid=pwd[current_depth-1];
	int column=(nowUid%10)*25;
	int block=nowUid/10+1;
	if(MyDisk[block][column+23]==0){
		printf("no such file or directory\n");
		return;
	}
	const char *name2=name.c_str();
	nowUid=MyDisk[block][column+23];
	int lastUid=nowUid; 
	while(true){
		column=(nowUid%10)*25;
		block=nowUid/10+1;
		char *n=(char*)(&MyDisk[block][column+4]);
		if(strcmp(n,name2)==0){
			break;
		}
		lastUid=nowUid;
		nowUid=MyDisk[block][column+24];
		if(nowUid==0){
			printf("no such file or directory\n");
			return;
		}
	}
	//ָ���������� 
	if(nowUid==lastUid){
		int nextUid=MyDisk[block][column+24];
		lastUid=pwd[current_depth-1];
		column=(lastUid%10)*25;
		block=lastUid/10+1;
		MyDisk[block][column+23]=nextUid;
	}
	else{
		int nextUid=MyDisk[block][column+24];
		column=(lastUid%10)*25;
		block=lastUid/10+1;
		MyDisk[block][column+24]=nextUid;
	}
	
	Del(nowUid);	
}

void ListSub(string information){
	//�г���ǰĿ¼�����е��ļ�
	int nowUid=pwd[current_depth-1];
	int column=(nowUid%10)*25;
	int block=nowUid/10+1;
	if(MyDisk[block][column+23]==0){
		return;
	}
	nowUid=MyDisk[block][column+23];
	int i=0;
	while(true){
		int column=(nowUid%10)*25;
		int block=nowUid/10+1;
		i++;
		printf("%8s ",(char*)(&MyDisk[block][column+4]));
		if(i%5==0) 
			printf("\n");
		nowUid=MyDisk[block][column+24];
		if(nowUid==0){
			printf("\n\n");
			return;
		}		
	}	
}
int CreatePCB(int mode){ 
	//����һ����FCB�����ش�����uid 
	bool flag=false;
	int i,j;
	for(i=1;i<33;i++){
		for(j=0;j<10;j++){
			if(MyDisk[i][j*25]==0){
				flag=true;
				break;
			}
		}
		if(flag) break;	
	}
	if(!flag){
		return false;
	}
	int uid=(i-1)*10+j;  //uid�ĸ�2λΪ1��33����λΪ10�� 
	tm *local;  //��ȡϵͳʱ�� 
	time_t t;
	t=time(NULL);
	local=localtime(&t);
	MyDisk[i][j*25]=mode;
	MyDisk[i][j*25+1]=uid;
	MyDisk[i][j*25+2]=local->tm_min;
	MyDisk[i][j*25+3]=local->tm_sec;
	MyDisk[i][j*25+6]=0;
	MyDisk[i][j*25+7]=0;
	MyDisk[i][j*25+8]=0;
	MyDisk[i][j*25+22]=0;
	MyDisk[i][j*25+23]=0;
	MyDisk[i][j*25+24]=0;
	return uid;
}
bool AddToDisk(int uid,char fi[1024]){  
	//����һ��uid����Ҫ��ӵ����ݣ������ӳɹ�����true���������˻������󷵻�false 
	//�ҵ�һ�����е��̿鲢���ռ�� 
	bool *omap=new bool[640];
	omap=ReadMap();
	int location;
	for(location=0;location<640;location++){
		if(omap[location]==0){
			break;
		}
	}
	if(location==640) return false;
	AddToOccupy(location);
	//����uid�ҵ��ļ���inode����ڴ����е�λ�� 
	int column=(uid%10)*25;
	int block=uid/10+1;
	if(MyDisk[block][column+8]<=12){
		//�����ǰռ�õĲ���12�飬������һ�� 
		MyDisk[block][column+8]++;
		int num=MyDisk[block][column+8];
		MyDisk[block][column+8+num]=location;
	}
	else if(MyDisk[block][column+8]==13){
		//�����ǰռ��Ϊ13�飬�����һ�������ķ�ʽ 
		MyDisk[block][column+8]++;
		MyDisk[block][column+22]=location;
		for(int i=0;i<256;i++){
			MyDisk[location][i]=0;
		}  
		//��Ҫ�ҵ�һ���µĿ��п�location2 
		omap=ReadMap();
		int location2;
		for(location2=0;location2<640;location2++){ 
			if(omap[location2]==0){
				break;
			}
		}
		if(location2==640) return false;
		AddToOccupy(location2);
		MyDisk[location][0]=location2;
		location=location2;
	}
	else if(MyDisk[block][column+8]==14){
		//����Ѿ���һ���������������һ�� 
		int cluster=MyDisk[block][column+22];
		int i;
		for(i=0;i<256;i++){
			if(MyDisk[cluster][i]==0)
				break;
		}
		if(i==256) return false;
		MyDisk[cluster][i]=location;
	}
	//�����ļ� 
	int *p=(int*)(fi);
	for(int i=0;i<256;i++){
		MyDisk[location][i]=*p;
		p++;
	}
	return true;
}
char* GetContentFromUid(int uid,int *length){
	//ͨ��uid�����ظ��ļ����������ݣ�����Ϊlength 
	int column=(uid%10)*25;
	int block=uid/10+1;
	int size=MyDisk[block][column+6];
	*length=size;
	char *file=new char[size+1];
	int blocks=size/1024+1;
	int i;
	int t=0;
	int j;
	for(i=0;i<14;i++){
		int location=MyDisk[block][column+9+i];
		int readbits=size<1024?size:1024;
		size-=1024;
		char *c=(char*)(&MyDisk[location][0]);
		for(j=0;j<readbits;j++,t++){
			file[t]=*c;
			c++;
		}
		if(size<=0) break;
 	}
 	int loc=MyDisk[block][column+22];
 	if(i==14 && size>0){
 		for(i=0;i<256;i++){
 			int location=MyDisk[loc][i];
 			int readbits=size<1024?size:1024;
 			size-=1024;
			char *c=(char*)(&MyDisk[location][0]);
			for(j=0;j<readbits;j++,t++){
				file[t]=*c;
				c++;
			}
			if(size<=0) break;
		}
	} 
	file[t]=0;
	return file;
}
void ShowFile(string name){
	//ͨ���ļ����ҵ�uid��������һ����������չʾ�ļ���moreָ��ɵ��� 
	int uid=GetSonUidByName(name);
	if(uid==-1){
		return;
	}
	int column=(uid%10)*25;
	int block=uid/10+1;
	printf("file uid: %d\n",uid);
	printf("file mode: ") ;
	if(MyDisk[block][column]==1){
		printf("direction\n");
	}
	else{
		printf("file\n");
	}
	printf("create time: %d:%d\n",MyDisk[block][column+2],MyDisk[block][column+3]);	
	printf("file name: %s\n",(char*)(&MyDisk[block][column+4]));
	printf("file size: %d\n",MyDisk[block][column+6]);
	
	if(MyDisk[block][column]==1) return;
	int length;
 	char *c=GetContentFromUid(uid,&length);
 	for(int i=0;i<length;i++){
 		if((i+1)%1024==0){
 			char t=getch();
 			if(t=='q'){
 				break;
			 }
		}
 		printf("%c",*c);
 		c++;
	}
	printf("\n\n");
}

bool SaveDisk(string name){
	//����������� 
	const char *location=name.c_str();
	ofstream outFile(location,ios::out|ios::binary);
	if(!outFile){
		printf("save disk error, check if you write the correct direction.\n");
		return false;
	}
	for(int i=0;i<639;i++){
		for(int j=0;j<256;j++){
			outFile.write((char*)(&MyDisk[i][j]),4);
		}
	
	}
	printf("file save successfully.\n");
	return true;
}
bool LoadDisk(string information){
	//���ش��� 
	const char *location=information.c_str();
	ifstream in(location,ios::binary);
	if(!in){
		printf("file not found error.\n");
	}
	printf("you are trying to disk overlay, that may cause error, would you like to continue[y/n]?");
	while(true){
		char c=getch();
		if(c=='n'){
			printf("\n");
			return false;
		}
		else if(c=='y'){
			printf("\n");
			break;
		}
	}
	char flush[1024];
    int inbit=0;
    int i=0;
	while(!in.eof()){//loaddisk C:\Users\lenovo\Desktop\te
    	in.read(flush,1024);
    	inbit+=in.gcount();
    	int *fl=(int*)(flush);
		
    	for(int j=0;j<256;j++){
    		MyDisk[i][j]=fl[j];
		}
		i++;
		
	}
	if(inbit!=1024*639){
		printf("file and disk corrupted, pleast format hard disk.\n");
	}
	else{
		printf("disk overlay successfully.\n");
	}
}
bool readBinaryFile(const char *fileName){
	//�������ݣ�Ҫ���� AddToDisk���� 
	char *location=new char[100];
	char *name=new char[8];
	int i,j; 
	for(i=0;i<100;i++){
		name[i]=fileName[i];
		if(fileName[i]==' ' || i==7)
			break;
	}
	name[i]=0;		
	for(j=0,i++;i<100;i++,j++){
		location[j]=fileName[i];
		if(fileName[i]==0)
			break;
	}
	if(GetSonUidByName(name)!=-1){
		printf("file or directory have already exist.\n");
		return 0;
	}
	ifstream in(location,ios::binary);
	if(!in) {
    	printf("File not found error!\n");
        return false;
    }
    int uid=CreatePCB(2);
    int column=(uid%10)*25;
	int block=uid/10+1;
	
	char *c=(char*)(&MyDisk[block][column+4]);
	for(int i=0;i<8;i++){
		*c=*name;
		c++;
		name++;
	}
    char flush[1024];
    int inbit=0;
    while(!in.eof()){
    	in.read(flush,1024);
    	inbit+=in.gcount();
    	if(!AddToDisk(uid,flush)){
    		printf("Error, can not add to disk\n");
    		DelByName(c);
    		return false; //ɾ���ļ� 
		}
	}
	in.close();
	MyDisk[block][column+6]=inbit;
	bool son;
	int Uid=GetLastSonUid(&son);
	LinkToSystem(Uid,uid,son);
   // writeBinaryFile("C:\\Users\\lenovo\\Desktop\\te.txt",fi,location);
    return true;
}
void ShowDiskMap(string num){
	//չʾ���̵�λʾͼ 
	int length=10;
	if(num!=""){
		for(int i=0;i<num.length();i++){
			if(num[i]>'9'||num[i]<'0'){
				printf("instruction error!\n");
				return;
			}
		}
		length=atoi(num.c_str());
		if(length>40) length=40;
	}
	bool *omap=ReadMap();
	ShowMap(omap,length);
}


int MakeDir(string information){
	//�ڵ�ǰĿ¼�������Ŀ¼ 
	if(information==""){
		printf("directory must have a name.\n");
		return 0;
	}
	if(GetSonUidByName(information)!=-1){
		printf("file or directory have already exist.\n");
		return 0;
	}
	int uid=CreatePCB(1);
	int column=(uid%10)*25;
	int block=uid/10+1;
	MyDisk[block][column+6]=0;
	char *c=(char*)(&MyDisk[block][column+4]);
	int i;
	for(i=0;i<7;i++){
		*c=information[i];
		c++;
	}
	if(current_depth==0) 
		return uid;
	bool son;
	int Uid=GetLastSonUid(&son);
	LinkToSystem(Uid,uid,son);
	return uid;
}


void EnterDir(string name){
	//����Ŀ¼��nameΪ..��ʾ������һ��Ŀ¼ 
	if(name==".."){
		if(current_depth!=1) 
			current_depth--;
		return;
	}
	int uid=GetSonUidByName(name);
	if(uid==0){
		printf("no such directiory\n");
		return;
	}
	int column=(uid%10)*25;
	int block=uid/10+1;
	if(MyDisk[block][column]!=1){
		printf("name is not a directory\n");
		return;
	}
	pwd[current_depth]=uid;
	current_depth++;
}

char *GetPWD(){
	//���ع���Ŀ¼���Զ����� 
	char *name=new char[150];
	int i;
	int loc=0;
	for(i=0;i<current_depth;i++){
		int uid=pwd[i];
		int column=(uid%10)*25;
		int block=uid/10+1;
		char *c=(char*)(&MyDisk[block][column+4]);
		for(int j=0;j<7;j++){
			name[loc]=*c;
			loc++;
			c++;
			if(*c==0) break;
		}
		if(i==current_depth-1){
			name[loc]='>';
			loc++;
			name[loc]=0;
		}
		else{
			name[loc]='\\';
			loc++;
		}
	}
	return name;

} 
void InitDisk(){
	//���̳�ʼ�� 
	MyDisk=new int*[640];
	for(int i=0;i<640;i++){
		MyDisk[i]=new int[256];
	}
	for(int i=0;i<33;i++){
		for(int j=0;j<256;j++){
			MyDisk[i][j]=0;
		}
	}
	for(int i=0;i<33;i++){
		AddToOccupy(i);
	}
	int uid=MakeDir("home");
	pwd[0]=uid;
	current_depth=1;
}
void FormatDisk(){
	//���̸�ʽ�������ó�ʼ�����̺��� 
	printf("you are trying to format disk, would you like to continue[y/n]?");
	while(true){
		char c=getch();
		if(c=='n'){
			printf("\n");
			return;
		}
		else if(c=='y'){
			printf("\n");
			break;
		}
	}
	InitDisk();
	printf("format disk successfully.\n");
}
int main(int argc, char** argv) {
	InitDisk(); 
	while(true){
		string instruction;
		string information;
		printf("%s",GetPWD());
		getline(cin,instruction);
		int location=instruction.find(' ');
		if(location!=-1){
			information=instruction.substr(location+1,instruction.size()-location);
			instruction=instruction.substr(0,location);
		}
		trim(information);
		trim(instruction);
		if(instruction=="quit"){
			break;
		}
		else if(instruction=="in"){
			readBinaryFile(information.c_str());
		}
		else if(instruction=="showdiskmap"){
			ShowDiskMap(information);
		}
		else if(instruction=="showfcb"){
			int *size=new int;
			ext2_inode *inode=GetFCB(size);
			ShowFCB(inode,*size);			
		}
		else if(instruction=="more"){
			ShowFile(information);
		}
		else if(instruction=="mkdir"){
			MakeDir(information);
		}
		else if(instruction=="cd"){
			EnterDir(information);
		}
		else if(instruction=="ls"){
			ListSub(information);
		}
		else if(instruction=="del"){
			DelByName(information);
		}
		else if(instruction=="savedisk"){
			SaveDisk(information);
		}
		else if(instruction=="loaddisk"){
			LoadDisk(information);
		}
		else if(instruction=="formatdisk"){
			FormatDisk();
		}
		else if(instruction!=""){
			printf("%s is not a instruction.\n",instruction.c_str());
		}
	}
	return 0;
}
