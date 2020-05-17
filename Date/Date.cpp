#include"Date.h"


bool LeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

Date::Date(int year=1990, int month=1, int day=1) //����
{
	if (year > 0 && (month > 0 && month < 13) &&(day > 0 && day <= GetMonthDay(year, month)))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else 
	{
		cout << "the date is error!\n";
	}
}

Date::Date(const Date& d)//�������� d2(d1) 
{                        //���봫���ã���ֹ�ݹ���ÿ������캯��
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
Date::~Date()
{

}

Date& Date::operator=(const Date& d) //��ֵ���������,�������ʱ��(�ַ���)��������ʽ����
{
	if (this != &d)   //�����Ը�ֵ
	{
		_year = d._year;
		_month = d._month;        //��������Ϊ�˼��ٵ��ÿ������캯��
		_day = d._day;
	}
	return *this;  //��������,������void,��Ϊ�˿���ʵ��������ֵ����
}

Date& Date::operator+=(int day) //����+=����
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month -= 12;
		}
	}
	return *this;
}

Date Date::operator+(int day)  //����+����
{
	Date temp(*this);
	temp += day;
	return temp;
}

Date& Date::operator-=(int day) //����-=����
{
	if (day < 0)
	{
		return *this += (-day);
	}
	_day -= day;
	while (_day < 1)
	{
		_day += GetMonthDay(_year, _month);
		_month--;
		if (_month < 1)
		{
			_year--;
			_month += 12;
		}
	}
	return *this;
}

Date  Date::operator-(int day)  //����-���������ı����ڱ���
{
	Date temp(*this);
	temp -= day;
	return temp;
}

Date& Date::operator++()        //++date
{
	*this += 1;
	return *this;
}

Date  Date::operator++(int)     //date++
{
	Date temp(*this);
	*this += 1;
	return temp;   //����������ջ֡���٣����ܷ�������
}

Date& Date::operator--()       //--date
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)    //date--
{
	Date temp(*this);
	*this -= 1;
	return temp;
}

bool Date::operator == (const Date& d) // ==���������
{
	return (_year == d._year) && (_month == d._month) && (_day == d._day);
}

bool Date::operator != (const Date& d) // !=���������
{
	return (_year != d._year) || (_month != d._month) || (_day != d._day);
}

bool Date::operator >  (const Date& d) // >���������
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year)
	{
		if (_month > d._month)
		{
			return true;
		}
		else if (_month == d._month)
		{
			if (_day > d._day)
			{

				return true;
			}
		}
	}
	return false;
}

bool Date::operator >= (const Date& d) // >=���������
{
	return *this > d || *this == d;
}

bool Date::operator <  (const Date& d) // <���������
{
	return !(*this >= d);
}

bool Date::operator <= (const Date& d) // <=���������
{
	return !(*this > d);
}

int Date::GetMonthDay(int year, int month)// ��ȡĳ��ĳ�µ�����
{
	static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = days[month];
	if (month == 2 && LeapYear(year))
	{
		day += 1;
	}
	return day;
}
int Date::operator-(const Date& d)//����������������
{
	Date maxDate(*this);
	Date minDate(d);
	if (maxDate < minDate) {
		maxDate = d;
		minDate = *this;
	}
	int days = 0;
	while (minDate + days < maxDate) 
	{
		days++;
	}
	return days;
}

void Date::Print()const //��ӡ
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

ostream& operator<<(ostream& _cout, const Date& date)
{
	_cout << date._year << "-" << date._month << "-" << date._day;
	return _cout;
}

istream& operator>>(istream& _cin, Date& date)
{
	_cin >> date._year >> date._month >> date._day;
	return _cin;
}