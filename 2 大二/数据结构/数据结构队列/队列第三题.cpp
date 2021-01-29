#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<iomanip> 
#include<conio.h>
#include<windows.h>
 
using namespace std;
struct car_que{
	int refuel_time;
	int car_number;
};
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;c.Y=y;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int describe_in_graphic(queue<car_que> a,int size,car_que b[],int CARNUMBER=0){
	static bool isfirst=true;
	static int time=-1;
	time++;
	if(isfirst){
		gotoxy(0,0);
		for(int i=0;i<CARNUMBER+10;i++)
			cout<<"                                                                                       \n";
		isfirst=false;
		gotoxy(0,10);
		cout<<"�����Ŷӵĳ���"<<a.size()<<"����";
		for(int i=0;i<size;i++){
			gotoxy(30,8+i*2);
			cout<<setw(2)<<i+1<<"�ż��ʹ����Ŷӳ���Ϊ��  "<<"��ʣ��   s";
		}
		gotoxy(0,15);
		cout<<"����ʱ��Ϊ��"<<setw(2)<<time<<"s";
	}
	else{
		gotoxy(14,10); cout<<"  \b\b"<<a.size();
		gotoxy(12,15); cout<<setw(2)<<time;
		for(int i=0;i<size;i++){
			if(b[i].refuel_time!=-1){
				gotoxy(52,8+i*2);
				cout<<b[i].car_number+1;
				gotoxy(62,8+i*2);
				cout<<"  \b\b"<<b[i].refuel_time;
			}
			else {
				gotoxy(30,8+i*2);
				cout<<"                                           "; 
			}
		}
	}
	return time;
}
int main(int argc, char** argv) {
	int CARNUMBER=100,maxtime=100,mintime=100;
	while(!(CARNUMBER<100&&CARNUMBER>=1)){
		cout<<"����������������С��100����";
		cin>>CARNUMBER;
	}
	while(!(maxtime<100&&maxtime>=1)){
		cout<<"�����������������ʱ�䣨С��100����";
		cin>>maxtime;
	}
	while(!(mintime<100&&mintime>=1) || mintime>=maxtime){
		cout<<"����������������Сʱ�䣨С��100��С�����ʱ�䣩��";
		cin>>mintime;
	}
	queue<car_que> first_step_car_queue;
	srand((int)time(0));
	cout<<"\n����һ���������ŶӶ��У�����Ϊ"<<CARNUMBER<<
		"����������ʱ�����Ϊ"<<maxtime<<"s����СΪ"<<mintime<<"s��\n"; 
	for(int i=0;i<CARNUMBER;i++){
		car_que temp;
		temp.car_number=i;
		int time;
		while(true){
			time=rand()%maxtime;
			if(time>=mintime) break;
		}
		temp.refuel_time=time;
		first_step_car_queue.push(temp);
		cout<<"��"<<setw(2)<<i<<"��������ʱ��Ϊ"<<temp.refuel_time<<endl;
	}
	cout<<"�������е�һ�׶����д�����ɡ�"<<endl<<endl;
	int length=100;
	while(!(length<11&&length>=1)){
		cout<<"���������վ�ļ��ͻ�����(С��12)��";
		cin>>length;
	}
	
	car_que second_step_car_queue[length];
	for(int i=0;i<length;i++)
		second_step_car_queue[i].refuel_time=0;
	cout<<"���������������ͽ׶�";
	int sumtime;
	getch();
	bool flag=true;
	describe_in_graphic(first_step_car_queue,length,second_step_car_queue,CARNUMBER);
	while(!first_step_car_queue.empty()||flag){
		for(int i=0;i<length;i++){
			if(second_step_car_queue[i].refuel_time<=0){
				if(!first_step_car_queue.empty()){
					second_step_car_queue[i]=first_step_car_queue.front();
					first_step_car_queue.pop();
				}
				else 
					second_step_car_queue[i].refuel_time=-1;
			}
			else
				second_step_car_queue[i].refuel_time--;;
		}
		int k;
		for(k=0;k<length;k++)
			if(second_step_car_queue[k].refuel_time !=-1) break;
		if(k==length) flag=false;
		sumtime=describe_in_graphic(first_step_car_queue,length,second_step_car_queue);
		Sleep(1000);
	}
	gotoxy(20,20);
	cout<<"�Ŷӽ���������ʱΪ"<<sumtime<<"s,�������������"; 
	getch();
	return 0;
}
