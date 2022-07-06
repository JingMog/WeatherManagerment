#include "Weather.h"
//默认构造函数 
Weather::Weather()
{
	year = 0;
	month = 0;
	day = 0;
	max_temp = 0;
	min_temp = 0;
	ave_temp = 0;
	rainfall = 0;
}
int Weather::get_day()
{
	return day;
}
int Weather::get_month()
{
	return month;
}
int Weather::get_year()
{
	return year;
}
double Weather::get_max_temp()
{
	return max_temp;
}
double Weather::get_min_temp()
{
	return min_temp;
}
double Weather::get_rainfall()
{
	return this->rainfall;
}
void Weather::set_day(int day)
{
	this->day = day;
}
void Weather::set_month(int month)
{
	this->month = month;
}
void Weather::set_year(int year)
{
	this->year = year;
}
void Weather::set_max_temp(double max_temp)
{
	this->max_temp = max_temp;
}
void Weather::set_min_temp(double min_temp)
{
	this->min_temp = min_temp;
}
void Weather::set_rainfall(double rainfall)
{
	this->rainfall = rainfall;
}
double Weather::get_ave_temp()
{
	return ave_temp;
}
void Weather::set_ave_temp(double ave_temp)
{
	this->ave_temp = ave_temp;
}
Weather* Weather::get_next()
{
	return next;
}
void Weather::set_next(Weather* _next)
{
	next = _next;
}