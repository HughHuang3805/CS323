
import java.io.PrintWriter;

public class HuffmanBinaryTree {
	private ListBinTreeNode root;

	class charInfo{
		public String charString;
		public int probability;
		public String code;
	}

	HuffmanBinaryTree(){

	}

	HuffmanBinaryTree(HuffmanLinkedList myList, PrintWriter pw3){
		constructHuffmanBinaryTree(myList, pw3);
	}

	public void preOrderTraversal(ListBinTreeNode node, PrintWriter pw2){
		if (node == null){
			return;
		}
		else{
			node.printNode(node, pw2);
			preOrderTraversal((node.getLeft()), pw2);
			preOrderTraversal((node.getRight()), pw2);

		}
	}

	public void constructHuffmanBinaryTree(HuffmanLinkedList myList, PrintWriter pw3){
		//construct the binary tree and print
		myList.setListHead(myList.getDummyNode().getNext());
		myList.setOldListHead(myList.getListHead().getNext());
		ListBinTreeNode next;
		while (!myList.isEmpty(myList.getListHead())){
			ListBinTreeNode newNode = new ListBinTreeNode();
			newNode.setProbability(myList.getListHead().getProbability() + myList.getOldListHead().getProbability());
			newNode.setCharString(myList.getListHead().getCharString() + myList.getOldListHead().getCharString());
			newNode.setLeft(myList.getListHead());
			newNode.setRight(myList.getOldListHead());
			next = myList.listInsert(newNode);
			if(myList.getListHead().getNext() == null){
				myList.setListHead(myList.getOldListHead().getNext());
			} else{
				myList.setListHead(myList.getOldListHead().getNext());
				myList.setOldListHead(myList.getListHead().getNext());
			}
			newNode.printNode(newNode, pw3);
			myList.printList(pw3);
			root = newNode;
		}
	}

	public void constructCharCode(ListBinTreeNode node, String code, PrintWriter pw1){
		if (node == null){
			return;
		}
		else if (node.getLeft() == null || node.getRight() == null){
			pw1.println(node.getCharString() + " " + code);
		}
		else{
			constructCharCode(node.getLeft(), code + "0", pw1);
			constructCharCode(node.getRight(), code + "1", pw1);
		}
	}
	
	public ListBinTreeNode getRoot(){
		return root;
	}
}

