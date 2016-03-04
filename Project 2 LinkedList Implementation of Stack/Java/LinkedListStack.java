package Project2;

public class LinkedListStack {

	private int length = 0;
	ListNode first;
	ListNode last;
	
	public LinkedListStack(){
		first = null;
		length++;
	}
	
	public LinkedListStack(int x){
		first = new ListNode(x);
		length++;
	}
	
	public ListNode top(){
		return first;
	}
	
	public void push(int data){
		ListNode node = new ListNode(data);
		node.setNext(first);
		first = node;
		length++;
	}
	
	public int pop(){
		if(isEmpty()){
			return 0;
		} else{
			ListNode node = first;
			first = first.getNext();
			length--;
			return node.getData();
		}
	}
	
	public boolean isEmpty(){
		return first == null;
	}
	
	public int getLength(){
		return length;
	}
	
}
