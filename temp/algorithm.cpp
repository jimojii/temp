//算法类的类外实现
#include"algorithm.h"
//构造函数
Algorithm::Algorithm(int id, string name, int dept_id) {
	this->Id = id;
	this->Name = name;
	this->Deptid = dept_id;
}

//显示个人信息
void Algorithm::Show_information() {
	cout << "职工编号：" << this->Id
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->Get_deptname()
		<< "\t岗位职责：构建数学模型，学会使用更简单高效的方法解决数学问题，参加竞赛" << endl;
}

//获取岗位名称
string Algorithm::Get_deptname() {
	return string("算法部门");
}