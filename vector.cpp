#include<iostream>
#include<assert.h>
using namespace std;

namespace Vector
{
	template<class T>
	class vector
	{
	public:
		typedef	T* iterator;
		typedef const T* const_iterator;

		iterator begin() { return _start; }
		iterator end() { return _finish; }

		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }

		vector()
			:_start(0), _finish(0), _end_of_storage(0)
		{}

		vector(int n, const T& value=T())
			:_start(0), _finish(0), _end_of_storage(0)
		{
			reserve(n);
			while (n--)
			{
				push_back(value);
			}
		}
			
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		vector(const vector<T>& v)
			:_start(0), _finish(0), _end_of_storage(0)
		{
			reserve(v.capacity());
			iterator it = begin();
			const_iterator vit = v.cbegin();
			while (vit != v.cend())
			{
				*it++ = *vit++;
			}
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}


		
		size_t size()const   
		{
			//return (size_t)(end() - begin());
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		bool empty()const
		{
			return begin() == end();
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldSize = size();
				T* temp = new T[n];
				if (_start)
				{
					//memcpy(temp, _start, sizeof(T)*size());
					//ǳ������ʹ���ã��������ڴ����Ķ����
					//����ڴ�й¶�Լ��Ƿ�����(����string���͵Ķ���)
					for (size_t i = 0; i < oldSize; i++)
					{
						temp[i] = _start[i];
					}
				}
				_start = temp;
				_finish = _start + oldSize;
				_end_of_storage = _start + n;
			}
		}

		//�ı���Ч���ȣ���value���
		void resize(size_t n,const T& value=T())
		{
			//1.��ЧԪ�ر��٣�ֱ����С
			if (n <= size())
			{
				_finish = _start + n;
				return;
			}
			//2.�ռ䲻��������
			if (n > capacity())
			{
				reservr(n);
			}
			//���
			iterator it = _finish;
			_finish = _start + n;
			while (it != _finish)
			{
				*it = value;
				it++;
			}
		}

		T& operator[](size_t pos)
		{
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			return _start[pos];
		}

		T& front() //��һ��Ԫ��
		{
			return *begin();
		}
		T& back() //���һ��Ԫ��
		{
			return *(end() - 1);
		}

		void push_back(const T& x) //��Ԫ�ز�����β��
		{
			insert(end(), x);
		}
		void pop_back()
		{
			erase(--end());
		}

		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_end_of_storage, v._end_of_storage);
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			// �ռ䲻���Ƚ�������
			if (_finish == _end_of_storage)
			{
				size_t Size = size();
				size_t newCapacity = (0 == capacity()) ? 1 : capacity() * 2;
				reserve(newCapacity);
				// ������������ݣ���Ҫ����pos
				pos = _start + Size;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			_finish++;
			return pos;
		}

		//����ɾ��Ԫ�ص���һ������
		iterator erase(iterator pos)
		{
			//
			iterator begin = pos + 1;
			while (begin != _finish)
			{
				*(begin - 1) = *begin;
				begin++;
			}
			_finish--;
			return pos;
		}

	private:
		iterator _start; //��ʾĿǰʹ�ÿռ��ͷ
		iterator _finish;//��ʾĿǰ���ÿռ��β
		iterator _end_of_storage;//��ʾĿǰ���ÿռ��β
	};
}

void Text1()
{
	Vector::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	Vector::vector<int> v2(5,3);
	//Vector::vector<int> v3(v1);
	//Vector::vector<int> v4(v1.begin(),v1.begin()+3);
	
	cout << v1.capacity() << endl;
	cout << v1[2] << endl;
	int a[] = { 1, 2, 3, 4 };
	Vector::vector<int> v(a, a + sizeof(a) / sizeof(a[0]));

	//cout << v1.size() << endl;
	//cout << v1.capacity() << endl;
	//v1.reserve(20);
	//cout << v1.capacity() << endl;
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	Text1();



	system("pause");
	return 0;
}