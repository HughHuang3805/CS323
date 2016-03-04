package Project4;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class HeapSort {

	private int size, index = 0;
	private int[] myHeap;
	private PrintWriter writer1;
	private PrintWriter writer2;

	HeapSort(){
		size = 0;
	}

	public void heapAry(){
		myHeap = new int[size];
		myHeap[0] = 0;
	}

	public void buildHeap(File inputFile, File outputFile) throws IOException{
		int value;
		FileReader fileReader = new FileReader(inputFile);
		Scanner myScanner = new Scanner(fileReader);
		writer1 = new PrintWriter(outputFile);
		while (myScanner.hasNextInt()){
			printHeap(writer1);
			value = myScanner.nextInt();
			insertOneDataItem(value);

		}
	}

	public void insertOneDataItem(int data){//position in the array depends on myHeap[0] which has #of items
		index++;
		if (isHeapFull()) return;
		else{
			myHeap[index] = data;
			myHeap[0]++;
			bubbleUp(myHeap[0]);
		}
	}


	public void deleteHeap(){
		myHeap[0] = 0;
	}

	public void deleteRoot(File outputFile1, File outputFile2){	
		try{
			writer2 = new PrintWriter(outputFile2);
			if (isHeapEmpty()){
				writer1.println("The heap is empty.");
				return;
			} else{
				while(!isHeapEmpty()){
					writer2.print(myHeap[1] + " ");
					myHeap[1] = myHeap[myHeap[0]];
					myHeap[0]--;
					if (myHeap[0] > 0){
						bubbleDown(1);
					}
					printHeap(writer1);				
				}
				writer1.close();
				writer2.close();
			}
		} catch(FileNotFoundException fnfe){
			System.out.println("Such file does not exist");
		} catch(IOException ioe){

		}
	}

	public void bubbleUp(int index){//bubble up
		int parentIndex, temp;
		if (index != 0){
			parentIndex = index / 2;
			if (myHeap[parentIndex] > myHeap[index]){
				temp = myHeap[parentIndex];
				myHeap[parentIndex] = myHeap[index];
				myHeap[index] = temp;
				bubbleUp(parentIndex);
			}
		}
	}

	public void bubbleDown(int root){//bubble down
		int leftChild, rightChild, minIndex, temp;
		leftChild = 2 * root;
		rightChild = 2 * root + 1;
		if (rightChild >= myHeap[0]){
			if (leftChild >= myHeap[0]){
				return;
			}
			else{
				minIndex = leftChild;
			}
		} else {
			if (myHeap[leftChild] <= myHeap[rightChild]){
				minIndex = leftChild;
			}
			else{
				minIndex = rightChild;
			}
		}
		if (myHeap[root] > myHeap[minIndex]){
			temp = myHeap[minIndex];
			myHeap[minIndex] = myHeap[root];
			myHeap[root] = temp;
			bubbleDown(minIndex);
		}
	}

	public boolean isHeapEmpty(){
		return myHeap[0] == 0;
	}

	public boolean isHeapFull(){
		return myHeap[0] == (size - 1);
	}

	public void printHeap(PrintWriter pw) throws IOException{//prints the heap
		if(myHeap[0]<=10){
			for (int i = 0; i <=  myHeap[0]; i++){
				pw.write(myHeap[i] + " ");
			}
			pw.println();
		}
	}

	public void setSize(int size){
		this.size = size;
	}

	public int getSize(){
		return size;
	}
}
