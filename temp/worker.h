//职工分为三个部门：前端，后端，算法，将三种职工抽象到一个类，用多态管理不同种类
//职工属性为：职工编号，职工姓名，部门编号
//对于职工这个类行为的函数：岗位信息描述，获取该员工的岗位名称
#pragma once
#include<iostream>
using namespace std;
class Worker {
public:
	int Id;	//员工编号
	string Name;	//员工姓名
	int Deptid;		//员工所在部门编号

	//显示个人信息函数(在抽象类中不需要做任何实现，写成纯虚函数)
	virtual void Show_information()=0;
	//获取岗位名称
	virtual string Get_deptname() = 0;
};