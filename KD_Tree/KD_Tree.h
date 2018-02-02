#ifndef _KDTREE_H_
#define _KDTREE_H_
#include "KD_TreeNode.h"
#include <stack>
template <typename T>
class KD_Tree 
{
private:
	Node<T> *root;

	void release(Node<T> *pRoot)
	{
		if (pRoot != nullptr)
		{
			release(pRoot->GetLeft());
			release(pRoot->GetRight());
			delete pRoot;
		}
	}

private:
	void Search(Node<T> *min, Node<T> *max, Node<T>* pRoot, std::stack<Node<T>*> &stack)
	{

		Node<T>* p = root;
		while (p!= nullptr)
		{
			if (p->CompareDataX(min) == 1 && p->CompareDataX(max) == -1 && p->CompareDataY(min) == 1 && p->CompareDataY(max) == -1)
			{
				stack.push(p);
			}

			if (p->GetDime() == X)
			{
				if (p->CompareDataX(min) == -1)
					Search(min, max, p->GetRight(), stack);
				else
					if (p->CompareDataX(max) == 1)
						Search(min, max, p->GetLeft(), stack)
			}
			else
			{
				if (p->GetDime() == Y)
				{
					if (p->CompareDataY(min) == -1)
						Search(min, max, p->GetRight(), stack);
					else
						if (p->CompareDataY(max) == 1)
							Search(min, max, p->GetLeft(), stack);
				}
			}


		}

	}
public:
	KD_Tree():
		root(nullptr)
	{}
	~KD_Tree()
	{
		release(root);
	}

	void Insert(Node<T> *node)
	{
		if (root == nullptr)
		{
			root = node;
			root->SetDime(X);
		}
		else
		{
			Node<T> *p = root;
			Dimensional preDi;

			while (p != nullptr)
			{
				preDi = p->GetDime();
				if (preDi == X)
				{
					if (p->CompareDataX(node))  //true: p's x > node's x
					{
						p = p->GetLeft();
					}
					else //node's x >= p's X
					{
						p = p->GetRight();
					}
				}
				else
				{
					if (p->CompareDataY(node))  //true: p's y > node's y
					{
						p = p->GetLeft();
					}
					else // p's y < node's y
					{
						p = p->GetRight();
					}
				}
			}
			p = node;
			preDi == X ? Y : X;
			p->SetDime(preDi);
		}
			
	}
	
	void Search(Node<T> *min, Node<T> *max)
	{
		std::stack<Node<T>*> stack;
		Search(min, max, root, stack);


	}

	void Remove()
	{}

};
#endif


