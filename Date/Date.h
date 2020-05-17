#pragma once
#include<iostream>
using namespace std;


class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& date);
	friend istream& operator>>(istream& _cin, Date& date);
public:
	Date(int year, int month, int day); //构造
	Date(const Date& d); //拷贝构造 d2(d1)
	~Date();

	Date& operator=(const Date& d);
	Date& operator+=(int day); //日期+=天数
	Date  operator+(int day);  //日期+天数
	Date& operator-=(int day); //日期-=天数
	Date  operator-(int day);  //日期-天数，不改变日期本身
	Date& operator++();        //++date
	Date  operator++(int);     //date++
	Date& operator--();        //--date
	Date  operator--(int);     //date--
	bool operator == (const Date& d); // ==运算符重载
	bool operator != (const Date& d); // !=运算符重载
	bool operator >  (const Date& d); // >运算符重载
	bool operator >= (const Date& d); // >=运算符重载
	bool operator <  (const Date& d); // <运算符重载
	bool operator <= (const Date& d); // <=运算符重载

	int GetMonthDay(int year, int month);// 获取某年某月的天数
	int operator-(const Date& d);//两个日期相差多少天
	void Print()const; //打印
private:
	int _year;
	int _month;
	int _day;
};