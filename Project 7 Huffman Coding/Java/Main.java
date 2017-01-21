
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		try{
			File infile = new File(args[0]);
			File outfile1 = new File(args[1]);
			File outfile2 = new File(args[2]);
			File outfile3 = new File(args[3]);
			FileReader myReader = new FileReader(infile);
			Scanner myScanner = new Scanner(myReader);
			PrintWriter myWriter1 = new PrintWriter(outfile1);
			PrintWriter myWriter2 = new PrintWriter(outfile2);
			PrintWriter myWriter3 = new PrintWriter(outfile3);
			HuffmanLinkedList myList = new HuffmanLinkedList();

			String first;
			int second;
			while (myScanner.hasNext()){
				first = myScanner.next();
				second = myScanner.nextInt();
				ListBinTreeNode newNode = new ListBinTreeNode(second, first);
				myList.listInsert(newNode);
			}
			ListBinTreeNode temp = myList.getDummyNode();
			HuffmanBinaryTree myBinaryTree = new HuffmanBinaryTree(myList, myWriter3);
			myBinaryTree.constructCharCode(myBinaryTree.getRoot(), "", myWriter1);
			myBinaryTree.preOrderTraversal(myBinaryTree.getRoot(), myWriter2);

			myScanner.close();
			myWriter1.close();
			myWriter2.close();
			myWriter3.close();
		} catch(FileNotFoundException fnfe){
			System.out.println("Such file does not exist.");
		}
	}
}
