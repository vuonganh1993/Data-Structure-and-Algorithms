#ifndef _KDTREENODE_H_
#define _KDTREENODE_H_

template <typename T>
class Node {
private:
	T* deliver;
	int direc;
	Node<T> *left;
	Node<T> *right;

public:
	Node() :
	{}

	~Node()
	{}

	T* GetDeliverClass()
	{
		return deliver;
	}

	virtual bool CompareDataX(Node<T> *other) = 0; //compare x

	virtual bool CompareDataY(Node<T> *other) = 0; //compare x

	void SetLeft(Node<T> *node)
	{
		left = node;
	}
	Node<T> *GetLeft()
	{
		return left;
	}

	Node<T> *GetRight()
	{
		return right;
	}
	void SetRight(Node<T> *node)
	{
		right = node;
	}
};
#endif
