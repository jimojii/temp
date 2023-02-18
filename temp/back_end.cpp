#include"back_end.h"
//构造函数
Back_end::Back_end(int id, string name, int dept_id) {
	this->Id = id;
	this->Name = name;
	this->Deptid = dept_id;
}

//显示个人信息
void Back_end::Show_information() {
	cout << "职工编号：" << this->Id
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->Get_deptname()
		<< "\t岗位职责：在后台工作，控制着前端的内容，主要负责程序设计架构思想，管理数据库" << endl;
}

//获取岗位名称
string Back_end::Get_deptname() {
	return string("后端开发部门");
}
