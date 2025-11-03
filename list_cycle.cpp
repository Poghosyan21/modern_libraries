#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int d) : data(d), next(nullptr) {}
};

bool hasLoop(Node* head) {
	Node* slow = head;
	Node* fast = head;

	while (fast && fast->next) {

		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast)
			return true;
	}
  return false;
}

int main() {
	Node* a = new Node(1);
	a->next = new Node(2);
	a->next->next = new Node(3);
	a->next->next->next = a;

	Node* b = new Node(10);
	b->next = new Node(20);
	b->next->next = new Node(30);

	cout << (hasLoop(a) ? "List 1 has a loop" : "List 1 has no loop") << endl;
	cout << (hasLoop(b) ? "List 2 has a loop" : "List 2 has no loop") << endl;

	return 0;
}
