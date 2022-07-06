#include "Application.h"
#include<iostream>
#include<string>
#include<conio.h>

using namespace std;

void MainWindow(Application & App)
{
	setbkcolor(WHITE);//���ô��ڱ�����ɫ
	cleardevice();//���
	IMAGE* main_menu = new IMAGE;//��¼���汳��
	loadimage(main_menu, "data/image/Menu_login.png", 950, 550);//����ͼƬ
	putimage(0, 0, main_menu);//��ʾ��¼�˵�
	//�����Ϣ
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN: 
				if (msg.x > 391 && msg.y > 152 && msg.x < 531 && msg.y < 212)
				{
				    cleardevice(); App.login(); break;//��¼
				}
				if (msg.x > 393 && msg.y > 223 && msg.x < 673 && msg.y < 284)
				{
					cleardevice(); App.login_admin(); break;//����Ա��¼
				}
				if (msg.x > 392 && msg.y > 296 && msg.x < 530 && msg.y < 356)
				{
					cleardevice(); App.regist(); break;//ע��
				}
				if (msg.x > 393 && msg.y > 369 && msg.x < 628 && msg.y < 429)
				{
					cleardevice(); App.delete_user(); break;//ע���˻�
				}
				if (msg.x > 393 && msg.y > 441 && msg.x < 531 && msg.y < 501)
				{
					cleardevice(); exit(1); break;//�˳�
				}
			default:
				break;
			}
		}
	}
	
}

void Application::save()
{
	ofstream outfile("data/Userinfo.txt", ios::out);
	if (!outfile)
	{
		cerr << "open error!" << endl;
		return;
	}
	//�����û����˺�������
	User* pt = u_head;
	//�ȱ����û�����
	outfile << length << endl;
	for (int i = 0; i < length; i++)
	{
		outfile << pt->get_name() << endl;
		outfile << pt->get_phone() << endl;
		outfile << pt->get_account() << endl;
		outfile << pt->get_password() << endl;
		//pt = pt->next;
		pt = pt->get_next();
	}
	outfile.close();
}

Application::Application()
{
	length = 0;//���ó�ʼֵ
	u_head = NULL;
	read();//���ļ��ж�ȡ�����û��ĵ�¼��Ϣ
}

//ɾ���û��˻���Ϣ������ע���˻�
void Application::delete_user()
{
	IMAGE* delete_user = new IMAGE;//��¼���汳��
	loadimage(delete_user, "data/image/delete_user.png", 950, 550);//����ͼƬ
	putimage(0, 0, delete_user);//��ʾ��¼�˵�
	char _account[15],_password[15];
	InputBox(_account, 15, "������Ҫע�����û��˺�", "ע��");
	InputBox(_password, 15, "������Ҫע�����û�����", "ע��");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	outtextxy(416, 238, _account);
	outtextxy(416, 308, _password);
	int flag = 0;
	User* pt = this->u_head;
	User* prept = this->u_head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account() && _password == pt->get_password())
		{	//�ҵ����û�
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "ע��");
			MessageBox(hwnd, "�ҵ����û���", "ע��", MB_OK);
			flag = 1;//�ҵ�
			break;
		}
		else
		{
			prept = pt;
			pt = pt->get_next();
			//pt = pt->next;
		}
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hwnd, "ע��");
		MessageBox(hwnd, "�˺Ż��������", "ע��", MB_OK);
		MainWindow(*this);
	}
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 566 && msg.y > 393 && msg.x < 671 && msg.y < 438)
				{
					//�����ɾ��
					string filepath = "data/" + pt->get_account() + ".txt";
					char path[30];
					strcpy(path, filepath.c_str());
					remove(path);
					if (pt == u_head)//���Ҫɾ��s�Ľڵ�Ϊͷ�ڵ㣬ֱ�ӽ��¸��ڵ���Ϊ����ͷ 
					{
						u_head = pt->get_next();
						//u_head = pt->next;
						delete pt;
						length--;
					}
					else//���Ҫɾ���Ľڵ㲻Ϊͷ�ڵ㣬ʹǰ���ڵ��nextֱ��ָ��Pt���¸��ڵ㲢�ͷ�pt 
					{
						prept->set_next(pt->get_next());
						//prept->next = pt->next;
						delete pt;
						length--;
					}
					//�����û���Ϣ
					pt = u_head;
					ofstream outfile("data/Userinfo.txt", ios::out);
					outfile << length << endl;
					for (int i = 0; i < length; i++)
					{
						outfile << pt->get_name() << endl;
						outfile << pt->get_phone() << endl;
						outfile << pt->get_account() << endl;
						outfile << pt->get_password() << endl;
						pt = pt->get_next();
						//pt = pt->get_next();pt = pt->next;
					}
					outfile.close();
					HWND hwnd = GetHWnd();
					MessageBox(hwnd, "ɾ���ɹ���", "ɾ���û���Ϣ", MB_OK);
				}
				if (msg.x > 568 && msg.y > 460 && msg.x < 672 && msg.y < 505)
				{
					//����˷���
					MainWindow(*this);
				}
				break;
			default:
				break;
			}
		}
	}
}

//��ȡ�û��ĵ�¼��Ϣ
void Application::read()
{
	ifstream infile("data/Userinfo.txt", ios::in);
	//���������ļ������󣬲������뷽ʽ�򿪴����ļ�user.txt
	if (!infile)
	{
		return;
	}
	infile >> length;
	//�����һ���ڵ�
	string name, phone, account, password;
	infile >> name >> phone >> account >> password;
	u_head = new User;
	u_head->set_name(name);
	u_head->set_phone(phone);
	u_head->set_account(account);
	u_head->set_password(password);
	u_head->set_next(NULL);
	//u_head->next = NULL;
	//����ʣ��ڵ�
	for (int i = 1; i < length; i++)
	{
		User* pt = new User;
		string name, phone, account, password;
		infile >> name >> phone >> account >> password;
		pt->set_name(name);
		pt->set_phone(phone);
		pt->set_account(account);
		pt->set_password(password);
		pt->set_next(u_head);
		//pt->next = u_head;
		u_head = pt;
	}
	infile.close();
}

void Application::login()
{
	IMAGE* _login = new IMAGE;//��¼����
	loadimage(_login, "data/image/login.png", 950, 550);//����ͼƬ
	putimage(0, 0, _login);//��ʾͼƬ
	char _account[15];
	InputBox(_account, 15, "�������˺�", "��¼");
	char _password[15];
	InputBox(_password, 15, "����������", "��¼");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(45, 0, "����");//����������ʽ
	outtextxy(416, 157, _account);
	outtextxy(416, 237, _password);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 542 && msg.y > 334 && msg.x < 649 && msg.y < 381)
				{
					//����˵�¼
					string account = _account, password = _password;
					User* pt = u_head;
					int flag = 0;//flag������¼�û��Ƿ��¼�ɹ�
					for (int i = 0; i < length; i++)
					{
						if (account == pt->get_account() && password == pt->get_password())
						{
							HWND hwnd = GetHWnd();
							//���ô��ڱ���
							SetWindowText(hwnd, "��¼");
							MessageBox(hwnd, "��ϲ������¼�ɹ���", "��¼", MB_OK);
							flag = 1;
							cleardevice();
							Menu_user(*pt,*this);//��½�ɹ�������û���������
						}
						//��һ���ڵ�
						pt = pt->get_next();
						//pt = pt->next;
					}
					if (flag == 0)
					{
						HWND hwnd = GetHWnd();
						//���ô��ڱ���
						SetWindowText(hwnd, "��¼");
						MessageBox(hwnd, "�˺Ż�����������������룡", "��¼", MB_OK);
						break;
					}
				}
				if (msg.x > 543 && msg.y > 399 && msg.x < 648 && msg.y < 444)
				{
					//����˷���
					MainWindow(*this);
				}
			}
		}
	}
	return;
}

//ע���˺�
void Application::regist()
{
	IMAGE* _regist = new IMAGE;//��¼���汳��
	loadimage(_regist, "data/image/regist.png", 950, 550);//����ͼƬ
	putimage(0, 0, _regist);//��ʾͼƬ
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	char _name[15], _phone[15], _account[15], _password[15];
	InputBox(_name, 15, "����������", "ע��");
	outtextxy(423, 133, _name);
	InputBox(_phone, 15, "������绰", "ע��");
	outtextxy(423, 197, _phone);
	InputBox(_account, 15, "�������˺�", "ע��");
	outtextxy(423, 265, _account);
	InputBox(_password, 15, "����������", "ע��");
	outtextxy(423, 330, _password);
	read();
	User* pt = u_head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account())
		{
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "ע��");
			MessageBox(hwnd, "ע��ʧ�ܣ����˺��ѱ�ע�ᣡ", "ע��", MB_OK);
			MainWindow(*this);
		}
		else
			pt = pt->get_next();
			//pt = pt->next;
	}
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 567 && msg.y > 394 && msg.x < 672 && msg.y < 442)
				{
					//�����ע��
					if (u_head == NULL)
					{
						u_head = new User;//��̬����һ���û�
						u_head->set_account(_account);
						u_head->set_password(_password);
						u_head->set_name(_name);
						u_head->set_phone(_phone);
						u_head->set_next(NULL);
						//u_head->next = NULL;
						length++;//�����Լ�
					}
					else
					{
						User* pt = new User;//��̬����һ���û�
						u_head->set_account(_account);
						u_head->set_password(_password);
						u_head->set_name(_name);
						u_head->set_phone(_phone);
						pt->set_next(u_head);
						//pt->next = u_head;//�������Ľڵ�ӵ�����ͷ�� 
						u_head = pt;//��ʱͷ�ڵ�Ϊpt 
						length++;//�����Լ�
					}
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "ע��");
					MessageBox(hwnd, "ע��ɹ���", "ע��", MB_OK);
					save();
					break;
				}
				if (msg.x > 567 && msg.y > 462 && msg.x < 672 && msg.y < 507)
				{
					//����˷���
					MainWindow(*this);
				}
			}
		}
	}
}

//����Ա��½
void Application::login_admin()
{
	IMAGE* _login = new IMAGE;//��¼����
	loadimage(_login, "data/image/login.png", 950, 550);//����ͼƬ
	putimage(0, 0, _login);//��ʾͼƬ
	char _account[15];
	InputBox(_account, 15, "�������˺�", "��¼");
	char _password[15];
	InputBox(_password, 15, "����������", "��¼");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(45, 0, "����");//����������ʽ
	outtextxy(416, 157, _account);
	outtextxy(416, 237, _password);
	ifstream infile("data/admin.txt", ios::in);
	//���������ļ������󣬲������뷽ʽ�򿪴����ļ�admin.txt
	if (!infile)
	{
		return;
	}
	string account, password;
	infile >> account >> password;
	infile.close();
	int flag = 0;
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 542 && msg.y > 334 && msg.x < 649 && msg.y < 381)
				{
					//����˵�¼
					if (account == _account && password == _password)
					{
						HWND hwnd = GetHWnd();
						//���ô��ڱ���
						SetWindowText(hwnd, "��¼");
						MessageBox(hwnd, "��ϲ������¼�ɹ���", "��¼", MB_OK);
						flag = 1;
						cleardevice();
						Admin* admin = new Admin(u_head, length);
						read();
						Menu_admin(admin,*this);
					}
					if (flag == 0)
					{
						HWND hwnd = GetHWnd();
						//���ô��ڱ���
						SetWindowText(hwnd, "��¼");
						MessageBox(hwnd, "�˺Ż�����������������룡", "��¼", MB_OK);
						break;
					}
				}
				if (msg.x > 543 && msg.y > 399 && msg.x < 648 && msg.y < 444)
				{
					//����˷���
					MainWindow(*this);
				}
			}
		}
	}
	return;
}
