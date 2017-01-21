
#include<iostream>
#include<fstream>
using namespace std;

class Dijkstra{
public:
	int numNodes, sourceNode, minNode, currentNode, newCost;
	int** costMatrix;
	int* fatherArray;
	int* markedArray;
	int* bestCostArray;
	void loadCostMatrix(ifstream&);
	void loadBestCostArray(int);
	void loadFatherArray(int);
	void loadMarkedArray();
	void computeCost(int, int);
	void markMinNode(int);
	void changeFather(int, int);
	void changeCost(int, int);
	void debugPrint(ofstream&);
	void printShortestPath(int, ofstream&);
};

void Dijkstra::loadCostMatrix(ifstream& infile){
	infile >> numNodes;
	int value1, value2, value3;
	sourceNode = 1;
	costMatrix = new int*[numNodes];
	for (int i = 0; i < numNodes; i++){
		costMatrix[i] = new int[numNodes];
	}
	for (int i = 0; i < numNodes; i++){
		for (int j = 0; j < numNodes; j++){
			costMatrix[i][j] = 99999;
		}
		costMatrix[i][i] = 0;
	}
	while (infile >> value1){
		infile >> value2 >> value3;
		costMatrix[value1 - 1][value2 - 1] = value3;
		//cout << costMatrix[value1 - 1][value2 - 1] << " ";
	}
}

/* Row of source node from cost matrix */
void Dijkstra::loadBestCostArray(int node){ 
	bestCostArray = new int[numNodes];
	for (int i = 0; i < numNodes; i++){
		bestCostArray[i] = costMatrix[node - 1][i]; //why node -1? 
	}
	//sourceNode = node;
	minNode = sourceNode; //why assign min node here? 
}

void Dijkstra::loadFatherArray(int node){
	fatherArray = new int[numNodes];
	for (int i = 0; i < numNodes; i++){
		//wrong, should be dynamic loading the entire row, not all same 
		fatherArray[i] = node; 
	}
}

void Dijkstra::loadMarkedArray(){
	markedArray = new int[numNodes];
	for (int i = 0; i < numNodes; i++){
		markedArray[i] = 0;
	}
}

void Dijkstra::computeCost(int node1, int node2){
	if (costMatrix[node1][node2] != 99999){
		newCost = bestCostArray[node1] + costMatrix[node1][node2];
		//cout << newCost << endl;
	}
	else{
		newCost = bestCostArray[node2];
	}
}

void Dijkstra::markMinNode(int minNode){
	markedArray[minNode] = 1;
}

void Dijkstra::changeFather(int node, int minNode){
	fatherArray[node] = minNode;
}

void Dijkstra::changeCost(int node, int newCost){
	bestCostArray[node] = newCost;
}

void Dijkstra::debugPrint(ofstream& outfile2){
	outfile2 << "The source node is: " << sourceNode << endl;
	//
	outfile2 << "The father array is: ";
	for (int i = 0; i < numNodes; i++){
		outfile2 << fatherArray[i] << " ";
	}
	outfile2 << endl;
	//
	outfile2 << "The best cost array is: ";
	for (int i = 0; i < numNodes; i++){
		outfile2 << bestCostArray[i] << " ";
	}
	outfile2 << endl;
	//
	outfile2 << "The marked array is: ";
	for (int i = 0; i < numNodes; i++){
		outfile2 << markedArray[i] << " ";
	}
	outfile2 << endl << endl;
}

void Dijkstra::printShortestPath(int node, ofstream& outfile1){
	outfile1 << "There are " << numNodes << " nodes in the input graph." << endl;
	outfile1 << "Source Node = " << sourceNode << endl;
	outfile1 << "The shortest paths from node " << sourceNode << " are: " << endl;
	outfile1 << "The path from " << sourceNode << " to " << node << ": " << newCost << endl << endl;
}

int main(int argc, char* argv[])
{
	ifstream infile;
	ofstream outfile1;
	ofstream outfile2;
	infile.open(argv[1]);
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);

	Dijkstra* myDijkstra = new Dijkstra();
	myDijkstra->loadCostMatrix(infile);
	int numNodes = myDijkstra->numNodes;
	myDijkstra->sourceNode = 1;


	while (myDijkstra->sourceNode <= numNodes){
		myDijkstra->loadBestCostArray(myDijkstra->sourceNode);
		myDijkstra->loadFatherArray(myDijkstra->sourceNode);
		myDijkstra->loadMarkedArray();

		int minCost = 99999;
		for (int j = 0; j < numNodes; j++){
			for (int i = 0; i < numNodes; i++){
				if (myDijkstra->markedArray[i] == 0){
					if (myDijkstra->sourceNode - 1 == i) continue;
					if (myDijkstra->bestCostArray[i] < minCost){

						minCost = myDijkstra->bestCostArray[i];
						myDijkstra->minNode = i;
						
					}
				}
			}
			myDijkstra->markMinNode(myDijkstra->minNode);
			//cout << myDijkstra->minNode << endl;
			myDijkstra->debugPrint(outfile2);

			for (int i = 0; i < numNodes; i++){
				if (myDijkstra->sourceNode - 1 == i) continue;
				if (myDijkstra->markedArray[i] == 0){
					myDijkstra->currentNode = i;
					//myDijkstra->markedArray[i] = 1;
					//cout << "hi";
					//break;
					myDijkstra->computeCost(myDijkstra->minNode, myDijkstra->currentNode);
					for (int j = i; j < numNodes; j++){
						if (j == myDijkstra->minNode) continue;
						if (myDijkstra->markedArray[j] == 0){
							myDijkstra->currentNode = j;
							myDijkstra->computeCost(myDijkstra->minNode, myDijkstra->currentNode);
							if (myDijkstra->newCost < myDijkstra->bestCostArray[myDijkstra->currentNode]){
								myDijkstra->changeFather(myDijkstra->currentNode, myDijkstra->minNode);
								myDijkstra->changeCost(myDijkstra->currentNode, myDijkstra->newCost);
								//myDijkstra->markMinNode(j);
								//cout << myDijkstra->minNode << " ";
								myDijkstra->debugPrint(outfile2);
							}
						}
					}
				}
			}
		}
		myDijkstra->currentNode = 1;
		while (myDijkstra->currentNode <= numNodes){
			myDijkstra->printShortestPath(myDijkstra->currentNode, outfile1);
			myDijkstra->currentNode++;
		}
		myDijkstra->sourceNode++;
	}
	outifle1.close();
	outfile2.close();
	system("pause");
	return 0;
}

