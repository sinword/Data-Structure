#include <iostream>
#include <string>
using namespace std;

bool state; // 0 = input, 1 = delete
int rotatingTime = 0;
string rotatingLog = "";
string output = "";


class Node
{
	friend class AVL;
public:
	Node() :value(0), left_node(NULL), right_node(NULL), BF(0), height(0)
	{

		left_node = NULL;
		right_node = NULL;
		value = 0;
	}
	Node(int a) :value(a), left_node(NULL), right_node(NULL), BF(0), height(0)
	{

	};
	Node(int a, Node* L, Node* R) :value(a), left_node(L), right_node(R), BF(0), height(0)
	{

	};
	int value, BF, height;
	Node* left_node;
	Node* right_node;

private:
	//int getheigh();
	void set_heigh();
	void updateBF();
};
void Node::set_heigh()
{
	if (this == NULL)
	{
		return;
	}
	int lvalue, rvalue;
	if (this->left_node != NULL)
		lvalue = this->left_node->height;
	else
		lvalue = -1;
	if (this->right_node != NULL)
		rvalue = this->right_node->height;
	else
		rvalue = -1;
	if (lvalue > rvalue)
		this->height = lvalue + 1;
	else
		this->height = rvalue + 1;
	//this->height = max((this->left_node != NULL)? this->left_node->getheigh() :-1 , (this->right_node != NULL) ? this->right_node->getheigh() : -1)+1;
	//return this->height;
}
void Node::updateBF()
{
	this->BF = ((this->left_node != NULL) ? this->left_node->height : -1) - ((this->right_node != NULL) ? this->right_node->height : -1);
	if (this->left_node != NULL)
	{
		this->left_node->updateBF();
	}
	if (this->right_node != NULL)
	{
		this->right_node->updateBF();
	}
}
class AVL
{
public:
	AVL();
	~AVL();



	void insert(Node*& a, int number);
	Node* dele(Node* a, int number);

	void rebalance(Node* a);
	//void update_heigh(Node* a);
	//void update_BF();
	Node* root;
	void print(Node* root, int mode);
	void R0(Node* a, Node* b);
	void R1(Node* a, Node* b);
	void R_1(Node* a, Node* b);
	int height(Node* temp)
	{
		int h = -1;
		if (temp != NULL)
		{
			int l_height = (temp->left_node != NULL) ? temp->left_node->height : -1;
			int r_height = (temp->right_node != NULL) ? temp->right_node->height : -1;
			int max_height = std::max(l_height, r_height);
			temp->BF = l_height - r_height;
			h = max_height + 1;
			temp->height = h;
		}
		return h;
	}
private:
	void left_rotation(Node* A, Node* B);
	void right_rotation(Node* A, Node* B);
};
AVL::AVL() :root(NULL)
{
}

AVL::~AVL()
{
}

void AVL::rebalance(Node* a)
{

	Node* b;
	if (a == NULL)
	{
		return;
	}
	height(a);
	if (a->BF > 1)
	{
		b = a->left_node;
	}
	else if (a->BF < -1)
	{
		b = a->right_node;
	}
	else
	{
		return;
	}
	switch (b->BF)
	{
		case 0:
			R0(a, b);
			break;
		case 1:
			R1(a, b);
			break;
		case -1:
			R_1(a, b);
			break;
		default:
			break;
	}

}
void AVL::print(Node* root, int mode)
{
	switch (mode)
	{
	case 1:
		if (root == NULL)
		{
			return;
		}
		cout << root->value << " ";
		print(root->left_node, mode);
		cout << " ";
		print(root->right_node, mode);
		cout << " ";
		break;

	case 2:// ok
		if (root == NULL)
		{
			return;
		}
		print(root->left_node, mode);
		output += to_string(root->value) + " ";
		print(root->right_node, mode);
		break;

	case 3:
		if (root == NULL)
		{
			return;
		}
		cout << "(";
		print(root->left_node, mode);
		cout << ")(";
		print(root->right_node, mode);
		cout << ')' << root->value;
		break;
	default:
		break;
	}
	return;
}
void AVL::R0(Node* a, Node* b)
{
	rotatingTime++;
	if (state) {
		rotatingLog += ",R0";
	}
	if (a == this->root)
	{
		//this->root = b;
	}
	if (a->BF > 1)//LL
	{
		if (!state) {
			rotatingLog += ",LL";
		}
		right_rotation(a, b);
	}
	else//RR
	{
		if (!state) {
			rotatingLog += ",RR";
		}
		left_rotation(a, b);
	}

}
void AVL::R1(Node* a, Node* b)
{
	rotatingTime++;
	if (state) {
		rotatingLog += ",R1";
	}
	if (a->BF > 1)//LL
	{	
		if (!state) {
			rotatingLog += ",LL";
		}
		right_rotation(a, b);
	}
	else//RL
	{
		if (!state) {
			rotatingLog += ",RL";
		}
		Node* c = b->left_node;
		right_rotation(b, c);
		left_rotation(a, b);
	}
}
void AVL::R_1(Node* a, Node* b)
{
	rotatingTime++;
	if (state) {
		rotatingLog += ",R-1";
	}
	if (a->BF > 1)//LR
	{
		if (!state) {
			rotatingLog += ",LR";
		}
		Node* c = b->right_node;
		left_rotation(b, c);
		right_rotation(a, b);
	}
	else//RR
	{
		if (!state) {
			rotatingLog += ",RR";
		}
		left_rotation(a, b);
	}
}
void AVL::left_rotation(Node* A, Node* B)
{
	int temp = A->value;
	A->value = B->value;
	B->value = temp;
	A->right_node = B->right_node;
	B->right_node = B->left_node;
	B->left_node = A->left_node;
	A->left_node = B;
	height(B);
	height(A);
	return;
}
void AVL::right_rotation(Node* A, Node* B)
{
	int temp = A->value;
	A->value = B->value;
	B->value = temp;
	A->left_node = B->left_node;
	B->left_node = B->right_node;
	B->right_node = A->right_node;
	A->right_node = B;
	height(B);
	height(A);
	return;
}
void AVL::insert(Node*& a, int number)
{
	if (a == NULL)
	{
		a = new Node(number);
	}
	else
	{
		if (number <= a->value)
		{
			insert(a->left_node, number);
		}
		else
		{
			insert(a->right_node, number);
		}
		//a->height = std::max(height(a->left_node), height(a->right_node)) + 1;
	}
	height(a);
	rebalance(a);
}
Node* AVL::dele(Node* a, int number)
{
	if (a == NULL)
	{
		return NULL;
	}
	if (a->value == number)
	{
		if (a->left_node == NULL && a->right_node == NULL)
		{
			delete a;
			a = NULL;
			return NULL;
		}
		else if (a->left_node == NULL)
		{
			return a->right_node;

		}
		else if (a->right_node == NULL)
		{

			return a->left_node;
		}
		else//two child
		{
			Node* temp = a->left_node;
			while (temp->right_node != NULL)
			{
				temp = temp->right_node;
			}
			a->value = temp->value;
			a->left_node = dele(a->left_node, temp->value);
		}
	}
	else if (number < a->value)
	{
		a->left_node = dele(a->left_node, number);
	}
	else
	{
		a->right_node = dele(a->right_node, number);
	}

	rebalance(a);
	return a;
}
int main()
{
	AVL AVL;
	string input;
	int num = 0;
	cin >> input;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ',') {
			AVL.insert(AVL.root, num);
			num = 0;
		}
		else {
			num = num * 10 + input[i] - '0';
		}
	}
	AVL.insert(AVL.root, num);

	char cmd;
	while (cin >> cmd)
	{
		cin >> num;
		switch (cmd)
		{
		case 'I':
			state = 0;
			AVL.insert(AVL.root, num);
			break;
		case 'D':
			state = 1;
			AVL.root = AVL.dele(AVL.root, num);
			break;
		default:
			break;
		}
	}
	AVL.print(AVL.root, 2);
	for (int i = 0; i < output.length() - 1; i++) {
		cout << output[i];
	}
	cout << endl;
	cout << rotatingTime << endl;
	for (int i = 1; i < rotatingLog.length(); i++) {
		cout << rotatingLog[i];
	}
	return 0;
}