#ifndef _KDTREE_H_
#define _KDTREE_H_
#include "KD_TreeNode.h"

template <typename T>
class Node;
template <typename T>
class KD_Tree 
{
private:
	Node<T> *root;

	void release(Node<T> *pRoot)
	{
		Node<T> *p = pRoot->GetLeft();
		if (p != nullptr)
		{
			release(Node<T> *pRoot)
		}
	}
public:
	KD_Tree():
	{}
	~KD_Tree()
	{}

	void Insert(Node<T> *node)
	{
		if (root == nullptr)
		{
			root = node;
		}
		else
		{
			Node<T> *p = root;
			if (root->CompareDataX(node)) { //compare x with root
				p = root->GetLeft();
			}
			else
			{
				p = root->GetRight();
			}

			while (p != nullptr)
			{
				if (p->CompareDataY(node)) //true: p's y > node's y
				{
					p = p->GetLeft();
				}
				else
				{
					p = p->GetRight();
				}
			}
			p = node;
		}
			
	}
	void Search()
	{}
	void Remove()
	{}

};
#endif


