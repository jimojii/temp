#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"front_end.h"
#include"back_end.h"
#include"algorithm.h"
using namespace std;

#define FILENAME "worker_file.txt" 

class Worker_manager {
public:
	Worker_manager();	//构造管理函数，类内声明

	void Show_meau();	//显示菜单的函数的类内声明

	void Exist();		//退出职工管理器函数的类内声明

	int worker_num;	//记录worker成员人数函数的类内声明
	Worker** woker_arr;	//成员数组指针(二维数组存放的是Worker指针，不管是哪一个部门，都可以用他们的父类代表，再细分部门)
	void Add_worker();	//添加成员信息的函数的类内声明
	
	void save();	//这个函数的作用是把信息写入磁盘文件中，不然程序运行结束后堆区信息就会被释放
	bool file_is_empty;	//判断文件是否为空
	int get_num();	//统计文件中的人数
	void init_worker();	//初始化成员，得到当前worker_num
	
	void Show_worker();//显示成员信息

	void Delete_worker();	//删除成员信息
	int Is_exist(int id);	//判断删除中所选择的成员是否存在的函数(存在就返回成员在指针数组中的位置)

	void Modify_worker(); //修改成员信息函数的类内声明

	void Find_worker();	//查找成员函数的类内声明

	void Sort_worker();	//排序函数类内声明

	void Clean_File();	//清空数据声明

	~Worker_manager();	//析构释放

};