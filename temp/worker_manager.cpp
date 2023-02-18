#include"worker_manager.h"
//类内Worker构造函数的类外实现(内有文件检测操作)
Worker_manager::Worker_manager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在
	if (!ifs.is_open()) {
		cout << "文件不存在!" << endl;
		//初始化属性
		this->worker_num = 0;
		this->woker_arr = NULL;
		this->file_is_empty = true;
		ifs.close();
		return; 
	}
	//文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空!" << endl;
		this->worker_num = 0;
		this->woker_arr = NULL;
		this->file_is_empty = true;
		ifs.close();
		return;
	}
	//文件存在且有数据 
	int num = this->get_num();
	cout << "当前职工人数为：" << num << endl;
	this->worker_num = num;

	this->woker_arr = new Worker * [this->worker_num];
	this->init_worker();

}

//显示菜单的函数的类外实现
void Worker_manager::Show_meau() {
	cout << "****************************" << endl;
	cout << "****欢迎使用工坊管理系统****" << endl;
	cout << "*******1.退出管理程序*******" << endl;
	cout << "*******2.添加职工信息*******" << endl;
	cout << "*******3.显示职工信息*******" << endl;
	cout << "*******4.删除离职职工*******" << endl;
	cout << "*******5.修改职工信息*******" << endl;
	cout << "*******6.查找职工信息*******" << endl;
	cout << "*******7.按照编号排序*******" << endl;
	cout << "*******8.清空职工信息*******" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

//退出管理器函数的类外实现
void Worker_manager::Exist() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加成员函数的类外实现
void Worker_manager::Add_worker() {
	cout << "请输入要添加职工的数量" << endl;
	int add_num = 0;

	//检测成员数量是否合法
	bool flag1 = 1;
	while (flag1) {
		flag1 = 0;
		cin >> add_num;
		if (add_num <= 0) {
			cout << "输入有误，请输入一个正数" << endl;
			flag1 = 1;
		}
	}
	
	if (add_num > 0) {
		//具体添加操作
		//计算需要为添加进来的数据开辟多少新的空间
		//新空间的大小为原来已记录人数+新增人数
		int new_size = this->worker_num + add_num;
		Worker** new_space = new Worker * [new_size];
		//将原来空间下数据拷贝到新空间下
		if (woker_arr != NULL) {
			for (int i = 0; i < worker_num; i++) {
				new_space[i] = this->woker_arr[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < add_num; i++) {
			int id;				//职工编号
			string name;		//职工姓名
			int dept_select;	//部门编号的选择
			cout << "请输入第" << i + 1 << "个新员工编号" << endl;

			//检测编号是否重复
			bool flag2 = true;
			while (flag2) {
				flag2 = false;
				cin >> id;
				for (int i = 0; i < this->worker_num; i++) {
					if (this->woker_arr[i]->Id == id) {
						cout << "编号已存在，请重新输入" << endl;
						flag2 = true;
					}
				}
			}
			cout << "请输入第" << i + 1 << "个新员工姓名" << endl;
			cin >> name;
			cout << "请选择该员工的部门：" << endl;
			cout << "1.前端部门" << endl;
			cout << "2.后端部门" << endl;
			cout << "3.算法竞赛部门" << endl;

			//检测部门选择输入
			bool flag3 = 1;
			while (flag3) {
				flag3 = 0;
				cin >> dept_select;
				if (dept_select != 1 && dept_select != 2 && dept_select != 3) {
					cout << "输入有误，请重新输入" << endl;
					flag3 = 1;
				}
			}
			
			Worker* w = NULL;
			switch (dept_select)
			{
			case 1:
				w = new Front_end(id, name, 1); break;
			case 2:
				w = new Back_end(id, name, 2); break;
			case 3:
				w = new Algorithm(id, name, 3); break;
			default:
				break;
			}
			new_space[this->worker_num + i] = w;
		}
		//释放原有空间
		delete[]this->woker_arr;
		
		//更改指针指向
		this->woker_arr = new_space;

		//更新成员人数
		this->worker_num= new_size;
		this->file_is_empty = 0;
		cout << "成功添加了" << add_num << "名新职工" << endl;
		this->save();
	}
	
		system("pause");
		system("cls"); 
}

//把终端输入的成员信息写入txt文件的函数的类外实现
void Worker_manager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);		//用输出的形式打开这个文件，也就是写文件

	//将每个人的数据写入文件的函数的类外实现
	for (int i = 0; i < this->worker_num; i++) {
		ofs << this->woker_arr[i]->Id << " "
			<< this->woker_arr[i]->Name << " "
			<< this->woker_arr[i]->Deptid << endl;
	}
	ofs.close();
}

//程序执行时得到当前文件中成员人数的函数的类外实现
int Worker_manager::get_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//打开文件，读
	int id;
	string name;
	int dept;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		num++;
	}
	ifs.close();
	return num;
}

//将当前文件中人员信息写入指针数组中，更新当前的实际成员人数的函数的类外实现
void Worker_manager::init_worker() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dept;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		Worker* worker = NULL;
		if (dept == 1) {
			worker = new Front_end(id, name, dept);
		}
		else if (dept == 2) {
			worker = new Back_end(id, name, dept);
		}
		else {
			worker = new Algorithm(id, name, dept);
		}
		this->woker_arr[index] = worker;
		index++;
	}
	ifs.close();
}

//在终端显示当前成员信息的函数的类外实现
void Worker_manager::Show_worker() {
	if (this->file_is_empty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < worker_num; i++) {
			cout << worker_num << endl;
			this->woker_arr[i]->Show_information();
		}
	}
	system("pause");
	system("cls");
}

//判断终端选择的人员是否存在的函数的类外实现(存在就返回成员在指针数组中的位置,否则返回-1)
int Worker_manager::Is_exist(int id) {
	int index = -1;
	for (int i = 0; i < this->worker_num; i++) {
		if (this->woker_arr[i]->Id == id) {
			index = i;
			break;
		}
	}
	return index;
}
void Worker_manager::Delete_worker() {
	if (this->file_is_empty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else	//按照成员ID删除 
	{
		cout << "输入想要删除的成员的编号" << endl;
		int tem = 0;	cin >> tem;
		int index = this->Is_exist(tem);

		if (index != -1) {
			//数组中通过数据前移删除数据
			for (int i = index; i < this->worker_num - 1; i++) {
				this->woker_arr[i] = this->woker_arr[i + 1];
			}
			this->worker_num--;	//更新数组记录人员个数

			//同步更新到文件
			this->save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "未找到该职工" << endl;
		}
	}
	//清屏
	system("pause");
	system("cls");
}

//修改成员信息函数类外实现
void Worker_manager::Modify_worker() {
	if (this->file_is_empty) {
		cout << "该成员不存在" << endl;
	}
	else {
		cout << "输入修改成员的编号" << endl;
		int id;	cin >> id;

		int ret = this->Is_exist(id);
		if (ret != -1)  //查找到了这个成员
		{
			//释放原来的内存空间，创建新的成员
			delete this->woker_arr[ret];
			int new_id = 0;
			string new_name = " ";
			int new_deptid = 0;

			cout << "查到了：" << id << "号成员，请输入新的成员编号：" << endl;
			cin >> new_id;

			cout << "请输入新的姓名：" << endl;
			cin >> new_name;

			cout << "请输入新的部门编号:" << endl;
			cout << "1.前端部门" << endl;
			cout << "2.后端部门" << endl;
			cout << "3.算法竞赛部门" << endl;
			cin >> new_deptid;

			//创建父类指针
			Worker* worker = NULL;
			//通过不同的编号选择创建不同的子类对象
			switch (new_deptid)
			{
			case 1:
				worker = new Front_end(new_id, new_name, new_deptid);
				break;
			case 2:
				worker = new Back_end(new_id, new_name, new_deptid);
				break;
			case 3:
				worker = new Algorithm(new_id, new_name, new_deptid);
				break;
			default:
				break;
			}

			//更新数据到数组中
			this->woker_arr[ret] = worker;
			cout << "修改成功" << endl;

			//数据保存在文件中
			this->save();
		}
		else //没有查找到 
		{
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找某个成员函数的类外实现
void Worker_manager::Find_worker() {
	if (this->file_is_empty) {
		cout << "成员不存在" << endl;
	}
	else//提供两种查找方式
	{
		cout << "请选择查找方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照姓名查找" << endl;
		int select = 0;
		bool flag = 1;
		while (flag) {
			flag = 0;
			cin >> select;
			if (select != 1 && select != 2) {
				cout << "输入有误，重新输入" << endl;
				flag = 1;
			}
		}

		if (select == 1) //按照编号查找
		{
			int id = 0;
			cout << "请输入要查找成员的编号：" << endl;
			cin >> id;

			int ret = this->Is_exist(id);
			if (ret != -1) {
				cout << "查找成功，编号为：" << this->woker_arr[ret]->Id << "号职工信息如下：" << endl;
				this->woker_arr[ret]->Show_information();
			}
			else {
				cout << "不存在该成员" << endl;
			}
		}

		else if (select == 2)  //按照姓名查
		{
			string name;
			cout << "请输入要查找的姓名" << endl;
			cin >> name;
			for (int i = 0; i < this->worker_num; i++)
			{
				if (this->woker_arr[i]->Name == name) {
					cout << "查找成功，编号为：" << this->woker_arr[i]->Id << "号职工信息如下：" << endl;
					this->woker_arr[i]->Show_information();
				}
				else { cout << "查无此人" << endl; }
			}
		}
	}
	system("pause");
	system("cls");
}


//快速排序
void quick_sort(Worker** woker_arr, int left, int right) {
	int i = left;
	int j = right;
	int pivot = woker_arr[i]->Id;
	if (i >= j) {
		return;
	}
	while (i < j) {
		while (i < j && woker_arr[j]->Id >= pivot) {
			j--;
		}
		woker_arr[i] = woker_arr[j];
		while (i < j && woker_arr[i]->Id <= pivot) {
			i++;
		}
		woker_arr[j] = woker_arr[i];
	}
	woker_arr[i]->Id= pivot;
	quick_sort(woker_arr, left, i - 1);
	quick_sort(woker_arr, i + 1, right);
}
//排序函数类外实现
void Worker_manager::Sort_worker() {
	if (this->file_is_empty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else 
	{
		quick_sort(this->woker_arr, 0, this->worker_num - 1);
		cout << "排序成功,排序结果为";
		this->save();
		this->Show_worker();
	}
}

void Worker_manager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select=0;	
	bool flag = 1;
	while (flag) {
		flag = 0;
		cin >> select;
		if (select != 1 && select != 2) {
			flag = 1;
			cout << "输入有误，请重新输入" << endl;
		}
	}
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->woker_arr != NULL) {
			for (int i = 0; i < this->worker_num; i++) {
				if (this->woker_arr[i] != NULL) {
					delete this->woker_arr[i];
				}
			}
			this->worker_num = 0;
			delete[] this->woker_arr;
			this->woker_arr = NULL;
			this->file_is_empty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}
Worker_manager::~Worker_manager()
{

}