#include <iostream>
#include <string>
using namespace std;

string output;

class Node {
public:
    int data;
    Node *parent;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
public:
    Node* root;
    int cnt;

    BinaryTree() {
        root = NULL;
        cnt = 0;
    }
    BinaryTree(Node *newNode) {
        root = newNode;
        cnt = 1;
    }

    void insert(Node *newNode, Node *current) {
        cnt++;
        if(newNode->data <= current->data) { // if new node data is smaller than current node data
            if(current->left == NULL) {  // if current node has no left child
                newNode->parent = current;
                current->left = newNode;
            }
            else { // current node has left child
                insert(newNode, current->left);
            }
        }
        else { // if new node data is greater than current node data
            if(current->right == NULL) {  // if current node has no right child
                newNode->parent = current;
                current->right = newNode;
            }
            else { // current node has left child
                insert(newNode, current->right);
            }
        }
    }

    void printInorder(Node *current) {
        if(current) {
            printInorder(current->left);
            output += to_string(current->data) + " ";
            printInorder(current->right);
        }
        else {
            return;
        }      
    }

     void printPreorder(Node *current) {
        if(current) {
            output += to_string(current->data) + " ";
            printPreorder(current->left);
            printPreorder(current->right);
        }
        else {
            return;
        }   

    }
     void printPostorder(Node *current) {
        if(current) {
            printPostorder(current->left);
            printPostorder(current->right);
            output += to_string(current->data) + " ";
        }
        else {
            return;
        }      
    }
};


int main() {
    int data;
    cin >> data;
    Node *newNode = new Node(data);
    BinaryTree tree(newNode);
    while(cin >> data) {
        newNode = new Node(data);
        tree.insert(newNode, tree.root);
    }
    
    output = "";
    tree.printInorder(tree.root);
    for(int i = 0; i < output.length() - 1; i++) {
        cout << output[i];
    }
    cout << endl;

    output = "";
    tree.printPreorder(tree.root);
    for(int i = 0; i < output.length() - 1; i++) {
        cout << output[i];
    }
    cout << endl;

    output = "";
    tree.printPostorder(tree.root);
    for(int i = 0; i < output.length() - 1; i++) {
        cout << output[i];
    }
    cout << endl;

}