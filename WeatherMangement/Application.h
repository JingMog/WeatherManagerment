#pragma once
#include<graphics.h>
using namespace std;
#include "Admin.h"

class User;
class Application
{
private:
	User* u_head;//用户链表的头指针
	int length;//用户数量
public:
	void save();//保存用户信息
	Application();//默认构造函数
	void delete_user();//删除用户账户信息，用于注销账户
	void read();//读取用户信息
	void login();//普通用户登录
	void login_admin();//管理员登录
	void regist();//注册
};

void MainWindow(Application &);//主界面

