
#include "Btree.h"
#include <stack>
#include <iostream>

BTree::BTree(int sn) :
	size_node(sn),
	root(nullptr)
{}

BTree::~BTree()
{
	std::stack<Node*> del_nodes = std::stack<Node*>();
	del_nodes.push(root);

	while (!del_nodes.empty())
	{
		Node* cur = del_nodes.top();
		del_nodes.pop();

		for (int i = 0; i < cur->GetNumberSubNode(); i++)
		{
			if (nullptr != cur->sub_nodes[i])
				del_nodes.push(cur->sub_nodes[i]);
		}

		delete cur;
	}

	root = nullptr;
}

void BTree::InsertData(int val)
{
	if (root == nullptr) 
	{
		root = new Node(size_node);
		root->AddData(val);
		return;
	}
	//Start from root
	std::stack<Node*> trail = std::stack<Node*>();
	trail.push(root);

	
	//Try to find a valid position for val
	while (trail.top() != nullptr)
	{
		if (trail.top()->IsFull())
		{
			//always create a empty room for the next value
			if (trail.top() == root)
			{
				Node *newRoot = new Node(size_node);
				newRoot->AddChild(0, root);
				trail.top()->SplitNode(val, newRoot);
				root = newRoot;
				trail.pop();
				trail.push(root);
			}
			else //node sibling full
			{
				int index = trail.top()->GetIndexValue(val);
				Node *fRoot = trail.top();
				trail.pop(); //back to father node
				fRoot->SplitNode(val, trail.top());
			}

		}
		else 
		{
			trail.push(trail.top()->GetNextNode(val));
		}

	}
	
	//right now, the cur node isn't full for sure
	trail.pop(); //remove top because it's nullptr
	trail.top()->AddData(val);
}

bool BTree::SearchData(int val)
{
	Node* cur = root;

	while (nullptr != cur)
	{
		if (cur->CheckExistedValue(val))
			return true;

		cur = cur->GetNextNode(val);
	}

	return false;
}

void BTree::Remove(int val)
{
	Node *p = root;
	//Try to find a valid position for val
	while (p != nullptr)
	{
		int index = p->SearchValue(val);
		if (index != -1)
		{
			if (p->GetChild(0) == nullptr)
			{
				p->RemoveData(index);
			}
			else
			{
				int result = p->RemoveNonLeaf(p, index);
				if (result != -1) {
					p->ChangeValue(index, result);
				}
			}
		}
		else 
		{
			p = p->GetNextNode(val);
		}
	}


}

//void BTree::Print(Node * pRoot)
//{
//	std::stack<Node*> print_nodes = std::stack<Node*>();
//	print_nodes.push(root);
//
//	while (!print_nodes.empty())
//	{
//		Node* cur = print_nodes.top();
//		print_nodes.pop();
//
//		for (int i = 0; i < cur->GetCountValue() + 1; i++)
//		{
//			if (nullptr != cur->GetChild(i))
//				print_nodes.push(cur->GetChild(i));
//		}
//
//		cur->print();
//	}
//}


Node::Node(int sn) :
	size_node(sn),
	values(new int[sn]),
	count_value(0),
	sub_nodes(new Node*[sn + 1])
{
	for (int i = 0; i < sn + 1; i++)
		sub_nodes[i] = nullptr;
}

Node::~Node()
{
	delete[] values;
	values = nullptr;

	delete[] sub_nodes;
	sub_nodes = nullptr;
}



int Node::GetIndexValue(int val)
{
	for (int i = 0; i < count_value; i++)
	{
		if (val < values[i])
			return i;
	}
	return -1;
}

Node * Node::GetNextNode(int val)
{
	int sub_node_index = GetIndexValue(val);

	if (sub_node_index != -1)
		return sub_nodes[sub_node_index];

	return nullptr;
}

bool Node::IsFull()
{
	return size_node == count_value;
}

void Node::SplitNode(int val, Node * parent)
{

	Node *nodeNew = new Node(size_node);

	int u = size_node / 2;
	//copy from node split to new node
	for (int i = 0; i < u; i++) {
		nodeNew->AddData(values[i + u + 1]);
		nodeNew->AddChild(i,sub_nodes[i + u + 1]);
	}
	nodeNew->sub_nodes[size_node/2] = sub_nodes[size_node];
	count_value /= 2;
	int tempVal = values[u];
	parent->AddData(tempVal);
	int index = parent->SearchValue(tempVal);
	parent->AddChild(index + 1, nodeNew);
}

void Node::AddData(int val)
{
	//this node always has empty room for new value
	int index = count_value;

	for (index; index > 0; index--)
	{
		if (val < values[index - 1])
		{
			values[index] = values[index - 1];
		}
		else break;
	}
	values[index] = val;
	count_value++;
}

bool Node::CheckExistedValue(int val)
{
	for (int i = 0; i < count_value; i++)
	{
		if (values[i] == val)
			return true;
	}
	return false;
}

int Node::GetCountValue()
{
	return count_value;
}

int Node::SearchValue(int val)
{
	for (int i = 0; i < count_value; ++i)
	{
		if (values[i] == val) return i;
	}
	return -1;
}

void Node::RemoveData(int index)
{
	for (int i = 0; i < count_value - 1; i++) {
		values[i] = values[i + 1];
		sub_nodes[i] = sub_nodes[i + 1];
	}
	count_value--;
}


int Node::RemoveNonLeaf(Node *p, int index)
{
	if (p->GetChild(index)->GetCountValue() > size_node / 2) //left brach
	{
		RemoveNonLeaf(p->GetChild(index), p->GetCountValue() - 1);
	}
	else
		if (p->GetChild(index + 1)->GetCountValue() > size_node / 2) //right branch
		{
			RemoveNonLeaf(p->GetChild(index), 0);
		}
		else
			if (p->GetChild(0)==nullptr)
			{
				int result = p->GetValue(index);
				p->RemoveData(index);
				return result;
			}
			else //combine 2 branch
			{
				CombineTwoBranch(index, GetChild(index), GetChild(index + 1));
				return -1;
			}

}

void Node::CombineTwoBranch(int index, Node * left, Node *right)
{
	left->AddNode(right);
	delete right;
	RemoveData(index);
	sub_nodes[index] = left;
}

Node * Node::GetChild(int index)
{
	return sub_nodes[index];
}


void Node::AddNode(Node *other)
{
	for (int i = 0; i < other->GetCountValue(); i++) {
		AddData(other->GetValue(i));
		AddChild(count_value + i + 1, other->GetChild(i));
	}
	sub_nodes[count_value] = other->GetChild(other->GetCountValue());
}

void Node::ChangeValue(int index, int val)
{
	values[index] = val;
}

int Node::GetValue(int index)
{
	return values[index];
}

void Node::AddChild(int index, Node *child)
{
	sub_nodes[index] = child;
}

//void Node::print()
//{
//	for (int i = 0; i < count_value; i++)
//	{
//		std::cout << values[i];
//	}
//}

int Node::GetNumberSubNode()
{
	return size_node + 1;
}

