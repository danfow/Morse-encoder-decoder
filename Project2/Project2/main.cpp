#include <iostream>

#include "binary_tree.h"
#include <string>
#include <algorithm>
using namespace std;

int main() {
	/*
	BTNode<char> empty('A');
	empty.BuildTree(6);
	BTNode<char>* left = empty.left;
	BTNode<char>* right = empty.right;
	Binary_Tree<BTNode<char>> lleft(*left);
	Binary_Tree<BTNode<char>> rright(*right);
	Binary_Tree<BTNode<char>> tree(empty,lleft,rright);
	cout << tree.get_left_subtree();
	*/

	Binary_Tree<BTNode<char>> tree;
	tree = tree.create_empty_tree();
	cout << tree;
	cout << tree.number_of_nodes();
	cout << endl;
	cout << endl;
	cout << endl;

	string user_message;
	cout << "Enter your desired word to be encoded and decoded" << endl;
	getline(cin, user_message);
	transform(user_message.begin(), user_message.end(), user_message.begin(), ::toupper);

	string coded_message = tree.encode(user_message);
	cout << coded_message << endl;
	tree.decode(coded_message);
	
	
	
	

	
	

	




















	return 0;
}