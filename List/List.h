#pragma once

#include<iostream>
using namespace std;

namespace List
{

	/////////////////////////////////////
	//�ڵ���Ϣ�ṹ��
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T())
			:_pPre(0), _pNext(0), _val(val)
		{}

		ListNode<T>* _pPre;
		ListNode<T>* _pNext;
		T _val;
	};

	/////////////////////////////////////
	//��װԭ��̬������
	template < class T, class Ref, class Ptr > 
	class ListIterator
	{
		typedef ListNode<T> Node; ///�ڵ�

		typedef ListIterator<T, Ref, Ptr> Self;
	public:
		
		ListIterator(Node* pNode = nullptr)
			: _pNode(pNode)
		{}

		ListIterator(const Self& L)
			: _pNode(L._pNode)
		{}

		T& operator*(){ return _pNode->_val; }
		T* operator->(){ return &(operator*()); }
		
		Self& operator++() //ǰ��++
		{
			_pNode = _pNode->_pNext;
			return *this;
		}
		
		Self operator++(int) //����++
		{
			Self temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}
		
		Self operator--()//ǰ��--
		{
			_pNode = _pNode->_pPre;
			return *this;
		}

		Self& operator--(int)//����--
		{
			Self temp(*this);
			_pNode = _pNode->_pPre;
			return temp;
		}
		bool operator!=(const Self& L){ return _pNode != L._pNode; }
		bool operator==(const Self& L){ return _pNode == L._pNode; }

		Node* _pNode;
	};

	/////////////////////////////////////
	//Listʵ��
	template<class T>
	class List
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;

	public:
		
		//����
		List()
		{
			CreateHead();
		}

		List(int n, const T& value = T())
		{
			CreateHead();
			for (int i = 0; i < n; i++)
			{
				push_back(value);
			}
		}

		template <class Iterator>
		List(Iterator first, Iterator last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first++);
			}	
		}

		List(const List<T>& L)
		{
			CreateHead();
			Node* pCur = L._pHead->_pNext;
			while (pCur != L._pHead)
			{
				push_back(pCur->_val);
				pCur = pCur->_pNext;
			}
		}

		List<T>& operator=(const List<T> L)
		{
			if (this != &L)
			{
				CreateHead();
				Node* ptr = L._pHead->_pNext;
				while (ptr != L._pHead)
				{
					push_back(ptr->_val);
					ptr = ptr->_pNext;
				}
			}
			return *this;
		}
		
		//����
		~List()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		//����������
		iterator begin() { return iterator(_pHead->_pNext); }
		iterator end(){ return iterator(_pHead); }
		const_iterator begin()const{ return const_iterator(_pHead->_pNext); }
		const_iterator end()const{ return const_iterator(_pHead); }
		
		//����
		int size()const
		{
			int count = 0;
			Node* ptr = _pHead->_pNext;
			while (ptr != _pHead)
			{
				count++;
				ptr = ptr->_pNext;
			}
			return count;
		}
		bool empty()const
		{
			return _pHead == _pHead->_pNext;
		}

		void resize(size_t newSize, const T& val = T())
		{
			size_t oldSize = size();
			if (oldSize < newSize)
			{
				for (size_t i = oldSize; i < newSize; i++)
					push_back(val);
			}
			else
				for (size_t i = oldSize; i > newSize; i--)
					pop_back();
		}
		//����ͷβ�ڵ�
		T& front() {return _pHead->_pNext->_val;}
		const T& front()const {return _pHead->_pNext->_val;}
		T& back()  {return _pHead->_pPre->_val;}
		const T& back()const  {return _pHead->_pPre->_val;}

		//����ɾ������
		void push_back(const T& val) { insert(end(), val); }
		void pop_back() { erase(--end()); }
		void push_front(const T& val)  { insert(begin(), val); }
		void pop_front()  { erase(begin()); }
		
		//��posλ��ǰ����ֵΪval�Ľڵ�
		iterator insert(iterator pos, const T& val)
		{
			Node* pNewNode = new Node(val);
			Node* ptr = pos._pNode;
			pNewNode->_pNext = ptr;
			pNewNode->_pPre = ptr->_pPre;
			ptr->_pPre->_pNext = pNewNode;
			ptr->_pPre = pNewNode;
			return iterator(pNewNode);
		}
		
		// ɾ��posλ�õĽڵ㣬���ظýڵ����һ��λ��
		iterator erase(iterator pos)
		{
			Node* ptr = pos._pNode;
			Node* cur = ptr->_pNext;
			ptr->_pPre->_pNext = ptr->_pNext;
			ptr->_pNext->_pPre = ptr->_pPre;
			delete ptr;
			return cur;
		}

		void Swap(List<T>& L)
		{
			swap(_pHead, L._pHead);
		}

		void clear()
		{
			Node* ptr = _pHead->_pNext;
			while (ptr != _pHead)
			{
				_pHead->_pNext = ptr->_pNext;
				delete ptr;
				ptr = _pHead->_pNext;
			}
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}

		void PrintList()
		{
			Node* ptr = _pHead->_pNext;
			while (ptr != _pHead)
			{
				cout << ptr->_val << " ";
				ptr = ptr->_pNext;
			}
			cout << endl;
		}

	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pPre = _pHead;
			_pHead->_pNext = _pHead;
		}
	private:
		Node* _pHead;
	};
}