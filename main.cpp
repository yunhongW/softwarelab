#include<iostream>
#include<vector>
#include"Graph.h"
#include <windows.h>
#include"Tourism.h"
using namespace std;

void menu() {
	// 输出界面
	cout << "====--景区信息管理系统====" << endl;
	cout << "1.创建景区景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.搜索最短路径" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出" << endl;
}

int main() {
	

	menu();
	int n; cin >> n;
	while (n!=0) {
		switch (n) {
		case 1: CreateGraph(); break;
		case 2: checkvex(); cout << "请输入你选择的景区" << endl; int x; cin >> x; GetSpotIfo(x); break;
		case 3: /*printJQ();*/cout << "请输入你的起始位置:"; int y; cin >> y;TravelPath(y); break;
		case 4: FindSortPath(); break;
		case 5:DesignPath(); break;
		case 0:break;
		}
		menu();
		 cin >> n;
	}
	return 0;
}