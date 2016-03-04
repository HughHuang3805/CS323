package Project1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		try{
			StackArray myStack;
			int number, counter = 0;
			FileReader fileReader = new FileReader(args[0]);
			Scanner myScanner = new Scanner(fileReader);

			while(myScanner.hasNextInt()) {
				counter++;
				number = myScanner.nextInt();
				System.out.println(number);
			}   
			myScanner.close();    
			System.out.println("There are " + counter + " numbers in the stack.");

			FileReader fileReader2 = new FileReader(args[0]);
			Scanner myScanner2 = new Scanner(fileReader2);
			myStack = new StackArray(counter);
			while(myScanner2.hasNextInt()) {
				number = myScanner2.nextInt();
				myStack.push(number);
				System.out.println(number);
			}   
			myScanner2.close();
			while(!myStack.isEmpty()){
				System.out.println(myStack.pop());
			}
		} catch(FileNotFoundException ex){
			System.out.println("Such file does not exist.");
		}
	}

}
