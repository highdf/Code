package src.family;

import src.FamilyAccount;;

public class ChildAccount extends FamilyAccount{
	public ChildAccount() {
	;
	}	
	public ChildAccount(String familyName, double totalBalance, String[] members, String password) {
		this.setFamilyName(familyName);
		this.setTotalBalance(totalBalance);
		// this.setMembers(members);
	}

}
