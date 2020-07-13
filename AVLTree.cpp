/**********************
*  AVL树
*  关于AVL树的定义，插入，旋转，删除
*
*  陈展鹏
*  2020.6.25
***********************/



#include<iostream>
using namespace std;


//AVL树节点的定义
template<class T>
struct AVLTreeNode
{
	//孩子双亲表示法
	AVLTreeNode<T>* _Left;
	AVLTreeNode<T>* _Right;
	AVLTreeNode<T>* _Parent;
	T _data;
	int _bf;//平衡因子(右高度减左高度)

	AVLTreeNode(const T& data = T())
		:_Left(nullptr)
		, _Right(nullptr)
		, _Parent(nullptr)
		, _data(data)
		, _bf(0)
	{}
};


//AVL树的操作
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
		//构建二叉搜索树

		//树为空，直接插入
		if (nullptr == _root)
		{
			_root = new Node(data);
			return true;
		}

		//找插入位置
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

		//插入新节点
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


		//从cur的双亲节点往上开始更新每个节点的平衡因子
		//平衡因子=右高度-左高度
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

			//检测平衡因子是否还满足AVL树的性质
			if (0 == pParent->_bf)
			{
				//中间部分插入，整体高度没变，直接返回
				return true;
			}
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{
				//平衡因子变成1或者-1，证明在叶子节点底下进行的插入。
				//高度增加了，就需要继续向上更新每个节点的平衡因子
				//且1或-1不需要调整
				cur = pParent;
				pParent = cur->_Parent;
			}
			else
			{
				//有_parent的平衡因子变成2或-2了
				//需要进行旋转调整了


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

	//左单旋
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

		//是子树
		if (parent->_Parent)
		{
			//是左子树
			if (parent == parent->_Parent->_Left)
			{
				parent->_Parent->_Left = subR;
				subR->_Parent = parent->_Parent;
			}
			else
			{
				//是右子树
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

	//右单旋
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

		//是子树
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

	//右左双旋
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

	//左右双旋
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