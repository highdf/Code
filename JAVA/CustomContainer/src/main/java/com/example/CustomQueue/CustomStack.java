package com.example.CustomQueue;

import java.util.Iterator;

import com.example.CustomList.Node;

public class CustomStack<T> implements Iterable<T> {
	private Node<T>  top;

	public CustomStack() {
		this.setTop(null);
	}

	public void setTop(Node<T> top) {
	    this.top = top;
	}
	public Node<T> getTop() {
	    return top;
	}
	public boolean push (T data) {
		Node<T> new_node = new Node<T>(data, null);
		if (this.empty() == false) {
			new_node.setNext(this.getTop());
		}
		this.setTop(new_node);

		return true;
	}
	public T pop () {
		T ret = null;

		if (this.empty() == false) {
			ret = this.getTop().getData();
			this.setTop(this.getTop().getNext());
		} else {
			System.out.printf("In the customStack.pop():%n");
			System.out.printf("Error: The stack is empty%n");
		}

		return ret;
	}
	public String toString() {
		StringBuilder ret = new StringBuilder();
		Iterator<T> iterator = this.iterator();

		ret.append("[");
		while (iterator.hasNext() == true) {
			T data = iterator.next();
			ret.append(data.toString());

			if (iterator.hasNext() == true) {
				ret.append(", ");
			}

		}
		ret.append("]");

		return ret.toString();
	}
	public Iterator<T> iterator() {
		return new CustomIterator();
	}
	private boolean empty () {
		return (this.getTop() == null);
	}
	private class CustomIterator implements Iterator<T> {
		private Node<T> current_node;

		public CustomIterator() {
			this.setCurrent_node(CustomStack.this.getTop());
		}
		public void setCurrent_node(Node<T> current_node) {
		    this.current_node = current_node;
		}
		public Node<T> getCurrent_node() {
		    return current_node;
		}
		public boolean hasNext() {
			return (this.getCurrent_node() != null);
		}
		public T next() {
			T ret = null;

			if (this.hasNext() == true) {
				ret = this.getCurrent_node().getData();
				this.setCurrent_node(this.getCurrent_node().getNext());
			}

			return ret;
		}

	}
}
