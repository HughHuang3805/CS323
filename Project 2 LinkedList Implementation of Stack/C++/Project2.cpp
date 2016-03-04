// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;

class ListNode{
	friend class LinkedListStac;
public:
	ListNode();
	int data;
	ListNode(int value);
	int getData();
	ListNode* getNext();
	void setNext(ListNode*);
	void setData(int);
	ListNode* next;
	~ListNode();
};

ListNode::ListNode(){
	data = 0;
	next = NULL;
}

ListNode::ListNode(int x){
	data = x;
	next = NULL;
}

int ListNode::getData(){
	return data;
}

ListNode* ListNode::getNext(){
	return next;
}

void ListNode::setData(int data2){
	data = data2;
}

void ListNode::setNext(ListNode* node){
	next = node;
}

class LinkedListStack{
public:
	LinkedListStack();
	LinkedListStack(int);
	ListNode* top();
	void push(int);
	int pop();
	bool isEmpty();
	int getLength();
	~LinkedListStack();
	ListNode* first;
	ListNode* last;
	int length = 0;
	
};

LinkedListStack::LinkedListStack(){
	first = NULL;
	last = NULL;
	length++;
}

LinkedListStack::LinkedListStack(int x){
	first = new ListNode(x);
	last = first;
	length++;
}

ListNode* LinkedListStack::top(){
	return first;
}

void LinkedListStack::push(int x){
	ListNode* node = new ListNode(x);
	node->next = first;
	first = node;
	length++;
}

int LinkedListStack::pop(){
	if (isEmpty()) return 0;
	else {
		ListNode* node = first;
		first = first->next;
		length--;
		return (node->data);
	}
}

bool LinkedListStack::isEmpty(){
	return first == NULL;
}

int LinkedListStack::getLength(){
	return length;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myfile;
	myfile.open(argv[1]);
	LinkedListStack* myListStack = new LinkedListStack();
	int count = 0, num, finish = 1;
	while (myfile >> num){
		count++;
		myListStack->push(num);
		cout << num << " " << myListStack->top()->next << endl;
	}
	cout << "There are " << count << " numbers." << endl << endl;
	myfile.close();

	ListNode* temp;
	temp = myListStack->first;
	while (temp!=NULL){
		temp = myListStack->first;
		if (myListStack->top() == 0){
			cout << "The stack is now empty, return 0." << endl;
			break;
		}
		cout << myListStack->pop() << endl;
	}

	system("pause");
	return 0;
}

