package Project1;

public class StackArray {

	public static final int DEFAULT_CAPACITY = 1024;

	int[] stack;
	private int topOfStack;
	int stackSize;

	public StackArray(){ 
		stack = new int[DEFAULT_CAPACITY]; 
		topOfStack = -1;
		stackSize = DEFAULT_CAPACITY;
	}

	public StackArray(int capacity){
		topOfStack = -1;
		stack = new int[capacity];
		stackSize = capacity;
	}

	public int size(){
		return topOfStack;
	}

	public boolean isEmpty(){
		return topOfStack == -1;
	}

	public void push(int e) throws IllegalStateException{
		if(topOfStack + 1 < stackSize){
			topOfStack++;
			stack[topOfStack] = e;
		} else{
			System.out.println("The stack is full.");
		}
	}

	public Integer top() throws IllegalStateException{
		if(!isEmpty()){
			return stack[topOfStack];
		}
		return null;
	}

	public Integer pop() throws IllegalStateException{
		if(topOfStack >= 0){
			int temp = topOfStack;
			topOfStack--;
			return stack[temp];
		} else{
			System.out.println("The stack is empty.");
			return null;
		}
	}

	public Integer getTopOfStack(){
		if(!isEmpty()){
			return topOfStack;
		} 
		return null;
	}

}
