#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include "RedBlackTree.h"

// Credit: insert fix-up cases follow the algorithm from the video lecture
// TODO: add your own timecodes / links here for the sources you actually used

// an empty tree has no root, the instance variable defaults in the header already
// set root to nullptr and numItems to 0
RedBlackTree::RedBlackTree() {
	root = nullptr;
	numItems = 0;
}

// makes a tree that already holds one node, the root must always be black
RedBlackTree::RedBlackTree(int newData) {
	root = new RBTNode(newData);
	root->color = COLOR_BLACK;
	numItems = 1;
}

// deep copy so that changing one tree never changes the other
RedBlackTree::RedBlackTree(const RedBlackTree& rbt) {
	root = CopyTree(rbt.root, nullptr);
	numItems = rbt.numItems;
}

// copies a subtree recursively, keeping the same colors and shape (preorder: node, then children)
RBTNode *RedBlackTree::CopyTree(RBTNode *n, RBTNode *newParent) {
	if (n == nullptr) {
		return nullptr;
	}
	RBTNode *copy = new RBTNode(n->data);
	copy->color = n->color;
	copy->parent = newParent;
	copy->left = CopyTree(n->left, copy);
	copy->right = CopyTree(n->right, copy);
	return copy;
}

// regular binary search tree insert, then fix any red black rules that got broken
void RedBlackTree::Insert(int newData) {
	// the assignment says duplicates must throw
	if (Contains(newData)) {
		throw invalid_argument("Duplicate value not allowed: " + to_string(newData));
	}

	RBTNode *newNode = new RBTNode(newData);

	// walk down the tree, keeping track of the parent so we know where to attach
	RBTNode *parent = nullptr;
	RBTNode *cur = root;
	while (cur != nullptr) {
		parent = cur;
		if (newData < cur->data) {
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}

	newNode->parent = parent;
	if (parent == nullptr) {
		root = newNode; // tree was empty
	} else if (newData < parent->data) {
		parent->left = newNode;
	} else {
		parent->right = newNode;
	}
	numItems++;

	InsertFixUp(newNode);
}

// n is red, so the only rule that can break is "a red node can't have a red parent"
// (or the root being red, which is handled at the very end)
void RedBlackTree::InsertFixUp(RBTNode *n) {
	// a red parent is never the root (root is black), so a grandparent always exists in this loop
	while (n != root && n->parent->color == COLOR_RED) {
		RBTNode *p = n->parent;
		RBTNode *g = p->parent;

		if (p == g->left) {
			RBTNode *uncle = g->right;
			if (uncle != nullptr && uncle->color == COLOR_RED) {
				// red uncle: just recolor and push the problem up two levels
				p->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				g->color = COLOR_RED;
				n = g;
			} else {
				// black (or null) uncle: rotate
				if (n == p->right) {
					// left-right case, rotate it into a left-left case first
					n = p;
					RotateLeft(n);
					p = n->parent;
				}
				// left-left case
				p->color = COLOR_BLACK;
				g->color = COLOR_RED;
				RotateRight(g);
			}
		} else {
			// mirror image of the block above
			RBTNode *uncle = g->left;
			if (uncle != nullptr && uncle->color == COLOR_RED) {
				p->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				g->color = COLOR_RED;
				n = g;
			} else {
				if (n == p->left) {
					// right-left case
					n = p;
					RotateRight(n);
					p = n->parent;
				}
				// right-right case
				p->color = COLOR_BLACK;
				g->color = COLOR_RED;
				RotateLeft(g);
			}
		}
	}
	// recoloring may have made the root red, so it is always set back to black
	root->color = COLOR_BLACK;
}

// x's right child y takes x's place and x becomes y's left child
// colors are NOT changed here, the caller does that
void RedBlackTree::RotateLeft(RBTNode *x) {
	RBTNode *y = x->right;

	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

// exact mirror of RotateLeft
void RedBlackTree::RotateRight(RBTNode *x) {
	RBTNode *y = x->left;

	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}

	y->right = x;
	x->parent = y;
}

// uses the binary search tree property to throw away half the tree at each step
bool RedBlackTree::Contains(int data) const {
	RBTNode *cur = root;
	while (cur != nullptr) {
		if (data == cur->data) {
			return true;
		} else if (data < cur->data) {
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}
	return false;
}

// the smallest value is the left-most node
int RedBlackTree::GetMin() const {
	if (root == nullptr) {
		throw invalid_argument("Cannot get the minimum of an empty tree.");
	}
	RBTNode *cur = root;
	while (cur->left != nullptr) {
		cur = cur->left;
	}
	return cur->data;
}

// the largest value is the right-most node
int RedBlackTree::GetMax() const {
	if (root == nullptr) {
		throw invalid_argument("Cannot get the maximum of an empty tree.");
	}
	RBTNode *cur = root;
	while (cur->right != nullptr) {
		cur = cur->right;
	}
	return cur->data;
}

// builds text like " B30 " (spaces on both sides, so neighbors end up with two spaces between them)
string RedBlackTree::NodeToString(RBTNode *n) const {
	string c = "B";
	if (n->color == COLOR_RED) {
		c = "R";
	}
	return " " + c + to_string(n->data) + " ";
}

// left, node, right
string RedBlackTree::ToInfixString(RBTNode *n) const {
	if (n == nullptr) {
		return "";
	}
	return ToInfixString(n->left) + NodeToString(n) + ToInfixString(n->right);
}

// node, left, right
string RedBlackTree::ToPrefixString(RBTNode *n) const {
	if (n == nullptr) {
		return "";
	}
	return NodeToString(n) + ToPrefixString(n->left) + ToPrefixString(n->right);
}

// left, right, node
string RedBlackTree::ToPostfixString(RBTNode *n) const {
	if (n == nullptr) {
		return "";
	}
	return ToPostfixString(n->left) + ToPostfixString(n->right) + NodeToString(n);
}

// null leaves count as black (height 1). Returns -1 if a red node has a red child
// or if two paths have a different number of black nodes
int RedBlackTree::BlackHeight(RBTNode *n) const {
	if (n == nullptr) {
		return 1;
	}
	int lh = BlackHeight(n->left);
	int rh = BlackHeight(n->right);
	if (lh == -1 || rh == -1 || lh != rh) {
		return -1;
	}
	if (n->color == COLOR_RED) {
		if ((n->left != nullptr && n->left->color == COLOR_RED) ||
		    (n->right != nullptr && n->right->color == COLOR_RED)) {
			return -1;
		}
		return lh;
	}
	return lh + 1;
}

// a rotation by itself can break the red black rules, so these tests only check the shape
// and not the validity of the tree
void RedBlackTree::PrivateTests() {
	cout << "Testing Private Methods..." << endl;

	// RotateLeft / RotateRight
	RedBlackTree t;
	t.Insert(10);
	t.Insert(20);
	assert(t.ToPrefixString() == " B10  R20 ");
	t.RotateLeft(t.root);
	assert(t.ToPrefixString() == " R20  B10 ");
	assert(t.root->parent == nullptr);
	assert(t.root->left->parent == t.root);
	t.RotateRight(t.root);
	assert(t.ToPrefixString() == " B10  R20 ");

	// BlackHeight on a hand made tree
	assert(BlackHeight(nullptr) == 1);

	// the tree must stay valid no matter what order the values come in
	vector<int> vals;
	for (int i = 1; i <= 500; i++) {
		vals.push_back(i);
	}
	RedBlackTree ascending;
	for (size_t i = 0; i < vals.size(); i++) {
		ascending.Insert(vals[i]);
	}
	assert(ascending.root->color == COLOR_BLACK);
	assert(ascending.BlackHeight(ascending.root) != -1);

	RedBlackTree descending;
	for (size_t i = vals.size(); i > 0; i--) {
		descending.Insert(vals[i - 1]);
	}
	assert(descending.BlackHeight(descending.root) != -1);

	// fixed seed so the test is the same every run
	mt19937 rng(222);
	shuffle(vals.begin(), vals.end(), rng);
	RedBlackTree shuffled;
	for (size_t i = 0; i < vals.size(); i++) {
		shuffled.Insert(vals[i]);
		assert(shuffled.BlackHeight(shuffled.root) != -1);
	}
	assert(shuffled.Size() == 500);

	// the copy needs its own nodes, not shared ones
	RedBlackTree copy = RedBlackTree(shuffled);
	assert(copy.root != shuffled.root);
	assert(copy.BlackHeight(copy.root) != -1);

	cout << "PASSED!" << endl << endl;
}
