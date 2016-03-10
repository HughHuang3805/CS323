// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class bucketSort{
private:
	int minData, maxData, bucketSize, offSet, index;
public:
	bucketSort();
	void findMinMax(ifstream&);
	int computeOffsetAndSize();
	int* initializeAry();
	int getOffSet();
	void printBucketAry(ofstream&, int*);
	void printSortedData(ofstream&, int*);
	~bucketSort();
};

bucketSort::bucketSort(){

}

void bucketSort::findMinMax(ifstream& infile){
	int data;
	infile >> minData;
	infile >> maxData;
	if (minData > maxData){
		int temp = minData;
		minData = maxData;
		maxData = temp;
	}
	while (infile >> data){
		if (data < minData){
			minData = data;
		}
		if (data > maxData){
			maxData = data;
		}
	}
}

int bucketSort::computeOffsetAndSize(){
	offSet = minData;
	bucketSize = maxData - minData + 1;
	return bucketSize;
}

/*int* bucketSort::initializeAry(){
	bucketAry = new int[bucketSize];
	bucketAry = { 0 };
	return bucketAry;
}*/

int bucketSort::getOffSet(){
	return offSet;
}

void bucketSort::printSortedData(ofstream& outfile1, int* bucketAry){
	for (int i = 0; i < bucketSize; i++){
		while (bucketAry[i] != 0){
			outfile1 << (i + offSet) << endl;
			bucketAry[i]--;
		}
	}
}

void bucketSort::printBucketAry(ofstream& outfile2, int* bucketAry){
	for (int i = 0; i < 19; i++){
		outfile2 << setw(4) << i << " ";
	}
	outfile2 << endl;

	for (int i = 0; i < 19; i++){
		outfile2 << setw(4) << bucketAry[i] << " ";
	}
}

bucketSort::~bucketSort(){
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	int data, index;
	bucketSort* myBucketSort = new bucketSort();
	ifstream infile;
	infile.open(argv[1]);
	ofstream outfile1, outfile2;
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);

	myBucketSort->findMinMax(infile);
	int* bucketAry = new int[myBucketSort->computeOffsetAndSize()]();
	infile.close();

	ifstream infile2;
	infile2.open(argv[1]);
	while (infile2 >> data){
		index = (data - myBucketSort->getOffSet());
		bucketAry[index]++;
		outfile2 << "Index " << index << ": " << data << endl;
	}

	myBucketSort->printBucketAry(outfile2, bucketAry);
	myBucketSort->printSortedData(outfile1, bucketAry);
	outfile1.close();
	outfile2.close();
	infile2.close();

	return 0;
}

