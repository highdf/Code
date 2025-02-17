package src;

public abstract class Shape{

	//abstract
	protected abstract double getArea();
	protected abstract double getPerimater();

	public void print() {
		System.out.printf("Area = %f%n",this.getArea());
		System.out.printf("Perimater = %f%n",this.getPerimater());
	}
}
