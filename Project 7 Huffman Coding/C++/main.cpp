
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class ListBinTreeNode{
public:
	friend class HuffmanLinkedList;
	char myChar;
	string charString = "";
	string code = "";
	int probability;
	ListBinTreeNode* next;
	ListBinTreeNode* left;
	ListBinTreeNode* right;
	ListBinTreeNode();
	ListBinTreeNode(int, string);
	~ListBinTreeNode();
	void printNode(ListBinTreeNode*, ofstream&);
};

ListBinTreeNode::ListBinTreeNode(){
	probability = 0;
	next = NULL;
	charString = "";
}

ListBinTreeNode::ListBinTreeNode(int value, string name){
	probability = value;
	next = NULL;
	charString = name;
}

ListBinTreeNode::~ListBinTreeNode(){

}

void ListBinTreeNode::printNode(ListBinTreeNode* node, ofstream& outfile3){

	//cout << node->charString<<" "<<node->probability << endl;
	if(node == NULL) return;
	if(node->charString == "") return;
	//cout << "hi" << endl;
	outfile3 << "CharString: " << setw(7) << node->charString << " Probability: " << setw(3) << node->probability;
	if (node->next == NULL){
		outfile3 << " Next CharString: " << setw(7) << "NULL" << " Left CharString: "
			<< setw(6) << node->left->charString << " Right CharString: " << setw(4) << node->right->charString << endl;
	}
	else if (node->left == NULL || node->right == NULL){
		outfile3 << " Next CharString: " << setw(7) << node->next->charString << " Left CharString: " 
			<< setw(6) << "NULL" << " Right CharString: " << setw(4) << "NULL" << endl;
	}
	else{
		outfile3 << " Next CharString: " << setw(7) << node->next->charString << " Left CharString: "
			<< setw(6) << node->left->charString << " Right CharString: " << setw(4) << node->right->charString << endl;
	}
}

class HuffmanLinkedList{
public:
	ListBinTreeNode* listHead;
	ListBinTreeNode* oldListHead;
	ListBinTreeNode* dummyNode;
	HuffmanLinkedList();
	ListBinTreeNode* listInsert(ListBinTreeNode*);
	ListBinTreeNode* findSpot(int);
	bool isEmpty(ListBinTreeNode*);
	void printList(ofstream&);
};

HuffmanLinkedList::HuffmanLinkedList(){
	dummyNode = new ListBinTreeNode();
	listHead = new ListBinTreeNode();
	dummyNode = listHead;
	oldListHead = listHead;
}

ListBinTreeNode* HuffmanLinkedList::listInsert(ListBinTreeNode* newNode){
	ListBinTreeNode* temp = findSpot(newNode->probability);
	if (temp == NULL){
		temp = dummyNode;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp = newNode;
	}
	else{
		newNode->next = temp->next;
		temp->next = newNode;
	}
	return newNode->next;
}

ListBinTreeNode* HuffmanLinkedList::findSpot(int data){
	ListBinTreeNode* spot = dummyNode;
	while (spot->next != NULL){
		if (spot->next->probability < data){
			spot = spot->next;
		}
		else {
			return spot;
		}
	}
	return spot;
}

bool HuffmanLinkedList::isEmpty(ListBinTreeNode* node){
	return node->next == NULL;
}

void HuffmanLinkedList::printList(ofstream& outfile3){
	ListBinTreeNode* temp = dummyNode;
	outfile3 << "ListHead --> (dummy, 0, " << temp->next->charString << ")";
	temp = temp->next;
	while (temp != NULL){
		if (temp->next == NULL){
			outfile3 << " --> (" << temp->charString << ", " << temp->probability << ", NULL) --> NULL" << endl;
			break;
		}
		outfile3 << " --> (" << temp->charString << ", " << temp->probability << ", " << temp->next->charString << ")";
		temp = temp->next;
	}
}

class HuffmanBinaryTree{
public:
	class charInfo{
	public:
		string charString;
		int probability;
		string code;
	};
	ListBinTreeNode* root;
	void preOrderTraversal(ListBinTreeNode*, ofstream&);
	HuffmanBinaryTree();
	HuffmanBinaryTree(HuffmanLinkedList*, ofstream&);
	void constructHuffmanBinaryTree(HuffmanLinkedList*, ofstream&);
	void constructCharCode(ListBinTreeNode*, string, ofstream&);
	~HuffmanBinaryTree();
};

void HuffmanBinaryTree::preOrderTraversal(ListBinTreeNode* node, ofstream& outfile2){
	if (node == NULL){
		return;
	}
	else{
		//cout << node->charString << " " << node->probability << endl;
		node->printNode(node, outfile2);
		preOrderTraversal((node->left), outfile2);
		preOrderTraversal((node->right), outfile2);

	}
}

HuffmanBinaryTree::HuffmanBinaryTree(){

}

HuffmanBinaryTree::HuffmanBinaryTree(HuffmanLinkedList* myList, ofstream& outfile3){
	constructHuffmanBinaryTree(myList, outfile3);
}

void HuffmanBinaryTree::constructHuffmanBinaryTree(HuffmanLinkedList* myList, ofstream& outfile3){
	ListBinTreeNode* dummyNode = new ListBinTreeNode();
	dummyNode = myList->oldListHead;
	myList->listHead = myList->dummyNode->next;
	//cout << dummyNode->charString << " " << dummyNode->probability << endl;
	myList->oldListHead = myList->listHead->next;
	ListBinTreeNode* next;
	while (!myList->isEmpty(myList->listHead)){
		ListBinTreeNode* newNode = new ListBinTreeNode();
		newNode->probability = myList->listHead->probability + myList->oldListHead->probability;
		newNode->charString = myList->listHead->charString + myList->oldListHead->charString;
		newNode->left = myList->listHead;
		//cout << newNode->left->charString << " " << newNode->left->probability << endl;
		newNode->right = myList->oldListHead;
		//cout << newNode->right->charString << " " << newNode->right->probability << endl;
		next = myList->listInsert(newNode);
		if(myList->listHead->next==NULL){
			myList->listHead = myList->oldListHead->next;
			//myList->oldListHead = myList->listHead->next;
		} else{
			myList->listHead = myList->oldListHead->next;
			myList->oldListHead = myList->listHead->next;
		}
		//cout << myList->oldListHead->charString << endl;
		newNode->printNode(newNode, outfile3);
		myList->printList(outfile3);
		root = newNode;
	}
}

void HuffmanBinaryTree::constructCharCode(ListBinTreeNode* node, string code, ofstream& outfile1){
	if (node == NULL){
		return;
	}
	else if (node->left == NULL || node->right == NULL){
		outfile1 << node->charString << " " << code << endl;
	}
	else{
		constructCharCode(node->left, code + "0", outfile1);
		constructCharCode(node->right, code + "1", outfile1);
		//cout << node->right << endl;
	}
}

HuffmanBinaryTree::~HuffmanBinaryTree(){

}

int main(int argc, char* argv[])
{
	ifstream infile;
	ofstream outfile1, outfile2, outfile3;
	infile.open(argv[1]);
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);
	outfile3.open(argv[4]);
	HuffmanLinkedList* myList = new HuffmanLinkedList();

	fstream fin(argv[1], fstream::in);
	string first;
	int second;
	string name = "";
	while (infile >> first >> second){
		ListBinTreeNode* newNode = new ListBinTreeNode((int)second, first);
		myList->listInsert(newNode);
	}
	ListBinTreeNode* temp = myList->dummyNode;
	HuffmanBinaryTree* myBinaryTree = new HuffmanBinaryTree(myList, outfile3);
	myBinaryTree->constructCharCode(myBinaryTree->root, "", outfile1);
	myBinaryTree->preOrderTraversal(myBinaryTree->root, outfile2);

	infile.close();
	outfile1.close();
	outfile2.close();
	outfile3.close();
	return 0;
}

