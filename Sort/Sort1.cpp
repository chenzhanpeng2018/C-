#include<iostream>
#include<vector>
#include<map>

using namespace std;

//��������
void swap(vector<int>& v, int a, int b)
{
	int temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

//1.ð������
//˼�룺�������ұ������Ƚ���������Ԫ�صĴ�С�������һ�����ں��棬ÿ����һ�ˣ����ҵ�һ�����ֵ��������󣬾���n - 1�˱������ɡ�
//���ܣ�ʱ�临�Ӷ�ΪO(n2),�ռ临�Ӷ�O(1),Ԫ�رȽϴ������ʼ״̬�޹أ������Ե��ڲ�������
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

//2.ѡ������
//˼�룺�������飬ÿ�α�������δ����Ĳ����ҵ���СԪ�ص��±꣬�ڴ˴α�����������СԪ�ؽ�����������ʼ��λ�á�
//���ܣ�ʱ�临�Ӷ�ΪO(n2),�ռ临�Ӷ�O(1),�㷨�Ƚϴ������ʼ����״̬�޹أ����������������㷨����
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

//3.��������
//˼�룺����ǰԪ������ǰ�����ź����Ԫ�����ν��бȽϣ��������ں��ʵ�λ��
//      ��ʼʱ�ɴӵڶ���Ԫ�ؿ�ʼ����Ϊ��һ��Ԫ�����ź���
//���ܣ��㷨ʱ�临�Ӷ�ΪO(n2),�ռ临�Ӷ�O(1),�����й�ģ��Сʱ�����ܱȽϺã���Ԫ�رȽϴ������ʼ�������ҳ̶����
//      ���Ÿ��Ӷ�ΪO(n)��
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

//ϣ������
//˼�룺���ò��������˼�룬���ǵ��������������л�����������������ʱ���ܽϸߣ�
//����ȶ����н����߼��ϵķ���Ȼ����������磺�趨��ʼ����Ϊx����0��0 + x��0 + x + x ...Ϊһ�飬
//1��1 + x��1 + x + x ...Ϊ�ڶ��飬����x�飬�ֱ���������Ǹ����������������ӷ��飬ֱ������Ϊ1��
//���ܣ��㷨ʱ�临�Ӷ�ΪO(n1.3) - O(n2)������ȡ�����������С�
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
//��������
//˼�룺��鲢�������ƣ�Ҳʹ�÷���˼�룬ѡ��һ��Ԫ��ֵ��һ��ѡ�����һ��Ԫ�أ���������С�ķ�����߲��֣�
//������ķ����ұߣ�Ȼ��������ֱַ������������֪���ݹ�������ؼ���������Ԫ�صķ��࣬��ֻռ��O(1)�Ķ���洢�ռ䡣
//���ܣ�ʱ�临�Ӷ�ΪO(nlgn)����鲢����ͬ�����㷨ռ�ó���������洢���ڴ��ģ��������Ӧ�������ܽϺá�
//��������-ǰ�󽻻���
int PartSort1(vector<int>&v, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = v[end];
	while (begin < end)
	{
		//begin��ǰ�����ң��ұȻ�׼ֵ���Ԫ��
		while (begin < end&&v[begin] <= key)
		{
			begin++;
		}
		//end�Ӻ���ǰ�ң��ұȻ�׼ֵС��Ԫ��
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
	return begin; //��div
}

//��������-�ڿӷ�
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

//��������-ǰ��ָ�뷨
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
	//����ҿ�
	if (left >= right) return;
	int div = PartSort3(v, left, right);
	Quick_Sort(v, left, div);
	Quick_Sort(v, div + 1, right);
}

//�鲢����
//˼�룺ʹ�÷���˼�룬��ԭʼ���з�Ϊ�����ֱַ�����Ȼ��ϲ����ص����ںϲ����̡�
//���ܣ�ʱ�临�Ӷ�ΪO(nlgn)�������ϲ����̻�ʹ�ö���Ĵ洢�ռ䣬ռ���ڴ档
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

//������
//˼�룺ʹ�ö����ݽṹ�������򣬶���һ��������洢�Ķ����������ݸ��ڵ���ӽڵ�Ĵ�С��ϵ��Ϊ���Ѻ���С�ѣ�����ʹ�����ѽ�������
//���ܣ�ʱ�临�Ӷ�ΪO(nlgn)����ʵ��ʹ���У����������������ͨ��ѷ���������
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
//ֻ�ܺ�0���н���
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
	//Bubble_Sort(v);   //ð������
	//Violence_Sort(v); //ѡ������
	//Insert_Sort(v);   //��������
	//Shell_Sort(v);    //ϣ������
	//Quick_Sort(v, 0, v.size()); //��������
	//MergeSort(v); //�鲢����
	//HeapSort(v); //������
	//Sort1(v);     //0����
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
//	printf("%s��%5.3s,%2d\n","Hithink","Hithink",nTest);
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
