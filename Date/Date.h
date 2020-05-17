#pragma once
#include<iostream>
using namespace std;


class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& date);
	friend istream& operator>>(istream& _cin, Date& date);
public:
	Date(int year, int month, int day); //����
	Date(const Date& d); //�������� d2(d1)
	~Date();

	Date& operator=(const Date& d);
	Date& operator+=(int day); //����+=����
	Date  operator+(int day);  //����+����
	Date& operator-=(int day); //����-=����
	Date  operator-(int day);  //����-���������ı����ڱ���
	Date& operator++();        //++date
	Date  operator++(int);     //date++
	Date& operator--();        //--date
	Date  operator--(int);     //date--
	bool operator == (const Date& d); // ==���������
	bool operator != (const Date& d); // !=���������
	bool operator >  (const Date& d); // >���������
	bool operator >= (const Date& d); // >=���������
	bool operator <  (const Date& d); // <���������
	bool operator <= (const Date& d); // <=���������

	int GetMonthDay(int year, int month);// ��ȡĳ��ĳ�µ�����
	int operator-(const Date& d);//����������������
	void Print()const; //��ӡ
private:
	int _year;
	int _month;
	int _day;
};