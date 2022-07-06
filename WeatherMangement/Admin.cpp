#include "Admin.h"

Admin::Admin(User* head, int length)
{
	//���ù���Ա�˺�������
	account = "root";
	password = "root";
	this->head = head;
	this->length = length;
}

void Admin::read()
{
	ifstream infile("data/admin.txt", ios::in);
	//���������ļ������󣬲������뷽ʽ�򿪴����ļ�user.txt
	if (!infile)
	{
		return;
	}
	infile >> account >> password;
	infile.close();
}

void Admin::save()
{
	ofstream outfile("data/admin.txt", ios::out);
	if (!outfile)
	{
		return;
	}
	outfile << account << endl;
	outfile << password << endl;
	outfile.close();
}

void Admin::delete_user(Application& App)
{
	IMAGE* delete_user = new IMAGE;
	loadimage(delete_user, "data/image/delete_user_admin.png", 950, 550);
	putimage(0, 0, delete_user);//��ʾͼƬ
	char _account[15];
	InputBox(_account, 15, "������Ҫɾ�����û��˺�", "ɾ���û���Ϣ");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	outtextxy(386, 229, _account);
	int flag = 0;
	User* pt = this->head;
	User* prept = this->head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account())
		{	//�ҵ����û�
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "ɾ���û���Ϣ");
			MessageBox(hwnd, "��ϲ�����ҵ����û���", "ɾ��������Ϣ", MB_OK);
			flag = 1;//�ҵ��ó���
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
		SetWindowText(hwnd, "ɾ���û���Ϣ");
		MessageBox(hwnd, "�޸��û���", "ɾ���û���Ϣ", MB_OK);
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
				if (msg.x > 579 && msg.y > 343 && msg.x < 685 && msg.y < 390)
				{
					//�����ɾ��
					string filepath = "data/" + pt->get_account() + ".txt";
					char path[30];
					//strcpy(path, filepath.c_str());
					strcpy_s(path, filepath.length() + 1, filepath.c_str());
					remove(path);
					if (pt == head)//���Ҫɾ��s�Ľڵ�Ϊͷ�ڵ㣬ֱ�ӽ��¸��ڵ���Ϊ����ͷ 
					{
						head = pt->get_next();
						//head = pt->next;
						pt->clear_city();
						delete pt;
						length--;
					}
					else//���Ҫɾ���Ľڵ㲻Ϊͷ�ڵ㣬ʹǰ���ڵ��nextֱ��ָ��Pt���¸��ڵ㲢�ͷ�pt 
					{
						prept->set_next(pt->get_next());
						//prept->next = pt->next;
						pt->clear_city();
						delete pt;
						length--;
					}
					//�����û���Ϣ
					pt = head;
					ofstream outfile("data/Userinfo.txt", ios::out);
					outfile << length << endl;
					for (int i = 0; i < length; i++)
					{
						outfile << pt->get_name() << endl;
						outfile << pt->get_phone() << endl;
						outfile << pt->get_account() << endl;
						outfile << pt->get_password() << endl;
						pt = pt->get_next();
					}
					outfile.close();
					HWND hwnd = GetHWnd();
					MessageBox(hwnd, "ɾ���ɹ���", "ɾ���û���Ϣ", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
					Menu_admin(this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

void Admin::show_user(Application& App)
{
	App.read();
	User* temp = head;
	for (int i = 0; i < length; i++)
	{
		temp->read();
		temp = temp->get_next();
	}
	IMAGE* show_user = new IMAGE;
	loadimage(show_user, "data/image/show_user.png", 950, 550);
	putimage(0, 0, show_user);//��ʾͼƬ
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	User* pt = head;
	int i = 0;
	while (1)
	{
		//չʾ��ǰ�û���Ϣ
		settextstyle(20, 0, "����");//����������ʽ
		string _account = pt->get_account();
		const char* account = _account.c_str();
		outtextxy(235, 126, account);
		string _password = pt->get_password();
		const char* password = _password.c_str();
		outtextxy(435, 126, password);
		string _name = pt->get_name();
		const char* name = _name.c_str();
		outtextxy(635, 126, name);
		string _phone = pt->get_phone();
		const char* phone = _phone.c_str();
		outtextxy(825, 126, phone);
		City* pw = pt->get_head();
		int d = 0;//���
		if (pw->get_head() == NULL)
		{
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, "�ó�������������Ϣ������Ӻ��ٲ鿴��", "��ʾ�û���Ϣ", MB_OK);
			continue;
		}
		for (int j = 0; j < pt->get_length(); j++)
		{
			pw->forecast_ols();
			pw->forecast_time_alg();
			pw->forecast_time_exp();
			settextstyle(20, 0, "����");//����������ʽ
			string _city_name = pw->get_name();
			const char* city_name = _city_name.c_str();
			outtextxy(130 + d, 175, city_name);
			string _phone = pw->get_phone();
			const char* phone = _phone.c_str();
			outtextxy(130 + d, 230, phone);
			//ģ��һ
			double _forevalue_ols = pw->get_forecast_value_ols();
			char forevalue_ols[10];
			//gcvt(_forevalue, 4, forevalue);
			_gcvt_s(forevalue_ols, 10, _forevalue_ols, 6);
			outtextxy(130 + d, 293, forevalue_ols);
			//ģ�Ͷ�
			double _forevalue_exp = pw->get_forecast_time_exp();
			char forevalue_exp[10];
			//gcvt(_forevalue_exp, 4, forevalue_exp);
			_gcvt_s(forevalue_exp, 10, _forevalue_exp, 6);
			outtextxy(130 + d, 346, forevalue_exp);
			//ģ����
			double _forevalue_alg = pw->get_forecast_time_alg();
			char forevalue_alg[10];
			//gcvt(_forevalue_alg, 4, forevalue_alg);
			_gcvt_s(forevalue_alg, 10, _forevalue_alg, 6);
			outtextxy(130 + d, 413, forevalue_alg);
			d = d + 100;
			//pw = pw->next;
			pw = pw->get_next();
		}

		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 469 && msg.x < 685 && msg.y < 514)
				{
					//����˷���
					Menu_admin(this, App);
				}
				if (msg.x > 711 && msg.y > 470 && msg.x < 846 && msg.y < 515)
				{
					if (i + 1 < length)
					{
						i++;
						pt = pt->get_next();
						cleardevice();
						IMAGE* show_user = new IMAGE;
						loadimage(show_user, "data/image/show_user.png", 950, 550);
						putimage(0, 0, show_user);//��ʾͼƬ
					}
					else
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "����ʾ�����û���Ϣ��", "��ʾ�û���Ϣ", MB_OK);
						Menu_admin(this, App);
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void Admin::modify_admin(Application& App)
{
	read();
	IMAGE* modify_admin = new IMAGE;
	loadimage(modify_admin, "data/image/modify_admin.png", 950, 550);
	putimage(0, 0, modify_admin);//��ʾͼƬ
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	char _account[15], _password[15];
	InputBox(_account, 15, "�����������˺�", "�޸��û�������Ϣ");
	outtextxy(295, 187, _account);
	InputBox(_password, 15, "��������������", "�޸��û�������Ϣ");
	outtextxy(295, 232, _password);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 343 && msg.x < 685 && msg.y < 390)
				{
					//������޸�
					this->account = _account;
					this->password = _password;
					//�޸ĺ���������
					save();
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�޸Ĺ���Ա��Ϣ");
					MessageBox(hwnd, "��Ϣ�޸ĳɹ���", "�޸Ĺ���Ա��Ϣ", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
					Menu_admin(this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

void Menu_admin(Admin * admin,Application& App)
{
	cleardevice();
	admin->read();
	IMAGE* Menu_admin = new IMAGE;//��¼����
	loadimage(Menu_admin, "data/image/Menu_admin.png", 950, 550);//����ͼƬ
	putimage(0, 0, Menu_admin);//��ʾͼƬ
	//�����Ϣ
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 315 && msg.y > 120 && msg.x < 544 && msg.y < 181)
				{
					//��ʾ�û�
					admin->show_user(App);
					break;
				}
				if (msg.x > 315 && msg.y > 212 && msg.x < 544 && msg.y < 271)
				{
					//�޸��˻�
					admin->modify_admin(App);
					break;
				}
				if (msg.x > 315 && msg.y > 297 && msg.x < 544 && msg.y < 357)
				{
					//ɾ���û�
					admin->delete_user(App);
					break;
				}
				if (msg.x > 315 && msg.y > 380 && msg.x < 544 && msg.y < 439)
				{
					//�˳���¼
					MainWindow(App);
					break;
				}
				if (msg.x > 315 && msg.y > 462 && msg.x < 544 && msg.y < 524)
				{
					//�˳�����
					exit(1);
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}
