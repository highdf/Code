import java.util.Scanner;
import src.Animal;
import src.Cat;

public class Main {

	public static void main(String[] arge) {
		Scanner scan = new Scanner(System.in);

		System.out.printf("Please enter animal's name%n");
		String name = scan.next();
		System.out.printf("Please enter animal's age%n");
		int age = scan.nextInt();

		Animal animal  = new Animal(name, age);
		Cat cat = new Cat(name, age, 10);

		animal.print();
		cat.print();

		scan.close();
	}
}
