﻿/* Michal Kozakiewicz 21859; 27.11.2019 */

#include <iostream>

using namespace std;

class Node {
public:
	Node *left;
	Node *right;
	int value;

	Node(int &value): value(value) {
		this->left = NULL;
		this->right = NULL;
	}

	virtual ~Node() {
		if(this->left != NULL) {
			cout << "ptr: " << this->left << "; dtor Node left;  value: " << this->left->value << endl;
			delete this->left;
		}

		if(this->right != NULL) {
			cout << "ptr: " << this->right << "; dtor Node right; value: " << this->right->value << endl;
			delete this->right;
		}
	}
};

class Tree {
private:
	Node *root;

public:
	Tree() {
		this->root = NULL;
	}

	virtual ~Tree() {
		if(this->root != NULL) {
			cout << "ptr: " << this->root << "; dtor Tree;       value: " << this->root->value << endl;
			delete this->root;
		}
	}

	/* with recursion */
	Tree& add(int value) {
		Node *element = new Node(value);

		if(this->root == NULL) {
			this->root = element;
			return *this;
		}

		class _add {
			Node *root;
			Node *element;
		public:
			_add(Node *root, Node *element): root(root), element(element) {}
			void run() {
				if(this->element->value < this->root->value) {
					if(this->root->left == NULL) {
						this->root->left = this->element;
						return;
					}
					this->root = this->root->left;
					run();
				} else {
					if(this->root->right == NULL) {
						this->root->right = this->element;
						return;
					}
					this->root = this->root->right;
					run();
				}
			}
		} help(this->root, element);

		help.run();
		return *this;
	}

	/* without recursion */
	Tree& add2(int value) {
		Node *element = new Node(value);

		if(this->root == NULL) {
			this->root = element;
			return *this;
		}

		Node *tmp = this->root;
		unsigned char dir = 0; /* Left: 1, Right: 2 */

		if(element->value < tmp->value) {
			dir = 1;
		} else {
			dir = 2;
		}

		while(((dir == 1) ? tmp->left : tmp->right) != NULL) {
			if(dir == 1) {
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}

			if(element->value < tmp->value) {
				dir = 1;
			} else {
				dir = 2;
			}
		}

		if(dir == 1) {
			tmp->left = element;
		} else {
			tmp->right = element;
		}

		return *this;
	}

	void print() const {
		class recursionPrint {
		public:
			static void run(Node *from) {
				if(from != NULL) {
					run(from->left);
					cout << "ptr: " << from << "; value: " << from->value << endl;
					run(from->right);
				}
			}
		};

		recursionPrint::run(this->root);
	}
};

int main() {
	Tree t1;
	t1.add(5).add(7).add(4).add(3).add(12).add(6);
	t1.print();

	return 0;
}