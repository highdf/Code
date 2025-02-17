package src;

public class FamilyAccount {
	private String familyName;
	private double totalBalance;
	private String[] members;
	private  String password;

	public FamilyAccount() {
		;
	}
	public FamilyAccount(String familyName, double totalBalance, String[] members, String password) {
		this.setFamilyName(familyName);
		this.setTotalBalance(totalBalance);
		this.setMembers(members);
		this.setPassword(password);
	}

	public void setFamilyName(String familyName) {
		this.familyName = familyName;
	}
	protected void setTotalBalance(double totalBalance) {
		this.totalBalance = totalBalance;
	}
	void setMembers(String[] members) {
		this.members = members;
	}
	private void setPassword(String password) {
		this.password = password;
	}

	public String getFamilyName() {
		return this.familyName;
	}
	protected double getTotalBalance() {
		return this.totalBalance;
	}
	String[] getMembers() {
		return this.members;
	}
	private String getPassword() {
		return this.password;
	}

	public void addIncome(double amount) {
		double current_amount = this.getTotalBalance();
		this.setTotalBalance(current_amount + amount);
	}

	public void deductExpense(double amount) {
		double current_amount = this.getTotalBalance();
		this.setTotalBalance(current_amount - amount);
	}
	public void print() {
		System.out.printf("FamilyName: %s%n",this.getFamilyName());
		System.out.printf("TotalBalance: %s%n",this.getTotalBalance());
		System.out.printf("Family members: ");
		members = this.getMembers();
		for(int i = 0;i < members.length;i ++) {
			System.out.printf("%s ",members[i]);
		}
		System.out.printf("%n");
	}
}
