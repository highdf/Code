package com.example.CustomQueue;

import java.util.Iterator;

import com.example.CustomList.Node;

public class CustomQueue<T> implements Iterable<T> {
	private Node<T> head;
	private Node<T> tail;

	public CustomQueue() {
		this.setHead(null);
		this.setTail(null);
	}

	public void setTail(Node<T> tail) {
	    this.tail = tail;
	}
	public void setHead(Node<T> head) {
	    this.head = head;
	}
	public Node<T> getTail() {
	    return tail;
	}
	public Node<T> getHead() {
	    return head;
	}

	public boolean isEmpty() {
		return (this.getHead() == null);
	}
	public boolean push (T data) {
		Node<T> new_node = new Node<>(data, null);

		if (this.isEmpty() == true) {
			this.setHead(new_node);
		} else {
			this.getTail().setNext(new_node);
		}
		this.setTail(new_node);

		return true;
	}
	public T pop () {
		T ret = null;

		if (this.isEmpty() == false) {
			ret = this.getHead().getData();
			this.setHead(this.getHead().getNext());
		} else {
			System.out.printf("In the CustomQueue.pop():%n");
			System.out.printf("Error: The queue is empty%n");
		}

		return ret;
	}
	public Iterator<T> iterator () {
		return new CustomIterator();
	}
	public String toString () {
		StringBuilder ret = new StringBuilder();
		Iterator<T> iterator = this.iterator();

		ret.append("[");
		while (iterator().hasNext()) {
			T data = iterator.next();
			ret.append(data.toString());

			if (iterator.hasNext() == true) {
				ret.append(", ");
			}
		}

		return ret.toString();
	}

	private class CustomIterator implements Iterator<T> {
		private Node<T> current_node;

		public CustomIterator() {
			this.setCurrent_node(CustomQueue.this.getHead());
		}
		public void setCurrent_node(Node<T> current_node) {
		    this.current_node = current_node;
		}
		public Node<T> getCurrent_node() {
		    return current_node;
		}
		public boolean hasNext () {
			return this.getCurrent_node() != null;
		}
		public T next () {
			T ret = null;

			if (this.hasNext() == true) {
				ret = this.getCurrent_node().getData();
				this.setCurrent_node(this.getCurrent_node().getNext());
			}

			return ret;
		}
	}
}
