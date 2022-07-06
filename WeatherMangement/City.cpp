#include "City.h"
#include<iostream>

using namespace std;

City::City()
{
	head = NULL;//��ָֹ������� 
	length = 0;//Ŀǰδ��ӳ���
	forecast_value_ols = 0;
	forecast_value_exp = 0;
	forecast_value_alg = 0;
}

//����ת��
double* MatT(int row, int col, double* Mat)
{
	double* result = new double[row * col];//�������
	for (int i = 0; i < row * col; i++)//����Mat
	{
		//��x��Ԫ�ض�Ӧrow*col�׾���ĵ�rowMat�е�colMat��
		int x = i + 1;//i��0��ʼ x��1��ʼ
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
		//������һά�����±�i  ת��������Ȼ������rowMat��colMat
		//ת�ú�ΪcolMat��rowMat��
		//��ת��Ϊһά���꼴��j=(colMat-1)*row+rowMat-1
		result[(colMat - 1) * row + rowMat - 1] = Mat[i];
	}
	return result;
}

//������ʽ
double det(int n, double* Mat)
{
	if (n == 1)
		return Mat[0];
	double* subMat = new double[(n - 1) * (n - 1)];//����n-1�׵Ĵ�������ʽ��subMat    
	int mov = 0;//�ж����Ƿ��ƶ�   
	double sum = 0.0;//sumΪ����ʽ��ֵ  
	for (int Matrow = 0; Matrow < n; Matrow++) // Mat�������Ѿ���Mat(nn)��ֵ��subMat(n-1)  
	{
		for (int subMatrow = 0; subMatrow < n - 1; subMatrow++)//��Mat���һ�и�Ԫ�صĴ�������ʽ�浽subMat  
		{
			mov = Matrow > subMatrow ? 0 : 1; //subMat��С��Matrow���У�ͬ�и�ֵ�����ڵĴ�������ڵļ�һ  
			for (int j = 0; j < n - 1; j++)  //��Mat�ĵڶ��и�ֵ����n��  
			{
				subMat[subMatrow * (n - 1) + j] = Mat[(subMatrow + mov) * n + j + 1];
			}
		}
		int flag = (Matrow % 2 == 0 ? 1 : -1);//��Ϊ����Ϊ0������������ż��ʱ�򣬴�������ʽΪ1.  
		sum += flag * Mat[Matrow * n] * det(n - 1, subMat);//Mat��һ�и�Ԫ�������������ʽ���ĺͼ�Ϊ����ʽ
	}
	delete[]subMat;
	return sum;
}

//�������
double* inverseMat(int n, double* Mat)
{
	int i;
	double* subMat = new double[(n - 1) * (n - 1)];//Mat��(����)����ʽsubMat[]
	double* adjointMat = new double[n * n];//Mat�İ������adjointMat[]
	double detMat;//Mat������ʽ
	double* inverseMat = new double[n * n];//Mat�������inverseMat[]
	detMat = det(n, Mat);//��Mat������ʽ,detMatΪMat������ʽ 
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
				//���Mat_i,Mat_j������ʽMij
				for (i = 0; i < n * n; i++)//ѭ��Mat���±�ѡ������ʽ
				{
					//��x��Ԫ�ض�Ӧn�׾���ĵ�row�е�col��
					int x = i + 1;//i��0��ʼ x��1��ʼ
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
				adjointMat[adjointMat_index] = (adjointMat_index % 2 == 0 ? 1 : -1) * det(n - 1, subMat);//���������Ԫ��
				adjointMat_index++;
			}
		}
		adjointMat = MatT(n, n, adjointMat);//ת��
		//���ö���������� 
		for (i = 0; i < n * n; i++)
			inverseMat[i] = adjointMat[i] / detMat;
	}
	return inverseMat;
}

//�ж��Ƿ�Ϊ����
bool IsLeapYear(int year)
{
	return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

//��ǰ����ת���ɴ�1��1��1���������
int date_to_day(int year,int month,int day)
{
	int i, sum = 0;//sumΪ������ 
	int d[2][12] =
	{//��һ��Ϊ������0���ڶ���Ϊ����1
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

//����Ԥ��,��С���˷�
void City::forecast_ols()
{
	if (length == 0 || length == 1)
	{
		forecast_value_ols = 0;
		return;
	}
	double a_max, a_min, b_max, b_min;//bΪб�ʣ�aΪ�ؾ�
	double* x = new double[length];//������
	double* y_max = new double[length];//�����꣬�������
	double* y_min = new double[length];//�����꣬�������
	Weather* pt = head;
	//���ú�������
	for (int i = 0; i < length; i++)
	{
		y_max[i] = pt->get_max_temp();
		y_min[i] = pt->get_min_temp();
		x[i] = date_to_day(pt->get_year(), pt->get_month(), pt->get_day());
		//pt = pt->next;
		pt = pt->get_next();
	}
	//���ֵ����
	//xy_maxΪx*y_max, xy_minΪx*y_min, xxΪx*x, _xΪxƽ��ֵ, _y_maxΪy_maxƽ��ֵ, _y_minΪy_minƽ��ֵ
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
	double fore_max, fore_min;//Ԥ����������ֵ��Ԥ���������Сֵ
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	int x_now = date_to_day(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	fore_max = b_max * x_now + a_max;
	fore_min = b_min * x_now + a_min;
	forecast_value_ols = (fore_max + fore_min) / 2;
	delete []x, y_max, y_min;
}

//����Ԥ�⣬ʱ������Ԥ�⣬���鹫ʽ
void City::forecast_time_exp()
{
	if (length == 0)
	{
		forecast_value_exp = 0;
		return;
	}
	//����������ݲ��㣬���޷�Ԥ��
	if (length < 11)
	{
		forecast_value_exp = head->get_ave_temp();
		return;
	}
	//����ǰʮ������Ԥ�⵱������
	double a[11];
	//���ݾ������ò���ֵ
	//�������ݣ���Ԥ������Խ��������ֵԽ��
	a[1] = 0.055;
	for (int i = 2; i <= 10; i++)
	{
		a[i] = a[i - 1] + 0.01;
	}
	//��a[0]
	//����ǰʮ��������a0
	double avetemp[11];
	Weather* pt = head;
	//��ȡ��ʷ��������
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

//����Ԥ�⣬ʱ������Ԥ�⣬�㷨��ʽ
void City::forecast_time_alg()
{
	if (length == 0)
	{
		forecast_value_alg = 0;
		return;
	}
	//����������ݲ��㣬���޷�Ԥ��
	if (length < 11)
	{
		forecast_value_alg = head->get_ave_temp();
		return;
	}
	double a[5] = {0};//δ֪������
	double y[5];//�������ݾ���2
	//11��ϵ����Ҫ11�����Է��������
	double Mat[25];//��������1
	double x[11] = {0};
	Weather* pt = head;
	for (int i = 1; i <= 9; i++)
	{
		x[i] = pt->get_ave_temp();
		//pt = pt->next;
		pt = pt->get_next();
	}
	//�����������ݾ���1
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
	//�����������ݾ���2
	for (int i = 0; i < 5; i++)
	{
		y[i] = x[5 + i];
	}
	double* _inverse = inverseMat(5, Mat);//�����
	double* inverse = MatT(5, 5, _inverse);
	//�������ݾ�������������
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

//��ȡģ��һԤ����
double City::get_forecast_value_ols()
{
	return forecast_value_ols;
}
//��ȡģ�Ͷ�Ԥ����
double City::get_forecast_time_exp()
{
	return forecast_value_exp;
}
//��ȡģ����Ԥ����
double City::get_forecast_time_alg()
{
	return forecast_value_alg;
}