#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <string>

using namespace std;

// colors are stored as ints (assignment 6 description, "colors" reference section)
// using #define so the code reads as COLOR_RED instead of a mystery 0
#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2 // only needed by Remove() in part 2

// the node lives in the header (instead of the cpp) so that every file that includes
// RedBlackTree.h can see the type, and the tree class needs it for its private pointers
struct RBTNode {
	int data;
	int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	// the parent pointer makes rotations and the insert fix-up much easier
	// because we can walk back up the tree from a newly inserted node
	RBTNode *parent = nullptr;

	// every new node starts red, the insert fix-up decides if it needs to change
	RBTNode(int newData) : data(newData), color(COLOR_RED) {}
};

class RedBlackTree {
	public:
		RedBlackTree();
		RedBlackTree(int newData);
		RedBlackTree(const RedBlackTree& rbt);

		void Insert(int newData);
		bool Contains(int data) const;
		int GetMin() const;
		int GetMax() const;
		unsigned long long int Size() const { return numItems; };

		string ToInfixString() const { return ToInfixString(root); };
		string ToPrefixString() const { return ToPrefixString(root); };
		string ToPostfixString() const { return ToPostfixString(root); };

		// tests the private methods, called from RedBlackTreeTests.cpp
		void PrivateTests();

	private:
		unsigned long long int numItems = 0;
		RBTNode *root = nullptr;

		// recursive string helpers
		string ToInfixString(RBTNode *n) const;
		string ToPrefixString(RBTNode *n) const;
		string ToPostfixString(RBTNode *n) const;

		// helper that builds the text for one node, like " B30 "
		string NodeToString(RBTNode *n) const;

		// recursive helper for the copy constructor
		RBTNode *CopyTree(RBTNode *n, RBTNode *newParent);

		void RotateLeft(RBTNode *x);
		void RotateRight(RBTNode *x);
		void InsertFixUp(RBTNode *n);

		// returns the black height of a subtree, or -1 if a red black rule is broken (used in PrivateTests)
		int BlackHeight(RBTNode *n) const;
};

#endif
