// Project 3.cpp : Defines the entry point for the console application.
//


#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class listNode{
	friend class linkedList;
public:
	listNode();
	listNode(int value);
	int data;
	listNode* next;
	void setNext(listNode*);
	void setData(int);
	~listNode();
};

listNode::listNode(){
	data = -9999;
	next = NULL;
}

listNode::listNode(int value){
	data = value;
	next = NULL;
}

void listNode::setNext(listNode* nextNode){
	next = nextNode;
}

void listNode::setData(int value){
	data = value;
}

listNode::~listNode(){

}

class linkedList{
public:
	listNode* listHead;
	listNode* dummyNode;
	linkedList();
	bool isEmpty();
	void listInsert(int);
	int listDelete(int);
	listNode* findSpot(int);
	void printList();
};

linkedList::linkedList(){
	dummyNode = new listNode();
	listHead = new listNode();
	dummyNode = listHead;
}

bool linkedList::isEmpty(){
	return listHead == NULL;
}

void linkedList::listInsert(int value){
	listNode* temp = findSpot(value);
	listNode* newNode = new listNode(value);
	if (temp == NULL){
		temp = dummyNode;
		while (temp -> next != NULL){
			temp = temp->next;
		}
		temp = newNode;
	}
	else{
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

listNode* linkedList::findSpot(int value){
	listNode* spot = dummyNode;
	while (spot->next != NULL){
		if (spot->next->data < value){
			spot = spot->next;
		}
		else {
			return spot;
		}
	}
	return spot;
}

void linkedList::printList(){
	listNode* temp = dummyNode;
	while (temp != NULL){
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open(argv[1]);
	ofstream outfile;
	outfile.open(argv[2]);
	linkedList* myLinkedList = new linkedList();
	int input;
	listNode* spot;
	listNode* temp;
	while (infile >> input){
		//cout << "hi";
		temp = myLinkedList->dummyNode;
		spot = myLinkedList->findSpot(input);
		//cout << "hi";
		
		if (spot ->next!= NULL){
			if (spot->next->data == input){
				outfile << "Insert data " << setw(5) << input << ": " << input << " is already in the list \n";
				continue;
			}
		}
		myLinkedList->listInsert(input);
		outfile << "Insert data " << setw(5) << input << ": listHead ";
		while (temp->next != NULL){
			int tempValue = temp->next->data;
			outfile << "--> " << "(" << temp->data << ", " << tempValue << ") ";
			temp = temp->next;
			if (temp -> next == NULL){
				outfile << "--> " << "(" << tempValue << ", " << -1 << ") \n";
			}
		}
		myLinkedList->printList();
	}
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}
