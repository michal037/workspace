/* Michal Kozakiewicz; 27.10.2019 */

#include <iostream>

using namespace std;

class Queue;

class Node {
private:
	string value;
	Node *next;

	/* create new Node */
	Node(const string &v, Node * const n): value(v), next(n) {
	}

	/* copy Node */
	Node(const Node &n) {
		this->value = n.value;
		this->next = n.next;
	}

	friend class Queue;
	friend ostream& operator<<(ostream &s, const Queue &q);
};

class Queue {
private:
	Node *tail;
	unsigned int length;

public:
	/* create new Queue */
	Queue() {
		this->tail = NULL;
		this->length = 0;
	}

	/* remove Queue */
	virtual ~Queue() {
		Node *rest;

		while(this->tail != NULL) {
			rest = this->tail->next;
			delete this->tail;
			this->tail = rest;
			this->length--;
		}
	}

	/* put string to Queue */
	Queue& operator<<(const string &s) {
		Node *tmp = new Node(s, this->tail);

		this->tail = tmp;
		this->length++;

		return *this;
	}

	/* get string from Queue */
	const Queue& operator>>(string &s) {
		/* no Nodes in Queue */
		if(this->tail == NULL) {
			s = "<NULL>";

			return *this;
		}

		/* one Node in Queue */
		if(this->tail->next == NULL) {
			s = this->tail->value;

			delete this->tail;
			this->tail = NULL;

			this->length--;

			return *this;
		}

		/* more than one Node in Queue */

		/* move `tmp` to second to last Node */
		Node *tmp = this->tail;
		while(tmp->next->next != NULL) {
			tmp = tmp->next;
		}

		s = tmp->next->value;

		delete tmp->next;
		tmp->next = NULL;

		this->length--;

		return *this;
	}

	unsigned int len() const {
		return this->length;
	}

	friend ostream& operator<<(ostream &s, const Queue &q);
};

ostream& operator<<(ostream &s, const Queue &q) {
	Node *tmp = q.tail;

	s << "len: " << q.len() << "; ";

	while(tmp != NULL) {
		s << "[" << tmp->value << "] ";
		tmp = tmp->next;
	}

	return s;
}

int main() {
	Queue test;

	test << "Michal" << "Kozakiewicz" << "27.10.2019" << "Queue";

	string tmp;
	while(test.len() != 0) {
		cout << "Queue: "<< test << endl;
		test >> tmp;
		cout << "Taken: ["<< tmp << "]" << endl;
	}

	return 0;
}
