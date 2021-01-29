#include <iostream>
#include <math.h>
#include <queue> 
using namespace std; 
struct point{
	int x;
	int y;
	int is_barrier;
	int formerx;
	int formery;
	bool triveled;
};
struct dir{
	int x;
	int y;
	dir(int a,int b){
		x=a;
		y=b;
	}
};
dir direction[4]={dir(0,1),dir(0,-1),dir(1,0),dir(-1,0)};
int main(int argc, char** argv) {
	int m,n;
	cout<<"�������Թ�������m������n��";
	cin>>m>>n;
	point **set=new point*[m];
	int i,j;
	cout<<"��ֱ�����ÿ�е�n��Ԫ�أ�1�����ɴ0����ɴ�";
	for(i=0;i<m;i++){
		set[i]=new point[n];  //����һ����ά�����е�ͼ�ļ�¼ 
		for(j=0;j<n;j++){		 
			cin>>set[i][j].is_barrier;
			set[i][j].x=i;
			set[i][j].y=j;
			set[i][j].triveled=false;
		}
		for(j=0;j<n;j++)
			cout<<set[i][j].is_barrier<<" ";
		cout<<endl;
	} 
	
	cout<<"�������Թ�����ڣ��������ӦΪһ������ֵ�����򲻽��к����Լ�⣩��\n";
	int startx,starty;
	cin>>startx>>starty;
	cout<<"�������Թ��ĳ��ڣ���������ӦΪһ������ֵ�����򲻽��к����Լ�⣩��\n";
	int endx,endy;
	cin>>endx>>endy;
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){		 
			cout<<set[i][j].is_barrier<<" ";
		}
		cout<<endl;
	} 
	
	queue<point> wait_for_handle;
	set[startx][starty].triveled=true;
	bool success=false;
	wait_for_handle.push(set[startx][starty]);
	
	while(!wait_for_handle.empty()){
		point nowpoint=wait_for_handle.front();
		wait_for_handle.pop();
		int oldx=nowpoint.x;
		int oldy=nowpoint.y;
		if(oldx==endx && oldy==endy) {
			success=true;
			break;
		}
			
		for(i=0;i<4;i++){
			int newx=direction[i].x+nowpoint.x;
			int newy=direction[i].y+nowpoint.y;
			if(newx<0 || newy<0 || newx>n || newy>n) continue;  //���� 
			if(set[newx][newy].triveled==true) continue;   //�����ʹ���
			if(set[newx][newy].is_barrier==1) continue; //��ǽ
			
			set[newx][newy].triveled=true;
			wait_for_handle.push(set[newx][newy]);
			cout<<newx<<" "<<newy<<endl;
		}
	}
	if(success){
		cout<<"���Ե����յ�"; 
	}
	else {
		cout<<"�����Ե����յ�"; 
	}
	
	/**********************
	5 5
	0 0 0 1 0
	0 1 0 0 0
	0 1 1 0 1
	0 0 0 0 0
	0 0 0 1 0
	0 0 
	4 4 
	***********************/



	for(i=0;i<m;i++)
		delete [] set[i];
	delete [] set;
	return 0;
}
