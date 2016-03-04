// Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;


class Stack{
public:
	int* stack;
	int topOfStack, stackSize;
	Stack(int size);
	int top();
	void push(int x);
	int pop();
	bool isEmpty();
	~Stack();
};

Stack::Stack(int size){
	stack = new int[size];
	topOfStack = -1;
	stackSize = size;
}

int Stack::top(){
	return stack[topOfStack];
}

void Stack::push(int x){
	if (topOfStack + 1 < stackSize){
		topOfStack++;
		stack[topOfStack] = x;
	}
	else{
		cout << "The stack is full";
	}
}

int Stack::pop(){
	if (topOfStack >= 0){
		return stack[topOfStack--];
	}
	else{
		cout << "The stack is empty.";
		return 0;
	}
}

bool Stack::isEmpty(){
	return topOfStack == -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myfile;
	myfile.open(argv[1]);
	int count = 0, num;
	while (myfile >> num){
		count++;
		cout << num << endl;
	}
	cout << "There are " << count << " numbers." << endl << endl;
	myfile.close();

	Stack* stack_array = new Stack(count);
	myfile.open(argv[1]);
	int data;
	while (myfile >> data){
		stack_array->push(data);
	}
	while (!stack_array->isEmpty()){
		cout <<  stack_array->pop();
		cout << endl;
	}
	myfile.close();

	system("pause");
	return 0;
}

