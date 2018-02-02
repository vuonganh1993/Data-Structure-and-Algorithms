#include "KD_Tree.h"

class Employee : public Node<Employee> {
private:

public:
	int age;
	int salary;

	bool CompareDataX(Node<Employee> *other) {
		return age >= other->GetDeliverClass()->age;
	}

	bool CompareDataY(Node<Employee> *other) {
		return salary >= other->GetDeliverClass()->salary;
	}

};

int main() 
{




	return 0;
}