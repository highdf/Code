import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);

		System.out.printf("Please enter number of sum%n");
		int num = 0;
		if ( scan.hasNextInt() == true ) {
			num = scan.nextInt();
		} else {
			System.out.printf("The is not number");
		}

		System.out.printf("num = %d%n", num);

		scan.close();
	}
}
