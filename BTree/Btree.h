#ifndef _BTREE_H_
#define _BTREE_H_

#include <vector>


class Node;
class BTree
{
private:
	int size_node;
	
public:

	Node* root;
	BTree(int sn = 3);
	~BTree();

	void InsertData(int val);
	bool SearchData(int val);
	void Remove(int val);

	void Print(Node *pRoot);
};

class Node
{
private:
	int size_node;
	int count_value;
	int* values;
	Node** sub_nodes;
public:
	
	Node(int sn);
	~Node();

	int GetIndexValue(int val);
	Node* GetNextNode(int val);
	bool IsFull();
	void SplitNode(int val, Node* parent);
	void AddData(int val);
	bool CheckExistedValue(int  val);
	int GetCountValue();
	int SearchValue(int val); //return index val, -1 if not math

	void RemoveData(int index);
	int  RemoveNonLeaf(Node *p, int index);
	void CombineTwoBranch(int index, Node *left, Node *right);
	Node *GetChild(int index);
	
	void AddNode(Node *other);
	void ChangeValue(int index, int val);
	int GetValue(int index);

	void AddChild(int index, Node *child);

	void print();
private:
	int GetNumberSubNode();

	friend BTree::~BTree();
};

#endif