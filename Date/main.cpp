#include"Date.h"
#include<Windows.h>

void Test()
{
	Date d(2020, 5, 15);

	cout<<"d : " << d << endl<<endl;

	cout <<"d+77 : "<< d + 77 << endl;
	cout <<"d : "<< d << endl << endl;


	cout <<"(d+=77) : "<< (d+=77) << endl;
	cout << "d : " << d << endl << endl;

	cout << "d-77 : " << d - 77 << endl;
	cout << "d : " << d << endl << endl;


	cout << "(d-=77) : " << (d -= 77) << endl;
	cout << "d : " << d << endl << endl;

	cout << "d++ : " << d++ << endl;
	cout << "d : " << d << endl << endl;

	cout << "++d : " << ++d << endl;
	cout << "d : " << d << endl << endl;

	cout << "d-- : " << d-- << endl;
	cout << "d : " << d << endl << endl;

	cout << "--d : " << --d << endl;
	cout << "d : " << d << endl << endl;

	Date d2(2020, 5, 15);
	Date d3(2020, 8, 1);
	cout << "d2-d3 : " << (d2 - d3) << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}
