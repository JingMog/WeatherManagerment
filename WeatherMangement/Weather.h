#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Weather;//类的提前声明 

class Weather_node
{
protected:
	Weather* next;//指向下一个节点	
};

class Weather :public Weather_node
{
private:
	int day;//日 
	int month;//月 
	int year;//年
	double min_temp;//最低气温 
	double max_temp;//最高气温 
	double ave_temp;//平均气温
	double rainfall;//降雨量
public:
	Weather();//构造函数
	//对外接口
	void set_day(int);//设置日
	void set_month(int);//设置月
	void set_year(int);//设置年
	int get_day();//获取日
	int get_month();//获取月
	int get_year();//获取年
	double get_max_temp();//获取最高气温
	double get_min_temp();//获取最低气温
	double get_ave_temp();//获取平均气温
	double get_rainfall();//获取降雨量
	void set_rainfall(double);//设置降雨量
	void set_max_temp(double);//设置最高气温
	void set_min_temp(double);//设置最低气温
	void set_ave_temp(double);//设置平均气温
	Weather* get_next();//获取后继节点
	void set_next(Weather*);//设置后继节点
};
