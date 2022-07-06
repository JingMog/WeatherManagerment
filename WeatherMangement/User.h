#pragma once
#include<string>
#include "City.h"
#include "Application.h"
using namespace std;

class User;//�����ǰ���� 
class Application;//�����ǰ����
class User_node
{
protected:
	User* next;//�û��ڵ��nextָ�� 
};

//�û��� 
class User :public User_node
{
private:
	string account;//�û���¼�˺�
	string password;//�û���¼����
	string name;//�û������� 
	string phone;//�û����ֻ���
	City * head;//�û��ĳ��������ͷָ��
	int length;//�û���ӵĳ�������
	void modify_weather(Application&);//�޸ĳ���ĳ�������
	void modify_city(Application&);//�޸ĳ�����Ϣ
public:
	User();//Ĭ�Ϲ��캯��
	void save();//���û�����Ϣ���浽�ļ���
	void read();//���ļ��ж�ȡ�û���Ϣ 
	void modify_user(Application&);//�޸��û�������Ϣ
	void input_city(Application&);//Ϊ���û���ӳ�����Ϣ
	void input_weather(Application&);//Ϊĳ�����м������������Ϣ
	void modify(Application&);//�޸�ĳ�����е���Ϣ
	void show_city(Application&);//��ʾ���û����г��е���Ϣ
	void delete_city(Application&);//ɾ��������Ϣ
	void clear_city();//������û��ĳ�����Ϣ���û�ע���˻�
	void contact_author(Application&);//��ϵ����
	void intrd(Application&);//ʹ�ý���
	
	//����ӿ�
	string get_account();//��ȡ�˺�
	string get_password();//��ȡ����
	string get_name();//��ȡ����
	string get_phone();//��ȡ�绰
	City* get_head();//��ȡͷָ��
	int get_length();//��ȡ��������
	void set_password(string);//��������
	void set_account(string);//�����˺�
	void set_name(string);//��������
	void set_phone(string);//�����ֻ���
	User* get_next();//��ȡ��̽ڵ�
	void set_next(User*);//���ú�̽ڵ�
};

void MainWindow(Application&);//���˵�
void Menu_user(User &, Application &);//�û��˵�

