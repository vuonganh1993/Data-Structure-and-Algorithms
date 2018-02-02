#include "KD_Tree.h"

class Employee : public Node<Employee> {
private:

public:
	int age;
	int salary;

	int CompareDataX(Node<Employee> *other) {
		if (age > other->GetDeliverClass()->age)
			return 1;
		if (age < other->GetDeliverClass()->age)
			return -1;

		return 0;
	}

	int CompareDataY(Node<Employee> *other) {
		if (salary > other->GetDeliverClass()->salary)
			return 1;
		if (salary < other->GetDeliverClass()->salary)
			return -1;

		return 0;
	}

};

int main() 
{




	return 0;
}