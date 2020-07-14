/*
  �����
    ����������+��ɫ+Լ�����·���ڵ�������ᳬ�����·���Ľڵ����������
    
      ����+����
	  Ĭ�ϲ�����ɫΪ��ɫ����ɫ��Ӱ������4��
      1.˫��Ϊ�죬���������Ϊ��---->����ɫ������������
      2.˫��Ϊ�죬���岻����||������Ϊ��---->��ת+����ɫ+��ת
	    IsValidRBTree()---->�жϺ�����Ƿ���������

  ����1:ÿ���ڵ㲻�Ǻ�ɫ���Ǻ�ɫ
  ����2:���ڵ��Ǻ�ɫ
  ����3:���һ���ڵ��Ǻ�ɫ�ģ��������������ӵĽڵ��Ǻ�ɫ������������һ��ĺ�ɫ�ڵ㣩
  ����4:ÿ��·���к�ɫ�ڵ��������ͬ
  ����5:�սڵ���ɫ�Ǻ�ɫ
  
  �������ʾ�����Լ������������

  2020.07.05
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

	RBTreeNode(const T& data = T(), Color color=RED)
		:_left(nullptr)
		,_right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _color(color)
	{}
};

template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
	{
		head = new Node;
		head->_left = head;
		head->_right = head;
		head->_parent = nullptr;
	}

	bool Insert(const T& data)
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
			return true;
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
				return false;
		}

		//�����½ڵ�
		cur = new Node(data);
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
		return true;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
		cout << endl;
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
private:

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
			cout << root->_data <<" ";
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

};


void TestRBTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> bt;
	for (auto e : a)
		bt.Insert(e);

	bt.InOrder();
	cout << bt.LeftMost()->_data << endl;
	cout << bt.RightMost()->_data << endl;

	if (bt.IsValidRBTree())
	{
		cout << "bt is rbtree!!!" << endl;
	}
	else
	{
		cout << "bt is not rbtree!!!" << endl;
	}
}

int main()
{
	TestRBTree();
	return 0;
}