//算法部门类作为子类继承父类
#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
//算法类的类内声明
class Algorithm :public Worker{
public:
	//构造函数
	Algorithm(int id,string name,int dept_id);

	//显示个人信息
	void Show_information();

	//获取岗位名称
	string Get_deptname();
};