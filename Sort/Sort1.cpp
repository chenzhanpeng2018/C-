#include<iostream>
#include<vector>
#include<map>

using namespace std;

//交换函数
void swap(vector<int>& v, int a, int b)
{
	int temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

//1.冒泡排序
//思想：从左往右遍历，比较相邻两个元素的大小，将大的一个放在后面，每遍历一趟，可找到一个最大值放置在最后，经过n - 1趟遍历即可。
//性能：时间复杂度为O(n2),空间复杂度O(1),元素比较次数与初始状态无关，性能略低于插入排序。
void Bubble_Sort(vector<int>& v)
{
	int flag = 0;
	int len = v.size();
	for (int i = 0; i < len - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < len - i - 1; j++)
		{
			if (v[j]>v[j + 1])
			{
				swap(v, j, j + 1);
				flag = 1;
			}
		}
		if (!flag)
		{
			break;
		}
	}
	return ;
}

//2.选择排序
//思想：遍历数组，每次遍历都在未排序的部分找到最小元素的下标，在此次遍历结束后将最小元素交换到遍历开始的位置。
//性能：时间复杂度为O(n2),空间复杂度O(1),算法比较次数与初始序列状态无关，性能在所有排序算法中最差。
void Violence_Sort(vector<int>& v)
{
	int len = v.size();

	for (int i = 0; i < len - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (v[j] < v[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(v, i, min);
		}
	}
	return ;
}

//3.插入排序
//思想：将当前元素与它前面已排好序的元素依次进行比较，最后放置在合适的位置
//      初始时可从第二个元素开始，认为第一个元素已排好序。
//性能：算法时间复杂度为O(n2),空间复杂度O(1),在序列规模较小时，性能比较好，且元素比较次数与初始序列杂乱程度相关
//      最优复杂度为O(n)。
void Insert_Sort(vector<int>& v)
{
	int len = v.size();
	for (int i = 1; i < len; i++)
	{
		int key = v[i];
		int j = i - 1;
		while (j >= 0 && v[j] > key)
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = key;
	}
	return ;
}

//希尔排序
//思想：利用插入排序的思想，考虑到插入排序在序列基本有序且数量较少时性能较高，
//因此先对序列进行逻辑上的分组然后插入排序，如：设定初始增量为x，则0，0 + x，0 + x + x ...为一组，
//1，1 + x，1 + x + x ...为第二组，共有x组，分别进行排序。那个随后减少增量，增加分组，直到增量为1。
//性能：算法时间复杂度为O(n1.3) - O(n2)，性能取决于增量序列。
void Shell_Sort(vector<int>& v)
{
	int len = v.size();
	int flag = len / 2;
	for (flag; flag > 0; flag /= 2)
	{
		for (int i = flag; i < len; i++)
		{
			int key = v[i];
			int j = i - flag;
			while (j >= 0 && v[j] > key)
			{
				v[j + flag] = v[j];
				j -= flag;
			}
			v[j + flag] = key;
		}
	}
	return ;
}
//快速排序
//思想：与归并排序类似，也使用分治思想，选择一个元素值（一般选择最后一个元素），将比它小的放在左边部分，
//比它大的放在右边，然后对两部分分别进行上述操作知道递归结束，关键步骤在于元素的分类，且只占用O(1)的额外存储空间。
//性能：时间复杂度为O(nlgn)，与归并排序不同，该算法占用常数级额外存储，在大规模序列排序应用中性能较好。
//快速排序-前后交换法
int PartSort1(vector<int>&v, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = v[end];
	while (begin < end)
	{
		//begin从前往后找，找比基准值大的元素
		while (begin < end&&v[begin] <= key)
		{
			begin++;
		}
		//end从后往前找，找比基准值小的元素
		while (begin < end&&v[end] >= key)
		{
			end--;
		}
		if (begin < end)
		{
			swap(v, begin, end);
		}
	}
	if (begin != right - 1)
	{
		swap(v, begin, right - 1);
	}
	return begin; //新div
}

//快速排序-挖坑法
int PartSort2(vector<int>&v, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = v[begin];

	while (begin < end)
	{
		while (begin < end&&v[end] >= key)
		{
			end--;
		}
		if (begin < end)
		{
			v[begin] = v[end];
			begin++;
		}

		while (begin < end&&v[begin] <= key)
		{
			begin++;
		}
		if (begin < end)
		{
			v[end] = v[begin];
			end--;
		}
	}
	v[begin] = key;

	return begin;
}

//快速排序-前后指针法
int PartSort3(vector<int>&v, int left, int right)
{
	int cur = 0;
	int prev = cur - 1;
	int key=v[right-1];
	while (cur < right)
	{
		if (v[cur] < key&&++prev != cur)
		{
			swap(v, prev, cur);
		}
		cur++;
	}
	swap(v, ++prev, right - 1);
	return prev;
}

void Quick_Sort(vector<int>& v,int left,int right)
{
	//左闭右开
	if (left >= right) return;
	int div = PartSort3(v, left, right);
	Quick_Sort(v, left, div);
	Quick_Sort(v, div + 1, right);
}

//归并排序
//思想：使用分治思想，将原始序列分为两部分分别排序，然后合并，重点在于合并过程。
//性能：时间复杂度为O(nlgn)，不过合并过程会使用额外的存储空间，占用内存。
void MergeData(vector<int>&v, int left, int mid, int right, vector<int>&temp)
{
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;

	while (begin1 < end1&&begin2 < end2)
	{
		if (v[begin1] <= v[begin2])
		{
			temp[index++] = v[begin1++];
		}
		else
			temp[index++] = v[begin2++];
	}
	while (begin1<end1) temp[index++] = v[begin1++];
	while (begin2<end2) temp[index++] = v[begin2++];
}

void _MergeSort(vector<int>&v, int left, int right, vector<int>&temp)
{
	if (right - left > 1)
	{
		int mid = left + ((right - left)>>1);
		_MergeSort(v, left, mid, temp);
		_MergeSort(v, mid, right, temp);
		MergeData(v, left, mid, right, temp);
		for (int i = 0; i < (right-left); i++)
		{
			v[left + i] = temp[left + i];
		}
	}
}

void MergeSort(vector<int>& v)
{
	int len = v.size();
	vector<int>temp(len);
	_MergeSort(v, 0, len, temp);
}

//堆排序
//思想：使用堆数据结构进行排序，堆是一种用数组存储的二叉树，根据父节点和子节点的大小关系分为最大堆和最小堆，这里使用最大堆进行排序。
//性能：时间复杂度为O(nlgn)，在实际使用中，堆排序的排序性能通常逊与快速排序
void AdjustDown(vector<int>& v,int len,int parent)
{
	//int len = v.size();
	int child = parent * 2 + 1;
	while (child < len)
	{
		if (child + 1 < len&&v[child + 1] < v[child])
		{
			child++;
		}
		if (v[child] < v[parent])
		{
			swap(v, child, parent);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}
void HeapSort(vector<int>&v)
{
	int len = v.size();
	for (int root = (len - 2) >> 1; root >= 0; root--)
	{
		AdjustDown(v, len,root);
	}
	int end = len - 1;
	while (end)
	{
		swap(v, 0, end);
		AdjustDown(v,end, 0);
		end--;
	}
}
//只能和0进行交换
void my_swap(vector<int>&v, int num)
{
	int len = v.size();
	int index;
	for (int i = 0; i < len; i++)
	{
		if (v[i] == 0) index = i;
	}
	swap(v, index, num);
}
void Sort1(vector<int>& v)
{
	int len = v.size();
	int num;
	for (int i = 0; i < len; i++)
	{
		if (v[i] == i) continue;
		num = i;
		my_swap(v, i);
		for (int j = 0; j < len; j++)
		{
			if (v[j]==num) 
				swap(v,num, j);
		}
	}
}
void Printf(const vector<int> v)
{
	for (auto ch : v)
	{
		cout << ch << " ";
	}
	cout << endl;
}

void Test1()
{
	vector<int> v{ 1, 4, 8, 5, 3, 9, 0, 2, 7, 6 };
	//Bubble_Sort(v);   //冒泡排序
	//Violence_Sort(v); //选择排序
	//Insert_Sort(v);   //插入排序
	//Shell_Sort(v);    //希尔排序
	//Quick_Sort(v, 0, v.size()); //快速排序
	//MergeSort(v); //归并排序
	//HeapSort(v); //堆排序
	//Sort1(v);     //0排序
	Printf(v);
}

int main()
{
	Test1();
	system("pause");
	return 0;
}






//bool matchNames(string alias, string names)
//{
//	int len = alias.size();
//	map < string, char > m;
//	int left = 0;
//	for (int i = 0; i < len - 1; i++)
//	{
//		int right = names.find(" ", left);
//		string temp = names.substr(left, right - left);
//		left = right + 1;
//		if (m.find(temp) == m.end())
//		{
//			m[temp] = alias[i];
//		}
//		else
//		{
//			if (m[temp] != alias[i])
//			{
//				return 0;
//			}
//		}
//	}
//	string temp = names.substr(left);
//	if (m.find(temp) == m.end())
//	{
//		m[temp] = alias[len - 1];
//	}
//	else
//	{
//		if (m[temp] != alias[len - 1])
//		{
//			return 0;
//		}
//	}
//	return 1;
//}
//int main()
//{
//	//Test1();
//	string s1 = "abbac";
//	string s2 = "sd1 sd2 sd2 sd1 sd3";
//	if (matchNames(s1, s2)) 
//		cout << 1 << endl;
//	else cout << 2 << endl;
//	system("pause");
//	return 0;
//}




//int main(void)
//{
//	int nTest = 1234;
//	printf("%s，%5.3s,%2d\n","Hithink","Hithink",nTest);
//	system("pause");
//	return 0;
//}

//int num(int n)
//{
//	if (n / 10 == 0) return n;
//	int count = 0;
//	while (n)
//	{
//		count += n % 10;
//		n /= 10;
//	}
//	return num(count);
//}
//int main()
//{
//	cout << num(38) << endl;
//	system("pause");
//	return 0;
//}
