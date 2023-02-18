#include<iostream>
#include"worker_manager.h"
#include"worker.h"
#include"front_end.h"
#include"back_end.h"
#include"algorithm.h"
using namespace std;
int main() {
	//实例化一个对象
	Worker_manager wm;
	int choice = 0;
	while (true) {
		wm.Show_meau();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://退出程序功能的接口
			wm.Exist();
			break;
		case 2://添加成员功能的接口(支持批量添加并保存进文件)
			wm.Add_worker();
			
			break;
		case 3://显示信息功能的接口
			wm.Show_worker();
			break;
		case 4://删除成员功能的接口
			wm.Delete_worker();
			break;
		case 5://修改某一个成员信息功能的接口
			wm.Modify_worker();
			break;
		case 6://查找某一位员工功能的接口
			wm.Find_worker();
			break;
		case 7://排序功能的接口（快速排序）
			wm.Sort_worker();
			break;
		case 8://清空数据接口
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}