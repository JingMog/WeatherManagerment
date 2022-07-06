#include "User.h"
#include<iostream>
#include<graphics.h>
#include<fstream>
using namespace std;

User::User()
{
	head = NULL;
	length = 0;
	name = "zhangsan";
	phone = "123456789";
	//初始化账号密码
	account = "123456";
	password = "123456";
}

//为该用户添加城市信息
void User::input_city(Application& App)
{
	IMAGE* input_city = new IMAGE;
	loadimage(input_city, "data/image/input_city.png", 950, 550);
	putimage(0, 0, input_city);//显示图片
	char _city_name[15];
	InputBox(_city_name, 15, "请输入城市名称", "添加城市");
	char _phone[15];
	InputBox(_phone, 15, "请输入电话区号", "添加城市");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(45, 0, "楷体");//设置文字样式
	outtextxy(285, 207, _city_name);
	outtextxy(285, 283, _phone);
	string city_name = _city_name;
	string phone = _phone;
	City* pt = head;
	for (int i = 0; i < length; i++)
	{
		if (city_name == pt->get_name())
		{
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "添加城市");
			MessageBox(hwnd, "添加失败，该城市已存在！", "添加城市", MB_OK);
			Menu_user(*this, App);
		}
		else
			//pt = pt->next;
			pt = pt->get_next();
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
					//点击了登录
					if (head == NULL)
					{
						head = new City;//动态创建一个城市对象
						head->set_city_name(city_name);
						head->set_phone(phone);
						//head->next = NULL;//只有一个节点 
						head->set_next(NULL);
						length++;//长度自加
					}
					else
					{
						City* pt = new City;//动态创建一个城市对象
						pt->set_city_name(city_name);
						pt->set_phone(phone);
						//pt->next = this->head;//将创建的节点加到链表头部 
						pt->set_next(this->head);
						this->head = pt;//此时头节点为pt 
						length++;//长度自加 
					}
					//输入完用户天气信息后立即保存
					save();
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "添加城市");
					MessageBox(hwnd, "城市添加成功！", "添加城市", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
	
	
}

void User::input_weather(Application &App)
{
	read();
	IMAGE* input_weather = new IMAGE;
	loadimage(input_weather, "data/image/input_weather.png", 950, 550);
	putimage(0, 0, input_weather);//显示图片
	char _city_name[15];
	InputBox(_city_name, 15, "请输入要添加天气的城市名称", "添加天气");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	outtextxy(263, 184, _city_name);
	string city_name = _city_name;
	City* pt = this->head;
	int flag = 0;
	int year=0, month=0, day=0;
	double max_temp=0, min_temp=0, ave_temp=0,rainfall=0;
	for (int i = 0; i < length; i++)
	{
		if (city_name == pt->get_name())
		{	//找到该城市
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "添加天气");
			MessageBox(hwnd, "找到该城市，请继续输入该城市的天气信息", "添加天气", MB_OK);
			char _year[5];
			InputBox(_year, 5, "请输入年(数字)", "添加天气");
			outtextxy(180, 237, _year);
			year = int(atof(_year));
			char _month[5];
			InputBox(_month, 5, "请输入月(数字)", "添加天气");
			outtextxy(180, 277, _month);
			month = int(atof(_month));
			char _day[5];
			InputBox(_day, 5, "请输入日(数字)", "添加天气");
			outtextxy(180, 319, _day);
			day = int(atof(_day));
			char _max_temp[5];
			InputBox(_max_temp, 5, "请输入最高气温(数字)", "添加天气");
			outtextxy(682, 183, _max_temp);
			max_temp = atof(_max_temp);
			char _min_temp[5];
			InputBox(_min_temp, 5, "请输入最低气温(数字)", "添加天气");
			outtextxy(682, 225, _min_temp);
			min_temp = atof(_min_temp);
			char _rainfall[10];
			InputBox(_rainfall, 10, "请输入降雨量(数字)", "添加天气");
			outtextxy(651, 274, _rainfall);
			rainfall = atof(_rainfall);
			flag = 1;//找到该城市
			Weather* temp = pt->get_head();
			for (int m = 0; m < pt->get_length(); m++)
			{
				if (year == temp->get_year() && month == temp->get_year() && day == temp->get_day())
				{
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "添加天气");
					MessageBox(hwnd, "添加失败，该日已有天气信息！", "添加天气", MB_OK);
					Menu_user(*this, App);
				}
				else
					//temp = temp->next;
					temp = temp->get_next();
			}
			break;
		}
		else
			pt = pt->get_next();
			//pt = pt->next;	
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hwnd, "添加天气");
		MessageBox(hwnd, "无该城市，请重新输入要添加天气的城市名称", "添加天气", MB_OK);
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
					//点击了添加
					Weather* pwhead = pt->get_head();
					if (pwhead == NULL)
					{
						pwhead = new Weather;//动态创建一个天气对象
						pwhead->set_year(year);
						pwhead->set_month(month);
						pwhead->set_day(day);;
						pwhead->set_max_temp(max_temp);
						pwhead->set_min_temp(min_temp);
						pwhead->set_ave_temp((max_temp + min_temp) / 2);
						pwhead->set_rainfall(rainfall);
						//pwhead->next = NULL;//只有一个节点
						pwhead->set_next(NULL);
						//该城市的天气数量加一
						int weather_length = pt->get_length();
						weather_length++;
						pt->set_length(weather_length);
						pt->set_head(pwhead);
					}
					else
					{
						Weather* pw = new Weather;//动态创建一个天气对象
						pw->set_year(year);
						pw->set_month(month);
						pw->set_day(day);;
						pw->set_max_temp(max_temp);
						pw->set_min_temp(min_temp);
						pw->set_ave_temp((max_temp + min_temp) / 2);
						pw->set_rainfall(rainfall);
						pw->set_next(pt->get_head());
						//pw->next = pt->get_head();//将创建的节点加到链表头部
						pt->set_head(pw);
						//该城市的天气数量加一
						int weather_length = pt->get_length();
						weather_length++;
						pt->set_length(weather_length);
					}
					//输入完用户天气信息后立即保存
					save();
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "添加天气");
					MessageBox(hwnd, "天气添加成功！", "添加城市", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

void User::modify_city(Application& App)
{
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify_city.png", 950, 550);
	putimage(0, 0, modify_city);//显示图片
	char _city_name[15];
	InputBox(_city_name, 15, "请输入要修改的城市名称", "修改城市信息");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	outtextxy(263, 184, _city_name);
	City* pt = this->head;
	int flag = 0;
	string city_name, phone;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//找到该城市
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "修改城市信息");
			MessageBox(hwnd, "找到该城市，请继续输入该城市的信息", "修改城市信息", MB_OK);
			char temp_name[15], temp_phone[15];
			InputBox(temp_name, 15, "请输入城市名称", "修改城市信息");
			outtextxy(260, 303, temp_name);
			city_name = temp_name;
			InputBox(temp_phone, 15, "请输入城市电话区号", "修改城市信息");
			outtextxy(260, 349, temp_phone);
			phone = temp_phone;
			flag = 1;//找到该城市
			break;
		}
		else
			pt = pt->get_next();
			//pt = pt->next;
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hwnd, "修改城市信息");
		MessageBox(hwnd, "无该城市，请重新输入要修改的城市名称", "修改城市信息", MB_OK);
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
					//点击了修改
					pt->set_city_name(city_name);
					pt->set_phone(phone);
					//修改后立即保存
					save();
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "修改城市信息");
					MessageBox(hwnd, "城市信息修改成功！", "修改城市信息", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

void User::modify_weather(Application& App)
{
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify_weather.png", 950, 550);
	putimage(0, 0, modify_city);//显示图片
	char _city_name[15];
	InputBox(_city_name, 15, "请输入城市名称", "修改天气信息");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(30, 0, "楷体");//设置文字样式
	outtextxy(266, 172, _city_name);
	City* pt = this->head;
	Weather* pw = head->get_head();
	int flag = 0, flag1 = 0;
	int year = 0, month = 0, day = 0;
	double max_temp = 0, min_temp = 0, ave_temp = 0, rainfall = 0;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//找到该城市
			HWND hwnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hwnd, "修改天气信息");
			MessageBox(hwnd, "找到该城市，请输入要修改的日期", "修改天气信息", MB_OK);
			char _year[5], _month[5], _day[5];
			int preyear, premonth, preday;
			InputBox(_year, 15, "请输入年", "修改天气信息");
			outtextxy(180, 210, _year);
			preyear = int(atof(_year));
			InputBox(_month, 15, "请输入月", "修改天气信息");
			outtextxy(180, 248, _month);
			premonth = int(atof(_month));
			InputBox(_day, 15, "请输入日", "修改天气信息");
			outtextxy(180, 289, _day);
			preday = int(atof(_day));
			for (int j = 0; j < pt->get_length(); j++)
			{
				pw = pt->get_head();
				if (preyear == pw->get_year() && premonth == pw->get_month() && preday == pw->get_day())
				{
					//找到该天
					flag1 = 1;
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "修改天气信息");
					MessageBox(hwnd, "找到该日，请重新输入该日的天气信息", "修改天气信息", MB_OK);
					char _year[5], _month[5], _day[5], _max_temp[5], _min_temp[5], _rainfall[5];
					InputBox(_year, 15, "请输入年", "修改天气信息");
					outtextxy(564, 173, _year);
					year = int(atof(_year));
					InputBox(_month, 15, "请输入月", "修改天气信息");
					outtextxy(564, 213, _month);
					month = int(atof(_month));
					InputBox(_day, 15, "请输入日", "修改天气信息");
					outtextxy(564, 261, _day);
					day = int(atof(_day));
					InputBox(_max_temp, 15, "请输入最高气温", "修改天气信息");
					outtextxy(797, 173, _max_temp);
					max_temp = int(atof(_max_temp));
					InputBox(_min_temp, 15, "请输入最低气温", "修改天气信息");
					outtextxy(797, 215, _min_temp);
					min_temp = int(atof(_min_temp));
					InputBox(_rainfall, 15, "请输入降雨量", "修改天气信息");
					outtextxy(769, 264, _rainfall);
					rainfall = int(atof(_rainfall));
					ave_temp = (max_temp + min_temp) / 2;
					break;
				}
				else
					//pw = pw->next;
					pw = pw->get_next();
			}
			flag = 1;//找到该城市
			break;
		}
		else
			pt = pt->get_next();
			//pt = pt->next;
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hwnd, "修改天气信息");
		MessageBox(hwnd, "无该城市，请重新输入要修改的城市名称", "修改城市信息", MB_OK);
		flag1 = 1;
	}
	if (flag1 == 0)
	{
		HWND hwnd = GetHWnd();
		//设置窗口标题
		SetWindowText(hwnd, "修改天气信息");
		MessageBox(hwnd, "无该日，请重新输入日期", "修改天气信息", MB_OK);
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
					//点击了修改
					pw->set_year(year);
					pw->set_month(month);
					pw->set_day(day);
					pw->set_max_temp(max_temp);
					pw->set_min_temp(min_temp);
					pw->set_ave_temp(ave_temp);
					pw->set_rainfall(rainfall);
					//修改后立即保存
					save();
					HWND hwnd = GetHWnd();
					//设置窗口标题
					SetWindowText(hwnd, "修改天气信息");
					MessageBox(hwnd, "修改成功！", "修改天气信息", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

//修改某个城市的信息
//1.修改城市信息，
//2.修改城市某天的天气信息
void User::modify(Application& App)
{
	cleardevice();
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify.png", 950, 550);
	putimage(0, 0, modify_city);//显示图片
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 323 && msg.y > 182 && msg.x < 629 && msg.y < 242)
				{
					cleardevice(); this->modify_city(App); break;//修改城市信息
				}
				if (msg.x > 323 && msg.y > 278 && msg.x < 629 && msg.y < 399)
				{
					cleardevice(); this->modify_weather(App); break;//修改天气信息
				}
			default:
				break;
			}
		}
	}
}

void User::delete_city(Application& App)
{
	IMAGE* delete_city = new IMAGE;
	loadimage(delete_city, "data/image/delete_city.png", 950, 550);
	putimage(0, 0, delete_city);//显示图片
	char _city_name[15];
	InputBox(_city_name, 15, "请输入要删除的城市名称", "删除城市信息");
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	outtextxy(386, 229, _city_name);
	int flag = 0;
	City* pt = head;
	City* prept = this->head;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//找到该城市
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, "恭喜您，找到该城市！", "删除城市信息", MB_OK);
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
		MessageBox(hwnd, "无该城市，请重新输入要删除的城市名称", "删除城市信息", MB_OK);
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
					if (pt!=NULL)
					{
						if (pt == head)//如果要删除的节点为头节点，直接将下个节点设为链表头 
						{
							head = pt->get_next();
							//head = pt->next;
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
					}
					//修改后立即保存
					save();
					HWND hwnd = GetHWnd();
					MessageBox(hwnd, "删除成功！", "删除城市信息", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

//显示该用户所有城市的信息
void User::show_city(Application& App)
{
	City* temp = head;
	for (int i = 0; i < length; i++)
	{
		temp->forecast_ols();
		temp->forecast_time_exp();
		temp->forecast_time_alg();
		temp = temp->get_next();
		//temp = temp->next;
	}
	IMAGE* show_city = new IMAGE;
	loadimage(show_city, "data/image/show_city.png", 950, 550);
	putimage(0, 0, show_city);//显示图片
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	if (length == 0)
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, "当前无城市信息，请添加后再查看！", "显示城市信息", MB_OK);
		Menu_user(*this, App);
	}
	City* pt = this->head;
	int i = 0;
	while (1)
	{
		//展示当前城市信息
		settextstyle(20, 0, "楷体");//设置文字样式
		string _name = pt->get_name();
		const char* city_name = _name.c_str();
		outtextxy(93, 111, city_name);
		string _phone = pt->get_phone();
		const char* phone = _phone.c_str();
		outtextxy(270, 111, phone);
		//气温预测模型一，最小二乘法
		double _forevalue_ols = pt->get_forecast_value_ols();
		char forevalue_ols[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_ols, 10, _forevalue_ols, 6);
		outtextxy(447, 111, forevalue_ols);
		//气温预测模型二，经验公式
		double _forevalue_time_exp = pt->get_forecast_time_exp();
		char forevalue_exp[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_exp, 10, _forevalue_time_exp, 6);
		outtextxy(635, 111, forevalue_exp);
		//气温预测模型三，时间序列法，线性代数
		double _forevalue_time_alg = pt->get_forecast_time_alg();
		char forevalue_alg[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_alg, 10, _forevalue_time_alg, 6);
		outtextxy(819, 111, forevalue_alg);
		Weather* pw = pt->get_head();
		int d = 0;//间距
		for (int j = 0; j < pt->get_length(); j++)
		{
			settextstyle(13, 0, "楷体");//设置文字样式
			int _year = pw->get_year();
			char year[10];
			//_itoa(_year, year, 10);
			//考虑使用更安全的_itoa_s(要转化的数字，存放转化结果的字符串，存放结果的字符数组长度，转化的进制数)
			_itoa_s(_year, year, 10,10);
			outtextxy(58 + d, 141, year);//年
			int _month = pw->get_month();
			char month[10];
			//_itoa(_month, month, 10);
			_itoa_s(_month, month, 10, 10);
			outtextxy(58 + d, 177, month);//月
			int _day = pw->get_day();
			char day[10];
			//_itoa(_day, day, 10);
			_itoa_s(_day, day, 10, 10);
			outtextxy(58 + d, 212, day);//日
			double _max_temp = pw->get_max_temp();
			char max_temp[10];
			//_gcvt(_max_temp, 4, max_temp);
			//考虑使用更安全的_gcvt_s(存储结果转换的缓冲区,缓冲区的大小,要转换的值,存储的有效位数);
			//将浮点型数据转化为字符串
			_gcvt_s(max_temp, 10, _max_temp, 5);
			outtextxy(58 + d, 249, max_temp);//最高
			double _min_temp = pw->get_min_temp();
			char min_temp[10];
			//_gcvt(_min_temp, 4, min_temp);
			_gcvt_s(min_temp, 10, _min_temp, 5);
			outtextxy(58 + d, 302, min_temp);//最低
			double _ave_temp = pw->get_ave_temp();
			char ave_temp[10];
			//_gcvt(_ave_temp, 4, ave_temp);
			_gcvt_s(ave_temp, 10, _ave_temp, 5);
			outtextxy(58 + d, 352, ave_temp);//平均
			double _rainfall = pw->get_rainfall();
			char rainfall[10];
			//_gcvt(_rainfall, 4, rainfall);
			_gcvt_s(rainfall, 10, _rainfall, 5);
			outtextxy(58 + d, 404, rainfall);//降雨量
			d = d + 30;
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
					Menu_user(*this, App);
				}
				if (msg.x > 711 && msg.y > 470 && msg.x < 846 && msg.y < 515)
				{
					if (i+1 < length)
					{
						i++;
						pt = pt->get_next();
						//pt = pt->next;
						cleardevice();
						IMAGE* show_city = new IMAGE;
						loadimage(show_city, "data/image/show_city.png", 950, 550);
						putimage(0, 0, show_city);//显示图片
					}
					else
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "已显示所有城市信息！", "显示城市信息", MB_OK);
						Menu_user(*this, App);
					}
					
				}
				break;
			default:
				break;
			}
		}
	}
}

string User::get_account()
{
	return account;
}

void User::set_password(string password)
{
	this->password = password;
}

void User::set_account(string account)
{
	this->account = account;
}

void User::set_name(string name)
{
	this->name = name;
}

void User::set_phone(string phone)
{
	this->phone = phone;
}

string User::get_password()
{
	return password;
}

string User::get_name()
{
	return name;
}

string User::get_phone()
{
	return phone;
}

City* User::get_head()
{
	return head;
}

int User::get_length()
{
	return length;
}

User* User::get_next()
{
	return next;
}

void User::set_next(User* _next)
{
	next = _next;
}
//修改用户个人信息
void User::modify_user(Application& App)
{
	string oldname = "data/" + account + ".txt";
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify_user.png", 950, 550);
	putimage(0, 0, modify_city);//显示图片
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	settextstyle(35, 0, "楷体");//设置文字样式
	char _account[15], _password[15], _name[15], _phone[15];
	InputBox(_account, 15, "请重新输入账号", "修改用户个人信息");
	outtextxy(295, 187, _account);
	InputBox(_password, 15, "请重新输入密码", "修改用户个人信息");
	outtextxy(295, 232, _password);
	InputBox(_name, 15, "请重新输入姓名", "修改用户个人信息");
	outtextxy(295, 279, _name);
	InputBox(_phone, 15, "请重新输入电话号码", "修改用户个人信息");
	outtextxy(295, 323, _phone);
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
					this->name = _name;
					this->phone = _phone;
					//修改用户文件名
					string newname = "data/" + account + ".txt";
					if (!rename(oldname.c_str(), newname.c_str()))
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "信息修改成功！", "修改用户信息", MB_OK);
					}
					//修改后立即保存
					save();
					App.save();
					
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

void User::contact_author(Application & App)
{
	IMAGE* contact_author = new IMAGE;
	loadimage(contact_author, "data/image/contact_author.png", 950, 550);
	putimage(0, 0, contact_author);//显示图片
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			}
		}
	}
}

void User::intrd(Application& App)
{
	IMAGE* intrd = new IMAGE;
	loadimage(intrd, "data/image/intrd.png", 950, 550);
	putimage(0, 0, intrd);//显示图片
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//点击了返回
					Menu_user(*this, App);
				}
				break;
			}
		}
	}
}

void User::clear_city()
{
	City* pt = head;
	for (int i = 0; i < length; i++)
	{
		City* prept = pt;
		//pt = pt->next;
		pt = pt->get_next();
		delete prept;
	}
	return;
}

void User::save()
{
	City* pt = head;
	string filename = "data/" + account + ".txt";
	ofstream outfile(filename, ios::out);
	//定义输出文件流对象，并以输出方式打开磁盘文件,如果文件不存在则打开失败 
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	//city_num为城市数目, weather_num[i]为每个城市对应的天气数目
	int city_num = length;
	int* weather_num = new int[length];
	for (int i = 0; i < city_num; i++)
	{
		weather_num[i] = pt->get_length();//weather_num[i]存放第i个城市的天气数目 
		//pt = pt->next;//指针后移 
		pt = pt->get_next();
	}
	//首先保存该用户的城市数量以及每个城市保存的天气数量
	outfile << city_num << "\n";
	for (int i = 0; i < city_num; i++)
	{
		outfile << weather_num[i] << " ";
	}
	outfile << "\n";
	//用户名，电话区号 
	outfile << name << "\n" << phone << "\n";
	
	//向文件中保存城市信息
	City * p = head;
	for (int i = 0; i < city_num; i++)
	{
		//保存城市名，电话区号 
		outfile << p->get_name() << "\n" << p->get_phone() << "\n";
		Weather * pt = p->get_head();//通过get_head()来获取该城市的天气头节点
		//如果当前城市没有添加天气信息，直接下个城市
		if (weather_num[i] == 0)
		{
			//p = p->next;
			p = p->get_next();
			continue;
		}
		for (int j = 0; j < weather_num[i]; j++)
		{
			//保存年、月、日、最高、最低、平均气温、降雨量
			outfile << pt->get_year() << "\n" << pt->get_month() << "\n" << pt->get_day() << "\n";
			outfile << pt->get_max_temp() << "\n" << pt->get_min_temp() << "\n" << pt->get_ave_temp() << "\n";
			outfile << pt->get_rainfall() << "\n";
			//pt = pt->next;//下一天 
			pt = pt->get_next();
		}
		p = p->get_next();
		//p = p->next;//下一个城市 
	}
	outfile.close();
}

void User::read()
{
	string filepath = "data/" + account + ".txt";
	ifstream infile(filepath, ios::in);
	//定义输入文件流对象，并以输入方式打开磁盘文件user.txt
	if (!infile)
	{
		return;
	}
	//读取城市数量和天气数量
	infile >> length;
	//一维数组用来存放每个城市输入的天气数
	int* weather_num = new int[length];
	for (int i = 0; i < length; i++)
	{
		infile >> weather_num[i];
	}
	//读取用户名和电话
	infile >> name >> phone;
	//读取每个城市的信息
	//处理城市头节点
	head = new City;
	string CityName, Phone;
	infile >> CityName >> Phone;
	head->set_city_name(CityName);
	head->set_phone(Phone);
	head->set_length(weather_num[0]);//设置城市的天气数量
	//读取每个城市的天气信息

	//处理天气头节点
	//pwhead为天气链表的头节点
	if (head->get_length() != 0)
	{
		Weather* pwhead = head->get_head();
		pwhead = new Weather;
		int _day, _month, _year;
		double _max_temp, _min_temp, _ave_temp, _rainfall;
		infile >> _year >> _month >> _day >> _max_temp >> _min_temp >> _ave_temp >> _rainfall;
		pwhead->set_day(_day);
		pwhead->set_month(_month);
		pwhead->set_year(_year);
		pwhead->set_max_temp(_max_temp);
		pwhead->set_min_temp(_min_temp);
		pwhead->set_ave_temp(_ave_temp);
		pwhead->set_rainfall(_rainfall);
		//pwhead->next = NULL;
		pwhead->set_next(NULL);
		head->set_head(pwhead);
		//处理剩余天气节点
		for (int j = 1; j < weather_num[0]; j++)
		{
			Weather* pw = new Weather;
			//从文件中读取年，月，日，最高，最低气温
			int _day, _month, _year;
			double _max_temp, _min_temp, _ave_temp, _rainfall;
			infile >> _year >> _month >> _day >> _max_temp >> _min_temp >> _ave_temp >> _rainfall;
			pw->set_day(_day);
			pw->set_month(_month);
			pw->set_year(_year);
			pw->set_max_temp(_max_temp);
			pw->set_min_temp(_min_temp);
			pw->set_ave_temp(_ave_temp);
			pw->set_rainfall(_rainfall);
			//pw->next = head->get_head();
			pw->set_next(head->get_head());
			head->set_head(pw);
		}
		head->set_next(NULL);
		//head->next = NULL;

	}
	//处理剩余城市节点
	for (int i = 1; i < length; i++)
	{
		City * pt = new City;//创建节点
		//从文件中读取城市名称和电话区号
		string CityName, Phone;
		infile >> CityName >> Phone;
		pt->set_city_name(CityName);
		pt->set_phone(Phone);
		pt->set_length(weather_num[i]);//设置城市的天气数量

		//处理天气头节点
		//pwhead为天气链表的头节点
		if (pt->get_length() != 0)
		{
			Weather* pwhead = pt->get_head();
			pwhead = new Weather;
			int _day, _month, _year;
			double _max_temp, _min_temp, _ave_temp, _rainfall;
			infile >> _year >> _month >> _day >> _max_temp >> _min_temp >> _ave_temp >> _rainfall;
			pwhead->set_day(_day);
			pwhead->set_month(_month);
			pwhead->set_year(_year);
			pwhead->set_max_temp(_max_temp);
			pwhead->set_min_temp(_min_temp);
			pwhead->set_ave_temp(_ave_temp);
			pwhead->set_rainfall(_rainfall);
			//pwhead->next = NULL;
			pwhead->set_next(NULL);
			pt->set_head(pwhead);
			//处理剩余节点
			for (int j = 1; j < weather_num[i]; j++)
			{
				Weather* pw = new Weather;//创建节点
				//从文件中读取年，月，日，最高，最低气温
				int _day, _month, _year;
				double _max_temp, _min_temp, _ave_temp, _rainfall;
				infile >> _year >> _month >> _day >> _max_temp >> _min_temp >> _ave_temp >> _rainfall;
				pw->set_day(_day);
				pw->set_month(_month);
				pw->set_year(_year);
				pw->set_max_temp(_max_temp);
				pw->set_min_temp(_min_temp);
				pw->set_ave_temp(_ave_temp);
				pw->set_rainfall(_rainfall);
				pw->set_next(pt->get_head());
				//pw->next = pt->get_head();
				pt->set_head(pw);
			}
			pt->set_next(head);
			//pt->next = head;
			head = pt;
		}
		
	}
	infile.close();

}

void Menu_user(User& u, Application & App)
{
	cleardevice();
	u.read();
	IMAGE* Menu_user = new IMAGE;//登录界面
	loadimage(Menu_user, "data/image/Menu_user.png", 950, 550);//加载图片
	putimage(0, 0, Menu_user);//显示图片
	//鼠标消息
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 181 && msg.y > 124 && msg.x < 386 && msg.y < 174)
				{
					//添加城市
					u.input_city(App);
					break;
				}
				if (msg.x > 181 && msg.y > 209 && msg.x < 386 && msg.y < 257)
				{
					//为城市添加天气
					u.input_weather(App);
					break;
				}
				if (msg.x > 181 && msg.y > 293 && msg.x < 386 && msg.y < 343)
				{
					//修改城市
					u.modify(App);
					break;
				}
				if (msg.x > 182 && msg.y > 377 && msg.x < 386 && msg.y < 426)
				{
					//删除城市
					u.delete_city(App);
					break;
				}
				if (msg.x > 181 && msg.y > 462 && msg.x < 387 && msg.y < 509)
				{
					//显示城市
					u.show_city(App);
					break;
				}
				if (msg.x > 508 && msg.y > 125 && msg.x < 836 && msg.y < 174)
				{
					//修改用户个人信息
					u.modify_user(App);
					break;
				}
				if (msg.x > 508 && msg.y > 210 && msg.x < 713 && msg.y < 256)
				{
					//退出登录
					MainWindow(App);
					break;
				}
				if (msg.x > 508 && msg.y > 294 && msg.x < 712 && msg.y < 342)
				{
					//退出程序
					exit(1);
				}
				if (msg.x > 507 && msg.y > 379 && msg.x < 712 && msg.y < 427)
				{
					//使用介绍
					u.intrd(App);
					break;
				}
				if (msg.x > 508 && msg.y > 461 && msg.x < 712 && msg.y < 511)
				{
					//联系作者
					u.contact_author(App);
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}
