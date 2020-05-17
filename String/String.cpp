#include"String.h"
#include<assert.h>
//传统版:
String::String(const char* str) //缺省参数 str="" ,声明处给
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
//现代版:

String::String(const char* str) //缺省参数 str="" ,声明处给
{
	if (str == nullptr)
		str = "";

	_str = new char[strlen(str) + 1];
	strcpy(_str, str);
}

String::String(const String& str)
	:_str(nullptr) //必须初始化为空,防止swap之后,临时变量发生非法访问
{
	String temp(str._str);
	swap(_str, temp._str);
}

String& String::operator=(String str) //现代版使用了swap,交换会使str._str置空，所以传值，用拷贝构造创建一个临时的对象
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
