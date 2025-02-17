package src;

public class Rectangle extends Shape {
	private double lenght;
	private double width;

	public Rectangle() {
		;
	}
	public Rectangle(double lenght, double width) {
		this.setLength(lenght);
		this.setWidth(width);
	}

	//set
	public void setLength(double lenght) {
		this.lenght = lenght;
	}
	public void setWidth(double width) {
		this.width = width;
	}

	//get
	public double getLenght() {
		return this.lenght;
	}
	public double getWidth() {
		return this.width;
	}

	public double getArea() {
		return this.getLenght() * this.getWidth();
	}
	public double getPerimater() {
		return (this.getLenght() + this.getWidth()) * 2;
	}
}
