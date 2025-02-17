import java.util.Scanner;

import src.FamilyAccount;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);

		Main.prompt("Please enter familyName: ");
		String familyName = scan.next();

		Main.prompt("Please enter total balance: ");
		double totalBalance = scan.nextDouble();

		Main.prompt("Please enter family number: ");
		int number = scan.nextInt();
		Main.prompt("Please enter members%n");
		String[] members = new String[number];
		for(int i = 0;i < members.length;i ++) {
			System.out.printf("[%d]: ",i);
			String name = scan.next();
			members[i] = name;
		}
		Main.prompt("Please enter password: ");
		String password = scan.next();

		FamilyAccount familyAccount = new FamilyAccount(familyName, totalBalance, members, password);

		Main.prompt("Please enter income: ");
		double amount = scan.nextDouble();
		familyAccount.addIncome(amount);
		Main.prompt("Please enter expense: ");
		amount = scan.nextDouble();
		familyAccount.deductExpense(amount);

		familyAccount.print();
		scan.close();
	}

	static void prompt(String message) {
		System.out.printf(message);
	}
}
