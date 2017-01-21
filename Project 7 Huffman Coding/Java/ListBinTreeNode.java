
import java.io.PrintWriter;

public class ListBinTreeNode {
	private String charString = "";
	private int probability;
	private ListBinTreeNode next;
	private ListBinTreeNode left;
	private ListBinTreeNode right;

	ListBinTreeNode(){
		probability = 0;
		next = null;
		charString = "";
	}

	ListBinTreeNode(int value, String name){
		probability = value;
		next = null;
		charString = name;
	}

	public void printNode(ListBinTreeNode node, PrintWriter pw3){
		if(node == null) return;
		if(node.charString == "") return;
		pw3.printf("%s%-7s%s%-3d", "CharString: ", node.charString, " Probability: ", node.probability);
		if (node.next == null){
			pw3.printf("%s%-7s%s%-7s%s%-5s%n", " Next CharString: ", "NULL", " Left CharString: ", node.left.charString, " Right CharString: ", node.right.charString);
		}
		else if (node.left == null || node.right == null){
			pw3.printf("%s%-7s%s%-7s%s%-5s%n", " Next CharString: ", node.next.charString, " Left CharString: ", "NULL", " Right CharString: ", "NULL" );
		}
		else{
			pw3.printf("%s%-7s%s%-7s%s%-5s%n", " Next CharString: ", node.next.charString, " Left CharString: ", node.left.charString, " Right CharString: ", node.right.charString);
		}
	}
	
	public int getProbability(){
		return probability;
	}
	
	public void setProbability(int data){
		this.probability = data;
	}
	
	public String getCharString(){
		return charString;
	}
	
	public void setCharString(String charString){
		this.charString = charString;
	}
	
	public ListBinTreeNode getNext(){
		return next;
	}
	
	public void setNext(ListBinTreeNode node){
		this.next = node;
	}
	
	public ListBinTreeNode getLeft(){
		return left;
	}
	
	public void setLeft(ListBinTreeNode left){
		this.left = left;
	}
	
	public ListBinTreeNode getRight(){
		return right;
	}
	
	public void setRight(ListBinTreeNode right){
		this.right = right;
	}
}
