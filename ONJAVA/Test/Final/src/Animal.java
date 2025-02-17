package src;

public class Animal {
	private String name;
	private int age;

	public Animal() {
		;
	}

	public Animal(String name, int age) {
		this.setName(name);
		this.setAge(age);
	}

	//set
	public void setName(String name) {
		this.name = name;
	}
	public void setAge(int age) {
		this.age = age;
	}

	//get
	public String getName() {
		return this.name;
	}
	public int getAge() {
		return this.age;
	}

	public void print() {
		System.out.printf("My mane is %s:My age is %d%n",this.getName(),this.getAge());
	}
}
