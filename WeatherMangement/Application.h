#pragma once
#include<graphics.h>
using namespace std;
#include "Admin.h"

class User;
class Application
{
private:
	User* u_head;//�û������ͷָ��
	int length;//�û�����
public:
	void save();//�����û���Ϣ
	Application();//Ĭ�Ϲ��캯��
	void delete_user();//ɾ���û��˻���Ϣ������ע���˻�
	void read();//��ȡ�û���Ϣ
	void login();//��ͨ�û���¼
	void login_admin();//����Ա��¼
	void regist();//ע��
};

void MainWindow(Application &);//������

