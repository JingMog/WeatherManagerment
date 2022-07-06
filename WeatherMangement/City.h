#pragma once
#include <string>
#include "Weather.h"
using namespace std;

class City;//类的提前声明 

class City_node
{
protected:
	City* next;//节点的next指针 
};

class City :public City_node
{
protected:
	string city_name;//城市名称 
	string phone;//电话区号
	double forecast_value_ols;//平均气温的预测结果,最小二乘法
	double forecast_value_exp;//平均气温预测结果，经验公式
	double forecast_value_alg;//平均气温预测结果，时间序列法
	Weather * head;//天气指针,指向Weather,用来存放链表的头指针
	int length;//当前城市已经存放的天气数目
public:
	City();//构造函数
	void forecast_ols();//最小二乘法进行气温预测
	void forecast_time_exp();//时间序列预测，经验公式
	void forecast_time_alg();//时间序列预测，算法公式
	//类的对外接口
	string get_name();//获取该城市的名称
	string get_phone();//获取该城市的电话区号 
	int get_length();//获取城市已经存放的天气数目
	double get_forecast_value_ols();//获取气温预测结果,模型一
	double get_forecast_time_exp();//获取气温预测结果，模型二
	double get_forecast_time_alg();//获取气温预测结果，模型三
	Weather* get_head();//获取头节点
	void set_head(Weather*);//设置头节点
	void set_length(int);//设置城市的天气数量
	void set_city_name(string);//设置城市名字
	void set_phone(string);//设置城市电话区号
	City* get_next();//获取next指针
	void set_next(City*);//设置next指针
};
