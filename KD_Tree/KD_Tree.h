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
	void search(Node<T> *min, Node<T> *max, Node<T>* pRoot, std::stack<Node<T>*> &stack)
	{
		if (pRoot!= nullptr)
		{
			if (*pRoot >= *min && *pRoot <= *max)
			{
				stack.push(pRoot);
				search(min, max, pRoot->GetLeft(), stack);
				search(min, max, pRoot->GetRight(), stack);
			}
			else
			if (pRoot->GetDime() == Dimensional::X)
			{
				if (pRoot->CompareDataX(max) == 1)
					search(min, max, pRoot->GetLeft(), stack);
				else
				if (pRoot->CompareDataX(min) == -1 || pRoot->CompareDataX(min) == 0)
					search(min, max, pRoot->GetRight(), stack);
			}
			else
			if (pRoot->GetDime() == Dimensional::Y)
			{
				if (pRoot->CompareDataY(max) == 1)
					search(min, max, pRoot->GetLeft(), stack);
				else
				if (pRoot->CompareDataY(min) == -1 || pRoot->CompareDataY(min) == 0)
					search(min, max, pRoot->GetRight(), stack);
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
			root->SetDime(Dimensional::X);
		}
		else
		{
			Node<T> *p = root;
			Node<T> *fp = nullptr;
			
			int direc = 0; //0 right, 1 left

			while (p != nullptr)
			{
				fp = p;
				if ((p->GetDime() == Dimensional::X && p->CompareDataX(node) == 1) || (p->GetDime() == Dimensional::Y && p->CompareDataY(node) == 1))
				{
					p = p->GetLeft();
					direc = 1;
				}
				else {
					p = p->GetRight();
					direc = 0;
				}
			}
			
 			if (fp->GetDime() == Dimensional::X)
				node->SetDime(Dimensional::Y);
			else
				node->SetDime(Dimensional::X);

			if(direc)
				fp->SetLeft(node);
			else
				fp->SetRight(node);			
		}
		
	}
	
	void Search(Node<T> *min, Node<T> *max)
	{
		std::stack<Node<T>*> stack;
		search(min, max, root, stack);

		cout << "\nMin: ";
		min->output();
		cout << "\n\n";

		while (!stack.empty())
		{
			stack.top()->output();
			stack.pop();
		}

		cout << "\n\nMax: ";
		max->output();
	}

	void Remove()
	{}

};
#endif


