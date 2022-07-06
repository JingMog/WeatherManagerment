#include "Admin.h"

Admin::Admin(User* head, int length)
{
	//设置管理员账号与密码
	account = "root";
	password = "root";
	this->head = head;
	this->length = length;
}

void Admin::read()
{
	ifstream infile("data/admin.txt", ios::in);
	//定义输入文件流对象，并以输入方式打开磁盘文件user.txt
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
	putimage(0, 0, delete_user);//显示图片
	char _account[15];
	InputBox(_account, 15, "请输入要删除的用户账号", "删除用户信息");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	outtextxy(386, 229, _account);
	int flag = 0;
	User* pt = this->head;
	User* prept = this->head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account())
		{	//找到该用户
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "删除用户信息");
			MessageBox(hwnd, "恭喜您，找到该用户！", "删除城市信息", MB_OK);
			flag = 1;//找到该城市
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
		//设置窗口标题
		SetWindowText(hwnd, "删除用户信息");
		MessageBox(hwnd, "无该用户！", "删除用户信息", MB_OK);
	}
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 343 && msg.x < 685 && msg.y < 390)
				{
					//点击了删除
					string filepath = "data/" + pt->get_account() + ".txt";
					char path[30];
					//strcpy(path, filepath.c_str());
					strcpy_s(path, filepath.length() + 1, filepath.c_str());
					remove(path);
					if (pt == head)//如果要删除s的节点为头节点，直接将下个节点设为链表头 
					{
						head = pt->get_next();
						//head = pt->next;
						pt->clear_city();
						delete pt;
						length--;
					}
					else//如果要删除的节点不为头节点，使前驱节点的next直接指向Pt的下个节点并释放pt 
					{
						prept->set_next(pt->get_next());
						//prept->next = pt->next;
						pt->clear_city();
						delete pt;
						length--;
					}
					//保存用户信息
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
					MessageBox(hwnd, "删除成功！", "删除用户信息", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
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
	putimage(0, 0, show_user);//显示图片
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	User* pt = head;
	int i = 0;
	while (1)
	{
		//展示当前用户信息
		settextstyle(20, 0, "楷体");//设置文字样式
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
		int d = 0;//间距
		if (pw->get_head() == NULL)
		{
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, "该城市暂无天气信息，请添加后再查看！", "显示用户信息", MB_OK);
			continue;
		}
		for (int j = 0; j < pt->get_length(); j++)
		{
			pw->forecast_ols();
			pw->forecast_time_alg();
			pw->forecast_time_exp();
			settextstyle(20, 0, "楷体");//设置文字样式
			string _city_name = pw->get_name();
			const char* city_name = _city_name.c_str();
			outtextxy(130 + d, 175, city_name);
			string _phone = pw->get_phone();
			const char* phone = _phone.c_str();
			outtextxy(130 + d, 230, phone);
			//模型一
			double _forevalue_ols = pw->get_forecast_value_ols();
			char forevalue_ols[10];
			//gcvt(_forevalue, 4, forevalue);
			_gcvt_s(forevalue_ols, 10, _forevalue_ols, 6);
			outtextxy(130 + d, 293, forevalue_ols);
			//模型二
			double _forevalue_exp = pw->get_forecast_time_exp();
			char forevalue_exp[10];
			//gcvt(_forevalue_exp, 4, forevalue_exp);
			_gcvt_s(forevalue_exp, 10, _forevalue_exp, 6);
			outtextxy(130 + d, 346, forevalue_exp);
			//模型三
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
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 469 && msg.x < 685 && msg.y < 514)
				{
					//点击了返回
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
						putimage(0, 0, show_user);//显示图片
					}
					else
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "已显示所有用户信息！", "显示用户信息", MB_OK);
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
	putimage(0, 0, modify_admin);//显示图片
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	char _account[15], _password[15];
	InputBox(_account, 15, "请重新输入账号", "修改用户个人信息");
	outtextxy(295, 187, _account);
	InputBox(_password, 15, "请重新输入密码", "修改用户个人信息");
	outtextxy(295, 232, _password);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 343 && msg.x < 685 && msg.y < 390)
				{
					//点击了修改
					this->account = _account;
					this->password = _password;
					//修改后立即保存
					save();
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "修改管理员信息");
					MessageBox(hwnd, "信息修改成功！", "修改管理员信息", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
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
	IMAGE* Menu_admin = new IMAGE;//登录界面
	loadimage(Menu_admin, "data/image/Menu_admin.png", 950, 550);//加载图片
	putimage(0, 0, Menu_admin);//显示图片
	//鼠标消息
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
					//显示用户
					admin->show_user(App);
					break;
				}
				if (msg.x > 315 && msg.y > 212 && msg.x < 544 && msg.y < 271)
				{
					//修改账户
					admin->modify_admin(App);
					break;
				}
				if (msg.x > 315 && msg.y > 297 && msg.x < 544 && msg.y < 357)
				{
					//删除用户
					admin->delete_user(App);
					break;
				}
				if (msg.x > 315 && msg.y > 380 && msg.x < 544 && msg.y < 439)
				{
					//退出登录
					MainWindow(App);
					break;
				}
				if (msg.x > 315 && msg.y > 462 && msg.x < 544 && msg.y < 524)
				{
					//退出程序
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
