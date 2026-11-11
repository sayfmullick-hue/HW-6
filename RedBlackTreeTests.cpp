
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// the mirror images of the cases above
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(60); // Right Right
	assert(rbt->ToPrefixString() == " B45  R30  R60 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(35); // Left Right
	assert(rbt->ToPrefixString() == " B35  R30  R45 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	// red uncle, so it only recolors. All four spots a fourth node can land in
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	assert(rbt->ToPrefixString() == " B30  B15  R10  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B30  B15  R25  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(35);
	assert(rbt->ToPrefixString() == " B30  B15  B45  R35 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(60);
	assert(rbt->ToPrefixString() == " B30  B15  B45  R60 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	// a black uncle, so the fifth node triggers a rotation (left left, then right right)
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(5);
	assert(rbt->ToPrefixString() == " B30  B10  R5  R15  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(60);
	rbt->Insert(70);
	assert(rbt->ToPrefixString() == " B30  B15  B60  R45  R70 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}






void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(rbt->Contains(40)); // the root
	assert(rbt->Contains(12)); // a leaf on the far left
	assert(rbt->Contains(55)); // a leaf on the far right
	assert(!rbt->Contains(13));
	assert(!rbt->Contains(100));
	assert(!rbt->Contains(-5));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}




void TestInsertDuplicate(){
	cout << "Testing Insert Duplicate..." << endl;

	RedBlackTree rbt;
	rbt.Insert(10);
	rbt.Insert(5);
	bool threw = false;
	try {
		rbt.Insert(10);
	} catch (invalid_argument& e) {
		threw = true;
	}
	assert(threw);
	// the failed insert must not change the tree
	assert(rbt.Size() == 2);
	assert(rbt.ToPrefixString() == " B10  R5 ");

	cout << "PASSED!" << endl << endl;
}

void TestSize(){
	cout << "Testing Size..." << endl;

	RedBlackTree rbt;
	assert(rbt.Size() == 0);
	rbt.Insert(3);
	assert(rbt.Size() == 1);
	rbt.Insert(1);
	rbt.Insert(2);
	assert(rbt.Size() == 3);
	assert(RedBlackTree(8).Size() == 1);

	cout << "PASSED!" << endl << endl;
}

void TestLargeTree(){
	cout << "Testing Large Tree..." << endl;

	RedBlackTree rbt;
	for (int i = 1; i <= 1000; i++) {
		rbt.Insert(i);
	}
	assert(rbt.Size() == 1000);
	assert(rbt.GetMin() == 1);
	assert(rbt.GetMax() == 1000);
	for (int i = 1; i <= 1000; i++) {
		assert(rbt.Contains(i));
	}
	assert(!rbt.Contains(0));
	assert(!rbt.Contains(1001));

	cout << "PASSED!" << endl << endl;
}

void TestPrivateTests(){
	RedBlackTree rbt;
	rbt.PrivateTests();
}

void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree rbt;
	// an empty tree has no min or max so it should throw
	bool threw = false;
	try {
		rbt.GetMin();
	} catch (invalid_argument& e) {
		threw = true;
	}
	assert(threw);
	threw = false;
	try {
		rbt.GetMax();
	} catch (invalid_argument& e) {
		threw = true;
	}
	assert(threw);

	// one node is both the min and the max
	rbt.Insert(40);
	assert(rbt.GetMin() == 40);
	assert(rbt.GetMax() == 40);

	rbt.Insert(22);
	rbt.Insert(15);
	rbt.Insert(31);
	rbt.Insert(55);
	rbt.Insert(12);
	assert(rbt.GetMin() == 12);
	assert(rbt.GetMax() == 55);

	// negatives and new extremes
	rbt.Insert(-7);
	rbt.Insert(1000);
	assert(rbt.GetMin() == -7);
	assert(rbt.GetMax() == 1000);

	cout << "PASSED!" << endl << endl;
}





int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestInsertDuplicate();
	TestSize();
	TestLargeTree();
	TestPrivateTests();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
