package Project5;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		try{
			int data, index;
			BucketSort myBucketSort = new BucketSort();
			File infile1 = new File(args[0]);	
			File outfile1 = new File(args[1]);
			File outfile2 = new File(args[2]);
			FileReader myReader = new FileReader(infile1);//read the input file
			Scanner myScanner = new Scanner(myReader);
			PrintWriter myWriter1 = new PrintWriter(outfile1);//output files ready
			PrintWriter myWriter2 = new PrintWriter(outfile2);
			myBucketSort.findMinMax(infile1);
			int[] bucketAry = new int[myBucketSort.computeOffsetAndSize()];
			Arrays.fill(bucketAry, 0);
			
			while (myScanner.hasNextInt()){
				data = myScanner.nextInt();
				index = (data - myBucketSort.getOffSet());
				bucketAry[index]++;
				myWriter2.println("Index " + index + ": " + data);
			}
			

			myBucketSort.printBucketAry(myWriter2, bucketAry);
			myBucketSort.printSortedData(myWriter1, bucketAry);
			myScanner.close();
			myWriter1.close();
			myWriter2.close();
		} catch(FileNotFoundException fne){
			System.out.println("error");
		}
	}
}
