#include <iostream>
#include <stack>
#include <list>
#include <vector>
using namespace std;
stack<int> number;
list<vector<int> > go_off_list;
vector<int> current_list;
int schoolbus_size,current_number;
bool go_off(){
	if(current_number==0)
		return false;
	int num;
	cout<<"�������³���������ǰ������"<<current_number<<"��ͬѧ����";
	cin>>num;
	if(current_number-num<0) 
		return false;
	current_number-=num;
	 
	for(int i=0;i<num;i++){
		int temp=number.top();
		number.pop();
		current_list.push_back(temp);
	}
	return true;
}
bool go_on(int num){	
	if(current_number+num>=schoolbus_size)
		return false;
	cout<<"�������ϳ���ͬѧ��ţ���������"<<num<<"������";
	for(int i=0;i<num;i++){
		int temp;
		cin>>temp;
		number.push(temp);
	}
	current_number+=num;
	return true;
}
int main(int argc, char** argv) {
	int total_times;
	cout<<"����������������";
	cin>>total_times;
	cout<<endl;
	for(int q=0;q<total_times;q++){
		cout<<"��"<<q+1<<"�����ݣ�"<<endl;
		int stop_times;
		cout<<"������ͣ��������";
		cin>>stop_times;
		cout<<"������У��������";
		cin>>schoolbus_size;
		current_number=0;
		go_off_list.clear();
		for(int i=0;i<stop_times;i++){
			int operate;
			cout<<"��"<<i+1<<"��ͣ����ָ��Ϊ��"; 
			current_list.clear();
			current_list.push_back(i+1);
			cin>>operate;
			if(operate==0){
				if(!go_off()){ 
					cout<<"����û����ô���ˣ����������롣"<<endl;
					i--;
					continue;
				} 
			}
			else if(operate>0){
				if(!go_on(operate)){
					cout<<"������������������޷��ϳ���"<<endl;
					i--;
					continue;
				}
			}
			else{
				cout<<"�������������롣"<<endl;
				i--;
				continue;
			}
			go_off_list.push_back(current_list);
		}
		list<vector<int> >::iterator it;
		for(it=go_off_list.begin();it!=go_off_list.end();it++){
			vector<int> at=*it;
			if(at.size()==1) continue;
			cout<<"��"<<at[0]<<"��ͣ�����³������У�" ;
			for(int i=1;i<at.size();i++){
				cout<<at[i]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl<<endl;
	}
	
	return 0;
}
