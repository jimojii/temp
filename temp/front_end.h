//普通员工
#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
//让这个前端类去继承我们之前抽象过的Worker类
//在.h文件中依然只做声明，不做实现
class Front_end :public Worker{
public:
		Front_end(int id, string name, int dept_id);	//构造函数

		//显示个人信息
		void Show_information();

		//获取岗位名称
		string Get_deptname();
};