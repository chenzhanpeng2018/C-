/*
红黑树迭代器


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

	// 让迭代器具有指针类似的操作
	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		//return &_node->_data;
		return &(operator*());
	}

	// 让迭代器可以移动
	Self& operator++()
	{
		Increment();  // 取node的下一个节点
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increment();  // 取node的下一个节点
		return temp;
	}

	Self& operator--()
	{
		Decrement();  // 取node的下一个节点
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		Decrement();  // 取node的下一个节点
		return temp;
	}

	// 迭代器可以比较
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	//让迭代器取下一个节点
	void Increment()
	{
		if (_node->_right)
		{
			// _node的下一个节点就为其右子树中最小的节点--->最左侧的节点
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			//如果右子树不存在，下一个节点再双亲里面找
			Node* parent = _node->_parent;
			while (_node == parent->_right)
			{
				_node = parent;
				parent = _node->_parent;
			}
			//迭代器在根节点，且根节点没有右子树，停下来的时候，_node在head的位置，parent在根节点，此种场景要避免
			if (_node->_right != parent)
			{
				_node = parent;
			}
		}
	}

	//让迭代器取前一个节点
	void Decrement()
	{
		if (_node == _node->_parent->_parent && _node->_color == RED)
		{
			// 迭代器在end() / head的位置
			_node = _node->_right;
		}
		//在左子树中找最右侧的节点
		else if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}		
		}
		//没有左子树
		else
		{
			//在双亲里面找，往上找
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
		//取第一个节点
		Node* & root = GetRoot();

		//按照二叉搜索树规则插入新节点

		//树空
		//如果没节点,插入节点，因为为根节点，所以设置为黑色
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
			root->_parent = head;
			head->_left = root;
			head->_right = root;
			return make_pair(begin(), true);
		}

		//树非空
		//先找位置
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

		//插入新节点
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


		//调整
		//cur节点默认是红色
		//如果cur双亲是黑色，则没有问题
		//如果cur双亲是红色，违反了性质3：没有连在一起的红色节点
		//需要对节点颜色进行调整+旋转
		while (parent != head&&RED == parent->_color)
		{

			Node* grandFather = parent->_parent;
			//parent在左子树
			if (parent == grandFather->_left)
			{
				Node* uncle = grandFather->_right;
				if (uncle&&RED == uncle->_color)
				{
					//叔叔节点存在且为红---场景一
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					cur = grandFather;
					parent = cur->_parent;
				}
				else
				{
					//叔叔节点不存在||叔叔节点存在且为黑
					if (cur == parent->_right)
					{
						//先左旋，把场景三转换成场景二
						RotateLeft(parent);
						swap(parent, cur);
					}
					//场景二
					grandFather->_color = RED;
					parent->_color = BLACK;
					RotateRight(grandFather);
				}
			}
			//parent在右子树
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
		}//while调整结束

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

	//最小值
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
	//最大值
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

	//判断红黑树是否满足所有性质
	bool IsValidRBTree()
	{
		Node* root = GetRoot();
		if (nullptr == root)
		{
			return true;
		}
		if (root->_color != BLACK)
		{
			cout << "违反性质二：根节点必须是黑色--->根节点不是黑色" << endl;
			return false;
		}

		//获取路径中的黑色节点个数,以最左侧的路径为基准
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
				cout << "违反了性质3：没有连在一起的红色节点--->现在有连在一起的红色节点" << endl;
				return false;
			}
		}

		//root是叶子节点，说明已经找到了一条路径
		if (nullptr == root->_left&&nullptr == root->_right)
		{
			if (pathCount != BlackCount)
			{
				cout << "违反了性质4：每条路径中黑色节点的个数相等-->现在不相等" << endl;
				return false;
			}
		}
		return _IsValidRBTree(root->_left, BlackCount, pathCount) &&
			_IsValidRBTree(root->_right, BlackCount, pathCount);
	}
	//中序遍历
	void _InOrder(Node* root)
	{
		if (root)
		{
			_InOrder(root->_left);
			cout << root->_data << " ";
			_InOrder(root->_right);
		}
	}

	//获取第一个节点
	Node* & GetRoot()
	{
		return head->_parent;
	}

	//parent右子树高，左单旋
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
		//旋转前是子树
		if (head != pparent)
		{
			//是子树，是左子树
			if (parent == pparent->_left)
			{
				pparent->_left = subR;
			}
			else
			{
				pparent->_right = subR;
			}
		}
		//是根节点
		else
		{
			head->_parent = subR;
		}
	}

	//右单旋
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
		//旋转前是子树
		if (head != pparent)
		{
			//是子树，是左子树
			if (parent == pparent->_left)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
		}
		//是根节点
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