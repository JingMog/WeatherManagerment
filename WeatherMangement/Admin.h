#pragma once
#include<iostream>
#include<string>
#include "User.h"
using namespace std;

//管理员类
//管理员可以查看所有用户信息
class User;
class Application;
class Admin
{
private:
	User* head;//用户链表头指针
	int length;//用户数量
	string account;
	string password;
public:
	void save();//保存管理员信息
	void read();//读取管理员信息
	Admin(User*, int);//构造函数
	void show_user(Application&);//通过文件读取所有用户信息并显示
	void modify_admin(Application&);//修改管理员账号密码
	void delete_user(Application&);//删除用户的所有信息
};

void Menu_admin(Admin*, Application&);//函数声明