#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Weather;//�����ǰ���� 

class Weather_node
{
protected:
	Weather* next;//ָ����һ���ڵ�	
};

class Weather :public Weather_node
{
private:
	int day;//�� 
	int month;//�� 
	int year;//��
	double min_temp;//������� 
	double max_temp;//������� 
	double ave_temp;//ƽ������
	double rainfall;//������
public:
	Weather();//���캯��
	//����ӿ�
	void set_day(int);//������
	void set_month(int);//������
	void set_year(int);//������
	int get_day();//��ȡ��
	int get_month();//��ȡ��
	int get_year();//��ȡ��
	double get_max_temp();//��ȡ�������
	double get_min_temp();//��ȡ�������
	double get_ave_temp();//��ȡƽ������
	double get_rainfall();//��ȡ������
	void set_rainfall(double);//���ý�����
	void set_max_temp(double);//�����������
	void set_min_temp(double);//�����������
	void set_ave_temp(double);//����ƽ������
	Weather* get_next();//��ȡ��̽ڵ�
	void set_next(Weather*);//���ú�̽ڵ�
};
