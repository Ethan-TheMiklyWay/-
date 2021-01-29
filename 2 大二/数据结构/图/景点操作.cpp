#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <windows.h>
#include <shlobj.h>
#include <sstream> 
using namespace std;
struct view{
	//ͼ���õ�����ӱ����ʽ 
	string name;
	map<string,double> loc;
	bool has_been_walked;
	int step;
	int from;
};
namespace variation{
	bool have_operate=false;
	int max_read_length=20000;
}
class Error{
	//�˴��г��˳�����������п��ܳ��ֵĴ��� 
	public:
		void static file_format_error(){
			cout<<"�ļ���ʽ���ִ��󣬴�ʧ�ܣ�\n";
		}
		void static view_has_exist_error(){
			cout<<"�þ����Ѿ����ڣ�"<<endl;
		}
		void static view_donot_exist_error(){
			cout<<"�þ��㲻���ڣ�"<<endl;
		}
		void static filename_exit_limit(){
			cout<<"�ļ����������ȷ�Χ�����������룡"<<endl;
		}
		void static name_has_exist(){
			cout<<"�����ظ���"<<endl;
		}
};
vector<view> information;
int search_view(string name){
	//���ݴ��ݵľ���������Ѱ�Ҿ��� 
	int i;
	for(i=0;i<information.size();i++)
		if(information[i].name==name) 
			break;
	if(i==information.size()) 
		return -1;
	return i;
}
void insert(){
	//����һ������ 
	string s;
	view tempview;
	cout<<"�������ƣ�";
	cin>>s;
	getchar();
	int k=search_view(s);
	if(k!=-1){
		Error e;
		e.view_has_exist_error();
		return;
	} 
	tempview.name=s;
	string a;
	double b;
	while(true){
		if(information.size()==0) break; 
		cout<<"����֪����Ĺ�ϵ�����㣬·�̣�������0 0��ʾ�˳���";
		cin>>a>>b; 
		getchar();
		if(a=="0"&&b==0) break;
		map<string,int>::iterator iter;
		view operview;
		int i=search_view(a);
		if(i==-1){
			Error e;
			e.view_donot_exist_error();
			return;
		}
		information[i].loc[s]=b;
		tempview.loc[a]=b;
	}
	variation::have_operate=true;
	information.push_back(tempview);
}
void show(){
	//չʾȫ���ľ��� 
	for(int i=0;i<information.size();i++){
		cout<<"��"<<i<<"�����㣬���֣�  "<<information[i].name<<endl;
		map<string,double>::iterator it;
		for(it=information[i].loc.begin();it!=information[i].loc.end();it++)
			cout<<"    ����\""<<it->first<<"\"����    "<<it->second<<"����\n"; 
	}
}

string strip(string com){
	//ȥ���ַ�����ȫ���Ŀո� 
	string temp;
	for(int i=0;i<com.length();i++){
		if(com[i]!=' ') temp+=com[i];
	}
	return temp;
}
void preserve_path(char *path){
	int size,i;
	size=information.size();
	ofstream file(path);
	file<<size<<endl;
	for(int i=0;i<size;i++)
		file<<information[i].name<<endl;
	//�����ļ��ĵ�һ��Ϊ����������֮��n��Ϊÿ���������� 
	for(int i=0;i<size;i++){
		file<<information[i].loc.size()<<endl;
		map<string,double>::iterator it;
		for(it=information[i].loc.begin();it!=information[i].loc.end();it++)
			file<<it->first<<endl<<it->second<<endl; 
	}
	variation::have_operate=false;
	file.close();
}
void preserve(){
	//�����ļ�������·��Ϊ���� 
	string name;
	while(true){
		cout<<"�������ļ�����   ";
		getline(cin,name);
		if(name.size()>=50){
			Error e;
			e.filename_exit_limit();
		}
		else break;
	}
	TCHAR path[255];
	SHGetSpecialFolderPath(0,path,CSIDL_DESKTOPDIRECTORY,0);
	int lo;
	for(lo=0;lo<255;lo++)
		if(path[lo]=='\0') 
			break;
	path[lo++]='\\';
	for(int i=0;i<name.size();i++){
		path[lo]=name[i];
		lo++;
	}
	path[lo++]='.';
	path[lo++]='t';
	path[lo++]='x';
	path[lo++]='t';
	path[lo]='\0';
	cout<<"����·��Ϊ���棺"<<path<<endl;
	preserve_path(path);
}
void open(){
	ifstream file;
	while(true){
		char path[255];
		cout<<"�������ļ�·����";
		cin>>path;
		getchar();
		file.open(path);
		if(file.is_open()==true) break;
		cout<<"·������\n";
	}
	if(variation::have_operate==true){
		cout<<"��ǰִ�еĲ�����δ���棬�����潫�������ݶ�ʧ���Ƿ񱣴棨y,n��?  ";
		char flag;
		cin>>flag;
		getchar();
		if(flag=='y') preserve();
	} 
	information.clear();
	string line;
	getline(file,line);
	stringstream ss;
	ss<<line;
	int size;
	ss>>size;
	for(int i=0;i<size;i++){
		getline(file,line);
		view tempview;
		tempview.name=line;
		information.push_back(tempview);
	}
	for(int i=0;i<size;i++){
		getline(file,line);
		stringstream st;
		st<<line;
		int nowsize;
		st>>nowsize;
		for(int j=0;j<nowsize;j++){
			string name1;
			string length;
			getline(file,name1);
			getline(file,length);
			stringstream se;
			se<<length;
			int leng;
			se>>leng;
			information[i].loc[name1]=leng;
		}
	}
	cout<<"�ļ������"<<endl;	
//C:\Users\lenovo\Desktop\ss.txt
}
void look(string name){
	name=name.substr(4,name.size()-3);
	int i=search_view(name);
	if(i==-1){
		Error e;
		e.view_donot_exist_error();
		return;
	}
	cout<<"��"<<i<<"�����㣬���֣�"<<information[i].name<<endl;
	map<string,double>::iterator it;
	for(it=information[i].loc.begin();it!=information[i].loc.end();it++)
		cout<<"    ����\""<<it->first<<"\"����    "<<it->second<<"����\n"; 
}
void insert_path(){
	cout<<"������һ�����㣺";
	string s;
	Error e;
	cin>>s;
	getchar();
	int k=search_view(s);
	if(k==-1){
		e.view_donot_exist_error();
		return;
	}
	cout<<"��ǰ�����ľ���Ϊ��"<<s<<"�����е���������Ϊ��"<<endl;
	int i;
	for(i=0;i<information.size();i++)
		if(i!=k)
			cout<<"    "<<information[i].name<<endl;
	cout<<"������һ����֮�����ľ��㣺";
	string newpath;
	cin>>newpath;
	getchar();
	if(newpath==s){
		cout<<"�������Լ�Ϊ��������"<<endl;
		return;
	}
	int k2=search_view(newpath);
	if(k2==-1){
		e.view_donot_exist_error();
		return;
	}
	cout<<"��������룺";
	int leng;
	cin>>leng;
	getchar();
	information[k].loc[newpath]=leng;
	information[k2].loc[s]=leng; 
}

void delview(string com){
	string name=com.substr(7,com.size()-6);
	int k=search_view(name);
	Error e;
	if(k==-1){
		e.view_donot_exist_error();
		return;
	}
	vector<view>::iterator it=information.begin();
	for(int i=0;i<k;i++) it++;
	information.erase(it);
	for(int i=0;i<information.size();i++){
		map<string,double>::iterator it;
		for(it=information[i].loc.begin();it!=information[i].loc.end();){
			if(it->first==name)
				information[i].loc.erase(it++);
			else it++;
		}
	}
}
bool open_two_view(string *name1,string *name2,int *lo1,int *lo2){
	int loc1,loc2;
	Error e;
	cout<<"�����뾰��1��";
	cin>>*name1; 
	getchar();
	loc1=search_view(*name1);
	if(loc1==-1){
		e.view_donot_exist_error();
		return false;
	}
	cout<<"�����뾰��2��";
	cin>>*name2;
	getchar();
	loc2=search_view(*name2);
	if(loc2==-1){
		e.view_donot_exist_error();
		return false;
	}
	if(loc1==loc2){
		e.name_has_exist();
		return false;
	}
	*lo1=loc1;
	*lo2=loc2;
	return true;
}
void delpath(){
	string name1,name2;
	int loc1,loc2;
	if(!open_two_view(&name1,&name2,&loc1,&loc2))
		return;
	map<string,double>::iterator it;
	for(it=information[loc1].loc.begin();it!=information[loc1].loc.end();){
		if(it->first==name2){
			information[loc1].loc.erase(it);
			break;
		}
		it++;	
	}
	for(it=information[loc2].loc.begin();it!=information[loc2].loc.end();){
		if(it->first==name1){
			information[loc2].loc.erase(it);
			break;
		}
		it++;
	}
}
struct showpath{
	string name;
	double leng;
};
void show_path(int start,int end){
	vector<showpath> path;
	int now=end;
	while(now!=start){
		showpath temp;
		temp.name=information[now].name;
		int tempstep=information[now].step;
		now=information[now].from;
		temp.leng=tempstep-information[now].step;
		path.push_back(temp);
	}
	cout<<"��"<< information[now].name<<"����"<<endl; 
	for(int i=path.size()-1;i>=0;i--){
		cout<<"��"<<path[i].leng<<"�ף�����"<<path[i].name<<endl;
	} 
	cout<<"�ܹ�"<<information[end].step<<"��"<<endl;
}
void dijkstra_alg(){
	string name1,name2;
	int loc1,loc2;
	if(!open_two_view(&name1,&name2,&loc1,&loc2))
		return;
	int size,i,j;
	size=information.size();
	for(i=0;i<size;i++){
		information[i].step=100000;
		information[i].has_been_walked=false;
	} 	
	information[loc1].has_been_walked=true;
	information[loc1].step=0;
	int nowloc=loc1;
//	C:\Users\lenovo\Desktop\CAUViewMap.txt
	for(j=0;j<size;j++){
		map<string,double>::iterator it;
		for(it=information[nowloc].loc.begin();it!=information[nowloc].loc.end();it++){
			int operloc;
			operloc=search_view(it->first);
			if(information[operloc].has_been_walked==true) 
				continue;
			int operstep;
			operstep=information[nowloc].step+it->second;
			if(operstep<information[operloc].step){
				information[operloc].step=operstep;
				information[operloc].from=nowloc;
			}	
		}
		int minloc=0;
		int minsize=1000000;
		for(i=0;i<size;i++){
			if(information[i].has_been_walked==true)
				continue;
			if(information[i].step<minsize){
				minsize=information[i].step;
				minloc=i;
			}
		}
		if(minloc==loc2) 
			break;
		nowloc=minloc;
		information[minloc].has_been_walked=true;
	}
	show_path(loc1,loc2);
}
void help(){
	cout<<"                        �������ϵͳ1.0                           	  \n"<<
		  "    �˳���             q                ������          help      	  \n"<<
		  "    չʾȫ��������Ϣ�� show             �����µľ��㣺  insert         \n"<<
		  "    �����Ļ��         clear            ���澰����Ϣ��  preserve       \n"<<
		  "    ��һ�����㣺     open             ����һ��·����  insert path    \n"<<
		  "    �鿴һ�����㣺     look+������      ɾ��һ�����㣺  delview+������ \n"<<
		  "    ������̾��룺     cal\n";
		  
}
bool command(string com){
	com=strip(com);
	if(com=="q")        				return false;
	else if(com=="insert")				insert(); 
	else if(com=="show")				show();
	else if(com=="clear")				system("cls");
	else if(com=="help")    			help();
	else if(com=="")					return true;
	else if(com=="preserve")			preserve(); 
	else if(com=="open")				open();
	else if(com=="insertpath")   		insert_path();
	else if(com=="delpath")				delpath();
	else if(com.substr(0,4)=="look")	look(com);
	else if(com.substr(0,7)=="delview") delview(com);
	else if(com=="cal")					dijkstra_alg();
	else								cout<<"����"<<endl;
	return true; 
	
}
int main(int argc, char** argv) {
	cout<<"��ʾ��helpΪ����"<<endl;
	string com;
	while(true){
		cout<<">>";
		getline(cin,com);
		if(command(com)==false)
			break;
	}
	return 0;
}
//  p �޸�һ�����о���������Ϣ��
//  p ����һ���¾��㼰�������Ϣ��           
//  p ����һ���µ�·����
//  p ɾ��һ�����㼰�������Ϣ��
//  p ɾ��һ��·����
//  p ���ļ�graph.txt�ж�ȡ��Ӧ����, ����һ��ͼ,ʹ���ڽӾ����ʾͼ��
//  p ������Ϣ��ѯ��Ϊ���ÿ����ṩУ԰���⾰�������Ϣ�Ľ��ܣ�
//  p ��·��ѯ��Ϊ���ÿ����ṩУ԰������������֮���һ�����·����
