#pragma once
#include<iostream>
using namespace std;

class String
{
public:
	String(const char* str = "");
	String(const String& str);
	String& operator=(const String& str); //��ͳ��������
	//String& operator=(const String str); //�ִ���ʹ����swap,������ʹstr._str�ÿգ����Դ�ֵ���ÿ������촴��һ����ʱ�Ķ���
	~String();


private:
	char* _str;
};

