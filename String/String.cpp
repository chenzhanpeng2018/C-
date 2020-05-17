#include"String.h"
#include<assert.h>
//��ͳ��:
String::String(const char* str) //ȱʡ���� str="" ,��������
{
	if (str == nullptr)
	{
		assert(false);
		return;
	}

	_str = new char[strlen(str) + 1];
	strcpy(_str, str);
}

String::String(const String& str)
	:_str(nullptr)
{
	_str = new char[strlen(str._str) + 1];
	strcpy(_str, str._str);

}

String& String::operator=(const String& str)
{
	if (this != &str)
	{
		char* pStr = new char[strlen(str._str) + 1];
		strcpy(pStr, str._str);
		delete[] _str;
		_str = pStr;
	}
	return *this;
}

String::~String()
{
	if (_str)
	{
		delete[] _str;
		_str = nullptr;
	}
}

////////////////////////////////////////////////////////////
//�ִ���:

String::String(const char* str) //ȱʡ���� str="" ,��������
{
	if (str == nullptr)
		str = "";

	_str = new char[strlen(str) + 1];
	strcpy(_str, str);
}

String::String(const String& str)
	:_str(nullptr) //�����ʼ��Ϊ��,��ֹswap֮��,��ʱ���������Ƿ�����
{
	String temp(str._str);
	swap(_str, temp._str);
}

String& String::operator=(String str) //�ִ���ʹ����swap,������ʹstr._str�ÿգ����Դ�ֵ���ÿ������촴��һ����ʱ�Ķ���
{
	swap(_str, str._str);
	return *this;
}

String::~String()
{
	if (_str)
	{
		delete[] _str;
		_str = nullptr;
	}
}
