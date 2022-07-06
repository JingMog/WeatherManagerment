#pragma once
#include <string>
#include "Weather.h"
using namespace std;

class City;//�����ǰ���� 

class City_node
{
protected:
	City* next;//�ڵ��nextָ�� 
};

class City :public City_node
{
protected:
	string city_name;//�������� 
	string phone;//�绰����
	double forecast_value_ols;//ƽ�����µ�Ԥ����,��С���˷�
	double forecast_value_exp;//ƽ������Ԥ���������鹫ʽ
	double forecast_value_alg;//ƽ������Ԥ������ʱ�����з�
	Weather * head;//����ָ��,ָ��Weather,������������ͷָ��
	int length;//��ǰ�����Ѿ���ŵ�������Ŀ
public:
	City();//���캯��
	void forecast_ols();//��С���˷���������Ԥ��
	void forecast_time_exp();//ʱ������Ԥ�⣬���鹫ʽ
	void forecast_time_alg();//ʱ������Ԥ�⣬�㷨��ʽ
	//��Ķ���ӿ�
	string get_name();//��ȡ�ó��е�����
	string get_phone();//��ȡ�ó��еĵ绰���� 
	int get_length();//��ȡ�����Ѿ���ŵ�������Ŀ
	double get_forecast_value_ols();//��ȡ����Ԥ����,ģ��һ
	double get_forecast_time_exp();//��ȡ����Ԥ������ģ�Ͷ�
	double get_forecast_time_alg();//��ȡ����Ԥ������ģ����
	Weather* get_head();//��ȡͷ�ڵ�
	void set_head(Weather*);//����ͷ�ڵ�
	void set_length(int);//���ó��е���������
	void set_city_name(string);//���ó�������
	void set_phone(string);//���ó��е绰����
	City* get_next();//��ȡnextָ��
	void set_next(City*);//����nextָ��
};
