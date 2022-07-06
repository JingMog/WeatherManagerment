#include "City.h"
#include<iostream>

using namespace std;

City::City()
{
	head = NULL;//防止指针误操作 
	length = 0;//目前未添加城市
	forecast_value_ols = 0;
	forecast_value_exp = 0;
	forecast_value_alg = 0;
}

//矩阵转置
double* MatT(int row, int col, double* Mat)
{
	double* result = new double[row * col];//结果矩阵
	for (int i = 0; i < row * col; i++)//遍历Mat
	{
		//第x个元素对应row*col阶矩阵的第rowMat行第colMat列
		int x = i + 1;//i从0开始 x从1开始
		int rowMat = 1;
		int colMat = 0;
		while (1)
		{
			if (x - col > 0)
			{
				x = x - col;
				rowMat++;
			}
			else
			{
				colMat = x;
				break;
			}
		}
		//上述将一维数组下标i  转化成了自然矩阵行rowMat列colMat
		//转置后为colMat行rowMat列
		//再转化为一维坐标即可j=(colMat-1)*row+rowMat-1
		result[(colMat - 1) * row + rowMat - 1] = Mat[i];
	}
	return result;
}

//求行列式
double det(int n, double* Mat)
{
	if (n == 1)
		return Mat[0];
	double* subMat = new double[(n - 1) * (n - 1)];//创建n-1阶的代数余子式阵subMat    
	int mov = 0;//判断行是否移动   
	double sum = 0.0;//sum为行列式的值  
	for (int Matrow = 0; Matrow < n; Matrow++) // Mat的行数把矩阵Mat(nn)赋值到subMat(n-1)  
	{
		for (int subMatrow = 0; subMatrow < n - 1; subMatrow++)//把Mat阵第一列各元素的代数余子式存到subMat  
		{
			mov = Matrow > subMatrow ? 0 : 1; //subMat中小于Matrow的行，同行赋值，等于的错过，大于的加一  
			for (int j = 0; j < n - 1; j++)  //从Mat的第二列赋值到第n列  
			{
				subMat[subMatrow * (n - 1) + j] = Mat[(subMatrow + mov) * n + j + 1];
			}
		}
		int flag = (Matrow % 2 == 0 ? 1 : -1);//因为列数为0，所以行数是偶数时候，代数余子式为1.  
		sum += flag * Mat[Matrow * n] * det(n - 1, subMat);//Mat第一列各元素与其代数余子式积的和即为行列式
	}
	delete[]subMat;
	return sum;
}

//求逆矩阵
double* inverseMat(int n, double* Mat)
{
	int i;
	double* subMat = new double[(n - 1) * (n - 1)];//Mat的(代数)余子式subMat[]
	double* adjointMat = new double[n * n];//Mat的伴随矩阵adjointMat[]
	double detMat;//Mat的行列式
	double* inverseMat = new double[n * n];//Mat的逆矩阵inverseMat[]
	detMat = det(n, Mat);//求Mat的行列式,detMat为Mat的行列式 
	if (detMat == 0)
		;
	else
	{
		int adjointMat_index = 0;
		for (int Mat_i = 1; Mat_i <= n; Mat_i++)
		{
			for (int Mat_j = 1; Mat_j <= n; Mat_j++)
			{
				int M_index = 0;
				//求第Mat_i,Mat_j的余子式Mij
				for (i = 0; i < n * n; i++)//循环Mat的下标选出余子式
				{
					//第x个元素对应n阶矩阵的第row行第col列
					int x = i + 1;//i从0开始 x从1开始
					int row = 1;
					int col = 0;
					while (1)
					{
						if (x - n > 0)
						{
							x = x - n;
							row++;
						}
						else
						{
							col = x;
							break;
						}
					}
					if (row != Mat_i && col != Mat_j)
					{
						subMat[M_index] = Mat[i];
						M_index++;
					}
				}
				adjointMat[adjointMat_index] = (adjointMat_index % 2 == 0 ? 1 : -1) * det(n - 1, subMat);//求伴随矩阵各元素
				adjointMat_index++;
			}
		}
		adjointMat = MatT(n, n, adjointMat);//转置
		//利用定义求逆矩阵 
		for (i = 0; i < n * n; i++)
			inverseMat[i] = adjointMat[i] / detMat;
	}
	return inverseMat;
}

//判断是否为闰年
bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

//当前日期转换成从1年1月1日起的天数
int date_to_day(int year,int month,int day)
{
	int i, sum = 0;//sum为总天数 
	int d[2][12] =
	{//第一行为非闰年0，第二行为闰年1
	 {31,28,31,30,3l,30,3l,3l,30,31,30,31},
	 {31,29,31,30,31,30,31,31,30,31,30,31}
	};
	for (i = 1; i <= year - 1; i++)
	{
		if (IsLeapYear(i))
			sum = sum + 366;
		else
			sum = sum + 365;
	}
	bool flag = IsLeapYear(year);
	for (i = 0; i < month - 1; i++)
		sum += d[flag][i];
	sum += day;
	return sum;
}

//气温预测,最小二乘法
void City::forecast_ols()
{
	if (length == 0 || length == 1)
	{
		forecast_value_ols = 0;
		return;
	}
	double a_max, a_min, b_max, b_min;//b为斜率，a为截距
	double* x = new double[length];//横坐标
	double* y_max = new double[length];//纵坐标，最大气温
	double* y_min = new double[length];//纵坐标，最低气温
	Weather* pt = head;
	//设置横纵坐标
	for (int i = 0; i < length; i++)
	{
		y_max[i] = pt->get_max_temp();
		y_min[i] = pt->get_min_temp();
		x[i] = date_to_day(pt->get_year(), pt->get_month(), pt->get_day());
		//pt = pt->next;
		pt = pt->get_next();
	}
	//最大值曲线
	//xy_max为x*y_max, xy_min为x*y_min, xx为x*x, _x为x平均值, _y_max为y_max平均值, _y_min为y_min平均值
	double xy_max = 0, xy_min = 0, xx=0, _x=0, _y_max=0, _y_min=0;
	for (int i = 0; i < length; i++)
	{
		xx += x[i] * x[i];
		_x += x[i];
		_y_max += y_max[i];
		_y_min += y_min[i];
		xy_max += x[i] * y_max[i];
		xy_min += x[i] * y_min[i];
	}
	_x = _x / length;
	_y_max = _y_max / length;
	_y_min = _y_min / length;
	b_max = (xy_max - length * _x * _y_max) / (xx - length * _x * _x);
	b_min = (xy_min - length * _x * _y_min) / (xx - length * _x * _x);
	a_max = _y_max - b_max * _x;
	a_min = _y_min - b_min * _x;
	//y = b_max * x + a_max
	//y = b_min * x + a_min
	double fore_max, fore_min;//预测的气温最大值，预测的气温最小值
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	int x_now = date_to_day(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	fore_max = b_max * x_now + a_max;
	fore_min = b_min * x_now + a_min;
	forecast_value_ols = (fore_max + fore_min) / 2;
	delete []x, y_max, y_min;
}

//气温预测，时间序列预测，经验公式
void City::forecast_time_exp()
{
	if (length == 0)
	{
		forecast_value_exp = 0;
		return;
	}
	//如果样本数据不足，则无法预测
	if (length < 11)
	{
		forecast_value_exp = head->get_ave_temp();
		return;
	}
	//根据前十天气温预测当天气温
	double a[11];
	//根据经验设置参数值
	//设置依据：距预测天数越近，参数值越大
	a[1] = 0.055;
	for (int i = 2; i <= 10; i++)
	{
		a[i] = a[i - 1] + 0.01;
	}
	//求a[0]
	//根据前十天数据求a0
	double avetemp[11];
	Weather* pt = head;
	//获取历史气温数据
	for (int i = 0; i < 11; i++)
	{
		avetemp[i] = pt->get_ave_temp();
		//pt = pt->next;
		pt = pt->get_next();
	}
	a[0] = avetemp[10];
	for (int i = 0; i < 10; i++)
	{
		a[0] -= a[i + 1] * avetemp[i];
	}
	forecast_value_exp = a[0];
	for (int i = 0; i < 10; i++)
	{
		forecast_value_exp += a[i + 1] * avetemp[i];
		//y = a[0] + a[1]*x[1] + a[2]*x[2] + ... + a[10]*x[10]
	}
}

//气温预测，时间序列预测，算法公式
void City::forecast_time_alg()
{
	if (length == 0)
	{
		forecast_value_alg = 0;
		return;
	}
	//如果样本数据不足，则无法预测
	if (length < 11)
	{
		forecast_value_alg = head->get_ave_temp();
		return;
	}
	double a[5] = {0};//未知数矩阵
	double y[5];//样本数据矩阵2
	//11个系数需要11个线性方程来求解
	double Mat[25];//样本数据1
	double x[11] = {0};
	Weather* pt = head;
	for (int i = 1; i <= 9; i++)
	{
		x[i] = pt->get_ave_temp();
		//pt = pt->next;
		pt = pt->get_next();
	}
	//设置样本数据矩阵1
	for (int i = 0; i < 5; i++)
	{
		Mat[5*i] = 1;
		int d = 1;
		for (int j = 0; j < 4; j++)
		{
			Mat[5 * i + d] = x[i + d];
			d++;
		}
	}
	//设置样本数据矩阵2
	for (int i = 0; i < 5; i++)
	{
		y[i] = x[5 + i];
	}
	double* _inverse = inverseMat(5, Mat);//逆矩阵
	double* inverse = MatT(5, 5, _inverse);
	//样本数据矩阵与逆矩阵相乘
	int d = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			a[i] += y[j] * inverse[5 * j + d];
		}
		d++;
	}
	forecast_value_alg = a[0];
	for (int i = 0; i < 4; i++)
	{
		forecast_value_alg += a[i + 1] * x[i+1];
		//y = a[0] + a[1]*x[1] + a[2]*x[2] + ... + a[10]*x[10]
	}
}

int City::get_length()
{
	return length;
}

string City::get_name()
{
	return city_name;
}

string City::get_phone()
{
	return phone;
}

void City::set_city_name(string name)
{
	this->city_name = name;
}

void City::set_phone(string phone)
{
	this->phone = phone;
}

Weather* City::get_head()
{
	return head;
}

void City::set_length(int len)
{
	length = len;
}

void City::set_head(Weather* h)
{
	head = h;
}

void City::set_next(City* _next)
{
	this->next = _next;
}

City* City::get_next()
{
	return next;
}

//获取模型一预测结果
double City::get_forecast_value_ols()
{
	return forecast_value_ols;
}
//获取模型二预测结果
double City::get_forecast_time_exp()
{
	return forecast_value_exp;
}
//获取模型三预测结果
double City::get_forecast_time_alg()
{
	return forecast_value_alg;
}