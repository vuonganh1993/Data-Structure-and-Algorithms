#include "KD_Tree.h"
#include <iostream>

using namespace std;

class Employee : public Node<Employee> {
private:
	int age;
	int salary; 
public:
	Employee(int _age, int _salary) :
	Node<Employee>::Node(this),
	age(_age),
	salary(_salary)
	{}

	~Employee()
	{}

	int GetAge()
	{
		return age;
	}

	int GetSalary()
	{
		return salary;
	}

	int CompareDataX(Node<Employee> *other) {
		if (age > other->GetDeliverClass()->GetAge())
			return 1;
		if (age < other->GetDeliverClass()->GetAge())
			return -1;

		return 0;
	}

	int CompareDataY(Node<Employee> *other) {
		if (salary > other->GetDeliverClass()->GetSalary())
			return 1;
		if (salary < other->GetDeliverClass()->GetSalary())
			return -1;

		return 0;
	}

	void output()
	{
		cout << "\nAge: " << age;
		cout << "\nSalary: " << salary << endl;
	}
};

int main() 
{

	KD_Tree<Employee> *kdtree = new KD_Tree<Employee>();

	kdtree->Insert(new Employee(22, 1000));
	kdtree->Insert(new Employee(30, 2000));
	kdtree->Insert(new Employee(19, 500));
	kdtree->Insert(new Employee(15, 100));

	kdtree->Search(&Employee(10, 100), &Employee(31, 1000));

	system("pause");
	delete kdtree;
	return 0;
}
