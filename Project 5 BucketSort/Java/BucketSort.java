package Project5;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;

public class BucketSort {

	private int minData, maxData, bucketSize, offSet;

	BucketSort(){
		
	}

	public void findMinMax(File infile) throws FileNotFoundException{
		FileReader fileReader = new FileReader(infile);
		Scanner myScanner = new Scanner(fileReader);
		int data;
		minData = myScanner.nextInt();
		maxData = myScanner.nextInt();
		if (minData > maxData){
			int temp = minData;
			minData = maxData;
			maxData = temp;
		}
		while (myScanner.hasNextInt()){
			data = myScanner.nextInt();
			if (data < minData){
				minData = data;
			}
			if (data > maxData){
				maxData = data;
			}
		}
		myScanner.close();
	}

	public int computeOffsetAndSize(){
		offSet = minData;
		bucketSize = maxData - minData + 1;
		return bucketSize;
	}

	public int getOffSet(){
		return offSet;
	}

	public void printSortedData(PrintWriter pw, int[] bucketAry) throws FileNotFoundException{
		for (int i = 0; i < bucketSize; i++){
			while (bucketAry[i] != 0){
				pw.println(i + offSet);
				bucketAry[i]--;
			}
		}
		pw.close();
	}

	public void printBucketAry(PrintWriter pw, int[] bucketAry) throws FileNotFoundException{
		for (int i = 0; i < 19; i++){
			pw.printf("%4S ", i);
		}
		pw.println();
		for (int i = 0; i < 19; i++){
			pw.printf("%4S ", bucketAry[i]);
		}
		pw.close();
	}
}
