#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class QuadTreeNode{
	friend class QuadTree;
	friend class Image;
public:
	int numRows, numCols, minValue, maxValue, color, rowOffset, colOffset, type;
	QuadTreeNode* NW_Kid = NULL;
	QuadTreeNode* SW_Kid = NULL;
	QuadTreeNode* SE_Kid = NULL;
	QuadTreeNode* NE_Kid = NULL;
	void printNode(QuadTreeNode*, ofstream&);
	QuadTreeNode();
	QuadTreeNode(int);
	~QuadTreeNode();
};

void QuadTreeNode::printNode(QuadTreeNode* node, ofstream& outfile){
	outfile << node->color << " " << node->numRows << " " << node->numCols << " " << minValue << " "
		<< node->maxValue << " " << node->rowOffset << " " << node->colOffset << " " << node->NW_Kid->color << " "
		<< node->SW_Kid->color << " " << node->SE_Kid->color << " " << node->NE_Kid->color << endl;
}

QuadTreeNode::QuadTreeNode(){

}

QuadTreeNode::~QuadTreeNode(){

}

class QuadTree{
public:
	QuadTreeNode* rootNode;
	void computeOffsets(QuadTreeNode*, QuadTreeNode*, int, int, int);
	void computeNumRowsCols(QuadTreeNode*, int, int);
	void computeMinMaxValue(QuadTreeNode*, QuadTreeNode*, int**);
	void computeColor(QuadTreeNode*);
	QuadTree(int**, int, int, int, int, int, int);
	void printNode(QuadTreeNode*, ofstream&);
	void computeAll(QuadTreeNode*, QuadTreeNode*, int**, int, int, int, int, int, ofstream&);
	void buildQuadTree(QuadTreeNode*, int**, ofstream&);
	void printQuadTree(QuadTreeNode*, ofstream&);
	~QuadTree();
};

QuadTree::QuadTree(int **array, int rows, int cols, int minValue, int maxValue, int rowOff, int colOff){
	rootNode = new QuadTreeNode();
	rootNode->numRows = rows;
	rootNode->numCols = cols;
	if (minValue != maxValue) rootNode->color = 2;
	rootNode->minValue = minValue;
	rootNode->maxValue = maxValue;
	rootNode->rowOffset = 0;
	rootNode->colOffset = 0;
}

void QuadTree::computeAll(QuadTreeNode* parent, QuadTreeNode* node, int** array, int type, int row, int col, int min, int max, ofstream& outfile){
	computeNumRowsCols(node, row, col); 
	computeOffsets(parent, node, type, row, col);
	computeMinMaxValue(parent, node, array);
	computeColor(node);
	outfile
		<< "Type: " << node->type << endl
		<< "MinValue: " << node->minValue << endl
		<< "MaxValue: " << node->maxValue << endl
		<< "RowOffset: " << node->rowOffset << endl
		<< "ColOffset: " << node->colOffset << endl
		<< "Color: " << node->color << endl
		<< "NumRows: " << node->numRows << endl
		<< "NumCols: " << node->numCols << endl << endl;
}

void QuadTree::computeNumRowsCols(QuadTreeNode* node, int rows, int cols){
	node->numRows = (rows / 2);
	node->numCols = (cols / 2);
}

void QuadTree::computeMinMaxValue(QuadTreeNode* parent, QuadTreeNode* node, int **array){
	int min, max, num1, num2;
	min = array[node->rowOffset][node->colOffset];
	max = min;
	for (int i = node->rowOffset; i < (node->numRows + node->rowOffset); i++){
		for (int j = node->colOffset; j < (node->numCols + node->colOffset); j++){
			if (array[i][j] != min){
				min = 0;
				max = 1;
				node->maxValue = max;
				node->minValue = min;
				return;
			}
			num2 = j;
		}
		num1 = i;
	}
	node->maxValue = max;
	node->minValue = min;
}

void QuadTree::computeOffsets(QuadTreeNode* parent, QuadTreeNode* node, int type, int rows, int cols){
	switch (type){
	case 1:
		node->rowOffset = parent->rowOffset;
		node->colOffset = parent->colOffset;
		node->type = type;
		break;
	case 2:
		node->rowOffset = parent->rowOffset + (rows / 2);
		node->colOffset = parent->colOffset;
		node->type = type;
		break;
	case 3:
		node->rowOffset = parent->rowOffset + (rows / 2);
		node->colOffset = parent->colOffset + (cols / 2);
		node->type = type;
		break;
	case 4:
		node->rowOffset = parent->rowOffset;
		node->colOffset = parent->colOffset + (cols / 2);
		node->type = type;
		break;
	default:
		node->rowOffset = rows;
		node->colOffset = cols;
		break;
	}
}

void QuadTree::computeColor(QuadTreeNode* node){
	if (node->minValue != node->maxValue){
		node->color = 2;
	}
	else{
		node->color = node->maxValue;
	}
}

void QuadTree::printNode(QuadTreeNode* node, ofstream& outfile){
	if (node->minValue != node->maxValue){
		outfile
			<< "Type: " << setw(1) << node->type 
			<< " Color: " << setw(1) << node->color
			<< " RowNumber: " << setw(2) << node->numRows
			<< " ColNumber: " << setw(2) << node->numCols
			<< " MinValue: " << setw(1) << node->minValue
			<< " MaxValue: " << setw(1) << node->maxValue
			<< " RowOffset: " << setw(2) <<node->rowOffset
			<< " ColOffset: " << setw(2) << node->colOffset
			<< " NW_KidColor: " << node->NW_Kid->color 
			<< " SW_KidColor: " << node->SW_Kid->color 
		    << " SE_KidColor: " << node->SE_Kid->color 
			<< " NE_KidColor: " << node->NE_Kid->color 
			<< endl;
	} 
	return;
}

void QuadTree::buildQuadTree(QuadTreeNode* node, int** array, ofstream& outfile){
	if (node == NULL) return;
	else if (node -> color != 2) return;
	else{
		node->NW_Kid = new QuadTreeNode();
		computeAll(node, node->NW_Kid, array, 1, node->numRows, node->numCols, node->minValue, node->maxValue, outfile);
		buildQuadTree(node->NW_Kid, array, outfile);

		node->SW_Kid = new QuadTreeNode();
		computeAll(node, node->SW_Kid, array, 2, node->numRows, node->numCols, node->minValue, node->maxValue, outfile);
		buildQuadTree(node->SW_Kid, array, outfile);
		
		node->SE_Kid = new QuadTreeNode();
		computeAll(node, node->SE_Kid, array, 3, node->numRows, node->numCols, node->minValue, node->maxValue, outfile);
		buildQuadTree(node->SE_Kid, array, outfile);
		
		node->NE_Kid = new QuadTreeNode();
		computeAll(node, node->NE_Kid, array, 4, node->numRows, node->numCols, node->minValue, node->maxValue, outfile);
		buildQuadTree(node->NE_Kid, array, outfile);
	}
}

void QuadTree::printQuadTree(QuadTreeNode* node, ofstream& outfile){
	if (node == NULL) return;
	else if (node->color != 2) return;
	else{
		printNode(node, outfile);
		printQuadTree(node->NW_Kid, outfile);
		printQuadTree(node->SW_Kid, outfile);
		printQuadTree(node->SE_Kid, outfile);
		printQuadTree(node->NE_Kid, outfile);
	}
}

QuadTree::~QuadTree(){

}

class Image{
public:
	int numRows, numCols, minValue, maxValue;
	int** imageArray;
	void makeImageArray();
	void loadImage(ifstream&);
	void print();
	Image(ifstream&, int, int, int, int);
	~Image();
};

void Image::print(){
	for (int i = 0; i < 64; i++){
		for (int j = 0; j < 64; j++){
			cout << imageArray[i][j];
		}
		cout << endl;
	}
}

void Image::makeImageArray(){
	imageArray = new int*[numRows];
	for (int i = 0; i < numRows; i++){
		imageArray[i] = new int[numCols];
	}
}

void Image::loadImage(ifstream& infile){
	makeImageArray();
	for (int i = 0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){
			infile >> imageArray[i][j]; 
		}
	}
}

Image::Image(ifstream& infile, int rows, int cols, int min, int max){
	numRows = rows;
	numCols = cols;
	minValue = min;
	maxValue = max;
	loadImage(infile);
}

Image::~Image(){

}

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open(argv[1]);
	ofstream outfile1;
	outfile1.open(argv[2]);
	ofstream outfile2;
	outfile2.open(argv[3]);

	int row, col, max, min;
	infile >> row >> col >> min >> max;
	Image* myImage = new Image(infile, row, col, min, max);

	QuadTree* myQuadTree = new QuadTree(myImage->imageArray, row, col, min, max, 0, 64);
	myQuadTree->buildQuadTree(myQuadTree->rootNode, myImage->imageArray, outfile2);
	myQuadTree->printQuadTree((myQuadTree->rootNode), outfile1);
	
	infile.close();
	outfile1.close();
	outfile2.close();
	return 0;
}