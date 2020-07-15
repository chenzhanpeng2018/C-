/*
�����������


2020.07.08
*/




#include<iostream>
using namespace std;



enum Color{ RED, BLACK };

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;
	Color _color;

	RBTreeNode(const T& data = T(), Color color = RED)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _color(color)
	{}
};



template<class T>
class RBTreeIterator
{
public:
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;

	RBTreeIterator(Node* node)
		: _node(node)
	{}

	// �õ���������ָ�����ƵĲ���
	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		//return &_node->_data;
		return &(operator*());
	}

	// �õ����������ƶ�
	Self& operator++()
	{
		Increment();  // ȡnode����һ���ڵ�
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increment();  // ȡnode����һ���ڵ�
		return temp;
	}

	Self& operator--()
	{
		Decrement();  // ȡnode����һ���ڵ�
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		Decrement();  // ȡnode����һ���ڵ�
		return temp;
	}

	// ���������ԱȽ�
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	//�õ�����ȡ��һ���ڵ�
	void Increment()
	{
		if (_node->_right)
		{
			// _node����һ���ڵ��Ϊ������������С�Ľڵ�--->�����Ľڵ�
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			//��������������ڣ���һ���ڵ���˫��������
			Node* parent = _node->_parent;
			while (_node == parent->_right)
			{
				_node = parent;
				parent = _node->_parent;
			}
			//�������ڸ��ڵ㣬�Ҹ��ڵ�û����������ͣ������ʱ��_node��head��λ�ã�parent�ڸ��ڵ㣬���ֳ���Ҫ����
			if (_node->_right != parent)
			{
				_node = parent;
			}
		}
	}

	//�õ�����ȡǰһ���ڵ�
	void Decrement()
	{
		if (_node == _node->_parent->_parent && _node->_color == RED)
		{
			// ��������end() / head��λ��
			_node = _node->_right;
		}
		//���������������Ҳ�Ľڵ�
		else if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}		
		}
		//û��������
		else
		{
			//��˫�������ң�������
			Node* parent = _node->_parent;
			while (_node == parent->_left)
			{
				_node = parent;
				parent = _node->_parent;
			}

			_node = parent;
		}
	}
private:
	Node* _node;
};






template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> iterator;
public:
	RBTree()
		:_size(0)
	{
		head = new Node;
		head->_left = head;
		head->_right = head;
		head->_parent = nullptr;
	}
	~RBTree()
	{
		DestroyRBTree(head->_parent);
		delete head;
	}

	iterator begin()
	{
		return iterator(head->_left);
	}
	
	iterator end()
	{
		return iterator(head);
	}

	pair<iterator,bool> Insert(const T& data)
	{
		//ȡ��һ���ڵ�
		Node* & root = GetRoot();

		//���ն�����������������½ڵ�

		//����
		//���û�ڵ�,����ڵ㣬��ΪΪ���ڵ㣬��������Ϊ��ɫ
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
			root->_parent = head;
			head->_left = root;
			head->_right = root;
			return make_pair(begin(), true);
		}

		//���ǿ�
		//����λ��
		Node* cur = root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (data < cur->_data)
			{
				cur = cur->_left;
			}
			else if (data > cur->_data)
			{
				cur = cur->_right;
			}
			else
				return make_pair(iterator(cur),false);
		}

		//�����½ڵ�
		cur = new Node(data);
		Node* newNode = cur;
		if (data < parent->_data)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;


		//����
		//cur�ڵ�Ĭ���Ǻ�ɫ
		//���cur˫���Ǻ�ɫ����û������
		//���cur˫���Ǻ�ɫ��Υ��������3��û������һ��ĺ�ɫ�ڵ�
		//��Ҫ�Խڵ���ɫ���е���+��ת
		while (parent != head&&RED == parent->_color)
		{

			Node* grandFather = parent->_parent;
			//parent��������
			if (parent == grandFather->_left)
			{
				Node* uncle = grandFather->_right;
				if (uncle&&RED == uncle->_color)
				{
					//����ڵ������Ϊ��---����һ
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					cur = grandFather;
					parent = cur->_parent;
				}
				else
				{
					//����ڵ㲻����||����ڵ������Ϊ��
					if (cur == parent->_right)
					{
						//���������ѳ�����ת���ɳ�����
						RotateLeft(parent);
						swap(parent, cur);
					}
					//������
					grandFather->_color = RED;
					parent->_color = BLACK;
					RotateRight(grandFather);
				}
			}
			//parent��������
			else
			{
				Node* uncle = grandFather->_left;
				if (uncle && RED == uncle->_color)
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					cur = grandFather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateRight(parent);
						swap(parent, cur);
					}

					grandFather->_color = RED;
					parent->_color = BLACK;
					RotateLeft(grandFather);
				}
			}
		}//while��������

		root->_color = BLACK;
		head->_left = LeftMost();
		head->_right = RightMost();
		_size++;
		return make_pair(iterator(newNode),true);
	}

	iterator Find(const T& data)
	{
		Node* cur = GetRoot();
		while (cur)
		{
			if (data == cur->_data)
				return iterator(cur);
			else if (data < cur->_data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return end();
	}

	void InOrder()
	{
		_InOrder(GetRoot());
		cout << endl;
	}

	void Clear()
	{
		DestroyRBTree(GetRoot());
		_size = 0;
	}

	//��Сֵ
	Node* LeftMost()
	{
		Node* root = GetRoot();
		if (nullptr == root)
		{
			return head;
		}
		Node* cur = root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}
	//���ֵ
	Node* RightMost()
	{
		Node* root = GetRoot();
		if (nullptr == root)
		{
			return head;
		}
		Node* cur = root;
		while (cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}

	//�жϺ�����Ƿ�������������
	bool IsValidRBTree()
	{
		Node* root = GetRoot();
		if (nullptr == root)
		{
			return true;
		}
		if (root->_color != BLACK)
		{
			cout << "Υ�����ʶ������ڵ�����Ǻ�ɫ--->���ڵ㲻�Ǻ�ɫ" << endl;
			return false;
		}

		//��ȡ·���еĺ�ɫ�ڵ����,��������·��Ϊ��׼
		int BlackCount = 0;
		Node* cur = root;
		while (cur)
		{
			if (BLACK == cur->_color)
			{
				BlackCount++;
			}
			cur = cur->_left;
		}
		int pathCount = 0;
		return _IsValidRBTree(root, BlackCount, pathCount);
	}

	bool Empty()
	{
		return nullptr == head->_parent;
	}

	int Size()
	{
		return _size;
	}
private:

	void DestroyRBTree(Node* &root)
	{
		if (root)
		{
			DestroyRBTree(root->_left);
			DestroyRBTree(root->_right);
			delete root;
			root = nullptr;
		}
	}

	bool _IsValidRBTree(Node* root, int BlackCount, int pathCount)
	{
		if (nullptr == root)
		{
			return true;
		}
		if (BLACK == root->_color)
		{
			pathCount++;
		}

		Node* parent = root->_parent;
		if (parent != head)
		{
			if (RED == root->_color&&parent->_color == RED)
			{
				cout << "Υ��������3��û������һ��ĺ�ɫ�ڵ�--->����������һ��ĺ�ɫ�ڵ�" << endl;
				return false;
			}
		}

		//root��Ҷ�ӽڵ㣬˵���Ѿ��ҵ���һ��·��
		if (nullptr == root->_left&&nullptr == root->_right)
		{
			if (pathCount != BlackCount)
			{
				cout << "Υ��������4��ÿ��·���к�ɫ�ڵ�ĸ������-->���ڲ����" << endl;
				return false;
			}
		}
		return _IsValidRBTree(root->_left, BlackCount, pathCount) &&
			_IsValidRBTree(root->_right, BlackCount, pathCount);
	}
	//�������
	void _InOrder(Node* root)
	{
		if (root)
		{
			_InOrder(root->_left);
			cout << root->_data << " ";
			_InOrder(root->_right);
		}
	}

	//��ȡ��һ���ڵ�
	Node* & GetRoot()
	{
		return head->_parent;
	}

	//parent�������ߣ�����
	void RotateLeft(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;

		Node* pparent = parent->_parent;
		subR->_parent = pparent;
		parent->_parent = subR;
		//��תǰ������
		if (head != pparent)
		{
			//����������������
			if (parent == pparent->_left)
			{
				pparent->_left = subR;
			}
			else
			{
				pparent->_right = subR;
			}
		}
		//�Ǹ��ڵ�
		else
		{
			head->_parent = subR;
		}
	}

	//�ҵ���
	void RotateRight(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;

		Node* pparent = parent->_parent;
		subL->_parent = pparent;
		parent->_parent = subL;
		//��תǰ������
		if (head != pparent)
		{
			//����������������
			if (parent == pparent->_left)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
		}
		//�Ǹ��ڵ�
		else
		{
			head->_parent = subL;
		}
	}

private:
	Node* head;
	int _size;

};


void TestRBTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> bt;
	for (auto e : a)
		bt.Insert(e);

	auto it = bt.begin();
	while (it != bt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

int main()
{
	TestRBTree();
	return 0;
}