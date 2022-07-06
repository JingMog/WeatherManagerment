#include "Application.h"
#include<iostream>
#include<string>
#include<conio.h>

using namespace std;

void MainWindow(Application & App)
{
	setbkcolor(WHITE);//设置窗口背景颜色
	cleardevice();//清除
	IMAGE* main_menu = new IMAGE;//登录界面背景
	loadimage(main_menu, "data/image/Menu_login.png", 950, 550);//加载图片
	putimage(0, 0, main_menu);//显示登录菜单
	//鼠标消息
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN: 
				if (msg.x > 391 && msg.y > 152 && msg.x < 531 && msg.y < 212)
				{
				    cleardevice(); App.login(); break;//登录
				}
				if (msg.x > 393 && msg.y > 223 && msg.x < 673 && msg.y < 284)
				{
					cleardevice(); App.login_admin(); break;//管理员登录
				}
				if (msg.x > 392 && msg.y > 296 && msg.x < 530 && msg.y < 356)
				{
					cleardevice(); App.regist(); break;//注册
				}
				if (msg.x > 393 && msg.y > 369 && msg.x < 628 && msg.y < 429)
				{
					cleardevice(); App.delete_user(); break;//注销账户
				}
				if (msg.x > 393 && msg.y > 441 && msg.x < 531 && msg.y < 501)
				{
					cleardevice(); exit(1); break;//退出
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
	//保存用户的账号与密码
	User* pt = u_head;
	//先保存用户个数
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
	length = 0;//设置初始值
	u_head = NULL;
	read();//从文件中读取所有用户的登录信息
}

//删除用户账户信息，用于注销账户
void Application::delete_user()
{
	IMAGE* delete_user = new IMAGE;//登录界面背景
	loadimage(delete_user, "data/image/delete_user.png", 950, 550);//加载图片
	putimage(0, 0, delete_user);//显示登录菜单
	char _account[15],_password[15];
	InputBox(_account, 15, "请输入要注销的用户账号", "注销");
	InputBox(_password, 15, "请输入要注销的用户密码", "注销");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	outtextxy(416, 238, _account);
	outtextxy(416, 308, _password);
	int flag = 0;
	User* pt = this->u_head;
	User* prept = this->u_head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account() && _password == pt->get_password())
		{	//找到该用户
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "注销");
			MessageBox(hwnd, "找到该用户！", "注销", MB_OK);
			flag = 1;//找到
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
		SetWindowText(hwnd, "注销");
		MessageBox(hwnd, "账号或密码错误！", "注销", MB_OK);
		MainWindow(*this);
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
				if (msg.x > 566 && msg.y > 393 && msg.x < 671 && msg.y < 438)
				{
					//点击了删除
					string filepath = "data/" + pt->get_account() + ".txt";
					char path[30];
					strcpy(path, filepath.c_str());
					remove(path);
					if (pt == u_head)//如果要删除s的节点为头节点，直接将下个节点设为链表头 
					{
						u_head = pt->get_next();
						//u_head = pt->next;
						delete pt;
						length--;
					}
					else//如果要删除的节点不为头节点，使前驱节点的next直接指向Pt的下个节点并释放pt 
					{
						prept->set_next(pt->get_next());
						//prept->next = pt->next;
						delete pt;
						length--;
					}
					//保存用户信息
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
					MessageBox(hwnd, "删除成功！", "删除用户信息", MB_OK);
				}
				if (msg.x > 568 && msg.y > 460 && msg.x < 672 && msg.y < 505)
				{
					//点击了返回
					MainWindow(*this);
				}
				break;
			default:
				break;
			}
		}
	}
}

//读取用户的登录信息
void Application::read()
{
	ifstream infile("data/Userinfo.txt", ios::in);
	//定义输入文件流对象，并以输入方式打开磁盘文件user.txt
	if (!infile)
	{
		return;
	}
	infile >> length;
	//处理第一个节点
	string name, phone, account, password;
	infile >> name >> phone >> account >> password;
	u_head = new User;
	u_head->set_name(name);
	u_head->set_phone(phone);
	u_head->set_account(account);
	u_head->set_password(password);
	u_head->set_next(NULL);
	//u_head->next = NULL;
	//处理剩余节点
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
	IMAGE* _login = new IMAGE;//登录界面
	loadimage(_login, "data/image/login.png", 950, 550);//加载图片
	putimage(0, 0, _login);//显示图片
	char _account[15];
	InputBox(_account, 15, "请输入账号", "登录");
	char _password[15];
	InputBox(_password, 15, "请输入密码", "登录");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(45, 0, "楷体");//设置文字样式
	outtextxy(416, 157, _account);
	outtextxy(416, 237, _password);
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 542 && msg.y > 334 && msg.x < 649 && msg.y < 381)
				{
					//点击了登录
					string account = _account, password = _password;
					User* pt = u_head;
					int flag = 0;//flag用来记录用户是否登录成功
					for (int i = 0; i < length; i++)
					{
						if (account == pt->get_account() && password == pt->get_password())
						{
							HWND hwnd = GetHWnd();
							//设置窗口标题
							SetWindowText(hwnd, "登录");
							MessageBox(hwnd, "恭喜您，登录成功！", "登录", MB_OK);
							flag = 1;
							cleardevice();
							Menu_user(*pt,*this);//登陆成功后进入用户操作界面
						}
						//下一个节点
						pt = pt->get_next();
						//pt = pt->next;
					}
					if (flag == 0)
					{
						HWND hwnd = GetHWnd();
						//设置窗口标题
						SetWindowText(hwnd, "登录");
						MessageBox(hwnd, "账号或密码错误，请重新输入！", "登录", MB_OK);
						break;
					}
				}
				if (msg.x > 543 && msg.y > 399 && msg.x < 648 && msg.y < 444)
				{
					//点击了返回
					MainWindow(*this);
				}
			}
		}
	}
	return;
}

//注册账号
void Application::regist()
{
	IMAGE* _regist = new IMAGE;//登录界面背景
	loadimage(_regist, "data/image/regist.png", 950, 550);//加载图片
	putimage(0, 0, _regist);//显示图片
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	char _name[15], _phone[15], _account[15], _password[15];
	InputBox(_name, 15, "请输入姓名", "注册");
	outtextxy(423, 133, _name);
	InputBox(_phone, 15, "请输入电话", "注册");
	outtextxy(423, 197, _phone);
	InputBox(_account, 15, "请输入账号", "注册");
	outtextxy(423, 265, _account);
	InputBox(_password, 15, "请输入密码", "注册");
	outtextxy(423, 330, _password);
	read();
	User* pt = u_head;
	for (int i = 0; i < length; i++)
	{
		if (_account == pt->get_account())
		{
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "注册");
			MessageBox(hwnd, "注册失败，该账号已被注册！", "注册", MB_OK);
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
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 567 && msg.y > 394 && msg.x < 672 && msg.y < 442)
				{
					//点击了注册
					if (u_head == NULL)
					{
						u_head = new User;//动态创建一个用户
						u_head->set_account(_account);
						u_head->set_password(_password);
						u_head->set_name(_name);
						u_head->set_phone(_phone);
						u_head->set_next(NULL);
						//u_head->next = NULL;
						length++;//长度自加
					}
					else
					{
						User* pt = new User;//动态创建一个用户
						u_head->set_account(_account);
						u_head->set_password(_password);
						u_head->set_name(_name);
						u_head->set_phone(_phone);
						pt->set_next(u_head);
						//pt->next = u_head;//将创建的节点加到链表头部 
						u_head = pt;//此时头节点为pt 
						length++;//长度自加
					}
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "注册");
					MessageBox(hwnd, "注册成功！", "注册", MB_OK);
					save();
					break;
				}
				if (msg.x > 567 && msg.y > 462 && msg.x < 672 && msg.y < 507)
				{
					//点击了返回
					MainWindow(*this);
				}
			}
		}
	}
}

//管理员登陆
void Application::login_admin()
{
	IMAGE* _login = new IMAGE;//登录界面
	loadimage(_login, "data/image/login.png", 950, 550);//加载图片
	putimage(0, 0, _login);//显示图片
	char _account[15];
	InputBox(_account, 15, "请输入账号", "登录");
	char _password[15];
	InputBox(_password, 15, "请输入密码", "登录");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(45, 0, "楷体");//设置文字样式
	outtextxy(416, 157, _account);
	outtextxy(416, 237, _password);
	ifstream infile("data/admin.txt", ios::in);
	//定义输入文件流对象，并以输入方式打开磁盘文件admin.txt
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
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 542 && msg.y > 334 && msg.x < 649 && msg.y < 381)
				{
					//点击了登录
					if (account == _account && password == _password)
					{
						HWND hwnd = GetHWnd();
						//设置窗口标题
						SetWindowText(hwnd, "登录");
						MessageBox(hwnd, "恭喜您，登录成功！", "登录", MB_OK);
						flag = 1;
						cleardevice();
						Admin* admin = new Admin(u_head, length);
						read();
						Menu_admin(admin,*this);
					}
					if (flag == 0)
					{
						HWND hwnd = GetHWnd();
						//设置窗口标题
						SetWindowText(hwnd, "登录");
						MessageBox(hwnd, "账号或密码错误，请重新输入！", "登录", MB_OK);
						break;
					}
				}
				if (msg.x > 543 && msg.y > 399 && msg.x < 648 && msg.y < 444)
				{
					//点击了返回
					MainWindow(*this);
				}
			}
		}
	}
	return;
}
