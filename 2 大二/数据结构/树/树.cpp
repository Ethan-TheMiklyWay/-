#include <iostream>
#include <string>
#include <set>
using namespace std; 
string mid_tree;
string las_tree;

void travel_tree(int m_start,int m_end,int l_start,int l_end){
	if(m_start>m_end) return;
	char root=las_tree[l_end];
	cout<<root;
	if(m_start==m_end) return;
	int pos=mid_tree.find(root);
	travel_tree(m_start,pos-1,l_start,l_start+pos-1-m_start);
	travel_tree(pos+1,m_end,l_start+pos-m_start,l_end-1);
}
bool judge(){
	set<char> se,te;
	if(mid_tree.length()!=las_tree.length()){
		cout<<"���Ȳ���ȣ�����������"<<endl<<endl;
		return false;
	}
	for(int i=0;i<mid_tree.length();i++){
		se.insert(mid_tree[i]);
		te.insert(las_tree[i]);
	}
	if((se.size()!=mid_tree.length())||(te.size()!=las_tree.length())){
		cout<<"���ظ���ĸ������������"<<endl<<endl;
		return false;
	}
	set<char>::iterator ase,ate;
	ase=se.begin();
	ate=te.begin();
	while(ase!=se.end()){
		if(*ase!=*ate){
			cout<<"����������ĸ����ȣ�����������"<<endl<<endl;
			return false;
		}
		ase++;
		ate++;
	}
	if(mid_tree.length()>15){
		cout<<"���ȳ��ޣ���ǰ����Ϊ"<<mid_tree.length()<<"��������������"<<endl<<endl;
		return false;
	}
	return true;
		
} 
int main(int argc, char** argv) {
	for(int i=1;;i++){
		cout<<"��"<<i<<"������,���Ȳ��ܳ���15��\n�������������У�";
		cin>>mid_tree;
		cout<<"������������У�";
		cin>>las_tree;	
		if(judge()==false) continue;
		cout<<"��������Ϊ��"; 
		travel_tree(0,mid_tree.length()-1,0,mid_tree.length()-1);
		cout<<endl<<endl;
	}
	return 0;
}
