#pragma once
#include<iostream>
#include<string>
#include "User.h"
using namespace std;

//����Ա��
//����Ա���Բ鿴�����û���Ϣ
class User;
class Application;
class Admin
{
private:
	User* head;//�û�����ͷָ��
	int length;//�û�����
	string account;
	string password;
public:
	void save();//�������Ա��Ϣ
	void read();//��ȡ����Ա��Ϣ
	Admin(User*, int);//���캯��
	void show_user(Application&);//ͨ���ļ���ȡ�����û���Ϣ����ʾ
	void modify_admin(Application&);//�޸Ĺ���Ա�˺�����
	void delete_user(Application&);//ɾ���û���������Ϣ
};

void Menu_admin(Admin*, Application&);//��������