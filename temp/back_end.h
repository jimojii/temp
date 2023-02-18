//后端作为子类继承父类worker
#pragma once
#include<iostream>
#include"worker.h"
using namespace std;
class Back_end :public Worker {
public:
	//构造函数
	Back_end(int id, string name, int dept_id);
	
	//显示个人信息
	virtual void Show_information();

	//获取岗位名称
	virtual string Get_deptname();
};