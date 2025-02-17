package src;

public class Circle extends Shape {
	private double radius;

	public Circle() {
		;
	}
	public Circle(double radius) {
		this.setRadius(radius);
	}

	//set
	public void setRadius(double radius) {
		this.radius = radius;
	}

	//get
	public double getRadius() {
		return this.radius;
	}

	public double getArea() {
		return this.getRadius() * 2 * Math.PI;
	}
	public double getPerimater() {
		return 2 * Math.PI * this.getRadius();
	}
}
