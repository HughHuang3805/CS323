package Project2;

public class ListNode {
	
	private Integer data;
	ListNode next;
	
	public ListNode(){
		data = null;
		next  = null;
	}
	
	public ListNode(int x){
		data = x;
		next = null;
	}
	
	public int getData(){
		return this.data;
	}
	
	public ListNode getNext(){
		return next;
	}
	
	public void seData(int data){
		this.data = data;
	}
	
	public void setNext(ListNode node){
		this.next = node;
	}

}
