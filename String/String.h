#pragma once
#include<iostream>
using namespace std;

class String
{
public:
	String(const char* str = "");
	String(const String& str);
	String& operator=(const String& str); //传统版用引用
	//String& operator=(const String str); //现代版使用了swap,交换会使str._str置空，所以传值，用拷贝构造创建一个临时的对象
	~String();


private:
	char* _str;
};

