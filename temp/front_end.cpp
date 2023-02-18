#include"front_end.h"
Front_end::Front_end(int id,string name,int dept_id) {
	//对前端类的三个属性进行初始化
	this->Id = id;
	this->Name = name;
	this->Deptid = dept_id;
}
void Front_end::Show_information() {
	cout << "职工编号：" << this->Id
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->Get_deptname()
		<< "\t岗位职责：创建web或是app的前端页面，呈现给用户内容" << endl;
}
string Front_end::Get_deptname() {
	return string("前端开发");
}