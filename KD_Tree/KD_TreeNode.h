#ifndef _KDTREENODE_H_
#define _KDTREENODE_H_

enum class  Dimensional {
	X,
	Y
};

template <typename T>
class Node {
private:
	T* deliver;
	Dimensional dime;
	Node<T> *left;
	Node<T> *right;

public:
	Node(T* deliverClass) :
		deliver(deliverClass),
		left(nullptr),
		right(nullptr)
	{}

	~Node()
	{}

	T* GetDeliverClass()
	{
		return deliver;
	}

	virtual void output() = 0;

	virtual int CompareDataX(Node<T> *other) = 0; //compare X |||| -1 this's X < other's X, 1 >, 0 =

	virtual int CompareDataY(Node<T> *other) = 0; //compare Y

	bool operator>=(const Node<T>& other)
	{
		return	(CompareDataX((Node<T>*)&other) == 1 || CompareDataX((Node<T>*)&other) == 0) &&
			(CompareDataY((Node<T>*)&other) == 1 || CompareDataY((Node<T>*)&other) == 0);
	}

	bool operator<=(const Node<T>& other)
	{
		return	(CompareDataX((Node<T>*)&other) == -1 || CompareDataX((Node<T>*)&other) == 0) &&
			(CompareDataY((Node<T>*)&other) == -1 || CompareDataY((Node<T>*)&other) == 0);
	}

	void SetLeft(Node<T> *node)
	{
		left = node;
	}

	Node<T> *GetLeft()
	{
		return left;
	}

	void SetRight(Node<T> *node)
	{
		right = node;
	}

	Node<T> *GetRight()
	{
		return right;
	}
	
	Dimensional GetDime()
	{
		return dime;
	}

	void SetDime(Dimensional dimen)
	{
		dime = dimen;
	}
};
#endif
