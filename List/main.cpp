#include"List.h"

void testList()
{
	List::List<int> L1(7);
	L1.PrintList();
	cout << L1.size() << endl;

	List::List<int> LL;
	LL.PrintList();

	List::List<int> L2(5, 1);
	L2.PrintList();

	int array[] = { 1, 2, 3 };
	List::List<int> L3(array, array + sizeof(array) / sizeof(array[0]));
	L3.PrintList();

	List::List<int> L4(L2);
	L4.PrintList();

	LL = L3;
	LL.PrintList();

}
void test_capacity()
{
	int array[] = { 1, 2, 3, 4 };
	List::List<int> L(array, array + sizeof(array) / sizeof(array[0]));
	cout << L.size() << endl;
	cout << L.empty() << endl;
	L.resize(2);
	L.PrintList();
	L.resize(6);
	L.PrintList();
}
void test_modifiers()
{
	int array[] = { 1, 2, 3 };
	List::List<int> L(array, array + sizeof(array) / sizeof(array[0]));
	L.PrintList();

	L.push_back(4);
	L.PrintList();

	L.pop_back();
	L.PrintList();

	L.push_front(0);
	L.PrintList();

	L.pop_front();
	L.PrintList();

	L.clear();
	L.PrintList();

	List::List<int> LL(5, 1);
	L.Swap(LL);
	L.PrintList();
	LL.PrintList();
}
void test_access()
{
	int array[] = { 1, 2, 3 };
	List::List<int> L(array, array + sizeof(array) / sizeof(array[0]));
	L.PrintList();

	cout << L.front() << endl;
	cout << L.back() << endl;
}
int main()
{
	//testList();
	//test_capacity();
	//test_modifiers();
	//test_access();
	return 0;
}