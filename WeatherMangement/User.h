#pragma once
#include<string>
#include "City.h"
#include "Application.h"
using namespace std;

class User;//类的提前声明 
class Application;//类的提前声明
class User_node
{
protected:
	User* next;//用户节点的next指针 
};

//用户类 
class User :public User_node
{
private:
	string account;//用户登录账号
	string password;//用户登录密码
	string name;//用户的姓名 
	string phone;//用户的手机号
	City * head;//用户的城市链表的头指针
	int length;//用户添加的城市数量
	void modify_weather(Application&);//修改城市某天的天气
	void modify_city(Application&);//修改城市信息
public:
	User();//默认构造函数
	void save();//将用户的信息保存到文件中
	void read();//从文件中读取用户信息 
	void modify_user(Application&);//修改用户个人信息
	void input_city(Application&);//为该用户添加城市信息
	void input_weather(Application&);//为某个城市继续添加天气信息
	void modify(Application&);//修改某个城市的信息
	void show_city(Application&);//显示该用户所有城市的信息
	void delete_city(Application&);//删除城市信息
	void clear_city();//清除该用户的城市信息，用户注销账户
	void contact_author(Application&);//联系作者
	void intrd(Application&);//使用介绍
	
	//对外接口
	string get_account();//获取账号
	string get_password();//获取密码
	string get_name();//获取姓名
	string get_phone();//获取电话
	City* get_head();//获取头指针
	int get_length();//获取城市数量
	void set_password(string);//设置密码
	void set_account(string);//设置账号
	void set_name(string);//设置姓名
	void set_phone(string);//设置手机号
	User* get_next();//获取后继节点
	void set_next(User*);//设置后继节点
};

void MainWindow(Application&);//主菜单
void Menu_user(User &, Application &);//用户菜单

