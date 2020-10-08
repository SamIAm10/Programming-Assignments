
public class Checksum {
	public static void main(String[] args) {
		String d = args[0];
		int checksum = 0;
		for (int i = 0; i < d.length(); i++) {
			if (i % 2 == 0) {
				int digit = Character.getNumericValue(d.charAt(i));
				checksum += digit;
			}
			else {
				int digit = Character.getNumericValue(d.charAt(i));
				String dig = Integer.toString(2*digit);
				if (dig.length() == 2) {
					int y = Character.getNumericValue(dig.charAt(0)) 
							+ Character.getNumericValue(dig.charAt(1));
					checksum += y;
				}
				else
					checksum += Character.getNumericValue(dig.charAt(0));
			}
		}
		System.out.println("Account number and checksum: " + d + Integer.toString(checksum % 10));
		if (checksum % 10 != 0)
			System.out.println("This account number is invalid");
		else
			System.out.println("This account number is valid");
	}
}
