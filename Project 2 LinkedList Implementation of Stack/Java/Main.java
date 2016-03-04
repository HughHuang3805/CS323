package Project2;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		LinkedListStack myList = new LinkedListStack();
		int number, counter = 0;
		FileReader fileReader;
		try {
			fileReader = new FileReader(args[0]);
			Scanner myScanner = new Scanner(fileReader);
			while(myScanner.hasNextInt()) {
				counter++;
				number = myScanner.nextInt();
				myList.push(number);
				System.out.println(number);
			}   
			myScanner.close();    
			System.out.println("There are " + counter + " numbers in the stack.");

			ListNode temp = myList.first;
			while(temp!=null){
				temp = myList.first;
				if(myList.isEmpty()){
					System.out.println("The stack is now empty.\n\n");
					break;	
				}
				System.out.println(myList.pop());
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
