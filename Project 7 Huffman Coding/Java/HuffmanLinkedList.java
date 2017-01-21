
import java.io.PrintWriter;

public class HuffmanLinkedList {
	private ListBinTreeNode listHead;
	private ListBinTreeNode oldListHead;
	private ListBinTreeNode dummyNode;

	HuffmanLinkedList(){
		dummyNode = new ListBinTreeNode();
		listHead = new ListBinTreeNode();
		dummyNode = listHead;
		oldListHead = listHead;
	}

	public ListBinTreeNode listInsert(ListBinTreeNode newNode){
		//insert the node using insertion sort, first to find the spot where to insert
		ListBinTreeNode temp = findSpot(newNode.getProbability());
		if (temp == null){
			temp = dummyNode;
			while (temp.getNext() != null){
				temp = temp.getNext();
			}
			temp = newNode;
		}
		else{
			newNode.setNext(temp.getNext());
			temp.setNext(newNode);
		}
		return newNode.getNext();
	}

	public ListBinTreeNode findSpot(int data){
		ListBinTreeNode spot = dummyNode;
		while (spot.getNext() != null){
			if (spot.getNext().getProbability() < data){
				spot = spot.getNext();
			}
			else {
				return spot;
			}
		}
		return spot;
	}

	public boolean isEmpty(ListBinTreeNode node){
		return node.getNext() == null;
	}

	public void printList(PrintWriter pw3){
		ListBinTreeNode temp = dummyNode;
		pw3.print("ListHead --> (dummy, 0, " + temp.getNext().getCharString() + ")");
		temp = temp.getNext();
		while (temp != null){
			if (temp.getNext() == null){
				pw3.println(" --> (" + temp.getCharString() + ", " + temp.getProbability() + ", NULL) --> NULL");
				break;
			}
			pw3.print(" --> (" + temp.getCharString() + ", " + temp.getProbability() + ", " + temp.getNext().getCharString() + ")");
			temp = temp.getNext();
		}
		pw3.println();
	}
	
	public ListBinTreeNode getListHead(){
		return listHead;
	}
	
	public void setListHead(ListBinTreeNode node){
		this.listHead = node;
	}
	
	public ListBinTreeNode getOldListHead(){
		return oldListHead;
	}
	
	public void setOldListHead(ListBinTreeNode node){
		this.oldListHead = node;
	}
	
	public ListBinTreeNode getDummyNode(){
		return dummyNode;
	}
}
