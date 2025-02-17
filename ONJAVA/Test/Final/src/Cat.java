package src;

import src.Animal;

public class Cat extends Animal {
	private final int size = 1;

	public Cat() {
		super();
		this.size = 0;
	}

	public Cat(String name, int age, int size) {
		super(name, age);
		this.size = size;
	}

	public int getSize() {
		return this.size;
	}

	@Override
	public void print() {
		System.out.printf("I'm a cat%n");
		System.out.printf("My name is %s\tMy age is %d\tsize %d%n",this.getName(),this.getAge(),this.getSize());
	}
}
