import java.util.regex.Pattern;

public class StringDNA {
	public static void main(String[] args) {
		System.out.println("Input DNA string: " + args[0]);
		String str = args[0];
		System.out.println("Valid DNA?: " + isValidDNA(str));
		if (isValidDNA(str)) {
			System.out.println("Watson-Crick complement: " + complementWC(str));
			System.out.println("Watson-Crick complemented palindrome?: " + palindromeWC(str));
		}
		else
			System.out.println("Invalid DNA string");
	}
	
	public static boolean isValidDNA(String s) {
		return (Pattern.matches("[ACTG]+", s));
	}
	
	public static String complementWC(String s) {
		StringBuilder WC = new StringBuilder(s);
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == 'A')
				WC.setCharAt(i, 'T');
			else if (s.charAt(i) == 'C')
				WC.setCharAt(i, 'G');
			else if (s.charAt(i) == 'T')
				WC.setCharAt(i, 'A');
			else
				WC.setCharAt(i, 'C');
			}
		return WC.toString();
	}
	
	public static boolean palindromeWC(String s) {
		StringBuilder WCP = new StringBuilder(complementWC(s));
		return s.equals(WCP.reverse().toString());
	}
}