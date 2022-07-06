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
	//��ʼ���˺�����
	account = "123456";
	password = "123456";
}

//Ϊ���û���ӳ�����Ϣ
void User::input_city(Application& App)
{
	IMAGE* input_city = new IMAGE;
	loadimage(input_city, "data/image/input_city.png", 950, 550);
	putimage(0, 0, input_city);//��ʾͼƬ
	char _city_name[15];
	InputBox(_city_name, 15, "�������������", "��ӳ���");
	char _phone[15];
	InputBox(_phone, 15, "������绰����", "��ӳ���");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(45, 0, "����");//����������ʽ
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
			//���ô��ڱ���
			SetWindowText(hwnd, "��ӳ���");
			MessageBox(hwnd, "���ʧ�ܣ��ó����Ѵ��ڣ�", "��ӳ���", MB_OK);
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
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 579 && msg.y > 343 && msg.x < 685 && msg.y < 390)
				{
					//����˵�¼
					if (head == NULL)
					{
						head = new City;//��̬����һ�����ж���
						head->set_city_name(city_name);
						head->set_phone(phone);
						//head->next = NULL;//ֻ��һ���ڵ� 
						head->set_next(NULL);
						length++;//�����Լ�
					}
					else
					{
						City* pt = new City;//��̬����һ�����ж���
						pt->set_city_name(city_name);
						pt->set_phone(phone);
						//pt->next = this->head;//�������Ľڵ�ӵ�����ͷ�� 
						pt->set_next(this->head);
						this->head = pt;//��ʱͷ�ڵ�Ϊpt 
						length++;//�����Լ� 
					}
					//�������û�������Ϣ����������
					save();
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "��ӳ���");
					MessageBox(hwnd, "������ӳɹ���", "��ӳ���", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	putimage(0, 0, input_weather);//��ʾͼƬ
	char _city_name[15];
	InputBox(_city_name, 15, "������Ҫ��������ĳ�������", "�������");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	outtextxy(263, 184, _city_name);
	string city_name = _city_name;
	City* pt = this->head;
	int flag = 0;
	int year=0, month=0, day=0;
	double max_temp=0, min_temp=0, ave_temp=0,rainfall=0;
	for (int i = 0; i < length; i++)
	{
		if (city_name == pt->get_name())
		{	//�ҵ��ó���
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "�������");
			MessageBox(hwnd, "�ҵ��ó��У����������ó��е�������Ϣ", "�������", MB_OK);
			char _year[5];
			InputBox(_year, 5, "��������(����)", "�������");
			outtextxy(180, 237, _year);
			year = int(atof(_year));
			char _month[5];
			InputBox(_month, 5, "��������(����)", "�������");
			outtextxy(180, 277, _month);
			month = int(atof(_month));
			char _day[5];
			InputBox(_day, 5, "��������(����)", "�������");
			outtextxy(180, 319, _day);
			day = int(atof(_day));
			char _max_temp[5];
			InputBox(_max_temp, 5, "�������������(����)", "�������");
			outtextxy(682, 183, _max_temp);
			max_temp = atof(_max_temp);
			char _min_temp[5];
			InputBox(_min_temp, 5, "�������������(����)", "�������");
			outtextxy(682, 225, _min_temp);
			min_temp = atof(_min_temp);
			char _rainfall[10];
			InputBox(_rainfall, 10, "�����뽵����(����)", "�������");
			outtextxy(651, 274, _rainfall);
			rainfall = atof(_rainfall);
			flag = 1;//�ҵ��ó���
			Weather* temp = pt->get_head();
			for (int m = 0; m < pt->get_length(); m++)
			{
				if (year == temp->get_year() && month == temp->get_year() && day == temp->get_day())
				{
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�������");
					MessageBox(hwnd, "���ʧ�ܣ���������������Ϣ��", "�������", MB_OK);
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
		//���ô��ڱ���
		SetWindowText(hwnd, "�������");
		MessageBox(hwnd, "�޸ó��У�����������Ҫ��������ĳ�������", "�������", MB_OK);
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
					//��������
					Weather* pwhead = pt->get_head();
					if (pwhead == NULL)
					{
						pwhead = new Weather;//��̬����һ����������
						pwhead->set_year(year);
						pwhead->set_month(month);
						pwhead->set_day(day);;
						pwhead->set_max_temp(max_temp);
						pwhead->set_min_temp(min_temp);
						pwhead->set_ave_temp((max_temp + min_temp) / 2);
						pwhead->set_rainfall(rainfall);
						//pwhead->next = NULL;//ֻ��һ���ڵ�
						pwhead->set_next(NULL);
						//�ó��е�����������һ
						int weather_length = pt->get_length();
						weather_length++;
						pt->set_length(weather_length);
						pt->set_head(pwhead);
					}
					else
					{
						Weather* pw = new Weather;//��̬����һ����������
						pw->set_year(year);
						pw->set_month(month);
						pw->set_day(day);;
						pw->set_max_temp(max_temp);
						pw->set_min_temp(min_temp);
						pw->set_ave_temp((max_temp + min_temp) / 2);
						pw->set_rainfall(rainfall);
						pw->set_next(pt->get_head());
						//pw->next = pt->get_head();//�������Ľڵ�ӵ�����ͷ��
						pt->set_head(pw);
						//�ó��е�����������һ
						int weather_length = pt->get_length();
						weather_length++;
						pt->set_length(weather_length);
					}
					//�������û�������Ϣ����������
					save();
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�������");
					MessageBox(hwnd, "������ӳɹ���", "��ӳ���", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	putimage(0, 0, modify_city);//��ʾͼƬ
	char _city_name[15];
	InputBox(_city_name, 15, "������Ҫ�޸ĵĳ�������", "�޸ĳ�����Ϣ");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	outtextxy(263, 184, _city_name);
	City* pt = this->head;
	int flag = 0;
	string city_name, phone;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//�ҵ��ó���
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "�޸ĳ�����Ϣ");
			MessageBox(hwnd, "�ҵ��ó��У����������ó��е���Ϣ", "�޸ĳ�����Ϣ", MB_OK);
			char temp_name[15], temp_phone[15];
			InputBox(temp_name, 15, "�������������", "�޸ĳ�����Ϣ");
			outtextxy(260, 303, temp_name);
			city_name = temp_name;
			InputBox(temp_phone, 15, "��������е绰����", "�޸ĳ�����Ϣ");
			outtextxy(260, 349, temp_phone);
			phone = temp_phone;
			flag = 1;//�ҵ��ó���
			break;
		}
		else
			pt = pt->get_next();
			//pt = pt->next;
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hwnd, "�޸ĳ�����Ϣ");
		MessageBox(hwnd, "�޸ó��У�����������Ҫ�޸ĵĳ�������", "�޸ĳ�����Ϣ", MB_OK);
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
					//������޸�
					pt->set_city_name(city_name);
					pt->set_phone(phone);
					//�޸ĺ���������
					save();
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�޸ĳ�����Ϣ");
					MessageBox(hwnd, "������Ϣ�޸ĳɹ���", "�޸ĳ�����Ϣ", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	putimage(0, 0, modify_city);//��ʾͼƬ
	char _city_name[15];
	InputBox(_city_name, 15, "�������������", "�޸�������Ϣ");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(30, 0, "����");//����������ʽ
	outtextxy(266, 172, _city_name);
	City* pt = this->head;
	Weather* pw = head->get_head();
	int flag = 0, flag1 = 0;
	int year = 0, month = 0, day = 0;
	double max_temp = 0, min_temp = 0, ave_temp = 0, rainfall = 0;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//�ҵ��ó���
			HWND hwnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hwnd, "�޸�������Ϣ");
			MessageBox(hwnd, "�ҵ��ó��У�������Ҫ�޸ĵ�����", "�޸�������Ϣ", MB_OK);
			char _year[5], _month[5], _day[5];
			int preyear, premonth, preday;
			InputBox(_year, 15, "��������", "�޸�������Ϣ");
			outtextxy(180, 210, _year);
			preyear = int(atof(_year));
			InputBox(_month, 15, "��������", "�޸�������Ϣ");
			outtextxy(180, 248, _month);
			premonth = int(atof(_month));
			InputBox(_day, 15, "��������", "�޸�������Ϣ");
			outtextxy(180, 289, _day);
			preday = int(atof(_day));
			for (int j = 0; j < pt->get_length(); j++)
			{
				pw = pt->get_head();
				if (preyear == pw->get_year() && premonth == pw->get_month() && preday == pw->get_day())
				{
					//�ҵ�����
					flag1 = 1;
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�޸�������Ϣ");
					MessageBox(hwnd, "�ҵ����գ�������������յ�������Ϣ", "�޸�������Ϣ", MB_OK);
					char _year[5], _month[5], _day[5], _max_temp[5], _min_temp[5], _rainfall[5];
					InputBox(_year, 15, "��������", "�޸�������Ϣ");
					outtextxy(564, 173, _year);
					year = int(atof(_year));
					InputBox(_month, 15, "��������", "�޸�������Ϣ");
					outtextxy(564, 213, _month);
					month = int(atof(_month));
					InputBox(_day, 15, "��������", "�޸�������Ϣ");
					outtextxy(564, 261, _day);
					day = int(atof(_day));
					InputBox(_max_temp, 15, "�������������", "�޸�������Ϣ");
					outtextxy(797, 173, _max_temp);
					max_temp = int(atof(_max_temp));
					InputBox(_min_temp, 15, "�������������", "�޸�������Ϣ");
					outtextxy(797, 215, _min_temp);
					min_temp = int(atof(_min_temp));
					InputBox(_rainfall, 15, "�����뽵����", "�޸�������Ϣ");
					outtextxy(769, 264, _rainfall);
					rainfall = int(atof(_rainfall));
					ave_temp = (max_temp + min_temp) / 2;
					break;
				}
				else
					//pw = pw->next;
					pw = pw->get_next();
			}
			flag = 1;//�ҵ��ó���
			break;
		}
		else
			pt = pt->get_next();
			//pt = pt->next;
	}
	if (flag == 0)
	{
		HWND hwnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hwnd, "�޸�������Ϣ");
		MessageBox(hwnd, "�޸ó��У�����������Ҫ�޸ĵĳ�������", "�޸ĳ�����Ϣ", MB_OK);
		flag1 = 1;
	}
	if (flag1 == 0)
	{
		HWND hwnd = GetHWnd();
		//���ô��ڱ���
		SetWindowText(hwnd, "�޸�������Ϣ");
		MessageBox(hwnd, "�޸��գ���������������", "�޸�������Ϣ", MB_OK);
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
					//������޸�
					pw->set_year(year);
					pw->set_month(month);
					pw->set_day(day);
					pw->set_max_temp(max_temp);
					pw->set_min_temp(min_temp);
					pw->set_ave_temp(ave_temp);
					pw->set_rainfall(rainfall);
					//�޸ĺ���������
					save();
					HWND hwnd = GetHWnd();
					//���ô��ڱ���
					SetWindowText(hwnd, "�޸�������Ϣ");
					MessageBox(hwnd, "�޸ĳɹ���", "�޸�������Ϣ", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

//�޸�ĳ�����е���Ϣ
//1.�޸ĳ�����Ϣ��
//2.�޸ĳ���ĳ���������Ϣ
void User::modify(Application& App)
{
	cleardevice();
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify.png", 950, 550);
	putimage(0, 0, modify_city);//��ʾͼƬ
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 323 && msg.y > 182 && msg.x < 629 && msg.y < 242)
				{
					cleardevice(); this->modify_city(App); break;//�޸ĳ�����Ϣ
				}
				if (msg.x > 323 && msg.y > 278 && msg.x < 629 && msg.y < 399)
				{
					cleardevice(); this->modify_weather(App); break;//�޸�������Ϣ
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
	putimage(0, 0, delete_city);//��ʾͼƬ
	char _city_name[15];
	InputBox(_city_name, 15, "������Ҫɾ���ĳ�������", "ɾ��������Ϣ");
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	outtextxy(386, 229, _city_name);
	int flag = 0;
	City* pt = head;
	City* prept = this->head;
	for (int i = 0; i < length; i++)
	{
		if (_city_name == pt->get_name())
		{	//�ҵ��ó���
			HWND hwnd = GetHWnd();
			MessageBox(hwnd, "��ϲ�����ҵ��ó��У�", "ɾ��������Ϣ", MB_OK);
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
		MessageBox(hwnd, "�޸ó��У�����������Ҫɾ���ĳ�������", "ɾ��������Ϣ", MB_OK);
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
					if (pt!=NULL)
					{
						if (pt == head)//���Ҫɾ���Ľڵ�Ϊͷ�ڵ㣬ֱ�ӽ��¸��ڵ���Ϊ����ͷ 
						{
							head = pt->get_next();
							//head = pt->next;
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
					}
					//�޸ĺ���������
					save();
					HWND hwnd = GetHWnd();
					MessageBox(hwnd, "ɾ���ɹ���", "ɾ��������Ϣ", MB_OK);
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
					Menu_user(*this, App);
				}
				break;
			default:
				break;
			}
		}
	}
}

//��ʾ���û����г��е���Ϣ
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
	putimage(0, 0, show_city);//��ʾͼƬ
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	if (length == 0)
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, "��ǰ�޳�����Ϣ������Ӻ��ٲ鿴��", "��ʾ������Ϣ", MB_OK);
		Menu_user(*this, App);
	}
	City* pt = this->head;
	int i = 0;
	while (1)
	{
		//չʾ��ǰ������Ϣ
		settextstyle(20, 0, "����");//����������ʽ
		string _name = pt->get_name();
		const char* city_name = _name.c_str();
		outtextxy(93, 111, city_name);
		string _phone = pt->get_phone();
		const char* phone = _phone.c_str();
		outtextxy(270, 111, phone);
		//����Ԥ��ģ��һ����С���˷�
		double _forevalue_ols = pt->get_forecast_value_ols();
		char forevalue_ols[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_ols, 10, _forevalue_ols, 6);
		outtextxy(447, 111, forevalue_ols);
		//����Ԥ��ģ�Ͷ������鹫ʽ
		double _forevalue_time_exp = pt->get_forecast_time_exp();
		char forevalue_exp[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_exp, 10, _forevalue_time_exp, 6);
		outtextxy(635, 111, forevalue_exp);
		//����Ԥ��ģ������ʱ�����з������Դ���
		double _forevalue_time_alg = pt->get_forecast_time_alg();
		char forevalue_alg[10];
		//gcvt(_forevalue, 4, forevalue);
		_gcvt_s(forevalue_alg, 10, _forevalue_time_alg, 6);
		outtextxy(819, 111, forevalue_alg);
		Weather* pw = pt->get_head();
		int d = 0;//���
		for (int j = 0; j < pt->get_length(); j++)
		{
			settextstyle(13, 0, "����");//����������ʽ
			int _year = pw->get_year();
			char year[10];
			//_itoa(_year, year, 10);
			//����ʹ�ø���ȫ��_itoa_s(Ҫת�������֣����ת��������ַ�������Ž�����ַ����鳤�ȣ�ת���Ľ�����)
			_itoa_s(_year, year, 10,10);
			outtextxy(58 + d, 141, year);//��
			int _month = pw->get_month();
			char month[10];
			//_itoa(_month, month, 10);
			_itoa_s(_month, month, 10, 10);
			outtextxy(58 + d, 177, month);//��
			int _day = pw->get_day();
			char day[10];
			//_itoa(_day, day, 10);
			_itoa_s(_day, day, 10, 10);
			outtextxy(58 + d, 212, day);//��
			double _max_temp = pw->get_max_temp();
			char max_temp[10];
			//_gcvt(_max_temp, 4, max_temp);
			//����ʹ�ø���ȫ��_gcvt_s(�洢���ת���Ļ�����,�������Ĵ�С,Ҫת����ֵ,�洢����Чλ��);
			//������������ת��Ϊ�ַ���
			_gcvt_s(max_temp, 10, _max_temp, 5);
			outtextxy(58 + d, 249, max_temp);//���
			double _min_temp = pw->get_min_temp();
			char min_temp[10];
			//_gcvt(_min_temp, 4, min_temp);
			_gcvt_s(min_temp, 10, _min_temp, 5);
			outtextxy(58 + d, 302, min_temp);//���
			double _ave_temp = pw->get_ave_temp();
			char ave_temp[10];
			//_gcvt(_ave_temp, 4, ave_temp);
			_gcvt_s(ave_temp, 10, _ave_temp, 5);
			outtextxy(58 + d, 352, ave_temp);//ƽ��
			double _rainfall = pw->get_rainfall();
			char rainfall[10];
			//_gcvt(_rainfall, 4, rainfall);
			_gcvt_s(rainfall, 10, _rainfall, 5);
			outtextxy(58 + d, 404, rainfall);//������
			d = d + 30;
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
						putimage(0, 0, show_city);//��ʾͼƬ
					}
					else
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "����ʾ���г�����Ϣ��", "��ʾ������Ϣ", MB_OK);
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
//�޸��û�������Ϣ
void User::modify_user(Application& App)
{
	string oldname = "data/" + account + ".txt";
	IMAGE* modify_city = new IMAGE;
	loadimage(modify_city, "data/image/modify_user.png", 950, 550);
	putimage(0, 0, modify_city);//��ʾͼƬ
	settextcolor(BLACK);//����������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽ
	settextstyle(35, 0, "����");//����������ʽ
	char _account[15], _password[15], _name[15], _phone[15];
	InputBox(_account, 15, "�����������˺�", "�޸��û�������Ϣ");
	outtextxy(295, 187, _account);
	InputBox(_password, 15, "��������������", "�޸��û�������Ϣ");
	outtextxy(295, 232, _password);
	InputBox(_name, 15, "��������������", "�޸��û�������Ϣ");
	outtextxy(295, 279, _name);
	InputBox(_phone, 15, "����������绰����", "�޸��û�������Ϣ");
	outtextxy(295, 323, _phone);
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
					this->name = _name;
					this->phone = _phone;
					//�޸��û��ļ���
					string newname = "data/" + account + ".txt";
					if (!rename(oldname.c_str(), newname.c_str()))
					{
						HWND hwnd = GetHWnd();
						MessageBox(hwnd, "��Ϣ�޸ĳɹ���", "�޸��û���Ϣ", MB_OK);
					}
					//�޸ĺ���������
					save();
					App.save();
					
				}
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	putimage(0, 0, contact_author);//��ʾͼƬ
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	putimage(0, 0, intrd);//��ʾͼƬ
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//���������Ϣ����,ͬʱ��ȡ�����Ϣ
			//��Ϣ�ַ�
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 580 && msg.y > 417 && msg.x < 684 && msg.y < 462)
				{
					//����˷���
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
	//��������ļ������󣬲��������ʽ�򿪴����ļ�,����ļ����������ʧ�� 
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	//city_numΪ������Ŀ, weather_num[i]Ϊÿ�����ж�Ӧ��������Ŀ
	int city_num = length;
	int* weather_num = new int[length];
	for (int i = 0; i < city_num; i++)
	{
		weather_num[i] = pt->get_length();//weather_num[i]��ŵ�i�����е�������Ŀ 
		//pt = pt->next;//ָ����� 
		pt = pt->get_next();
	}
	//���ȱ�����û��ĳ��������Լ�ÿ�����б������������
	outfile << city_num << "\n";
	for (int i = 0; i < city_num; i++)
	{
		outfile << weather_num[i] << " ";
	}
	outfile << "\n";
	//�û������绰���� 
	outfile << name << "\n" << phone << "\n";
	
	//���ļ��б��������Ϣ
	City * p = head;
	for (int i = 0; i < city_num; i++)
	{
		//������������绰���� 
		outfile << p->get_name() << "\n" << p->get_phone() << "\n";
		Weather * pt = p->get_head();//ͨ��get_head()����ȡ�ó��е�����ͷ�ڵ�
		//�����ǰ����û�����������Ϣ��ֱ���¸�����
		if (weather_num[i] == 0)
		{
			//p = p->next;
			p = p->get_next();
			continue;
		}
		for (int j = 0; j < weather_num[i]; j++)
		{
			//�����ꡢ�¡��ա���ߡ���͡�ƽ�����¡�������
			outfile << pt->get_year() << "\n" << pt->get_month() << "\n" << pt->get_day() << "\n";
			outfile << pt->get_max_temp() << "\n" << pt->get_min_temp() << "\n" << pt->get_ave_temp() << "\n";
			outfile << pt->get_rainfall() << "\n";
			//pt = pt->next;//��һ�� 
			pt = pt->get_next();
		}
		p = p->get_next();
		//p = p->next;//��һ������ 
	}
	outfile.close();
}

void User::read()
{
	string filepath = "data/" + account + ".txt";
	ifstream infile(filepath, ios::in);
	//���������ļ������󣬲������뷽ʽ�򿪴����ļ�user.txt
	if (!infile)
	{
		return;
	}
	//��ȡ������������������
	infile >> length;
	//һά�����������ÿ�����������������
	int* weather_num = new int[length];
	for (int i = 0; i < length; i++)
	{
		infile >> weather_num[i];
	}
	//��ȡ�û����͵绰
	infile >> name >> phone;
	//��ȡÿ�����е���Ϣ
	//�������ͷ�ڵ�
	head = new City;
	string CityName, Phone;
	infile >> CityName >> Phone;
	head->set_city_name(CityName);
	head->set_phone(Phone);
	head->set_length(weather_num[0]);//���ó��е���������
	//��ȡÿ�����е�������Ϣ

	//��������ͷ�ڵ�
	//pwheadΪ���������ͷ�ڵ�
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
		//����ʣ�������ڵ�
		for (int j = 1; j < weather_num[0]; j++)
		{
			Weather* pw = new Weather;
			//���ļ��ж�ȡ�꣬�£��գ���ߣ��������
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
	//����ʣ����нڵ�
	for (int i = 1; i < length; i++)
	{
		City * pt = new City;//�����ڵ�
		//���ļ��ж�ȡ�������ƺ͵绰����
		string CityName, Phone;
		infile >> CityName >> Phone;
		pt->set_city_name(CityName);
		pt->set_phone(Phone);
		pt->set_length(weather_num[i]);//���ó��е���������

		//��������ͷ�ڵ�
		//pwheadΪ���������ͷ�ڵ�
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
			//����ʣ��ڵ�
			for (int j = 1; j < weather_num[i]; j++)
			{
				Weather* pw = new Weather;//�����ڵ�
				//���ļ��ж�ȡ�꣬�£��գ���ߣ��������
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
	IMAGE* Menu_user = new IMAGE;//��¼����
	loadimage(Menu_user, "data/image/Menu_user.png", 950, 550);//����ͼƬ
	putimage(0, 0, Menu_user);//��ʾͼƬ
	//�����Ϣ
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
					//��ӳ���
					u.input_city(App);
					break;
				}
				if (msg.x > 181 && msg.y > 209 && msg.x < 386 && msg.y < 257)
				{
					//Ϊ�����������
					u.input_weather(App);
					break;
				}
				if (msg.x > 181 && msg.y > 293 && msg.x < 386 && msg.y < 343)
				{
					//�޸ĳ���
					u.modify(App);
					break;
				}
				if (msg.x > 182 && msg.y > 377 && msg.x < 386 && msg.y < 426)
				{
					//ɾ������
					u.delete_city(App);
					break;
				}
				if (msg.x > 181 && msg.y > 462 && msg.x < 387 && msg.y < 509)
				{
					//��ʾ����
					u.show_city(App);
					break;
				}
				if (msg.x > 508 && msg.y > 125 && msg.x < 836 && msg.y < 174)
				{
					//�޸��û�������Ϣ
					u.modify_user(App);
					break;
				}
				if (msg.x > 508 && msg.y > 210 && msg.x < 713 && msg.y < 256)
				{
					//�˳���¼
					MainWindow(App);
					break;
				}
				if (msg.x > 508 && msg.y > 294 && msg.x < 712 && msg.y < 342)
				{
					//�˳�����
					exit(1);
				}
				if (msg.x > 507 && msg.y > 379 && msg.x < 712 && msg.y < 427)
				{
					//ʹ�ý���
					u.intrd(App);
					break;
				}
				if (msg.x > 508 && msg.y > 461 && msg.x < 712 && msg.y < 511)
				{
					//��ϵ����
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
