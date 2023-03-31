#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void SWAP(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
	return;
}

void SORT(vector<int>& num) {
	for (int i = 0; i < num.size() - 1; i++) {
		for (int j = i + 1; j < num.size(); j++) {
			if (num[i] > num[j]) {
				SWAP(num[i], num[j]);
			}
		}
	}
}

class Team {
public:
	string name;
	int jumpball;
	vector<int> players;
	vector<int> outfield;

public:
	Team(string color) {
		name = color + " team";
	}

	void join(int id) {
		players.push_back(id);
	}


	bool assign() {
		if (players.size() < 4) {
			return false;
		}
		else {
			for (int i = 1; i <= 3; i++) {
				outfield.push_back(players[players.size() - i]);
			}
			jumpball = players[0];
			SORT(players);
			SORT(outfield);
			return true;
		}
	}

	void printTeam() {
		cout << name << ": ";
		for (int i = 0; i < players.size(); i++) {
			cout << players[i];
			if (i != players.size() - 1) {
				cout << ",";
			}
		}
		cout << "\noutfield: ";
		for (int i = 0; i < outfield.size(); i++) {
			cout << outfield[i];
			if (i != outfield.size() - 1) {
				cout << ",";
			}
		}
		cout << "\njump ball: " << jumpball << "\n";
	}
};

class Node {
public:
	int data;
	char color;
	Node* left, * right, * parent;

public:
	Node(int value) {
		data = value;
		color = 'r'; // defualt color: red
		left = right = parent = NULL;
	}
	Node(int value, char c) {
		data = value;
		color = c;
		left = right = parent = NULL;
	}
	friend class RBTree;
};

class RBTree {
public:
	Node* root;

public:
	RBTree() {
		root = NULL;
	}
	void rbtInsert(int input) {
		Node* newNode = new Node(input);
		if (!root) {
			root = newNode;
			checkRoot();
			return;
		}
		Node* ptr = search(newNode);
		colorChange(ptr);
		rotate(ptr);
		insert(ptr, newNode);
		rotate(newNode);
		checkRoot();
	}

	Node* search(Node* newNode) {
		Node* ptr = root;
		while (ptr) {
			if (newNode->data > ptr->data) {
				if (ptr->right) {
					ptr = ptr->right;
				}
				else {
					return ptr;
				}
			}
			else {
				if (ptr->left) {
					ptr = ptr->left;
				}
				else {
					return ptr;
				}
			}
		}
	}

	void colorChange(Node* ptr) {
		ptr = ptr->parent;
		while (ptr) {
			if (ptr->left && ptr->right) {
				if (ptr->left->color == 'r' && ptr->right->color == 'r' && ptr->color == 'b') {
					ptr->color = 'r';
					ptr->left->color = 'b';
					ptr->right->color = 'b';
					return;
				}
			}
			ptr = ptr->parent;
		}
	}

	void rotate(Node* ptr) {
		Node* parentPtr = NULL;
		Node* gparentPtr = NULL;
		while (ptr) {
			parentPtr = ptr->parent;
			if (!parentPtr) { // if one of both not exist
				return;
			}
			gparentPtr = parentPtr->parent;
			if (!gparentPtr) {
				return;
			}
			else {
				if (ptr->color == 'r' && parentPtr->color == 'r' && gparentPtr->color == 'b') {
					if (gparentPtr->left == parentPtr) {
						// L*
						if (parentPtr->left == ptr) {
							// LL
							Rrotate(root, gparentPtr);
							SWAP(gparentPtr->color, parentPtr->color);
						}
						else {
							// LR
							Lrotate(root, parentPtr);
							Rrotate(root, gparentPtr);
							SWAP(gparentPtr->color, ptr->color);
						}
					}
					else { 
						// R*
						if (parentPtr->right == ptr) {
							// RR
							Lrotate(root, gparentPtr);
							SWAP(gparentPtr->color, parentPtr->color);
						}
						else {
							// RL
							Rrotate(root, parentPtr);
							Lrotate(root, gparentPtr);
							SWAP(gparentPtr->color, ptr->color);
						}
					}
				}
			}
			ptr = ptr->parent;
		}
	}
	void Lrotate(Node*& root, Node*& ptr) {
		Node* ptrRight = ptr->right;
		ptr->right = ptrRight->left;

		if (ptr->right != NULL) {
			ptr->right->parent = ptrRight;
		}
		ptrRight->parent = ptr->parent;

		if (ptr->parent == NULL) {
			root = ptrRight;
		}
		else if (ptr == ptr->parent->left) {
			ptr->parent->left = ptrRight;
		}
		else {
			ptr->parent->right = ptrRight;
		}

		ptrRight->left = ptr;
		ptr->parent = ptrRight;
	}
	void Rrotate(Node*& root, Node*& ptr) {
		Node* prtLeft = ptr->left;
		ptr->left = prtLeft->right;

		if (ptr->left != NULL) {
			ptr->left->parent = ptr;
		}
		prtLeft->parent = ptr->parent;

		if (ptr->parent == NULL) {
			root = prtLeft;
		}
		else if (ptr == ptr->parent->left) {
			ptr->parent->left = prtLeft;
		}
		else {
			ptr->parent->right = prtLeft;
		}

		prtLeft->right = ptr;
		ptr->parent = prtLeft;
	}

	void insert(Node* ptr, Node* newNode) {
		if (newNode->data < ptr->data) {
			ptr->left = newNode;
		}
		else {
			ptr->right = newNode;
		}
		newNode->parent = ptr;
	}

	void checkRoot() {
		root->color = 'b';
	}

	void levelOrder(Node* root, vector <Node*>& result) {
		if (!root) {
			return;
		}

		vector<Node*> queue;
		queue.push_back(root);
		while (!queue.empty()) {
			Node* node = queue.front();
			result.push_back(node);
			queue.erase(queue.begin(), queue.begin() + 1);
			if (node->left) {
				queue.push_back(node->left);
			}
			if (node->right) {
				queue.push_back(node->right);
			}
		}
	}

	void printTreePreorder(Node* node) {
		if (node) {
			cout << node->data;
			if (node->color == 'r') {
				cout << "(RED)\t";
			}
			else {
				cout << "(BLACK)\t";
			}

			if (node->parent) {
				cout << "parent: " << node->parent->data << "\n";
			}
			else {
				cout << "ROOT\n";
			}
			printTreePreorder(node->left);
			printTreePreorder(node->right);
		}
	}

	void printTreeInorder(Node* node) {
		if (node) {
			printTreeInorder(node->left);
			cout << node->data;
			if (node->color == 'r') {
				cout << "(RED)\t";
			}
			else {
				cout << "(BLACk)\t";
			}

			if (node->parent) {
				cout << "parent: " << node->parent->data << "\n";
			}
			else {
				cout << "ROOT\n";
			}
			printTreeInorder(node->right);
		}
	}
};

int main() {
	vector<int> allPlayers;
	RBTree tree;
	int input;
	while (cin >> input) {
		allPlayers.push_back(input);
		tree.rbtInsert(input);
		/*cout << "\nInsert " << input;
		cout << "\nPreorder:\n";
		tree.printTreePreorder(tree.root);
		cout << "\nInorder:\n";
		tree.printTreeInorder(tree.root);*/
	}

	Team redTeam("Red");
	Team blackTeam("Black");
	vector<Node*> result;
	tree.levelOrder(tree.root, result);


	for (int i = 0; i < result.size(); i++) {
		Node* node = result[i];
		if (node->color == 'r') {
			redTeam.join(node->data);
		}
		else {
			blackTeam.join(node->data);
		}
	}
	if (redTeam.assign() && blackTeam.assign()) {
		redTeam.printTeam();
		blackTeam.printTeam();
	}
	else {
		cout << "No game";
	}
}
// 23 25 8 9 12 3 17 28 41 48 37
// 8 18 5 15 17 25 40 80