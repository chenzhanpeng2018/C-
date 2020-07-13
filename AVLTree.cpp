/**********************
*  AVL��
*  ����AVL���Ķ��壬���룬��ת��ɾ��
*
*  ��չ��
*  2020.6.25
***********************/



#include<iostream>
using namespace std;


//AVL���ڵ�Ķ���
template<class T>
struct AVLTreeNode
{
	//����˫�ױ�ʾ��
	AVLTreeNode<T>* _Left;
	AVLTreeNode<T>* _Right;
	AVLTreeNode<T>* _Parent;
	T _data;
	int _bf;//ƽ������(�Ҹ߶ȼ���߶�)

	AVLTreeNode(const T& data = T())
		:_Left(nullptr)
		, _Right(nullptr)
		, _Parent(nullptr)
		, _data(data)
		, _bf(0)
	{}
};


//AVL���Ĳ���
template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}

	bool Insert(const T& data)
	{
		//��������������

		//��Ϊ�գ�ֱ�Ӳ���
		if (nullptr == _root)
		{
			_root = new Node(data);
			return true;
		}

		//�Ҳ���λ��
		Node* cur = _root;
		Node* pParent = nullptr;
		while (cur)
		{
			pParent = cur;
			if (data < cur->_data)
			{
				cur = cur->_Left;
			}
			else if (data > cur->_data)
			{
				cur = cur->_Right;
			}
			else
				return false;
		}

		//�����½ڵ�
		cur = new Node(data);
		if (data < pParent->_data)
		{
			pParent->_Left = cur;
		}
		else
		{
			pParent->_Right = cur;
		}
		cur->_Parent = pParent;


		//��cur��˫�׽ڵ����Ͽ�ʼ����ÿ���ڵ��ƽ������
		//ƽ������=�Ҹ߶�-��߶�
		while (pParent)
		{
			if (cur == pParent->_Left)
			{
				pParent->_bf--;
			}
			else
			{
				pParent->_bf++;
			}

			//���ƽ�������Ƿ�����AVL��������
			if (0 == pParent->_bf)
			{
				//�м䲿�ֲ��룬����߶�û�䣬ֱ�ӷ���
				return true;
			}
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				//ƽ�����ӱ��1����-1��֤����Ҷ�ӽڵ���½��еĲ��롣
				//�߶������ˣ�����Ҫ�������ϸ���ÿ���ڵ��ƽ������
				//��1��-1����Ҫ����
				cur = pParent;
				pParent = cur->_Parent;
			}
			else
			{
				//��_parent��ƽ�����ӱ��2��-2��
				//��Ҫ������ת������


				if (2 == pParent->_bf)
				{

					if (1 == cur->_bf)
					{
						RotateLeft(pParent);
					}
					else
					{
						RotateRL(pParent);
					}
				}
				else
				{

					if (-1 == cur->_bf)
					{
						RotateRight(pParent);
					}
					else
					{
						RotateLR(pParent);
					}
				}

				break;
			}
		}

		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if (root)
		{
			_InOrder(root->_Left);
			cout << root->_data << " ";
			_InOrder(root->_Right);
		}
	}

private:

	//����
	void RotateLeft(Node* parent)
	{
		Node* subR = parent->_Right;
		Node* subRL = subR->_Left;

		parent->_Right = subRL;
		if (subRL)
		{
			subRL->_Parent = parent;
		}
		subR->_Left = parent;

		//������
		if (parent->_Parent)
		{
			//��������
			if (parent == parent->_Parent->_Left)
			{
				parent->_Parent->_Left = subR;
				subR->_Parent = parent->_Parent;
			}
			else
			{
				//��������
				parent->_Parent->_Right = subR;
				subR->_Parent = parent->_Parent;
			}
		}
		else
		{
			_root = subR;
			subR->_Parent = nullptr;
		}
		parent->_Parent = subR;

		parent->_bf = 0;
		subR->_bf = 0;
	}

	//�ҵ���
	void RotateRight(Node* parent)
	{
		Node* subL = parent->_Left;
		Node* subLR = subL->_Right;

		parent->_Left = subLR;
		if (subLR)
		{
			subLR->_Parent = parent;
		}
		subL->_Right = parent;

		//������
		if (parent->_Parent)
		{
			if (parent->_Parent->_Left == parent)
			{
				parent->_Parent->_Left = subL;
				subL->_Parent = parent->_Parent;
			}
			else
			{
				parent->_Parent->_Right = subL;
				subL->_Parent = parent->_Parent;
			}
		}
		else
		{
			_root = subL;
			subL->_Parent = nullptr;
		}
		parent->_Parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;
	}

	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_Right;
		Node* subRL = subR->_Left;

		int bf = subRL->_bf;
		RotateRight(parent->_Right);
		RotateLeft(parent);

		if (1 == bf)
		{
			parent->_bf = -1;
		}
		else if (-1 == bf)
		{
			subR->_bf = 1;
		}
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_Left;
		Node* subLR = subL->_Right;

		int bf = subLR->_bf;
		RotateLeft(parent->_Left);
		RotateRight(parent);

		if (1 == bf)
		{
			subL->_bf = -1;
		}
		else if (-1 == bf)
		{
			parent->_bf = 1;
		}
	}

private:
	Node* _root;
};


void Test()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };

	AVLTree<int> t;

	for (auto e : array)
		t.Insert(e);

	t.InOrder();
}

int main()
{
	Test();
	system("pause");
	return 0;
}