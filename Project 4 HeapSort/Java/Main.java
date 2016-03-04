package Project4;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws IOException {
		try{
			int count = 0, data;
			HeapSort heapSort = new HeapSort();
			File inputFile = new File(args[0]);
			File outputFile1 = new File(args[1]);
			File outputFile2 = new File(args[2]);
			FileReader myReader = new FileReader(inputFile);
			Scanner myScanner1 = new Scanner(myReader);
			
			while(myScanner1.hasNextInt()){
				data = myScanner1.nextInt();
				count++;
			}
			
			heapSort.setSize(count+1);
			heapSort.heapAry();
			myScanner1.close();
			
			heapSort.buildHeap(inputFile, outputFile1);
			heapSort.deleteRoot(outputFile1, outputFile2);
		} catch(FileNotFoundException fne){
			System.out.println("Such file does not exist");
		}
	}

}
